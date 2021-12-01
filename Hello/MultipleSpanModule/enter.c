#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void)
{
	pr_info("Hello Kernel World!");
	return 0;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("JAI ARORA");

