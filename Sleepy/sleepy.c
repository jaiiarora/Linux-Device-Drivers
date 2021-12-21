/*
 * sleepy.c module
 */

//need to create a device file for this module with the major number

#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/wait.h>


MODULE_LICENSE("GPL");

static int sleepy_major=0;
static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag=0;

ssize_t sleepy_read(struct file* filp,  char __user* buff, size_t count, loff_t* pos)
{
	pr_info("process  %i (%s) going to sleep \n",
			current->pid, current->comm);
	wait_event_interruptible(wq, flag!=0);
	flag=0;
	pr_info("awoken %i (%s)\n", current->pid, current->comm);
	return 0;
}

ssize_t sleepy_write(struct file* filp, const char __user *buff, size_t count, loff_t* pos)
{
	pr_info("process %i (%s) awakening the readers... \n", current->pid, current->comm);
	flag=1;
	wake_up_interruptible(&wq);
	return count;
}


struct file_operations sleepy_fops={
	.owner=THIS_MODULE,
	.read= sleepy_read,
	.write= sleepy_write,
};

static int __init sleepy_init(void)
{
	int result;
	result=register_chrdev(sleepy_major, "sleepy", &sleepy_fops);
	 
	if (result<0)
		return result;
	if (sleepy_major==0)
		sleepy_major=result;
	pr_info("%d\n", sleepy_major);
	return 0;
}

void sleepy_cleanup(void)
{
	pr_info("Cleaning up Module\n");
	unregister_chrdev(sleepy_major, "sleepy");
}

module_init(sleepy_init);
module_exit(sleepy_cleanup);
