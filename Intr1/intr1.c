/*
Handles keyboard Interrupts.
Binds to IRQ1
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");


/*
ISR
*/
irqreturn_t irq_handler(int irq, void* dev_id)
{

  //need static variables so that they can be accessed via pointers in bottom half
  static unsigned char scancode;
  unsigned char status;
  /*
  Read status of keyboard
  */
  status=inb(0x64);
  scancode=inb(0x60);
  switch(scancode)
  {
    case 0x01:
      printk(KERN_INFO "! You pressed Esc .. \n");
      break;
    case 0x3B:
      printk(KERN_INFO "! You pressed F1 .. \n");
      break;
    case 0x3C:
      printk(KERN_INFO "! You pressed F2 .. \n");
      break;
    default:
      break;

  }
  return IRQ_HANDLED;
}

//Init function
static int __init irq_ex_init(void)
{
  /*Free Interrupt*/
  free_irq(1,NULL);
  //Reques IRQ1, the keyboard IRQ for our irq_handler
  return request_irq(1, (irq_handler_t)irq_handler, IRQF_SHARED, "test_keyboard_handler", (void*) irq_handler);
}
static void __exit irq_ex_exit(void)
{
  printk(KERN_INFO "!Unloading Module \n");
  free_irq(1,(void*)irq_handler);
}

module_init(irq_ex_init);
module_exit(irq_ex_exit);
