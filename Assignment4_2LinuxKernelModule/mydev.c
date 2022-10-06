

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define  DEVICE_MAJOR 0         ///< Requested device node major number or 0 for dynamic allocation
#define  DEVICE_NAME "mydev1"   ///< In this implementation, the device name has nothing to do with the name of the device in /dev. You must use mknod to create the device node in /dev

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Steinarr Hrafn");
MODULE_DESCRIPTION("A simple Linux LKM that accepts characters (bytes) from the user.");
MODULE_VERSION("0.1");

static int   majorNumber;        ///< Stores the device number -- determined automatically
static int   numberOpens = 0;    ///< Counts the number of times the device is opened
static char *name = "world";

module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");

// The prototype functions for the character driver -- must come before the struct definition
static int     mydev_open(struct inode *, struct file *);
static int     mydev_release(struct inode *, struct file *);
static ssize_t mydev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops =
{
   .open = mydev_open,
   .write = mydev_write,
   .release = mydev_release,
};

static ssize_t mydev_write(struct file * file, const char *buf, size_t count, loff_t *ppos)
{
   printk("mydev write: accepting %zu bytes from the user\n", count);
   return count;
}

static int mydev_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "mydev: Device successfully closed\n");
   return 0;
}

static int __init mydev_init(void) {
   printk(KERN_INFO "mydev: Hello %s from the RPi LKM!\n", name);
   majorNumber = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &fops);
   if (majorNumber<0){
      printk(KERN_ALERT "mydev failed to register a major number\n");
      return majorNumber;
   }
   printk(KERN_INFO "mydev: Device registered correctly with major number %d\n", majorNumber);
   return 0;
}

static void __exit mydev_exit(void) {
   unregister_chrdev(majorNumber, DEVICE_NAME);
   printk(KERN_INFO "mydev: Goodbye %s from the RPi LKM!\n", name);
}

static int mydev_open(struct inode *inodep, struct file *filep){
   numberOpens++;
   printk(KERN_INFO "mydev: Device has been opened %d time(s)\n", numberOpens);
   return 0;
}

module_init(mydev_init);
module_exit(mydev_exit);



