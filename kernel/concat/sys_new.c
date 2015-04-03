/* The code I implement in my spare time for Erez Zadok's OS class */

#include <linux/export.h>
#include <linux/mm.h>
#include <linux/utsname.h>
#include <linux/mman.h>
#include <linux/reboot.h>
#include <linux/prctl.h>
#include <linux/highuid.h>
#include <linux/fs.h>
#include <linux/kmod.h>
#include <linux/perf_event.h>
#include <linux/resource.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/capability.h>
#include <linux/device.h>
#include <linux/key.h>
#include <linux/times.h>
#include <linux/posix-timers.h>
#include <linux/security.h>
#include <linux/dcookies.h>
#include <linux/suspend.h>
#include <linux/tty.h>
#include <linux/signal.h>
#include <linux/cn_proc.h>
#include <linux/getcpu.h>
#include <linux/task_io_accounting_ops.h>
#include <linux/seccomp.h>
#include <linux/cpu.h>
#include <linux/personality.h>
#include <linux/ptrace.h>
#include <linux/fs_struct.h>
#include <linux/file.h>
#include <linux/mount.h>
#include <linux/gfp.h>
#include <linux/syscore_ops.h>
#include <linux/version.h>
#include <linux/ctype.h>

#include <linux/compat.h>
#include <linux/syscalls.h>
#include <linux/kprobes.h>
#include <linux/user_namespace.h>
#include <linux/binfmts.h>

#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/uidgid.h>
#include <linux/cred.h>

#include <linux/kmsg_dump.h>

struct concat_params
{
	char **in_files;
	char *out_file;
	int num_files;
};

// append ifile at the end of ofile
void append_file(struct file *ifile, struct file *ofile)
{
	char *buf;
	int ret;

	buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	memset(buf, 0, PAGE_SIZE);
	while((ret=vfs_read(ifile, buf, PAGE_SIZE, &ifile->f_pos)) > 0)
	{
		vfs_write(ofile, buf, ret, &ofile->f_pos);
		memset(buf, 0, PAGE_SIZE);
	}

	kfree(buf);
}

asmlinkage int sys_concatfiles(struct concat_params __user *ucp)
{
	mm_segment_t oldfs;
	int i;
	struct file *ifile, *ofile;

	oldfs = get_fs();
	set_fs(KERNEL_DS);

	printk(KERN_ALERT "num_files: %d\n", ucp->num_files);
	for(i=0; i<ucp->num_files; i++)
	{
		printk(KERN_ALERT "in %d, %s\n", i, ucp->in_files[i]);
	}

	ofile = filp_open(ucp->out_file, O_WRONLY|O_CREAT, 0);
	if(IS_ERR(ofile))
	{
		printk(KERN_ALERT "Open file %s failed\n", ucp->out_file);
		goto finish;
	}

	for(i=0; i<ucp->num_files; i++)
	{
		ifile = filp_open(ucp->in_files[i], O_RDONLY, 0);
		if(IS_ERR(ifile))
		{
			printk(KERN_ALERT "Open file %s failed\n", ucp->in_files[i]);
			goto finish;
		}

		append_file(ifile, ofile);

		filp_close(ifile, NULL);
	}

	vfs_fsync(ofile, 0);

finish:	
	filp_close(ofile, NULL);
	set_fs(oldfs);
		
	return 0;
}
