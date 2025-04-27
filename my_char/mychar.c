#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/device.h>
#include<linux/ioctl.h>


//Define Macros

#define DEVICE_NAME "mychar"
#define BUFFER_SIZE 100
#define CLASS_NAME "myclass"

#define MY_IOCTL_MAGIC 'x'
#define IOCTL_RESET _IO(MY_IOCTL_MAGIC, 0)
#define IOCTL_GET_STATUS _IOR(MY_IOCTL_MAGIC, 1, int)
#define IOCTL_SET_STATUS _IOW(MY_IOCTL_MAGIC, 2, int)

static dev_t dev;
static struct cdev my_cdev;
static char kernel_buffer[BUFFER_SIZE];
static struct class *my_class;
static struct device *my_device;
static int device_status = 0;


// Open function
static int my_open(struct inode *inode, struct file *file) {
    pr_info("mychar: Device opened\n");
    return 0;
}

// Read function
ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    int data_size = strlen(kernel_buffer);

    if (*offset >= data_size) {
        return 0; // 📢 Important: Send EOF if already read
    }

    if (len > data_size - *offset)
        len = data_size - *offset; // Read only available data

    if (copy_to_user(buf, kernel_buffer + *offset, len) != 0)
        return -EFAULT;

    *offset += len; // Move file pointer
    return len;     // Return number of bytes read
}
// Write function
static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos) {
    pr_info("mychar: Write requested\n");
    copy_from_user(kernel_buffer, buf, BUFFER_SIZE);
    return BUFFER_SIZE;
}

// Release (close) function
static int my_release(struct inode *inode, struct file *file) {
    pr_info("mychar: Device closed\n");
    return 0;
}

long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd) {
        case IOCTL_RESET:
            device_status = 0;
            pr_info("IOCTL: Device reset\n");
            break;

        case IOCTL_GET_STATUS:
            if (copy_to_user((int __user *)arg, &device_status, sizeof(device_status)))
                return -EFAULT;
            pr_info("IOCTL: Get status = %d\n", device_status);
            break;

        case IOCTL_SET_STATUS:
            if (copy_from_user(&device_status, (int __user *)arg, sizeof(device_status)))
                return -EFAULT;
            pr_info("IOCTL: Set status = %d\n", device_status);
            break;

        default:
            return -EINVAL;
    }
    return 0;
}
// File operations structure
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .read = my_read,
    .write = my_write,
    .release = my_release,
    .unlocked_ioctl = my_ioctl
};

// Module Init
static int __init mychar_init(void) {
    // Allocate device number
    alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    pr_info("mychar: Major = %d Minor = %d\n", MAJOR(dev), MINOR(dev));

    // Initialize cdev
    cdev_init(&my_cdev, &fops);

    // Add cdev
    cdev_add(&my_cdev, dev, 1);

    my_class = class_create(THIS_MODULE, CLASS_NAME);
    my_device = device_create(my_class, NULL, dev, NULL, DEVICE_NAME);

    return 0;
}

// Module Exit
static void __exit mychar_exit(void) {
    device_destroy(my_class, dev);
    class_unregister(my_class);
    class_destroy(my_class);
    cdev_del(&my_cdev);               // Delete character device
    unregister_chrdev_region(dev, 1);  // Free major/minor number
    pr_info("mychar: Module unloaded\n");
}

module_init(mychar_init);
module_exit(mychar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siva Kumar<sivakumar.bs@gmail.com>");
MODULE_DESCRIPTION("Simple Character Device Driver Example");
