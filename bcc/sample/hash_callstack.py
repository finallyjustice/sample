#!/usr/bin/python

# sudo ./stack.py 
# Tracing ... Ctrl-C to end.
# ^CTrancing stopped.
#
# scsi_queue_rq+0x1
# blk_mq_do_dispatch_sched+0xa3
# blk_mq_sched_dispatch_requests+0xfb
# __blk_mq_run_hw_queue+0x81
# __blk_mq_delay_run_hw_queue+0x11d
# blk_mq_run_hw_queue+0x64
# blk_mq_sched_insert_requests+0x7a
# blk_mq_flush_plug_list+0x18c
# blk_flush_plug_list+0xcf
# blk_finish_plug+0x2c
# wb_writeback+0x18b
# wb_workfn+0x368
# process_one_work+0x179
# worker_thread+0x4f
# kthread+0x105
# ret_from_fork+0x24
#     2
#
# scsi_queue_rq+0x1
# blk_mq_do_dispatch_sched+0xa3
# blk_mq_sched_dispatch_requests+0xfb
# __blk_mq_run_hw_queue+0x81
# __blk_mq_delay_run_hw_queue+0x11d
# blk_mq_run_hw_queue+0x64
# blk_mq_sched_insert_requests+0x7a
# blk_mq_flush_plug_list+0x18c
# blk_flush_plug_list+0xcf
# blk_finish_plug+0x2c
# xfs_buf_delwri_submit_buffers+0x229
# xfs_buf_delwri_submit_nowait+0x10
# xfsaild+0x2e8
# kthread+0x105
# ret_from_fork+0x24
#     5
#
# scsi_queue_rq+0x1
# blk_mq_do_dispatch_sched+0xa3
# blk_mq_sched_dispatch_requests+0xfb
# __blk_mq_run_hw_queue+0x81
# blk_mq_run_work_fn+0x1b
# process_one_work+0x179
# worker_thread+0x4f
# kthread+0x105
# ret_from_fork+0x24
#     25

from bcc import BPF
from time import sleep

prog = """
#include <uapi/linux/ptrace.h>
#include <linux/sched.h>

struct key_t {
    u32 tgid;
    int kernel_stack_id;
};

BPF_HASH(counts, struct key_t);
BPF_STACK_TRACE(stack_traces, 1024);

int bpf_callstack(void *ctx)
{
	struct key_t key = {};
	
	key.tgid = 0xffffffff;
	key.kernel_stack_id = stack_traces.get_stackid(ctx,
						BPF_F_REUSE_STACKID);
	counts.increment(key);

	return 0;
}
"""

b = BPF (text = prog);
#b.attach_kprobe(event="napi_gro_receive", fn_name="bpf_callstack")
b.attach_kprobe(event="scsi_queue_rq", fn_name="bpf_callstack")

try:
    print("Tracing ... Ctrl-C to end.")
    sleep(99999999)
except KeyboardInterrupt:
    print("Trancing stopped.\n")

counts = b["counts"]
stack_traces = b["stack_traces"]

for k, v in sorted(counts.items(),key=lambda counts: counts[1].value):
    kernel_stack = stack_traces.walk(k.kernel_stack_id)
    for addr in kernel_stack:
        print("%s" % (b.ksym(addr, show_offset=True)));
    print("    %d\n" % v.value)
