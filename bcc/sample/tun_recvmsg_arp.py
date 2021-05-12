#!/usr/bin/python

# About ARP type: 1 is REQUEST while 2 is REPLY
#
# sudo ./tun_recvmsg_arp.py 
# Tracing tun_recvmsg() ... Ctrl-C to end.
# 11/05/2021 23:08:07 (vnet0 1) src:10.x.x.2(xx.xx.xx.xx.xx.7f)->tgt:10.x.x.119(00.00.00.00.00.00)
# 11/05/2021 23:08:07 (vnet0 1) src:10.x.x.3(xx.xx.xx.xx.xx.ff)->tgt:10.x.x.119(00.00.00.00.00.00)
# 11/05/2021 23:08:07 (vnet0 1) src:10.x.x.70(xx.xx.xx.xx.xx.b0)->tgt:10.x.x.58(ff.ff.ff.ff.ff.ff)
# 11/05/2021 23:08:07 (vnet0 1) src:10.x.x.70(xx.xx.xx.xx.xx.b0)->tgt:10.x.x.1(ff.ff.ff.ff.ff.ff)

from bcc import BPF
from datetime import datetime

prog = """
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/if_arp.h>
#include <linux/socket.h>

struct data_t {
	unsigned char sip[4];
	unsigned char tip[4];
	unsigned char smac[6];
	unsigned char tmac[6];
        unsigned char type;
	char name[IFNAMSIZ];
};

BPF_PERF_OUTPUT(events);

int bpf_tun_recvmsg(struct pt_regs *ctx, struct socket *sock,
		    struct msghdr *m, size_t total_len, int flags)
{
	struct sk_buff *skb = m->msg_control;
	void *mac_header_ptr = skb->head + skb->mac_header;
	struct ethhdr *m_eh;
	char mac_base[64];
	struct arphdr *arp;
	unsigned char *arp_ptr;
	struct data_t data = {};
	struct net_device *dev;

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

				bpf_probe_read(&dev, sizeof(skb->dev), ((char *)skb + offsetof(struct sk_buff, dev)));
				bpf_probe_read(&data.name, IFNAMSIZ, dev->name);
				
				events.perf_submit(ctx, &data, sizeof(data));
		}
	}

	return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="tun_recvmsg", fn_name="bpf_tun_recvmsg")

print("Tracing tun_recvmsg() ... Ctrl-C to end.")

def print_event(cpu, data, size):
        event = b["events"].event(data)
        now = datetime.now()
        dt = now.strftime("%d/%m/%Y %H:%M:%S")

        print("%s (%s %u) src:%u.%u.%u.%u(%02x.%02x.%02x.%02x.%02x.%02x)->tgt:%u.%u.%u.%u(%02x.%02x.%02x.%02x.%02x.%02x)" % (dt,
              event.name, event.type,
              event.sip[0], event.sip[1],event.sip[2], event.sip[3],
              event.smac[0], event.smac[1], event.smac[2], event.smac[3], event.smac[4], event.smac[5],
              event.tip[0], event.tip[1], event.tip[2], event.tip[3],
              event.tmac[0], event.tmac[1], event.tmac[2], event.tmac[3], event.tmac[4], event.tmac[5]))

b["events"].open_perf_buffer(print_event)
while 1:
        b.perf_buffer_poll()
