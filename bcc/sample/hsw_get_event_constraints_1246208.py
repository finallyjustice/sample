#!/usr/bin/python

from bcc import BPF

prog = """
#if defined(CONFIG_FUNCTION_TRACER)
#define CC_USING_FENTRY
#endif
#include <linux/perf_event.h>

int bpf_hsw_get_event_constraints(struct pt_regs *ctx, void *cpuc,
                                  int idx, struct perf_event *event)
{

    if (event->hw.config == 1246208)
        bpf_trace_printk("hsw_get_event_constraints() %llu\\n", event->hw.config);

    return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="hsw_get_event_constraints", fn_name="bpf_hsw_get_event_constraints")

print("Tracing hsw_get_event_constraints() ... Ctrl-C to end.")

b.trace_print()
