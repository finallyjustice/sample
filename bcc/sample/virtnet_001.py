#!/usr/bin/python

from bcc import BPF

print("Tracing virtnet_poll()... Ctrl-C to end.")

BPF(text='int kprobe__virtnet_poll(void *ctx) { bpf_trace_printk("virtnet_poll()\\n"); return 0; }').trace_print()
