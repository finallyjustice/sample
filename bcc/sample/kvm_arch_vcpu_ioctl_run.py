#!/usr/bin/python

from bcc import BPF

prog = """
#include <linux/kvm_host.h>

int bpf_kvm_arch_vcpu_ioctl_run(struct pt_regs *ctx, struct kvm_vcpu *vcpu, struct kvm_run *kvm_run)
{
    if (vcpu->vcpu_id == 4) {
        bpf_trace_printk("bpf_kvm_arch_vcpu_ioctl_run() %d\\n", vcpu->vcpu_id);
    }

    return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="kvm_arch_vcpu_ioctl_run", fn_name="bpf_kvm_arch_vcpu_ioctl_run")

print("Tracing kvm_arch_vcpu_ioctl_run() ... Ctrl-C to end.")

b.trace_print()
