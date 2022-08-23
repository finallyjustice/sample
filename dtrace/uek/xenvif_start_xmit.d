#!/usr/sbin/dtrace -qs

/*
 * This does not work
 */

struct icmphdr_local {
    __u8          type;
    __u8          code;
    __sum16       checksum;
    __be16  id;
    __be16  sequence;
};

dtrace:::BEGIN
{
}

fbt:xen_netback:xenvif_start_xmit:entry
/
((struct sk_buff *)arg0)->dev->name == $$1
&&
((struct ethhdr *)(((struct sk_buff *)arg0)->head + ((struct sk_buff *)arg0)->mac_header))->h_proto == htons(0x0800)
&&
((struct iphdr *)(((struct sk_buff *)arg0)->head + ((struct sk_buff *)arg0)->network_header))->protocol == 1
/
{
    skb = (struct sk_buff *)arg0;
    iph = (struct iphdr *) (skb->head + skb->network_header);
    icmph = (struct icmphdr_local *) (skb->head + skb->network_header + iph->ihl * 4);
    printf("xenvif_start_xmit(%s) type=%u, id=%u, sequence=%u\n",
            ((struct sk_buff *)arg0)->dev->name,
            icmph->type, icmph->id, icmph->sequence);
}

dtrace:::END
{
}
