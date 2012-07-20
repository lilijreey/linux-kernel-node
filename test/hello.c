/*
 * =====================================================================================
 *
 *       Filename:  hello.c
 *
 *    Description:  A hello device module
 *
 *        Created:  07/18/2012 02:45:40 PM
 *         Author:  YOUR NAME (), 
 *
 * =====================================================================================
 */

#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual DSD/GPL");

static int hello_init(void)
{
    printk(KERN_ALERT "Hello, device\n");
    return ;
}

static void hello_exit(void)
{
    printk(KERN_ALERT, "Goodbye, cruel device\n");
}

module_init(hello_init);
module_exit(hello_exit);
