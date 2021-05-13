#!/usr/sbin/dtrace -qs

/*
 * modprobe fbt
 *
 * usage:
 * ./tap_handle_frame_arp.d <tap device name>
 *
 * # ./tap_handle_frame_arp.d vnet0
 * 4305333508 (vnet0 1) src:10.x.xx.1(00.xx.xx.xx.xx.a7)->tgt:10.x.x.21(00.00.00.00.00.00)
 * 4305348508 (vnet0 1) src:10.x.x.1(00.xx.xx.xx.xx.a7)->tgt:10.x.x.21(00.00.00.00.00.00)
 * 4305363507 (vnet0 1) src:10.x.x.1(00.xx.xx.xx.xx.a7)->tgt:10.x.x.21(00.00.00.00.00.00)
 * 4305371627 (vnet0 2) src:168.x.x.4(00.xx.xx.xx.xx.a7)->tgt:10.x.x.21(xx.xx.xx.xx.xx.xx)
*/


dtrace:::BEGIN
{

}

fbt:ksplice_c3azkx8j_tap_new:__dta_tap_handle_frame_49:entry
/
(*(struct sk_buff **)arg0)->dev->name == $$1
&&
((struct ethhdr *)((*(struct sk_buff **)arg0)->head + (*(struct sk_buff **)arg0)->mac_header))->h_proto == htons(0x0806)
&&
((struct arphdr *)((*(struct sk_buff **)arg0)->head + (*(struct sk_buff **)arg0)->network_header))->ar_pro == htons(0x0800)
&&
(((struct arphdr *)((*(struct sk_buff **)arg0)->head + (*(struct sk_buff **)arg0)->network_header))->ar_op == htons(1) || ((struct arphdr *)((*(struct sk_buff **)arg0)->head + (*(struct sk_buff **)arg0)->network_header))->ar_op == htons(2))
/
{
    skb = *(struct sk_buff **) arg0;
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

