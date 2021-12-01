#include <linux/kernel.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");


static int initfunc(void)
{
	int i=5;
	pr_info("Hello Kernel World \n");
	printk("address of i is 0x	%p\n",&i);
	return 0;
}

static void  mrmv(void)
{
	pr_info("Module removed \n");
}




module_init(initfunc);
module_exit(mrmv);
