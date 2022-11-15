#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

#define MYMAJOR 90

//based on tutorial from https://www.youtube.com/watch?v=h7ybJMYyqDQ

static int driver_open(struct inode *device_file, struct file *instance){
	printk("dev_nr - open was called!\n");
	return 0;
}

static int driver_close(struct inode *device_file, struct file *instance){
	printk("dev_nr - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close
};



static int __init ModuleInit(void){
	int retval;
	printk("hello, Kernel!\n");
	// registering device nr
	retval = register_chrdev(MYMAJOR, "my_dev_nr", &fops);
	if(retval == 0){
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
	}
	else if(retval > 0){
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", retval >>20, retval & 0xfffff);
	}
	else{
		printk("could not register device number!\n");
		return -1;
	}

	return 0;
}

static void __exit ModuleExit(void){
	unregister_chrdev(MYMAJOR, "my_dev_nr");
	printk("goodbye, Kernel!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
