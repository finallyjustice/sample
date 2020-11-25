
#!/usr/bin/python

# sudo ./napi_gro_receive_stack.py 
# Tracing napi_gro_receive() ... Ctrl-C to end.
# callstack for napi_gro_receive:
#   napi_gro_receive+0x1
#   virtnet_poll+0x168
#   net_rx_action+0x289
#   __do_softirq+0xe1
#   irq_exit+0xdb
#   do_IRQ+0x5a
#   ret_from_intr+0x0
#   native_safe_halt+0x12
#   default_idle+0x20
#   arch_cpu_idle+0x15
#   default_idle_call+0x23
#   do_idle+0x199
#   cpu_startup_entry+0x1d
#   start_secondary+0x169
#   secondary_startup_64+0xb6
#
#
# callstack for napi_gro_receive:
#   napi_gro_receive+0x1
#   virtnet_poll+0x168
#   net_rx_action+0x289
#   __do_softirq+0xe1
#   irq_exit+0xdb
#   do_IRQ+0x5a
#   ret_from_intr+0x0
#   native_safe_halt+0x12
#   default_idle+0x20
#   arch_cpu_idle+0x15
#   default_idle_call+0x23
#   do_idle+0x199
#   cpu_startup_entry+0x1d
#   start_secondary+0x169
#   secondary_startup_64+0xb6

from bcc import BPF

prog = """
#include <uapi/linux/ptrace.h>
#include <linux/sched.h>

struct data_t {
    int kernel_stack_id;
};

BPF_PERF_OUTPUT(events);
BPF_STACK_TRACE(stack_traces, 1024);
        
int bpf_napi_gro_receive(void *ctx)
{
	struct data_t data = {};

	data.kernel_stack_id = stack_traces.get_stackid(ctx,
					BPF_F_REUSE_STACKID);
	events.perf_submit(ctx, &data, sizeof(data));

	return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="napi_gro_receive", fn_name="bpf_napi_gro_receive")

print("Tracing napi_gro_receive() ... Ctrl-C to end.")

def print_event(cpu, data, size):
    try:
        event = b["events"].event(data)
        stack_traces = b["stack_traces"]
        kernel_stack = stack_traces.walk(event.kernel_stack_id)

        print("callstack for napi_gro_receive:");
        for addr in kernel_stack:
            print("  %s" % (b.ksym(addr, show_offset=True)));
        print("\n")
    except KeyboardInterrupt:
        exit()

b["events"].open_perf_buffer(print_event)
while 1:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
