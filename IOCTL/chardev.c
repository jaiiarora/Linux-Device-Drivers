#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>

#include "chardev.h"

#define SUCCESS  0
#define DEVICE_NAME  "char_dev"
#define BUF_LEN 80

enum{
	CDEV_NOT_USED=0,
	CDEV_EXCLUSIVE_OPEN=1,
};

static atomic_t already_open=ATOMIC_INIT(CDEV_NOT_USED);

//message given by device when asked
static char message[BUF_LEN];
static struct class *cls;

static int device_open(struct inode* inode, struct file* file)
{
	pr_info("device_open(%p)\n", file);
	try_module_get(THIS_MODULE);
	return SUCCESS;
}

static int device_release(struct inode* inode, struct file* file)
{
	pr_info("device_release(%p,%p)\n", inode, file);
	return SUCCESS;
}


static ssize_t  device_read(struct file* file, char __user* buffer, size_t length, loff_t* offset)
{
	int bytes_read=0;
	const char* message_ptr=message;
	if (!*(message_ptr+*offset)){
		*offset=0;
		return 0;
	}
	message_ptr+=*offset;
	while (length && *(message_ptr))
	{
		put_user(*(message_ptr++),  buffer++);
		length--;
		bytes_read++;
	}
	pr_info("Read %d bytes, %ld left\n", bytes_read,  length);
	*offset+=bytes_read;
	return bytes_read;
}

static ssize_t device_write(struct file* file, const char __user* buffer, size_t length,  loff_t* offset)
{
	int i=0;
	pr_info("device_write(%p,%p,%ld", file,  buffer, length);
	for (i=0;i<length;i++)
	{
		get_user(message[i],buffer+i);

	}
	return i;
}


static long device_ioctl(struct file* file, unsigned int ioctl_num, unsigned long ioctl_param)
{
	int i;
	long ret=SUCCESS;

	//SETTING ATOMICITY
	if (atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN))
		return -EBUSY;

	switch(ioctl_num)
	{
		case IOCTL_SET_MSG:{
					   char __user* temp=(char __user*) ioctl_param;
					   char ch;
					   get_user(ch, temp);
					   for (i=0; ch&& i<BUF_LEN; i++, temp++)
						   get_user(ch, temp);
					   device_write(file, (char __user*)ioctl_param
							   , i, NULL);
					   break;
						   
}


	case IOCTL_GET_MSG:{
				   loff_t offset=0;
				   i=device_read(file, (char __user*)ioctl_param, 99, &offset);
				   put_user('\0',  (char __user*)ioctl_param+i);
				   break;
			   }
	}
	atomic_set(&already_open, CDEV_NOT_USED);
	return ret;
}
static struct file_operations fops = {
		.read=device_read,
		.write=device_write,
		.unlocked_ioctl=device_ioctl,
		.release=device_release,
		.open=device_open,
	};

static int chardev2_init(void)
{
	int ret_val= register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
       	if (ret_val<0)
	{
		pr_alert("%s failed with %d\n","Registering vhar device failed", ret_val);
		return ret_val;
	}
	cls= class_create(THIS_MODULE, DEVICE_FILE_NAME);
	device_create(cls,  NULL, MKDEV(MAJOR_NUM, 0), NULL, DEVICE_FILE_NAME);
	pr_info("Device create don /dev/%s\n", DEVICE_FILE_NAME);
	return 0;

}
		

static void __exit chardev2_exit(void)
{
	device_destroy(cls,  MKDEV(MAJOR_NUM, 0));
	class_destroy(cls);
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);

}


module_init(chardev2_init);
module_exit(chardev2_exit);

MODULE_LICENSE("GPL");


