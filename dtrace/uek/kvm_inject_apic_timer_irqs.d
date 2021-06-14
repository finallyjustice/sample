#!/usr/sbin/dtrace -qs

/*
 * modprobe fbt
 *
 * usage: ./kvm_inject_apic_timer_irqs.d <qemu-pid> <vcpu-idx>
 *
 * # ./kvm_inject_apic_timer_irqs.d 7432 0
 * kvm_inject_apic_timer_irqs() (created=4) pid=7432, vcpu=0, time=258298970295
 * # ./kvm_inject_apic_timer_irqs.d 7432 1
 * kvm_inject_apic_timer_irqs() (created=4) pid=7432, vcpu=1, time=258302619331
 * # ./kvm_inject_apic_timer_irqs.d 7432 2
 * kvm_inject_apic_timer_irqs() (created=4) pid=7432, vcpu=2, time=258304974291
 * # ./kvm_inject_apic_timer_irqs.d 7432 3
 * kvm_inject_apic_timer_irqs() (created=4) pid=7432, vcpu=3, time=258307264290
 *
 * current timestamp in dmesg is 258307.264290
 */

dtrace:::BEGIN
{
}

fbt:kvm:kvm_inject_apic_timer_irqs:entry
/
((struct kvm_vcpu *)arg0)->kvm->userspace_pid == $1 && ((struct kvm_vcpu *)arg0)->vcpu_id == $2
/
{
    vcpu = (struct kvm_vcpu *) arg0;
    printf("kvm_inject_apic_timer_irqs() (created=%d) pid=%d, vcpu=%d, time=%lu",
           vcpu->kvm->created_vcpus,
           vcpu->kvm->userspace_pid, vcpu->vcpu_id, timestamp/1000);
    exit(0);
}

dtrace:::END
{
}
