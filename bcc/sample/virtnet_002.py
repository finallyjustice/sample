#!/usr/bin/python

from bcc import BPF

#define BPF program
prog = """
int bpf_virtnet_poll(void *ctx)
{
	bpf_trace_printk("virtnet_poll()\\n");
	return 0;
}
"""

b = BPF(text=prog)
b.attach_kprobe(event="virtnet_poll", fn_name="bpf_virtnet_poll")

print("Tracing virtnet_poll() ... Ctrl-C to end.")
b.trace_print()
