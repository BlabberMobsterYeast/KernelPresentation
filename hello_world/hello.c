#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init start(void)
{
  printk(KERN_INFO "Loading module...");
  printk(KERN_INFO "Hello world...");
  return 0;
}

static void __exit end(void){
  printk(KERN_INFO "Bye world");
}

module_init(start);
module_exit(end);
