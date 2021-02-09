#!/usr/bin/python

# # ./tun_net_xmit_tcp.py 
# Tracing tun_net_xmit() ... Ctrl-C to end.
#           <idle>-0     [004] d.s. 22252.407535: 0x00000001: tun_net_xmit(): name=vnet0, queue=2, src=59792
#           <idle>-0     [004] d.s. 22252.407538: 0x00000001: tun_net_xmit(): len=60, seq=689941440, syn=16777216
#           <idle>-0     [012] d.s. 22252.473407: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59792
#           <idle>-0     [012] d.s. 22252.473409: 0x00000001: tun_net_xmit(): len=52, seq=689941441, syn=0
#           <idle>-0     [012] dNs. 22252.473416: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59792
#           <idle>-0     [012] dNs. 22252.473417: 0x00000001: tun_net_xmit(): len=89, seq=689941441, syn=0
#           <idle>-0     [012] d.s. 22252.539166: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59792
#           <idle>-0     [012] d.s. 22252.539169: 0x00000001: tun_net_xmit(): len=52, seq=689941478, syn=0
#           <idle>-0     [012] dNs. 22252.539190: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59792
#           <idle>-0     [012] dNs. 22252.539191: 0x00000001: tun_net_xmit(): len=56, seq=689941478, syn=0
#           <idle>-0     [012] d.s. 22252.645500: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59792
#           <idle>-0     [012] d.s. 22252.645502: 0x00000001: tun_net_xmit(): len=135, seq=689941482, syn=0
#           <idle>-0     [012] d.s. 22252.711200: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59792
#           <idle>-0     [012] d.s. 22252.711201: 0x00000001: tun_net_xmit(): len=52, seq=689941565, syn=0
#           <idle>-0     [017] d.s. 22252.711415: 0x00000001: tun_net_xmit(): name=vnet0, queue=1, src=59794
#           <idle>-0     [017] d.s. 22252.711418: 0x00000001: tun_net_xmit(): len=60, seq=1378829932, syn=16777216
#           <idle>-0     [012] d.s. 22252.777273: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59794
#           <idle>-0     [012] d.s. 22252.777276: 0x00000001: tun_net_xmit(): len=52, seq=1378829933, syn=0
#           <idle>-0     [012] dNs. 22252.777296: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59794
#           <idle>-0     [012] dNs. 22252.777297: 0x00000001: tun_net_xmit(): len=89, seq=1378829933, syn=0
#           <idle>-0     [012] d.s. 22252.844220: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59792
#           <idle>-0     [012] d.s. 22252.844223: 0x00000001: tun_net_xmit(): len=52, seq=689941565, syn=0
#           <idle>-0     [012] d.s. 22252.909946: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59792
#           <idle>-0     [012] d.s. 22252.909947: 0x00000001: tun_net_xmit(): len=52, seq=689941565, syn=0
#           <idle>-0     [012] d.s. 22252.910074: 0x00000001: tun_net_xmit(): name=vnet0, queue=0, src=59794
#           <idle>-0     [012] d.s. 22252.910075: 0x00000001: tun_net_xmit(): len=1440, seq=1378829970, syn=0

from bcc import BPF

prog = """
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/ip.h>

struct tcphdr {
    __be16  source;
    __be16  dest;
    __be32  seq;
    __be32  ack_seq;
#if defined(__LITTLE_ENDIAN_BITFIELD)
    __u16   res1:4,
    doff:4,
    fin:1,
    syn:1,
    rst:1,
    psh:1,
    ack:1,
    urg:1,
    ece:1,
    cwr:1;
#elif defined(__BIG_ENDIAN_BITFIELD)
    __u16   doff:4,
    res1:4,
    cwr:1,
    ece:1,
    urg:1,
    ack:1,
    psh:1,
    rst:1,
    syn:1,
    fin:1;
#else
#error  "Adjust your <asm/byteorder.h> defines"
#endif
    __be16  window;
    __sum16 check;
    __be16  urg_ptr;
};

int bpf_tun_net_xmit(struct pt_regs *ctx, struct sk_buff *skb,
                         struct net_device *dev)
{
    void *mac_header_ptr = skb->head + skb->mac_header;
    int txq = skb->queue_mapping;
    struct ethhdr *m_eh;
    struct iphdr *m_iph;
    struct tcphdr *m_th_ptr;
    struct tcphdr m_th;
    char mac_base[64];

    bpf_probe_read(mac_base, 64, mac_header_ptr);

    m_eh = (struct ethhdr *)mac_base;

    if (m_eh->h_proto == htons(ETH_P_IP)) {
        m_iph = (struct iphdr *)(mac_base + ETH_HLEN);

        if (m_iph->ihl >= 5 && m_iph->version == 4 &&
            m_iph->protocol == IPPROTO_TCP) {
            m_th_ptr = (struct tcphdr *)(mac_base + ETH_HLEN + m_iph->ihl * 4);
            bpf_probe_read(&m_th, sizeof(m_th), m_th_ptr);

            if (ntohs(m_th.source) == 5201 || ntohs(m_th.dest) == 5201) {
                bpf_trace_printk("tun_net_xmit(): name=%s, queue=%d, src=%d\\n",
                         dev->name, txq, ntohs(m_th.source));
                bpf_trace_printk("tun_net_xmit(): len=%d, seq=%u, syn=%u\\n",
                         ntohs(m_iph->tot_len), ntohl(m_th.seq), ntohl(m_th.syn));
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
