#!/usr/bin/python

from bcc import BPF

prog = """
#include <linux/kvm_host.h>

#define MSR_IA32_TSC_ADJUST 0x0000003b

int bpf_kvm_set_msr_common(struct pt_regs *ctx, struct kvm_vcpu *vcpu,
                           struct msr_data *msr_info)
{
    if (msr_info->index == MSR_IA32_TSC_ADJUST)
        bpf_trace_printk("kvm_set_msr_common() vcpu=%d, data=%lu, host_initiated=%d\\n",
                          vcpu->vcpu_id, msr_info->data,
                          msr_info->host_initiated);
    return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="kvm_set_msr_common", fn_name="bpf_kvm_set_msr_common")

print("Tracing kvm_set_msr_common() ... Ctrl-C to end.")

b.trace_print()
