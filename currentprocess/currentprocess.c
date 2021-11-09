#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

static int current_task_init(void)
{
    
    pr_info("Current Process Pointer is %p: \n",current);
    return 0;
}

static void test_tasks_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

MODULE_LICENSE("GPL");
module_init(current_task_init);
module_exit(test_tasks_exit);
