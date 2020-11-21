#!/usr/bin/python

# # sudo ./arp.py 
# Tracing napi_gro_receive() ... Ctrl-C to end.
# 21/11/2020 07:15:01 src:10.0.0.1(00.00.xx.xx.xx.a7)->tgt:10.0.0.21(00.00.00.00.00.00)
# 21/11/2020 07:15:16 src:10.0.0.1(00.00.xx.xx.xx.a7)->tgt:10.0.0.21(00.00.00.00.00.00)
# 21/11/2020 07:15:31 src:10.0.0.254(00.00.xx.xx.xx.a7)->tgt:10.0.0.21(xx.xx.xx.xx.xx.81)
# 21/11/2020 07:15:46 src:10.0.0.1(00.00.xx.xx.xx.a7)->tgt:10.0.0.21(00.00.00.00.00.00)
# 21/11/2020 07:16:01 src:10.0.0.1(00.00.xx.xx.xx.a7)->tgt:10.0.0.21(00.00.00.00.00.00)

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

        print("%s src:%u.%u.%u.%u(%02x.%02x.%02x.%02x.%02x.%02x)->tgt:%u.%u.%u.%u(%02x.%02x.%02x.%02x.%02x.%02x)" % (dt,
              event.sip[0], event.sip[1],event.sip[2], event.sip[3],
              event.smac[0], event.smac[1], event.smac[2], event.smac[3], event.smac[4], event.smac[5],
              event.tip[0], event.tip[1], event.tip[2], event.tip[3],
              event.tmac[0], event.tmac[1], event.tmac[2], event.tmac[3], event.tmac[4], event.tmac[5]))

b["events"].open_perf_buffer(print_event)
while 1:
        b.perf_buffer_poll()
