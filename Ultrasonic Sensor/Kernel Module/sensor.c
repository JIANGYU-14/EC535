#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/sched.h>
#include <asm/hardware.h>
#include <asm/arch/pxa-regs.h>
#include <asm/gpio.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/checksum.h>
#include <asm-arm/arch/hardware.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/jiffies.h>

#ifndef __KERNEL__
#define __KERNEL__
#endif

#ifndef MODULE
#define MODULE
#endif

#ifndef _LINUX_TIME_H
#define _LINUX_TIME_H
#endif

MODULE_LICENSE("Dual BSD/GPL");

static void sensor_exit(void);
static int sensor_init(void);
static int sensor_open(struct inode *inode, struct file *filp);
static int sensor_release(struct inode *inode, struct file *filp);
static ssize_t sensor_read(struct file *filp,
		char *buf, size_t count, loff_t *f_pos);
static ssize_t sensor_write(struct file *filp,
		const char *buf, size_t count, loff_t *f_pos);

static int sensor_major = 61;

const int trigPin = 28;
const int echoPin = 117;

module_init(sensor_init);
module_exit(sensor_exit);

static int duration = 0;
static int distance = 10000;
static int flag = 0;

static struct timeval start, end;
static struct timer_list mycounter;
void counter_callback(unsigned long data);

static unsigned int irqnum1;
static unsigned int irqnum2;
static irq_handler_t handler1(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t handler2(unsigned int irq, void *dev_id, struct pt_regs *regs);

struct file_operations sensor_fops = {
	read: sensor_read,
	write: sensor_write,
	open: sensor_open,
	release: sensor_release
};

static int sensor_init(void)
{
	int result;
	result = register_chrdev(sensor_major, "sensor", &sensor_fops);
	if (result < 0)
	{
		printk(KERN_ALERT
			"sensor: cannot obtain major number %d\n", sensor_major);
		return result;
	}
	
	pxa_gpio_mode( 117 | GPIO_IN );
	pxa_gpio_mode( 118 | GPIO_IN );	
	pxa_gpio_mode( trigPin | GPIO_OUT );
	pxa_gpio_mode( 29 | GPIO_OUT );
	pxa_gpio_mode( 30 | GPIO_OUT );
	pxa_gpio_mode( 31 | GPIO_OUT );

	irqnum1 = gpio_to_irq(117);
	irqnum2 = gpio_to_irq(118);
	
	//if (request_irq(irqnum1, (irq_handler_t) handler1, IRQF_TRIGGER_RISING,"handler1", NULL) == 0)
	//{
		setup_timer(&mycounter, counter_callback, 0);
		mod_timer(&mycounter, jiffies + msecs_to_jiffies(1000));
	//}
	result = request_irq(irqnum1, (irq_handler_t) handler1, IRQF_TRIGGER_RISING,"handler1", NULL);    
    	result = request_irq(irqnum2, (irq_handler_t) handler2, IRQF_TRIGGER_FALLING,"handler2", NULL);  

	printk(KERN_ALERT "Inserting sensor module\n"); 

	
	return 0;
}
static void sensor_exit(void)
{
	del_timer(&mycounter);	
	free_irq(irqnum1,NULL);
	free_irq(irqnum2,NULL);
	
	unregister_chrdev(sensor_major, "sensor");
		
	printk(KERN_ALERT "Removing sensor module\n");
}
static int sensor_open(struct inode *inode, struct file *filp)
{
	//printk("Sensor file opened\n");
	return 0;
}

static int sensor_release(struct inode *inode, struct file *filp)
{
	//printk("Sensor file released\n");
	return 0;
}
static irq_handler_t handler1(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
	do_gettimeofday(&start);
	//printk(KERN_INFO "Echo start, %ld\n", start.tv_usec);
	return (irq_handler_t) IRQ_HANDLED;      
}

static irq_handler_t handler2(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
	do_gettimeofday(&end);
	//printk(KERN_INFO "Echo end, %ld\n", end.tv_usec);
	duration = end.tv_usec - start.tv_usec;
	distance = (duration*340/20000); //Unit in cm
	if (distance < 300 && distance > 0)
	{
	//printk(KERN_INFO "Target Detected, Distance is %dcm\n", distance);
	}
	return (irq_handler_t) IRQ_HANDLED;      
}
static ssize_t sensor_read(struct file *filp, char *buf, 
							size_t count, loff_t *f_pos)
{
	char msg[512];
	char *tbuf = msg;

	if (flag == 0){
		flag = 1;
		return 0;
	}
	
	//duration = end.tv_usec - start.tv_usec;
	//distance = (duration*340/20000); //Unit in cm
	if (distance < 300 && distance > 0)
	{
	sprintf(tbuf, "%d\n", distance);
	}
	else
	{
	sprintf(tbuf, "0\n");
	}
	if (copy_to_user(buf, msg + *f_pos , count))
		{	
			return -EFAULT;
		}

	//printk(KERN_INFO "Distance is %dcm\n", distance);
	
	if (flag == 1){
		flag = 0;
	}
	return 0;
}
static ssize_t sensor_write(struct file *filp, const char *buf,
							size_t count, loff_t *f_pos)
{
	return 0;
}
void counter_callback(unsigned long data){
	gpio_set_value( trigPin,0);
	udelay(20);
	gpio_set_value( trigPin,1);
	udelay(20);
	gpio_set_value( trigPin,0);
	mod_timer(&mycounter, jiffies + msecs_to_jiffies(1000));
	//printk(KERN_INFO "TRIGGGGGGG\n");
}	


