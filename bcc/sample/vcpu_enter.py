#!/usr/bin/python

from bcc import BPF

prog = """
#include <linux/kvm_host.h>

int bpf_vcpu_enter_guest(struct pt_regs *ctx, struct kvm_vcpu *vcpu)
{
    if (vcpu->vcpu_id == 4) {
        bpf_trace_printk("vcpu_enter_guest() %d\\n", vcpu->vcpu_id);
    }

    return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="vcpu_enter_guest", fn_name="bpf_vcpu_enter_guest")

print("Tracing vcpu_enter_guest() ... Ctrl-C to end.")

b.trace_print()
