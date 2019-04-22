#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <asm/uaccess.h>

#define MAJOR_NUM 60
#define MODULE_NAME "demo"


static int iCount = 0;
char userChar[1024];


static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
{
	printk("device read\n");
	strcat(userChar," 107598023\n");
	
	copy_to_user(buf, userChar, 1024);
	printk("%s",userChar);
	return count;
}

static ssize_t drv_write(struct file *filp, char *buf, size_t count, loff_t *ppos)
{
	printk("device write\n");
	printk("%d\n", iCount);
	printk("W_buf_size: %d\n", (int)count);
	copy_from_user(userChar, buf, count);
	userChar[count - 1] = 0;

	printk("userChar(chr): %s\n", userChar);
	printk("userChar(int): %d\n", (int)sizeof(userChar));
    strcat(userChar," 107598024");

    printk("%s\n",userChar);
	iCount++;	
	return count;
}

int drv_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("device ioctl\n");
	return 0;
}

static int drv_open(struct inode *inode, struct file *filp)
{
	printk("device open\n");
	return 0;
}

static int drv_release(struct inode *inode, struct file *filp)
{
	printk("device release\n");
	return 0;
}

struct file_operations drv_fops =

{
	read: drv_read,
	write: drv_write,
	unlocked_ioctl: drv_ioctl,
	open: drv_open,
	release: drv_release
};


static int demo_init(void)
{


	if (register_chrdev(MAJOR_NUM, "demo", &drv_fops) < 0 )
	{
		printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM );
		return (-EBUSY);
	}

	printk("<1>%s: started \n", MODULE_NAME);
	return 0;

}



static void demo_exit(void)
{
	unregister_chrdev(MAJOR_NUM, "demo");
	printk("<1>%s: removed\n", MODULE_NAME);
}
module_init(demo_init);
module_exit(demo_exit);



