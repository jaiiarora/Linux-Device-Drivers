/*
 * System call stealing sample
 * */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>

#include <linux/sched.h>
#include <asm/uaccess.h>


