#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/module.h>
#include <linux/init.h>

static DEFINE_MUTEX(mymutex);

static int example_mutex_init(void)
{
	int ret;
	pr_info("Example mutex init \n");
	ret=mutex_trylock(&mymutex);
	if (ret!=0)
	{

		pr_info("Mutex is locked \n");
		if (mutex_is_locked(&mymutex)==0)
			pr_info("Mutex failed to lock\n");
		int i=1;
		pr_info("Hanging your System \n");
		while (i);
		mutex_unlock(&mymutex);
		pr_info("Mutex Unlocked\n");
	}
	else
		pr_info("Failed to lock\n");
	return 0;
}


static void example_mutex_exit(void)
{
	pr_info("Removing Example mutex Module \n");
}

module_init(example_mutex_init);
module_exit(example_mutex_exit);

MODULE_DESCRIPTION("Mutex Example");
MODULE_AUTHOR("JAI ARORA");
MODULE_LICENSE("GPL");
