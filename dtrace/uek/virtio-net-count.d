#!/usr/sbin/dtrace -qs

/*
 * # modprobe fbt
 *
 * # sudo ./virtio-net-count.d 
 * ^C
 * skb_recv_done() rq=input.0 cnt=23
 * virtnet_poll() rq=input.0 cnt=23
 */

dtrace:::BEGIN
{
}

fbt:virtio_net:skb_recv_done:entry
{
    vq = (struct virtqueue *)arg0;
    vi = (struct virtnet_info *)vq->vdev->priv;
    idx = vq->index / 2;
    rq = (struct receive_queue *)(&vi->rq[idx]);

    @skb_recv_done_cnt[rq->name] = count();

    /* printf("skb_recv_done %s\n", rq->name); */
}

fbt:virtio_net:__dta_virtnet_poll_92:entry
{
    napi_addr = (unsigned long)arg0;
    rq = (struct receive_queue *)(napi_addr-0x8);
   
    @virtnet_poll_cnt[rq->name] = count()
 
    /* printf("virtnet_poll() %s\n", rq->name); */
}

dtrace:::END
{
    printa("skb_recv_done() rq=%s cnt=%@d\n", @skb_recv_done_cnt);
    printa("virtnet_poll() rq=%s cnt=%@d\n", @virtnet_poll_cnt);
}
