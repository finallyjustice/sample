#!/usr/bin/python

# # sudo ./tun_net_xmit_icmp.py 
# Tracing tun_net_xmit() ... Ctrl-C to end.
#           <idle>-0     [003] d.s. 48546.956724: 0x00000001: ping echo (vnet0) id=9508, sequence=256
#           <idle>-0     [003] d.s. 48547.953511: 0x00000001: ping echo (vnet0) id=9508, sequence=512
#           <idle>-0     [003] d.s. 48548.950432: 0x00000001: ping echo (vnet0) id=9508, sequence=768
#           <idle>-0     [003] d.s. 48549.979420: 0x00000001: ping echo (vnet0) id=9508, sequence=1024
#           <idle>-0     [003] d.s. 48550.954915: 0x00000001: ping echo (vnet0) id=9508, sequence=1280

from bcc import BPF

prog = """
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/icmp.h>

int bpf_tun_net_xmit(struct pt_regs *ctx, struct sk_buff *skb,
                         struct net_device *dev)
{
    void *mac_header_ptr = skb->head + skb->mac_header;
    int txq = skb->queue_mapping;
    struct ethhdr *m_eh;
    struct iphdr *m_iph;
    char mac_base[64];
    struct icmphdr *icmph_ptr;
    struct icmphdr icmph;

    bpf_probe_read(mac_base, 64, mac_header_ptr);

    m_eh = (struct ethhdr *)mac_base;

    if (m_eh->h_proto == htons(ETH_P_IP)) {
        m_iph = (struct iphdr *)(mac_base + ETH_HLEN);

        if (m_iph->ihl >= 5 && m_iph->version == 4 &&
            m_iph->protocol == IPPROTO_ICMP) {
            icmph_ptr = (struct icmphdr *)(mac_base + ETH_HLEN + m_iph->ihl * 4);
            bpf_probe_read(&icmph, sizeof(icmph), icmph_ptr);

	    if (icmph.type == ICMP_ECHO) {
                bpf_trace_printk("ping echo (%s) id=%u, sequence=%u\\n",
                                 skb->dev->name, icmph.un.echo.id, icmph.un.echo.sequence);
            }
        }
    }

    return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="tun_net_xmit", fn_name="bpf_tun_net_xmit")

print("Tracing tun_net_xmit() ... Ctrl-C to end.")

b.trace_print()
