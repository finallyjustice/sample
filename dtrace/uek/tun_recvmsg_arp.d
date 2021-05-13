#!/usr/sbin/dtrace -qs

/*
 * modprobe fbt
 *
 * usage:
 * ./tun_recvmsg_arp.d <tun device name>
 *
 * # ./tun_recvmsg_arp.d vnet0
 * 27108081 (vnet0 1) src:10.x.x.3(00.xx.xx.xx.xx.xx)->tgt:10.x.x.3(ff.ff.ff.ff.ff.ff)
 * 27108081 (vnet0 1) src:10.x.x.3(00.xx.xx.xx.xx.xx)->tgt:10.x.x.3(ff.ff.ff.ff.ff.ff)
*/


dtrace:::BEGIN
{

}

fbt:tun:tun_recvmsg:entry
/
((struct sk_buff *)(((struct msghdr *) arg1)->msg_control))->dev->name == $$1
&&
((struct ethhdr *)(((struct sk_buff *)(((struct msghdr *) arg1)->msg_control))->head + ((struct sk_buff *)(((struct msghdr *) arg1)->msg_control))->mac_header))->h_proto == htons(0x0806)
&& 
((struct arphdr *)(((struct sk_buff *)(((struct msghdr *) arg1)->msg_control))->head + ((struct sk_buff *)(((struct msghdr *) arg1)->msg_control))->network_header))->ar_pro == htons(0x0800)
&&
(((struct arphdr *)(((struct sk_buff *)(((struct msghdr *) arg1)->msg_control))->head + ((struct sk_buff *)(((struct msghdr *) arg1)->msg_control))->network_header))->ar_op == htons(1) || ((struct arphdr *)(((struct sk_buff *)(((struct msghdr *) arg1)->msg_control))->head + ((struct sk_buff *)(((struct msghdr *) arg1)->msg_control))->network_header))->ar_op == htons(2))
/
{
    m = (struct msghdr *) arg1;
    skb = (struct sk_buff *) m->msg_control;
    arp = (struct arphdr *) (skb->head + skb->network_header);
    arp_ptr = (unsigned char *)(arp + 1);

    printf("%d (%s %d) src:%u.%u.%u.%u(%02x.%02x.%02x.%02x.%02x.%02x)->tgt:%u.%u.%u.%u(%02x.%02x.%02x.%02x.%02x.%02x)\n",
           timestamp/1000000,
           skb->dev->name,
           ntohs(arp->ar_op),
           arp_ptr[6], arp_ptr[7], arp_ptr[8], arp_ptr[9],
           arp_ptr[0], arp_ptr[1], arp_ptr[2], arp_ptr[3], arp_ptr[4], arp_ptr[5],
           arp_ptr[16], arp_ptr[17], arp_ptr[18], arp_ptr[19],
           arp_ptr[10], arp_ptr[11], arp_ptr[12], arp_ptr[13], arp_ptr[14], arp_ptr[15]);
}

dtrace:::END
{

}
