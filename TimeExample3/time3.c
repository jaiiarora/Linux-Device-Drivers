#include <linux/module.h>
#include <linux/types.h>
#include <linux/timer.h>
#include <linux/moduleparam.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>

#define CAPS_LED 4

MODULE_LICENSE("GPL/BSD");
MODULE_AUTHOR("Jai Arora");


static struct timer_list my_timer;

static int blink_rate=2;

static struct my_struct{
	unsigned char status_led;
}my_str;

module_param(blink_rate, int, S_IRUSR | S_IWUSR);

static void timer_response(struct timer_list* my_timer)
{
	int ret;
	if (blink_rate<=0)
	{
		printk(KERN_ERR "Blink Rate is negative! Error");
		return;
	}
	/*Turn led ON/OFF
	 * Read keyboard status
	 */
	while ((inb(0x64)&2)!=0){}
	/*SEND COMMAND 0xED to port to  sset led*/

	outb(0xED, 0x60);
	//read status again
	while ((inb(0x64)&2)!=0){}
	/*Send value to LED on keyboard*/

	outb(my_str.status_led, 0x60);
	my_str.status_led = my_str.status_led ^ CAPS_LED;
	ret=mod_timer(my_timer, ((jiffies/blink_rate)+HZ));
}


static int __init time_example2_init(void)
{
	int ret;
	printk(KERN_INFO "%s started,HZ=%d \n", __func__, HZ);
	my_str.status_led=0;
	timer_setup(&my_timer,timer_response,0);
	ret=mod_timer(&my_timer, ((jiffies/blink_rate)+(1*HZ)));
	if (ret)
		printk(KERN_INFO "Error in mod_timer \n");
	return 0;
}

static void __exit time_example2_exit(void)
{
	del_timer_sync(&my_timer);
	printk(KERN_INFO "unloaded \n");
}

module_init(time_example2_init);
module_exit(time_example2_exit);
