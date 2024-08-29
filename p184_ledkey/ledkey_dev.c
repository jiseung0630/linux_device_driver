#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gpio.h>
#include <linux/moduleparam.h>

#define CALL_DEV_NAME "calldev"
#define CALL_DEV_MAJOR 230

#define OFF 0
#define ON 1
#define GPIOCNT 8

static long gpioLedInit(void);
static void gpioLedSet(long);
static void gpioLedFree(void);
static long gpioKeyInit(void);
static long gpioKeyGet(void);
static void gpioKeyFree(void);

static int gpioLed[] = {6,7,8,9,10,11,12,13};
static int gpioKey[] = {16,17,18,19,20,21,22,23};

static int call_open(struct inode *inode,struct file *filp)
{
		int num = MINOR(inode->i_rdev);
		printk("call open->major : %d\n", num);
		num = MAJOR(inode->i_rdev);
		printk("call open->major: %d\n",num);
		return 0;
}
static loff_t call_llseek(struct file *filp, loff_t off, int whence)
{
		printk("call llseek -> off : %08X, whence : %08X\n", (unsigned int)off, whence);
		return 0x23;
}
static ssize_t call_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
		printk("call read -> buf :%08X, count : %08X\n", (unsigned int)buf,count);
    	*buf = (char)gpioKeyGet();
    	printk("key : %#04x\n",(int)*buf);
		return 0x33;
}
static ssize_t call_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
		printk("call write -> buf : %08X, count : %08X \n", (unsigned int)buf, count);
		gpioLedSet((long)*buf);
		return *buf;
}
static long call_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
		printk("call ioctl -> cmd : %08X, arg : %08X \n",cmd, (unsigned int)arg);
		return 0x53;
}
static int call_release(struct inode *inode, struct file *filp)
{
		printk("call release \n");
		return 0;
}
struct file_operations call_fops =
{
		.owner	= THIS_MODULE,
		.llseek	= call_llseek,
		.read	= call_read,
		.write	= call_write,
		.unlocked_ioctl	= call_ioctl,
		.open	= call_open,
		.release	= call_release,
};
static int call_init(void)
{
		int result;
		printk("call call_init \n");
		result = register_chrdev(CALL_DEV_MAJOR,CALL_DEV_NAME, &call_fops);
		if(result < 0) return result;
		long ret = 0;
    	printk("led test module \n");
    	ret = gpioLedInit();
    	if(ret < 0)return ret;
    	ret = gpioKeyInit();
    	if(ret < 0)return ret;
		return 0;
}
static void call_exit(void)
{
		printk("call call_exit \n");
		unregister_chrdev(CALL_DEV_MAJOR,CALL_DEV_NAME);
		printk("Goodbye, world\n");
    	gpioLedSet(0x00);
    	gpioLedFree();
    	gpioKeyFree();

}

static long gpioLedInit(void)
{
    long ret = 0;
    int i;
    char gpioName[10];
    for(i=0;i<GPIOCNT;i++)
    {
        sprintf(gpioName,"gpio%d",gpioLed[i]);
        ret = gpio_request(gpioLed[i],gpioName);
        if(ret < 0) {
            printk("Failed request gpio%d error\n",gpioLed[i]);
            return ret;
        }
    }
    for(i=0;i<GPIOCNT;i++)
    {
        ret = gpio_direction_output(gpioLed[i],OFF);
        if(ret < 0) {
            printk("Failed direction_output gpio%d error\n",gpioLed[i]);
            return ret;
        }
    }
    return ret;
}
static void gpioLedSet(long val)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        gpio_set_value(gpioLed[i],val & (0x1 << i));
//      gpio_set_value(gpioLed[i],(val>>i) & 0x1);
    }

}
static void gpioLedFree(void)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        gpio_free(gpioLed[i]);
    }
}
static long gpioKeyInit(void)
{
    long ret = 0;
    int i;
    char gpioName[10];
    for(i=0;i<GPIOCNT;i++)
    {
        sprintf(gpioName,"gpio%d",gpioKey[i]);
        ret = gpio_request(gpioKey[i],gpioName);
        if(ret < 0) {
            printk("Failed request gpio%d error\n",6);
            return ret;
        }
    }
    for(i=0;i<GPIOCNT;i++)
    {
        ret = gpio_direction_input(gpioKey[i]);
        if(ret < 0) {
            printk("Failed direction_output gpio%d error\n",6);
            return ret;
        }
    }
    return ret;
}
static long gpioKeyGet(void)
{
    long keyData=0;
    long temp;
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        temp = gpio_get_value(gpioKey[i]) << i;
        keyData |= temp;
    }
    return keyData;
}
static void gpioKeyFree(void)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        gpio_free(gpioKey[i]);
    }
}

module_init(call_init);
module_exit(call_exit);
MODULE_LICENSE("Dual BSD/GPL");
