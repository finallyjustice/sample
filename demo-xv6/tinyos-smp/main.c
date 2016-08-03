#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"

static void startothers(void);
extern char end[]; // first address after kernel loaded from ELF file

int main(void)
{
	int a = 12;
	cprintf("Hello World! %d\n", 12);
	consoleinit();
	kinit1(end, P2V(4*1024*1024)); // phys page allocator
	kvmalloc();
	if (acpiinit()) {
		cprintf("acpi is not working\n");
	}
	lapicinit();
	startothers();
	while(1);
	return 0;
}

void
mpenter(void)
{
	cprintf("cpux: starting\n");
	switchkvm();
	lapicinit();
	while(1);
}

void entry32mp(void);

// Start the non-boot (AP) processors.
static void
startothers(void)
{
	extern uchar _binary_entryother_start[], _binary_entryother_size[];
	uchar *code;
	struct cpu *c;
	char *stack;

	// Write entry code to unused memory at 0x7000.
	// The linker has placed the image of entryother.S in
	// _binary_entryother_start.
	code = p2v(0x7000);
	memmove(code, _binary_entryother_start, (uintp)_binary_entryother_size);

	for(c = cpus; c < cpus+ncpu; c++){
		if(c == cpus+cpunum())  // We've started already.
			continue;

		cprintf("start new cpu...\n");

		// Tell entryother.S what stack to use, where to enter, and what 
		// pgdir to use. We cannot use kpgdir yet, because the AP processor
		// is running in low  memory, so we use entrypgdir for the APs too.
		stack = kalloc();
		*(uint32*)(code-4) = 0x8000; // just enough stack to get us to entry64mp
		*(uint32*)(code-8) = v2p(entry32mp);
		*(uint64*)(code-16) = (uint64) (stack + KSTACKSIZE);

		lapicstartap(c->apicid, v2p(code));

		// wait for cpu to finish mpmain()
		//while(c->started == 0)
		//	;
	}
}
