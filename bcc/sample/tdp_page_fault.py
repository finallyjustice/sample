#!/usr/bin/python

from bcc import BPF

prog = """
#include <linux/kvm_types.h>
#include <linux/kvm_host.h>

int bpf_tdp_page_fault(struct pt_regs *ctx, struct kvm_vcpu *vcpu,
                       gva_t gpa, u32 error_code, bool prefault)
{
    if (error_code & PFERR_FETCH_MASK)
        bpf_trace_printk("tdp_page_fault()\\n");
    return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="tdp_page_fault", fn_name="bpf_tdp_page_fault")

print("Tracing tdp_page_fault() ... Ctrl-C to end.")

b.trace_print()
