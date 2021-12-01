***************************sema.c**********************************************
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // required for various structures related to files liked fops.
#include <asm/uaccess.h> // required for copy_from and copy_to user functions
#include <linux/semaphore.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>


static int Major;
char flag='y';
struct task_struct *task;
struct device {
    char array[100];
    struct semaphore sem;
}char_arr;

int open(struct inode *inode, struct file *filp)
{
   
    printk(KERN_INFO "Inside open \n");
    task = current;                 // Saving the task_struct for future use.
    if(down_interruptible(&char_arr.sem)) {
        printk(KERN_INFO " could not hold semaphore");
        return -1;
    }
    return 0;
}

int release(struct inode *inode, struct file *filp) {
    printk (KERN_INFO "Inside close \n");
    printk(KERN_INFO "Releasing semaphore");
    up(&char_arr.sem);
    return 0;
}

ssize_t read(struct file *filp, char *buff, size_t count, loff_t *offp) {
    unsigned long ret;
    printk("Inside read \n");
    ret = copy_to_user(buff, char_arr.array, count);
    return ret;
}

ssize_t write(struct file *filp, const char *buff, size_t count, loff_t *offp) {   
    unsigned long ret;
    printk(KERN_INFO "Inside write \n");
    ret =    copy_from_user(char_arr.array, buff, count);
    return ret;
}
int hold(char *buf,char **start,off_t offset,int count,int *eof,void *data )
{
int len=0;
down_interruptible(&char_arr.sem);   // holding the semaphore
printk(KERN_INFO "Inside hold");
return len;
}

int remove(char *buf,char **start ,off_t offset,int count,int *eof,void *data )
{
int len=0;
/* according to linux/sched.h the value of state and their meanings are
-1 unrunnable, 0 runnable, >0 stopped*/

printk(KERN_INFO "State before= %i", task->state);  // printing the state of user process
up(&char_arr.sem);
printk(KERN_INFO "Inside remove");
printk(KERN_INFO "State after = %i", task->state); // printing the state of user process

return len;
}


void create_new_proc_entry()
{
create_proc_read_entry("hold",0,NULL,hold,NULL);
create_proc_read_entry("remove",0,NULL,remove,NULL);
}

struct file_operations fops = {
    read:        read,
    write:        write,
    open:         open,
    release:    release
};


struct cdev *kernel_cdev;


int char_arr_init (void) {
    int ret;
    dev_t dev_no,dev;

    kernel_cdev = cdev_alloc();   
     kernel_cdev->ops = &fops;
    kernel_cdev->owner = THIS_MODULE;
    printk (" Inside init module\n");
     ret = alloc_chrdev_region( &dev_no , 0, 1,"chr_arr_dev");
    if (ret < 0) {
        printk("Major number allocation is failed\n");
        return ret;   
    }
   
    Major = MAJOR(dev_no);
    dev = MKDEV(Major,0);

    printk (" The major number for your device is %d\n", Major);
    ret = cdev_add( kernel_cdev,dev,1);
    if(ret < 0 )
    {
    printk(KERN_INFO "Unable to allocate cdev");
    return ret;
    }
    init_MUTEX(&char_arr.sem);

    create_new_proc_entry();
    return 0;
}

void char_arr_cleanup(void) {
    printk(KERN_INFO " Inside cleanup_module\n");
    remove_proc_entry("hold",NULL);
    remove_proc_entry("remove",NULL);
    cdev_del(kernel_cdev);
    unregister_chrdev_region(Major, 1);
}
MODULE_LICENSE("GPL");   
module_init(char_arr_init);
module_exit(char_arr_cleanup);
