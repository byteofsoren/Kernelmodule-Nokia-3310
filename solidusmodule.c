#include <linux/module.h>      // Standard header files.
#include <linux/kernel.h>
#include <linux/fs.h>          // This allows the module to read write to files
#include <linux/cdev.h>        // This is the char driver
#include <linux/semaphore.h>   // Gives the program acces to semaphores.
#include <linux/uaccess.h>     // copy to and from userspaces


// (1) create a fake device that we use to store data.
struct my_device{
    char data[100];
    struct semaphore sem;  // Used to prevent coruption from the device.
} virtual_device;


// (2) To later register our divice ve need a cdev object and some other
// variables to store information in.
struct cdev *mcdev;     // The M stands for my.
int major_number;       // The devices major number
int ret;                // Used to store the return value from functions.
                        // Used as global bceause kernel mode have smal stack.
dev_t dev_num;          // Whill hold the major number the kernel give us.
                        // name--> appere in /proc/devices
#define DEVICE_NAME     "solidusmodule"

static int driver_entry(void)
{
    // (3) Register the device with the system, this is a two stepp process.
    //  1.  use dynamic allocation to assign our device
    //      a major number -- alloc_chrdev_region
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    //  Arguments for alloc_chrdev_region:
    //  dev_num:    The structure that stores device numbers.
    //  0:          Start of the minor numer
    //  1:          End minor number.
    //  DEVICE_NAME Defined above to the name of our device

    // Now we need to check if the kernel sucessfoly loaded the module
    if (ret < 0) {
        printk(KERN_ALERT, "solidus: failed to allocate major_number");
        return ret;
    }
    major_number = MAJOR(dev_num);
    printk(KERN_INFO, "Solidus: Major number is %d", major_number);
    printk(KERN_INFO, "\tuse \"mknod /dev/%s c %d 0\" for device file", DEVICE_NAME, major_number);

    // 2. Now the secound step is to alocate the devicedriver to use the file.
    mcdev = cdev_alloc();           // Creates our cdev struct.
//    mcdev->ops = &fops;           // Noc created yet but user for file
//    operations
    mcdev->owner = THIS_MODULE;     // << What is this?
    // Now we have created our struct its time to add it to the kernel.
    ret = cdev_add(mcdev, dev_num, 1);
    // Allways check for errors.
    if (ret < 0) {
        printk(KERN_ALERT, "Solidus: unable to add module to kernel");
        return ret;
    }
    // (4) initiliase the semiphore.
    sema_init(&virtual_device.sem, 1);

    return 0;
}

static int driver_exit(void)
{
    // This removes the driver from the kernel.
    // This is done in exact reverce order then when we createdit.
    cdev_del(mcdev);
    // (b)
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO, "Solidus removed from the kore");

}
