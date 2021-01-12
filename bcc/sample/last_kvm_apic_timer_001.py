#!/usr/bin/python

# sudo ./last_kvm_apic_timer_001.py 
# Tracing ... Ctrl-C to end.
# ^CTrancing stopped.
#
# last timestamp to inject APIC timer for each vcpu (ns since host boot):
# (kvm=0xffffb14c60089000, vcpu=5, last_timestamp=27639807096970):
# (kvm=0xffffb14c60089000, vcpu=7, last_timestamp=27639821101960):
# (kvm=0xffffb14c60089000, vcpu=0, last_timestamp=27640152165826):
# (kvm=0xffffb14c60089000, vcpu=4, last_timestamp=27640376142673):
# (kvm=0xffffb14c60089000, vcpu=3, last_timestamp=27640554971083):
# (kvm=0xffffb14c60089000, vcpu=1, last_timestamp=27640648195263):
# (kvm=0xffffb14c60089000, vcpu=2, last_timestamp=27640703630576):
# (kvm=0xffffb14c60089000, vcpu=6, last_timestamp=27640784198531):
#
# [27477.030723] kvm [10304]: vcpu0, guest rIP: 0xffffffff9b67db34 disabled perfctr wrmsr: 0xc2 data 0xffff

from bcc import BPF
from time import sleep

prog = """
#include <uapi/linux/ptrace.h>
#include <linux/kvm_host.h>

struct key_t {
    u64 kvm;
    int vcpu;
};

BPF_HASH(lasttime, struct key_t);

int bpf_kvm_inject_apic_timer_irqs(struct pt_regs *ctx, struct kvm_vcpu *vcpu)
{
    struct key_t key = {};
    u64 ts;

    key.kvm = (u64)vcpu->kvm;
    key.vcpu = vcpu->vcpu_id;
    ts = bpf_ktime_get_ns();

    lasttime.update(&key, &ts);

    return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="kvm_inject_apic_timer_irqs", fn_name="bpf_kvm_inject_apic_timer_irqs")

try:
    print("Tracing ... Ctrl-C to end.")
    sleep(99999999)
except KeyboardInterrupt:
    print("Trancing stopped.\n")

counts = b["lasttime"]

print("last timestamp to inject APIC timer for each vcpu (ns since host boot):");
for k, v in sorted(counts.items(),key=lambda counts: counts[1].value):
    print("(kvm=0x%lx, vcpu=%d, last_timestamp=%lu):" % (k.kvm, k.vcpu, v.value));
