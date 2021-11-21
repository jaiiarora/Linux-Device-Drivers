#include <linux/module.h>
#include <linux/types.h>
#include <linux/time.h>


MODULE_LICENSE("GPL/BSD");
MODULE_AUTHOR("Jai Arora");

struct timer_list my_timer;

/*
 * Struct factor for  call mod_timer, Jiff saves currrent jiffies
 */


static struct my_struct {
	int factor;
	unsigned long jiff;
}my_str;

static void timer_response(struct timer_list* tm)
{
	struct my_struct* val=(struct my_struct*) tm;
	printk(KERN_INFO "factor=%u  elapsed time=%lu\n", val->factor, (jiffies - val->jiff));

	/* update data */
	val->factor++;
	val->jiff=jiffies;

	//restart timer
	mod_timer(&my_timer, (jiffies+(val->factor*HZ)));
}


static int __init time_example2_init(void)
{
	printk(KERN_INFO "%s started. HZ =%d\n", __func__, HZ);
	my_str.factor=1;
	my_str.jiff=jiffies;
	timer_setup(&my_timer, timer_response, (unsigned long)& my_str);
	mod_timer(&my_timer, (jiffies+ (1*HZ)));
	return 0;
}

static void __exit time_example2_exit(void)
{
	del_timer_sync(&my_timer);
	printk(KERN_INFO "unloaded\n");
}

module_init(time_example2_init);
module_exit(time_example2_exit);


