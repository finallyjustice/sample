#!/usr/bin/python

from bcc import BPF

#define BPF program
prog = """
#include <linux/sched.h>

int mmu_shrink_count_ret(struct pt_regs *ctx)
{
	int ret = PT_REGS_RC(ctx);
    bpf_trace_printk("mmu_shrink_count() ret=%d\\n", ret);
	return 0;
}

"""

b = BPF(text=prog)
b.attach_kretprobe(event="mmu_shrink_count", fn_name="mmu_shrink_count_ret")

print("Tracing mmu_shrink_count() ... Ctrl-C to end.")
b.trace_print()
