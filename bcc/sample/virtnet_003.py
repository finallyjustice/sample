#!/usr/bin/python

from bcc import BPF

prog = """
#include <linux/netdevice.h>
#include <linux/skbuff.h>

int bpf_napi_gro_receive(struct pt_regs *ctx, struct napi_struct *napi,
			 struct sk_buff *skb)
{
	bpf_trace_printk("napi_gro_receive(): %s\\n", skb->dev->name);

	return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="napi_gro_receive", fn_name="bpf_napi_gro_receive")

print("Tracing napi_gro_receive() ... Ctrl-C to end.")

b.trace_print()
