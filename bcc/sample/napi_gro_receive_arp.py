#!/usr/bin/python

# About ARP type: 1 is REQUEST while 2 is REPLY
#
# sudo ./napi_gro_receive_arp.py 
# Tracing napi_gro_receive() ... Ctrl-C to end.
# 10/05/2021 21:28:12 (2) src:10.0.48.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.xx.xx.xx.xx.21)
# 10/05/2021 21:28:14 (2) src:10.0.48.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.xx.xx.xx.xx.21)
# 10/05/2021 21:28:15 (2) src:10.0.48.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.xx.xx.xx.xx.21)
# 10/05/2021 21:28:16 (2) src:10.0.48.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.xx.xx.xx.xx.21)
# 10/05/2021 21:28:17 (2) src:10.0.48.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.xx.xx.xx.xx.21)
# 10/05/2021 21:28:18 (2) src:10.0.48.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.xx.xx.xx.xx.21)
# 10/05/2021 21:28:19 (2) src:10.0.48.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.xx.xx.xx.xx.21)
# 10/05/2021 21:28:19 (2) src:169.0.0.254(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.xx.xx.xx.xx.21)
# 10/05/2021 21:28:20 (2) src:10.0.248.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.xx.xx.xx.xx.21)
# 10/05/2021 21:28:35 (2) src:169.0.0.254(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(xx.00.xx.xx.xx.21)
# 10/05/2021 21:28:44 (1) src:10.0.48.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(00.00.00.00.00.00)
# 10/05/2021 21:29:14 (1) src:10.0.48.1(xx.xx.xx.xx.xx.a7)->tgt:10.0.48.210(00.00.00.00.00.00)

from bcc import BPF
from datetime import datetime

prog = """
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/virtio.h>
#include <linux/if_arp.h>

struct data_t {
	unsigned char sip[4];
	unsigned char tip[4];
	unsigned char smac[6];
	unsigned char tmac[6];
        unsigned char type;
};

BPF_PERF_OUTPUT(events);

int bpf_napi_gro_receive(struct pt_regs *ctx, struct napi_struct *napi,
			 struct sk_buff *skb)
{
	void *vq_addr_ptr = (void *)napi - 0x8;
	u64 vq_addr;
	struct virtqueue vq;
	void *mac_header_ptr = skb->head + skb->mac_header;
	struct ethhdr *m_eh;
	char mac_base[64];
	struct arphdr *arp;
	unsigned char *arp_ptr;
	struct data_t data = {};

	bpf_probe_read(&vq_addr, sizeof(u64), vq_addr_ptr);
	bpf_probe_read(&vq, sizeof(vq), (void *)vq_addr);
	bpf_probe_read(mac_base, 64, mac_header_ptr);

	m_eh = (struct ethhdr *)mac_base;

	if (m_eh->h_proto == htons(ETH_P_ARP)) {
		arp = (struct arphdr *)(mac_base + ETH_HLEN);

		if (arp->ar_pro == htons(ETH_P_IP) &&
		    (arp->ar_op == htons(ARPOP_REQUEST) || arp->ar_op == htons(ARPOP_REPLY))) {
				arp_ptr = (unsigned char *)(arp + 1);

				memcpy(&data.smac, arp_ptr,      6);
				memcpy(&data.sip,  arp_ptr + 6,  4);
				memcpy(&data.tmac, arp_ptr + 10, 6);
				memcpy(&data.tip,  arp_ptr + 16, 4);

				if (arp->ar_op == htons(ARPOP_REQUEST))
					data.type = 1;
				else if (arp->ar_op == htons(ARPOP_REPLY))
					data.type = 2;
				else
					data.type = 3;
				
				events.perf_submit(ctx, &data, sizeof(data));
		}
	}

	return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="napi_gro_receive", fn_name="bpf_napi_gro_receive")

print("Tracing napi_gro_receive() ... Ctrl-C to end.")

def print_event(cpu, data, size):
        event = b["events"].event(data)
        now = datetime.now()
        dt = now.strftime("%d/%m/%Y %H:%M:%S")

        print("%s (%u) src:%u.%u.%u.%u(%02x.%02x.%02x.%02x.%02x.%02x)->tgt:%u.%u.%u.%u(%02x.%02x.%02x.%02x.%02x.%02x)" % (dt,
              event.type,
              event.sip[0], event.sip[1],event.sip[2], event.sip[3],
              event.smac[0], event.smac[1], event.smac[2], event.smac[3], event.smac[4], event.smac[5],
              event.tip[0], event.tip[1], event.tip[2], event.tip[3],
              event.tmac[0], event.tmac[1], event.tmac[2], event.tmac[3], event.tmac[4], event.tmac[5]))

b["events"].open_perf_buffer(print_event)
while 1:
        b.perf_buffer_poll()
