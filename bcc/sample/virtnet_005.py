#!/usr/bin/python

# sudo ./bpf.py 
# Tracing napi_gro_receive() ... Ctrl-C to end.
#           <idle>-0     [003] ..s. 606138.404424: 0: napi_gro_receive(): device : ens3
#           <idle>-0     [003] ..s. 606138.404437: 0: napi_gro_receive(): queue  : input.0
#           <idle>-0     [003] ..s. 606138.408840: 0: napi_gro_receive(): device : ens3
#           <idle>-0     [003] ..s. 606138.408852: 0: napi_gro_receive(): queue  : input.0
#           <idle>-0     [003] ..s. 606138.486829: 0: napi_gro_receive(): device : ens3
#           <idle>-0     [003] ..s. 606138.486842: 0: napi_gro_receive(): queue  : input.0

from bcc import BPF

prog = """
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/virtio.h>

int bpf_napi_gro_receive(struct pt_regs *ctx, struct napi_struct *napi,
			 struct sk_buff *skb)
{
	void *vq_addr_ptr = (void *) napi - 0x8;
	u64 vq_addr;
	struct virtqueue vq;

	bpf_probe_read(&vq_addr, sizeof(u64), vq_addr_ptr);
	bpf_probe_read(&vq, sizeof(vq), (void *)vq_addr);

	bpf_trace_printk("napi_gro_receive(): device : %s\\n", skb->dev->name);
	bpf_trace_printk("napi_gro_receive(): queue  : %s\\n", vq.name);

	return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="napi_gro_receive", fn_name="bpf_napi_gro_receive")

print("Tracing napi_gro_receive() ... Ctrl-C to end.")

b.trace_print()
