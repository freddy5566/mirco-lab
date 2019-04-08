#include <linux/kernel.h>
#include <linux/module.h>
static int __init lab5_hello_module_init(void)
{
    printk("lab5 installed");
    return 0;
}
static void __exit lab5_hello_module_cleanup(void)
{
	printk("lab5 exit");
}
module_init(lab5_hello_module_init);
module_exit(lab5_hello_module_cleanup);
MODULE_LICENSE("GPL");
