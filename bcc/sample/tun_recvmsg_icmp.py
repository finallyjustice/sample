#!/usr/bin/python

# sudo ./tun_recvmsg_icmp.py
# Tracing tun_recvmsg() ... Ctrl-C to end.
#       vhost-3294-3308  [003] d... 49282.053586: 0x00000001: ping echo (vnet0) id=23589, sequence=256
#       vhost-3294-3309  [003] d... 49283.053999: 0x00000001: ping echo (vnet0) id=23589, sequence=512
#       vhost-3294-3309  [003] d... 49284.064819: 0x00000001: ping echo (vnet0) id=23589, sequence=768
#       vhost-3294-3309  [003] d... 49285.056602: 0x00000001: ping echo (vnet0) id=23589, sequence=1024
#       vhost-3294-3309  [003] d... 49286.058758: 0x00000001: ping echo (vnet0) id=23589, sequence=1280

from bcc import BPF

prog = """
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/icmp.h>

int bpf_tun_recvmsg(struct pt_regs *ctx, struct socket *sock,
                    struct msghdr *m, size_t total_len, int flags)
{
    struct sk_buff *skb = m->msg_control;
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
b.attach_kprobe(event="tun_recvmsg", fn_name="bpf_tun_recvmsg")

print("Tracing tun_recvmsg() ... Ctrl-C to end.")

b.trace_print()
