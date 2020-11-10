#!/usr/bin/python

from bcc import BPF

prog = """
#include <linux/sched.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>

struct data_t {
	u32 pid;
	u64 ts;
	char comm[TASK_COMM_LEN];
	void *netdev;
};

BPF_PERF_OUTPUT(events);

int bpf_napi_gro_receive(struct pt_regs *ctx, struct napi_struct *napi,
                         struct sk_buff *skb)
{
	struct data_t data = {};

	data.pid = bpf_get_current_pid_tgid();
	data.ts = bpf_ktime_get_ns();
	bpf_get_current_comm(&data.comm, sizeof(data.comm));
	data.netdev = skb->dev;

	events.perf_submit(ctx, &data, sizeof(data));

        return 0;
}
"""

b = BPF(text=prog)
b.attach_kprobe(event="napi_gro_receive", fn_name="bpf_napi_gro_receive")

print("%-18s %-16s %-6s %s" % ("TIME(s)", "COMM", "PID", "MSG"))

start = 0
def print_event(cpu, data, size):
        global start
        event = b["events"].event(data)
        if start == 0:
            start = event.ts
        time_s = (float(event.ts - start)) / 1000000000
        print("%-18.9f %-16s %-6d [dev=%x: %s]" % (time_s, event.comm, event.pid, event.netdev, "hello world!"))

b["events"].open_perf_buffer(print_event)
while 1:
        b.perf_buffer_poll()
