#!/usr/sbin/dtrace -qs

/*
 * modprobe fbt
 *
 * usage: ./kvm_set_pending_timer.d <qemu-pid> <vcpu-idx>
 *
 * # ./kvm_set_pending_timer.d 7432 0
 * kvm_set_pending_timer() (created=4) pid=7432, vcpu=0, time=260156910250
 * # ./kvm_set_pending_timer.d 7432 1
 * kvm_set_pending_timer() (created=4) pid=7432, vcpu=1, time=260159423241
 * # ./kvm_set_pending_timer.d 7432 2
 * kvm_set_pending_timer() (created=4) pid=7432, vcpu=2, time=260162087264
 * # ./kvm_set_pending_timer.d 7432 3
 * kvm_set_pending_timer() (created=4) pid=7432, vcpu=3, time=260164591265
 *
 * current timestamp in dmesg is 260164.591265
 */

dtrace:::BEGIN
{
}

fbt:kvm:kvm_set_pending_timer:entry
/
((struct kvm_vcpu *)arg0)->kvm->userspace_pid == $1 && ((struct kvm_vcpu *)arg0)->vcpu_id == $2
/
{
    vcpu = (struct kvm_vcpu *) arg0;
    printf("kvm_set_pending_timer() (created=%d) pid=%d, vcpu=%d, time=%lu",
           vcpu->kvm->created_vcpus,
           vcpu->kvm->userspace_pid, vcpu->vcpu_id, timestamp/1000);
    exit(0);
}

dtrace:::END
{
}
