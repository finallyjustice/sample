#!/usr/sbin/dtrace -qs

/*
 * # modprobe fbt
 */

dtrace:::BEGIN
{
}

fbt:tap:tap_handle_frame:entry
{
    pskb = (struct sk_buff **) arg0;
    skb = (struct sk_buff *) *pskb;
    dev = (struct net_device *) skb->dev;
    tap = (struct tap_dev *) dev->rx_handler_data;
    printf("tap_handle_frame() %s %d\n", dev->name, tap->numvtaps);
}

dtrace:::END
{
    /*printa("skb_recv_done() rq=%s cnt=%@d\n", @skb_recv_done_cnt); */
}
