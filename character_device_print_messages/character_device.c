#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

// based on tutorial from https://www.youtube.com/watch?v=CWihl19mJig

#define DEVICE_NAME "my_character_device"

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

static struct file_operations fops = {
  .open = dev_open,
  .read = dev_read,
  .write = dev_write,
  .release = dev_release
};

static int major;

static int __init myinit(void){
  major = register_chrdev(0, DEVICE_NAME, &fops);
  if(major < 0){
    printk(KERN_ALERT "Character device module load failed.\n");
    return major;
  }

  printk(KERN_INFO "Character device module has been loaded with major: %d.\n", major);

  return 0;
}

static void __exit myexit(void){
  printk(KERN_INFO "Character device module has been unloaded.\n");
  
}

module_init(myinit);
module_exit(myexit);


static int dev_open(struct inode* inodep, struct file *filep){
  printk(KERN_INFO "Character device opened.");
  return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
  printk(KERN_INFO "Sorry, character device is read only.");
  return -EFAULT;
}

static int dev_release(struct inode *inodep, struct file *filep){
  printk(KERN_INFO "Character device closed.");
  return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
  int errors = 0;
  char *message = "You are reading character stream from fake device.";
  int message_len = strlen(message);

  errors = copy_to_user(buffer, message, message_len);


  return errors == 0 ? message_len : -EFAULT;
}


