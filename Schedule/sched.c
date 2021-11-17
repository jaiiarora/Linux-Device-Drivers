/*
sched.c => calls a  function at every timer interrupt
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/workqueue.h> //for scheduling tasks
#include <linux/sched.h> //need to put process to sleep and execute later

#include <linux/init.h>
#include <linux/interrupt.h>

#define PROC_ENTRY_FILENAME "sched"
#define MY_WORK_QUEUE_NAME "WQsched.c"
struct proc_dir_entry* Our_Proc_File;

static int TimerIntrpt=0;
static void intrpt_routine(void*);

static int die=0; /* set to 1 for shutdown */
