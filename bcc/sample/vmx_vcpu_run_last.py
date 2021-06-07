#!/usr/bin/python

# Tested on 4.14.35-2047.501.2.el7uek.x86_64.
#
# sudo ./vmx_vcpu_run_last.py --pid 24592
# Tracing ... Ctrl-C to end.
# ^CTrancing stopped.
#
# last timestamp to __vmx_vcpu_run() for each vcpu (ns since host boot):
# (kvm-pid=24592, vcpu=0): last_timestamp=368286896898250
# (kvm-pid=24592, vcpu=3): last_timestamp=368286959954458
# (kvm-pid=24592, vcpu=1): last_timestamp=368286976023571
# (kvm-pid=24592, vcpu=2): last_timestamp=368287120856632
# kvm hypervisor uptime: 368287.160000s

from bcc import BPF
from time import sleep
import argparse

examples = """examples:
    ./vmx_vcpu_run_last.py         # trace all QEMU PID
    ./vmx_vcpu_run_last.py --pid   # trace this PID only
"""
parser = argparse.ArgumentParser(
    description="Track the last timestamp of __vmx_vcpu_run()",
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)

parser.add_argument("-p", "--pid", type=int,
    help="trace this PID only")

args = parser.parse_args()

prog = """
#include <uapi/linux/ptrace.h>
#include <linux/kvm_host.h>

struct key_t {
    u64 pid;
    int vcpu;
};

BPF_HASH(lasttime, struct key_t);

struct vcpu_vmx;

int bpf___vmx_vcpu_run(struct pt_regs *ctx, struct kvm_vcpu *vcpu,
                       struct vcpu_vmx *vmx)
{
    struct key_t key = {};
    u64 ts;
    u64 pid = vcpu->kvm->userspace_pid;

    key.pid = pid;
    key.vcpu = vcpu->vcpu_id;
    ts = bpf_ktime_get_ns();

    if (!##PID## || pid == ##PID##)
        lasttime.update(&key, &ts);

    return 0;
}
"""

if args.pid:
    prog = prog.replace('##PID##', str(args.pid))
else:
    prog = prog.replace('##PID##', '0')

b = BPF (text = prog);
b.attach_kprobe(event="__vmx_vcpu_run", fn_name="bpf___vmx_vcpu_run")

try:
    print("Tracing ... Ctrl-C to end.")
    sleep(99999999)
except KeyboardInterrupt:
    print("Trancing stopped.\n")

counts = b["lasttime"]

print("last timestamp to __vmx_vcpu_run() for each vcpu (ns since host boot):");
for k, v in sorted(counts.items(),key=lambda counts: counts[1].value):
    print("(kvm-pid=%d, vcpu=%d): last_timestamp=%lu" % (k.pid, k.vcpu, v.value));

with open('/proc/uptime', 'r') as f:
    uptime_seconds = float(f.readline().split()[0])

print("kvm hypervisor uptime: %fs" % uptime_seconds)
