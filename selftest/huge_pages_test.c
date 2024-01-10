/*
 * based on linux-6.6
 */

#include <pthread.h>

#include "kvm_util.h"
#include "processor.h"

#define HPAGE_SLOT              2
#define HPAGE_GPA               (4UL << 30) /* 4G prevents collision w/ slot 0 */
#define HPAGE_GVA               HPAGE_GPA /* GVA is arbitrary, so use GPA. */
#define PAGES_PER_2MB_HUGE_PAGE 512
#define NR_PAGES_2M             5120UL
#define NR_PAGES_4K             (NR_PAGES_2M * PAGES_PER_2MB_HUGE_PAGE)

#define RETURN_OPCODE 0xC3

static void guest_do_CALL(uint64_t target)
{
	((void (*)(void)) target)();
}

void guest_code(void)
{
	uint64_t base;
	uint64_t i;

again:
	for (i = 0; i < NR_PAGES_4K; i++) {
		base = HPAGE_GVA + i * PAGE_SIZE;
		READ_ONCE(*(uint64_t *)base);
	}

	for (i = 0; i < 1000; i++)
		asm volatile("nop");

	for (i = 0; i < NR_PAGES_2M; i++) {
		base = HPAGE_GVA + i * (PAGE_SIZE * 512);
		guest_do_CALL(base);
	}

	goto again;
}

static void run_vcpu(struct kvm_vcpu *vcpu)
{
	struct ucall uc;

	vcpu_run(vcpu);

	switch (get_ucall(vcpu, &uc)) {
	case UCALL_SYNC:
	case UCALL_DONE:
		break;
	case UCALL_ABORT:
		REPORT_GUEST_ASSERT(uc);
	default:
		TEST_ASSERT(false, "Unexpected exit: %s",
			    exit_reason_str(vcpu->run->exit_reason));
	}
}

static void *vcpu_worker(void *data)
{
	struct kvm_vcpu *vcpu = data;

	pr_info("Create thread for vcpu=%u\n", vcpu->id);
	run_vcpu(vcpu);

	return NULL;
}

int main(int argc, char **argv)
{
	struct kvm_vcpu **vcpus;
	struct kvm_vm *vm;
	uint64_t nr_bytes;
	int nr_vcpus = 20;
	pthread_t *tids;
	void *hva;
	int i;

	vm = __vm_create(VM_MODE_DEFAULT, nr_vcpus, 2621440);

	vcpus = malloc(sizeof(struct kvm_vcpu *) * nr_vcpus);
	for (i = 0; i < nr_vcpus; i++)
		vcpus[i] = vm_vcpu_add(vm, i, guest_code);

	vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS_HUGETLB,
				    HPAGE_GPA, HPAGE_SLOT,
				    NR_PAGES_4K, 0);

	nr_bytes = NR_PAGES_4K * vm->page_size;

	virt_map_level(vm, HPAGE_GVA, HPAGE_GPA, nr_bytes, PG_LEVEL_4K);

	hva = addr_gpa2hva(vm, HPAGE_GPA);
	memset(hva, RETURN_OPCODE, nr_bytes);

	tids = malloc(sizeof(pthread_t) * nr_vcpus);
	for (i = 0; i < nr_vcpus; i++)
		pthread_create(&tids[i], NULL, vcpu_worker, vcpus[i]);

	for (i = 0; i < nr_vcpus; i++)
		pthread_join(tids[i], NULL);

	return 0;
}

