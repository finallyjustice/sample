#!/usr/sbin/dtrace -qs

/*
 * modprobe fbt
 *
 * usage: ./vmx_vcpu_run.d <qemu-pid> <vcpu-idx>
 *
 * # ./vmx_vcpu_run.d 7432 0
 * __vmx_vcpu_run() (created=4) pid=7432, vcpu=0, time=257260591463
 * # ./vmx_vcpu_run.d 7432 1
 * __vmx_vcpu_run() (created=4) pid=7432, vcpu=1, time=257263214839
 * # ./vmx_vcpu_run.d 7432 2
 * __vmx_vcpu_run() (created=4) pid=7432, vcpu=2, time=257265520367
 * # ./vmx_vcpu_run.d 7432 3
 * __vmx_vcpu_run() (created=4) pid=7432, vcpu=3, time=257267917343
 *
 *
 * current timestamp in dmesg is 257267.917343
 */

dtrace:::BEGIN
{
}

fbt:kvm_intel:__vmx_vcpu_run:entry
/
((struct kvm_vcpu *)arg0)->kvm->userspace_pid == $1 && ((struct kvm_vcpu *)arg0)->vcpu_id == $2
/
{
    vcpu = (struct kvm_vcpu *) arg0;
    printf("__vmx_vcpu_run() (created=%d) pid=%d, vcpu=%d, time=%lu",
           vcpu->kvm->created_vcpus,
           vcpu->kvm->userspace_pid, vcpu->vcpu_id, timestamp/1000);
    exit(0);
}

dtrace:::END
{
}
