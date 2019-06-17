#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <asm/uaccess.h>



#define MAJOR_NUM 61
#define MODULE_NAME "led1"

static int iCount =0;
char userChar[1024];

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos){
	printk("Enter Read function\n");
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(get_ds());

	struct file *fp;
	loff_t pos = 0;

	char result[128];

	// LED value
	fp = filp_open("/sys/class/gpio/gpio163/value", O_RDONLY, 0);
	if (fp == NULL) {
		printk("163 value cannot be read\n");
		return -1;
	}
	vfs_read(fp, result, strlen(result), &pos);
	filp_close(fp, NULL);
	pos = 0;
	printk("163 value read OK\n");

	// send the result
	copy_to_user(buf, result, strlen(result));

	set_fs(old_fs);
	return count;
}

static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos){
	printk("Enter Write function\n");

	char input[128];
	copy_from_user(input,buf,strlen(buf));

	if(input[0] == '0' || input[0] == '1'){

		mm_segment_t old_fs;
		old_fs = get_fs();
    	set_fs(get_ds());

		struct file *fp;
		loff_t pos = 0;

		fp = filp_open("/sys/class/gpio/export",O_WRONLY,0);
    
		if(fp == NULL){
			printk("export 163 can't be set\n");
			return -1;
		}

    
    	vfs_write(fp,"163",strlen("163"),&pos);
		filp_close(fp, NULL);
		pos = 0;
		printk("163 export OK\n");

		fp = filp_open("/sys/class/gpio/gpio163/direction",O_WRONLY,0);
	
		if(fp == NULL){
			printk("dir 163 can't be set\n");
			return -1;
		}

		vfs_write(fp,"out",strlen("out"),&pos);
		filp_close(fp,NULL);
		pos = 0;
		printk("163 dir OK\n");

		fp = filp_open("/sys/class/gpio/gpio163/value",O_WRONLY,0);
	
		if(fp == NULL){
			printk("value 163 can't be set\n");
			return -1;
		}

		vfs_write(fp,input,strlen("1"),&pos);
		filp_close(fp,NULL);
		pos = 0;
		printk("163 value OK\n");

		set_fs(old_fs);
	}
	return count;
}

int drv_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg){
	printk("Enter I/O Control function\n");
	return 0;
}

static int drv_open(struct inode *inode, struct file *filp){
	printk("Enter Open function\n");
	return 0;
}

static int drv_release(struct inode *inode, struct file *filp){
	printk("Enter Release function\n");
	return 0;
}

struct file_operations drv_fops =
{
	read:	drv_read,
	write:	drv_write,
	unlocked_ioctl:	drv_ioctl,
	open:	drv_open,
	release:	drv_release,
};

static int demo_init(void){
	if(register_chrdev(MAJOR_NUM, MODULE_NAME, &drv_fops)<0){
		printk("<1> %s can't get major %d\n", MODULE_NAME, MAJOR_NUM);
		return (-EBUSY);
	}
	printk("<1>%s started\n", MODULE_NAME);
	return 0;
}

static void demo_exit(void){
	unregister_chrdev(MAJOR_NUM, MODULE_NAME);
	printk("<1>%s remove\n", MODULE_NAME);
}

module_init(demo_init);
module_exit(demo_exit);