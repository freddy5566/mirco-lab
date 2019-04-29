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

int gpio_export(unsigned int gpio){
    struct file *fd;
	loff_t pos = 0;
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(get_ds());

	int len;
    char buf[64];
	
    fd = filp_open("/sys/class/gpio/export", O_WRONLY, 0);
	printk("open file!!!\n");

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    vfs_write(fd, buf ,len, &pos);
    filp_close(fd, NULL); //close file

    return 0;
	set_fs(old_fs);
}

int gpio_unwxport(unsigned int gpio){
	struct file *fd;    
	loff_t pos = 0;
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(get_ds());
	int len;
    char buf[64];

    fd = filp_open("/sys/class/gpio/export", O_WRONLY, 0);
 
    len = snprintf(buf, sizeof(buf), "%d", gpio);
    vfs_write(fd, buf ,len, &pos);
    filp_close(fd, NULL); //close file
	set_fs(old_fs);

    return 0;

}

int gpio_set_dir(unsigned int gpio, char* dirStatus){
    struct file *fd;    
	loff_t pos = 0;
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(get_ds());
    char buf[64];

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);
    fd = filp_open(buf, O_WRONLY, 0);

    if (strcmp("out", dirStatus)){
        vfs_write(fd, "out", 4, &pos);
    }
    else
        vfs_write(fd, "in", 3, &pos);

    filp_close(fd, NULL);
	set_fs(old_fs);
    return 0;
}

void gpio_print_result(int value, char[] LED) {
	char onOrOff[10];
	onOrOff = value == 1 ? "on" ? "off";
	printk("%s %s\n", value, onOrOff);
}

int gpio_set_value(unsigned int gpio, int value) {
    struct file *fd;   
	loff_t pos = 0;
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(get_ds());
    char buf[64];
	
    switch (gpio) {
    case 166:
		gpio_print_result(value, "LED1");
        break;
    case 164:
        gpio_print_result(value, "LED2");
        break;
    case 162:
		gpio_print_result(value, "LED3");
        break;
    case 160:
		gpio_print_result(value, "LED4");
        break;
    default:
        break;
    }

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
    fd = filp_open(buf, O_WRONLY, 0);

    if (value == 0)
        vfs_write(fd, "0", 2, &pos);
    else
        vfs_write(fd, "1", 2, &pos);

    filp_close(fd, NULL);
	set_fs(old_fs);
    return 0;
}

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
	
	gpio_export(166);
    gpio_export(164);
    gpio_export(162);
    gpio_export(160);
    gpio_set_dir(166, "out");
    gpio_set_dir(164, "out");
    gpio_set_dir(162, "out");
    gpio_set_dir(160, "out");

	char LED[99];
	char action;
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		LED[i] = buf[i];
	}

	action = buf[3];

	printk("LED:%s\n action: %s\n", LED, action);

	long* gpio;
	kstrtol(LED, 10, gpio);
	gpio_set_dir(*gpio, "out");
	gpio_set_value(*gpio, action -'0');

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



