//bare scull  char module


#include <linux/config.h>
#include <linux/module.h> //for modules
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h> //printk
#include <linux/slab.h> //kmalloc
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/seq_file.h>
#include <linux/cdev.h>

#include <asm/system.h>
#include <asm/uaccess.h>
#include "scull.h"

/*
 * Load time paramters
 */

int scull_major = SCULL_MAJOR;
int scull_minor = 0;
int scull_nr_devs = SCULL_NR_DEVS;
int scull_quantum = SCULL_QUANTUM;
int scull_qset = SCULL_QSET;

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_nr_devs, int, S_IRUGO);
module_param(scull_quantum, int, S_IRUGO);
module_param(scull_qset, int, S_IRUGO);

MODULE_AUTHOR("Jai Arora");
MODULE_LICENSE("Dual BSD/GPL");

struct scull_dev* scull_devices;


/*
 * Empty out the scull device
 */

int scull_trim(struct scull_dev* dev)
{
	struct sscull_qset *next, *dptr;
	int qset=dev->qset;
	int i;
	//iterating all qsets
	for (dptr=dev->data;  dptr; dptr=next)
	{
		if (dptr->data)
		{
			for (i=0; i<qset; i++)
			{
				//free all quantums
				kfree(dptr->data[i]);
			}
			//free  the data array itself
			kfree(dptr->data)
			dptr->data=NULL;
		}
		next=dptr->next;
		kfree(dptr);
	}
	dev->size=0;
	dev->quantum=scull_quantum;
	dev_qset=scull_qset;
	dev->data=NULL;
	return 0;
}


/*
 * Open and close calls
 */

int scull_open(struct inode* inode, struct file* filp)
{
	struct scull_dev* dev;
	dev=container_of(inode->i_cdev, struct scull_dev, cdev);
	filp->private_data=dev;

	if ((filp->f_flags & O_ACCMODE)==O_WRONLY){
		if (down->interruptible(&dev->sem))
			return -ERESTARTSYS;
		scull_trim(dev);
		up(&dev->sem);
	}
	return 0;
}



