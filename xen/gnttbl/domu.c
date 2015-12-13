#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <xen/interface/xen.h>
#include <xen/interface/io/ring.h>
#include <xen/grant_table.h>
#include <asm/pgtable.h>
#include <asm/sync_bitops.h>
#include <xen/events.h>
#include <asm/xen/page.h>
#include <xen/evtchn.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>

unsigned long page;

struct as_request {
	unsigned int id;
	unsigned int status;
	unsigned int operation;
};

struct as_response {
	unsigned int id;
	unsigned int status;
	unsigned int operation;
};

DEFINE_RING_TYPES(as, struct as_request, struct as_response);

struct info_t {
	struct as_front_ring ring;
	grant_ref_t gref;
	int irq;
	int port;
}info;

#define DOM0_ID 0

static struct proc_dir_entry *proc_dir = NULL;
static struct proc_dir_entry *proc_file = NULL;
char proc_data[20];

int send_request_to_dom0(void) 
{
	struct as_request *ring_req;
	int notify;
	static int reqid = 9;
	
	ring_req = RING_GET_REQUEST(&(info.ring), info.ring.req_prod_pvt);
	ring_req->id = reqid;
	ring_req->operation = reqid;
	ring_req->status = reqid;
	
	printk(KERN_DEBUG "\nxen:DomU: Fill in IDX-%d, with id=%d, op=%d, st=%d",
		info.ring.req_prod_pvt, ring_req->id, ring_req->operation, ring_req->status);
	reqid++;
	info.ring.req_prod_pvt += 1;
	
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&(info.ring), notify);
	if (notify) {
		printk(KERN_DEBUG "\nxen: DomU: sent a req to Dom0");
		notify_remote_via_irq(info.irq);
	} else {
		printk(KERN_DEBUG "\nxen:DomU: No notify req to Dom0");
		notify_remote_via_irq(info.irq);
	}
	
	printk("...\n");
	return 0;
}

int file_write (struct file *filp, const char __user *buff, unsigned long len, void *data)
{
	int value;
	printk(KERN_DEBUG "\nxen:domU: file_write %lu bytes", len);
	if (copy_from_user(&proc_data[0], buff, len))
	return -EFAULT;

	proc_data[len] = '\x0';
	value = simple_strtol(proc_data, 0, 10);
	
	switch(value) {
	case 1:
		send_request_to_dom0();
		printk(KERN_DEBUG " ,value = %d", value);
		break;
	default:
		printk(KERN_DEBUG " ,value not recongnized!");
	}
	return len;
}

int file_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	sprintf(page, "%s", proc_data);
	return strlen(page);
}

int create_procfs_entry(void) 
{
	int ret = 0;
	proc_dir = proc_mkdir("demo", NULL);
	if (!proc_dir) {
		printk(KERN_DEBUG "\nxen:domU could not create demo entry in procfs");
		ret = - EAGAIN;
		return ret;
	}

	proc_file = create_proc_entry("file", 0600, proc_dir);
	if (proc_file) {
		proc_file->read_proc = file_read;
		proc_file->write_proc = file_write;
	} else {
		printk(KERN_DEBUG "\nxen:domU Could not create /proc/demo/file");
		ret = -EAGAIN;
		return ret;
	}
	return ret;
}

static irqreturn_t as_int (int irq, void *dev_id)
{
	struct as_response *ring_resp;
	RING_IDX i, rp;

	printk("\nxen:DomU: as_int called");
again:
	rp = info.ring.sring->rsp_prod;
	printk(KERN_DEBUG "\nxen:DomU:ring pointers %d to %d", info.ring.rsp_cons, rp);
	for (i = info.ring.rsp_cons; i != rp; i++) {
		unsigned long id;
		ring_resp = RING_GET_RESPONSE(&(info.ring), i);
		printk(KERN_DEBUG "\nxen:domU: Recvd in IDX-%d, with id=%d, op=%d, st=%d", i, ring_resp->id, ring_resp->operation, ring_resp->status);
		id = ring_resp->id;
		switch(ring_resp->operation) {
		case 0:
			printk(KERN_DEBUG "\nxen:DomU: operation: 0");
			break;
		default:
			break;
		}
	}

	info.ring.rsp_cons = i;
	if (i != info.ring.req_prod_pvt) {
		int more_to_do;
		RING_FINAL_CHECK_FOR_RESPONSES(&info.ring, more_to_do);
		if (more_to_do)
			goto again;
	} else
		info.ring.sring->rsp_event = i + 1;
	return IRQ_HANDLED;
}

int gnt_init(void)
{
	int mfn;
	int err;
	struct as_sring *sring;

	struct evtchn_alloc_unbound alloc_unbound;
	printk(KERN_INFO "gnt_init\n");

	page =  __get_free_pages(GFP_KERNEL, 0);
	if (page == 0) {
		printk(KERN_DEBUG "\nxen:DomU:could not get free page");
		return 0;
	}

	sring = (struct as_sring *)page;
	SHARED_RING_INIT(sring);
	FRONT_RING_INIT(&(info.ring), sring, PAGE_SIZE);
	mfn = virt_to_mfn(page);

	printk(KERN_INFO "grant foreign access\n");
	info.gref = gnttab_grant_foreign_access(DOM0_ID, mfn, 0);
	if (info.gref < 0) {
		printk(KERN_DEBUG "\nxen:could not grant foreign access");
		free_page((unsigned long)page);
		info.ring.sring = NULL;
		return 0;
	}
	printk(KERN_DEBUG "\n gref = %d", info.gref);
	alloc_unbound.dom = DOMID_SELF;
	alloc_unbound.remote_dom = DOM0_ID;
	err = HYPERVISOR_event_channel_op(EVTCHNOP_alloc_unbound, &alloc_unbound);
	if (err) {
		printk(KERN_DEBUG "\nalloc unbound port failure");
		return err;
	}

	err = bind_evtchn_to_irqhandler(alloc_unbound.port, as_int, 0, "xen-eg", &info);
	if (err < 0) {
		printk(KERN_DEBUG "\nbind evtchn to irqhandler failure");
		return err;
	}

	info.irq = err;
	info.port = alloc_unbound.port;
	printk(KERN_DEBUG " interrupt = %d, local_port = %d", info.irq, info.port);
	printk("...\n...");
	create_procfs_entry();
	return 0;
}

void gnt_exit(void)
{
	printk(KERN_DEBUG "\ncleanup grant ref:");
	if (gnttab_query_foreign_access(info.gref) == 0) {
		printk(KERN_DEBUG "\n xen:No one has mapped this frame");
		gnttab_end_foreign_access(info.gref, 0, page);
		//gnttab_end_foreign_access(info.gref, 0, sring);
	} else {
		printk(KERN_DEBUG "\n xen:Someone has mapped this frame");
		gnttab_end_foreign_access(info.gref, 0, page);
		//gnttab_end_foreign_access(info.gref, 0, sring);
	}
	
	remove_proc_entry("file", proc_dir);
	remove_proc_entry("demo", NULL);
	printk(KERN_DEBUG "...\n...");
}

module_init(gnt_init);
module_exit(gnt_exit);

MODULE_LICENSE("GPL");
