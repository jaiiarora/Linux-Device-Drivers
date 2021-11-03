/*
* chardev.c: Crates a read only  char device that says how many times you've read
* from the dev file
*/

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
//#include<asm/uaccess.h>

/* 
 * did not include prototypes
 */

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 80

static int Major;//Major number
static int Device_Open=0;//is it open to check multiple  access

static char msg[BUF_LEN];
static char *msg_Ptr;



//Methods

/* Called when a processs tries to 
 * open device file, like
 * cat/dev/mycharfile"
 */

static int device_open(struct inode *inode, struct file *file)
{
	static int counter=0;
	if (Device_Open)
		return -EBUSY;
	Device_Open++;
	sprintf(msg, "I already told you Hello World!: %d \n", counter++);
	msg_Ptr=msg;
	try_module_get(THIS_MODULE);
	return SUCCESS;
}





static int device_release(struct inode *inode, struct file *file)
{
        
        if (Device_Open)
                return -EBUSY;
        Device_Open--;
        module_put(THIS_MODULE);
        return SUCCESS;
}


static struct file_operations fops={
	.read=NULL,
	.write=NULL,
	.open=device_open,
	.release=device_release
};
/*
 * Called when module is loaded
 */

int init_module(void)
{
	Major=register_chrdev(0,DEVICE_NAME, &fops);

	if (Major<0)
	{
		printk(KERN_ALERT "Registering Driver Failed  with %d \n", Major);
	       return Major;
	}
	printk(KERN_INFO "I was assigned major number %d . TO talk to \n", Major);
	printk(KERN_INFO "the driver, create a dev file with \n");

	return SUCCESS;
}

/* Called
 * when 
 * Unloaded
 */

void cleanup_module(void)
{
	unregister_chrdev(Major, DEVICE_NAME);
	//if (ret<0)
	//	printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
}




