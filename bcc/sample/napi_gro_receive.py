#!/usr/bin/python

# This is the ebpf to track if the skb for specific tcp port 5201 has
# arrived at napi_gro_receive(). For instance, the virtio-net receives skb
# via napi_gro_receive(). The port 5201 is always used by iperf3.
#
# ./napi_gro_receive.py 
# Tracing napi_gro_receive() ... Ctrl-C to end.
#           <idle>-0     [003] ..s. 661067.836193: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589861
#           <idle>-0     [003] ..s. 661067.836755: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589862
#           <idle>-0     [003] ..s. 661067.836791: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589862
#           <idle>-0     [003] ..s. 661067.837349: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589899
#           <idle>-0     [003] ..s. 661067.837403: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589899
#           <idle>-0     [003] ..s. 661067.837520: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589903
#           <idle>-0     [006] ..s. 661067.837784: 0: napi_gro_receive(): queue=input.1, src=50344, seq=916761850
#           <idle>-0     [006] ..s. 661067.837936: 0: napi_gro_receive(): queue=input.1, src=50344, seq=916761851
#           <idle>-0     [006] ..s. 661067.837980: 0: napi_gro_receive(): queue=input.1, src=50344, seq=916761851
#           <idle>-0     [003] ..s. 661067.878021: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589986
#           <idle>-0     [003] ..s. 661067.878161: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589986
#             sshd-26815 [006] ..s. 661067.878297: 0: napi_gro_receive(): queue=input.1, src=50344, seq=916761888
#             sshd-26815 [006] ..s. 661067.878346: 0: napi_gro_receive(): queue=input.1, src=50344, seq=916806628
#           <idle>-0     [003] ..s. 661067.878352: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589986
#             sshd-26815 [006] ..s. 661067.878381: 0: napi_gro_receive(): queue=input.1, src=50344, seq=916815576
#             sshd-26815 [006] ..s1 661067.878477: 0: napi_gro_receive(): queue=input.1, src=50344, seq=916824524
#           <idle>-0     [006] ..s. 661067.878720: 0: napi_gro_receive(): queue=input.1, src=50344, seq=916824608
#           <idle>-0     [003] ..s. 661067.878790: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589987
#           <idle>-0     [003] ..s. 661067.878925: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246589991
#           <idle>-0     [006] ..s. 661067.879931: 0: napi_gro_receive(): queue=input.1, src=50344, seq=916851452
#           <idle>-0     [003] ..s. 661067.920009: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246590212
#           <idle>-0     [003] ..s. 661067.920131: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246590212
#           <idle>-0     [003] ..s. 661067.920323: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246590212
#           <idle>-0     [003] ..s. 661067.920695: 0: napi_gro_receive(): queue=input.0, src=50342, seq=246590213

from bcc import BPF

prog = """
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/virtio.h>
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

int bpf_napi_gro_receive(struct pt_regs *ctx, struct napi_struct *napi,
			 struct sk_buff *skb)
{
	void *vq_addr_ptr = (void *)napi - 0x8;
	u64 vq_addr;
	struct virtqueue vq;
	void *mac_header_ptr = skb->head + skb->mac_header;
	struct ethhdr *m_eh;
	struct iphdr *m_iph;
	struct tcphdr *m_th_ptr;
	struct tcphdr m_th;
	char mac_base[64];

	bpf_probe_read(&vq_addr, sizeof(u64), vq_addr_ptr);
	bpf_probe_read(&vq, sizeof(vq), (void *)vq_addr);
	bpf_probe_read(mac_base, 64, mac_header_ptr);

	m_eh = (struct ethhdr *)mac_base;

	if (m_eh->h_proto == htons(ETH_P_IP)) {
		m_iph = (struct iphdr *)(mac_base + ETH_HLEN);

		if (m_iph->ihl >= 5 && m_iph->version == 4 &&
		    m_iph->protocol == IPPROTO_TCP) {
			m_th_ptr = (struct tcphdr *)(mac_base + ETH_HLEN + m_iph->ihl * 4);
			bpf_probe_read(&m_th, sizeof(m_th), m_th_ptr);

			if (ntohs(m_th.source) == 5201 || ntohs(m_th.dest) == 5201) {
				bpf_trace_printk("napi_gro_receive(): queue=%s, src=%d, seq=%u\\n",
						 vq.name, ntohs(m_th.source), ntohl(m_th.seq));
			}
		}
	}

	return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="napi_gro_receive", fn_name="bpf_napi_gro_receive")

print("Tracing napi_gro_receive() ... Ctrl-C to end.")

b.trace_print()
