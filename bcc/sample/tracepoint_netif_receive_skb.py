#!/usr/bin/python

# sudo ./tracepoint_netif_receive_skb.py
# Tracing tracepoint netif_receive_skb ... Ctrl-C to end.
#           <idle>-0     [003] .Ns. 33931.947308: 0x00000001: skb=0xffff905735818400 len=52 dev=ens3
#           <idle>-0     [003] ..s. 33932.032507: 0x00000001: skb=0xffff905735818400 len=52 dev=ens3
#           <idle>-0     [003] ..s. 33932.115122: 0x00000001: skb=0xffff905735818400 len=52 dev=ens3
#           <idle>-0     [003] ..s. 33932.208352: 0x00000001: skb=0xffff905735818400 len=52 dev=ens3

from bcc import BPF

prog = """
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <trace/events/net.h>

struct netif_receive_skb_args {
	unsigned short common_type;
	unsigned char common_flags;
	unsigned char common_preempt_count;
	int common_pid;
	void *skbaddr;
	unsigned int len;
	char *name;
};

int bpf_netif_receive_skb(struct netif_receive_skb_args *args) {
	char name[IFNAMSIZ];
	
	bpf_probe_read(&name, IFNAMSIZ, &args->name);

	bpf_trace_printk("skb=0x%llx len=%u dev=%s\\n",
			 args->skbaddr, args->len, name);

	return 0;
};
"""

b = BPF(text=prog)
b.attach_tracepoint(tp="net:netif_receive_skb", fn_name="bpf_netif_receive_skb")

print("Tracing tracepoint netif_receive_skb ... Ctrl-C to end.")
b.trace_print()
