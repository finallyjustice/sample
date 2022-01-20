#!/usr/bin/python

from bcc import BPF

prog = """
#include <scsi/scsi_cmnd.h>
#include <scsi/scsi.h>

int bpf_scsi_mq_done(struct pt_regs *ctx, struct scsi_cmnd *cmd)
{
    int result = cmd->result;
    unsigned char cmnd = cmd->cmnd[0];

    if (driver_byte(result) == DRIVER_SENSE) {
        bpf_trace_printk("scsi_mq_done(): result=%d, cdb=0x%x\\n", result, cmnd);
    }

    return 0;
}
"""

b = BPF (text = prog);
b.attach_kprobe(event="scsi_mq_done", fn_name="bpf_scsi_mq_done")

print("Tracing scsi_mq_done() ... Ctrl-C to end.")

b.trace_print()
