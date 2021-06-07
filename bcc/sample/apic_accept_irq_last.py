#!/usr/bin/python

# Tested on 4.14.35-2047.501.2.el7uek.x86_64.
#
# sudo ./apic_accept_irq_last.py --pid 28611
# Tracing ... Ctrl-C to end.
# ^CTrancing stopped.
#
# last timestamp to __apic_accept_irq() for each vcpu (ns since host boot):
# (kvm-pid=28611, vcpu=1): last_timestamp=372291816654888
# (kvm-pid=28611, vcpu=0): last_timestamp=372293800850928
# (kvm-pid=28611, vcpu=6): last_timestamp=372294312860167
# (kvm-pid=28611, vcpu=7): last_timestamp=372294312891700
# (kvm-pid=28611, vcpu=3): last_timestamp=372294632856732
# (kvm-pid=28611, vcpu=4): last_timestamp=372294632857810
# (kvm-pid=28611, vcpu=5): last_timestamp=372294632858224
# (kvm-pid=28611, vcpu=2): last_timestamp=372294665026767
# kvm hypervisor uptime: 372294.760000s

from bcc import BPF
from time import sleep
import argparse

examples = """examples:
    ./apic_accept_irq_last.py         # trace all QEMU PID
    ./apic_accept_irq_last.py --pid   # trace this PID only
"""
parser = argparse.ArgumentParser(
    description="Track the last timestamp of __apic_accept_irq()",
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)

parser.add_argument("-p", "--pid", type=int,
    help="trace this PID only")

args = parser.parse_args()

prog = """
#include <uapi/linux/ptrace.h>
#include <linux/kvm_host.h>
#include <kvm/iodev.h>

struct dest_map {
    DECLARE_BITMAP(map, KVM_MAX_VCPU_ID);
    u8 vectors[KVM_MAX_VCPU_ID];
};

struct kvm_timer {
    struct hrtimer timer;
    s64 period;
    ktime_t target_expiration;
    u32 timer_mode;
    u32 timer_mode_mask;
    u64 tscdeadline;
    u64 expired_tscdeadline;
    atomic_t pending;
    bool hv_timer_in_use;
};

struct kvm_lapic {
    unsigned long base_address;
    struct kvm_io_device dev;
    struct kvm_timer lapic_timer;
    u32 divide_count;
    struct kvm_vcpu *vcpu;
    bool sw_enabled;
    bool irr_pending;
    bool lvt0_in_nmi_mode;
    s16 isr_count; 
    int highest_isr_cache;
    void *regs;
    gpa_t vapic_addr;
    struct gfn_to_hva_cache vapic_cache;
    unsigned long pending_events;
    unsigned int sipi_vector;
};

struct key_t {
    u64 pid;
    int vcpu;
};

BPF_HASH(lasttime, struct key_t);

int bpf___apic_accept_irq(struct pt_regs *ctx, struct kvm_lapic *apic,
                          int delivery_mode, int vector, int level,
                          int trig_mode, struct dest_map *dest_map)
{
    struct key_t key = {};
    u64 ts;
    struct kvm_vcpu *vcpu = apic->vcpu;
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
b.attach_kprobe(event="__apic_accept_irq", fn_name="bpf___apic_accept_irq")

try:
    print("Tracing ... Ctrl-C to end.")
    sleep(99999999)
except KeyboardInterrupt:
    print("Trancing stopped.\n")

counts = b["lasttime"]

print("last timestamp to __apic_accept_irq() for each vcpu (ns since host boot):");
for k, v in sorted(counts.items(),key=lambda counts: counts[1].value):
    print("(kvm-pid=%d, vcpu=%d): last_timestamp=%lu" % (k.pid, k.vcpu, v.value));

with open('/proc/uptime', 'r') as f:
    uptime_seconds = float(f.readline().split()[0])

print("kvm hypervisor uptime: %fs" % uptime_seconds)
