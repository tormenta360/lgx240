// +++++  [5556 Arima] 20160909 Add Hardware Display Function By Edwin
/* Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#define pr_fmt(fmt) "%s: " fmt, __func__

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h>
#include <linux/spinlock.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/arima_interface.h>
#include <linux/time.h>            

#define PROC_ARIMA_INFORMATION_HWVERSION "driver/hw_Version"
#define DRIVER_NAME "Arima_hw"

#define PCBA_ID_5554 0x0 //PCBA ID setting for 5554
#define PCBA_ID_5556 0x2 //PCBA ID setting for 5556
#define PCBA_ID_5557 0x3 //PCBA ID setting for 5557
#define PCBA_ID_5558 0x4 //PCBA ID setting for 5558
#define PCBA_ID_5559 0x5 //PCBA ID setting for 5559
#define PCBA_ID_5560 0x6 //PCBA ID setting for 5560
#define PCBA_ID_5561 0x7 //PCBA ID setting for 5561

#define PCBA_VER_001 0x0 //PCBA Version setting for 001
#define PCBA_VER_002 0x1 //PCBA Version setting for 002
#define PCBA_VER_003 0x2 //PCBA Version setting for 003
#define PCBA_VER_004 0x3 //PCBA Version setting for 004

struct arima_information_st {
	unsigned int hw_version;     
    unsigned int hw_id;            
    spinlock_t arima_spinlock;
	struct device *dev;
};

/*
 * hw_version of file_operation
 */
static int hw_version_read(struct seq_file *buf, void *v)
{
	printk("[Hw Version] BEGIN read by Edwin\n");
	int rc =0;
	struct arima_information_st *arima_info_struct;// = NULL;
    
	// To struct initial
	arima_info_struct = kzalloc(sizeof(struct arima_information_st), GFP_KERNEL);
	memset(arima_info_struct, 0x00, sizeof(struct arima_information_st));
    arima_info_struct->hw_version = 0;
    arima_info_struct->hw_id      = 0;

	seq_printf(buf, "=================================\n");    
    seq_printf(buf, "	      Hardware Display        \n");
    seq_printf(buf, "=================================\n");
	// Detection Arima HW ID
	
	int gpio_list[4] = {83,82,87,99};
	rc = arima_hw_detection( &arima_info_struct->hw_version ,gpio_list,sizeof(gpio_list)/sizeof(gpio_list[0])); 
	if (rc< 0){
		printk("PCBA ID Error\n");
	}
     
	seq_printf(buf,"[PCBA ID GPIO] GPIO99 = %d , GPIO87 = %d , GPIO82 = %d , GPIO83 = %d \n",
										  (arima_info_struct->hw_id & 0x8)>>3,
								  		  (arima_info_struct->hw_id & 0x4)>>2,
									      (arima_info_struct->hw_id & 0x2)>>1,
										  (arima_info_struct->hw_id & 0x1)>>0);
	// Select PCBA_ID
	switch(arima_info_struct->hw_id){
		case PCBA_ID_5554 :
   	        seq_printf(buf, "[PCBA ID]      : 5554 \n");
			break;
		case PCBA_ID_5556 :
			seq_printf(buf, "[PCBA ID]      : 5556 \n");
			break;
		case PCBA_ID_5557 :
			seq_printf(buf, "[PCBA ID]      : 5557 \n");
			break;
		case PCBA_ID_5558 :
			seq_printf(buf, "[PCBA ID]      : 5558 \n");
			break;
		case PCBA_ID_5559 :
			seq_printf(buf, "[PCBA ID]      : 5559 \n");
			break;
		case PCBA_ID_5560 :
			seq_printf(buf, "[PCBA ID]      : 5560 \n");
			break;
		case PCBA_ID_5561 :
			seq_printf(buf, "[PCBA ID]      : 5561 \n");
			break;
	    default :
		    seq_printf(buf, "[PCBA ID]      : No Match\n");
			break;
	}

	// Detection Arima HW Version
	int gpio_list2[3] = {86,12,7};
    rc = arima_hw_detection(&arima_info_struct->hw_version, gpio_list2,sizeof(gpio_list2)/sizeof(gpio_list2[0]));
	if (rc< 0){
		printk("PCBA ID Error\n");
	}

	seq_printf(buf,"\n");
	seq_printf(buf,"[PCBA Version GPIO] GPIO07 = %d , GPIO12 = %d , GPIO86 = %d  \n",
						(arima_info_struct->hw_version & 0x4)>>2,
						(arima_info_struct->hw_version & 0x2)>>1,
					    (arima_info_struct->hw_version & 0x1)>>0);

    // Select PCBA_VERSION
	switch(arima_info_struct->hw_version){
		case PCBA_VER_001 :
			seq_printf(buf, "[PCBA Version] : 001 \n");
			break;
		case PCBA_VER_002 :
			seq_printf(buf, "[PCBA Version] : 002 \n");
			break;
		case PCBA_VER_003 :
			seq_printf(buf, "[PCBA Version] : 003 \n");
			break;
		case PCBA_VER_004 :
			seq_printf(buf, "[PCBA Version] : 004 \n");
			break;
	    default :
		    seq_printf(buf, "PCBA Version : No Match\n");
			break;
	}

	printk( "[Hw Version] END read \n");
	return 0;
}


static int hw_version_open(struct inode *inode, struct file *file)
{
    printk("[Hw Version] open file \n");
	return single_open(file, hw_version_read, NULL);
}

static const struct file_operations hw_version_fops = {
	.owner = THIS_MODULE,
	.open  = hw_version_open,
	.read  = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

/*
 * Creat node
 */
static void arima_create_proc_file(void)
{
	struct proc_dir_entry *arima_hwVersion_entry;     //For hw_version
    printk("[Hw Version] Start create proc node\n");	
	
	arima_hwVersion_entry = proc_create(PROC_ARIMA_INFORMATION_HWVERSION, 0666, NULL, &hw_version_fops);
	if(arima_hwVersion_entry) {
		printk(KERN_INFO "[Hw Version] - %s create Hw Version Done !\n", __func__);
	}
	printk("[Hw Version] End create proc node\n");
}

 static const struct of_device_id arima_hwVersion_ids[]  = {
	{ .compatible = "arima,arima_hwVersion" },
	{}
};

static struct platform_driver arima_hwVersion_platform_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.owner= THIS_MODULE,
		.of_match_table = arima_hwVersion_ids,
	},
	.probe = arima_create_proc_file,
};

static int __init arima_hwVersion_init(void) {
    printk(KERN_ERR "[Hw Version] Driver Register \n");

    int pr = 0;
	pr  = platform_driver_register(&arima_hwVersion_platform_driver);
   
	if(pr) {
		printk(KERN_ERR "[Hw Version] - %s failed to load\n", __FUNCTION__);
	}
	return pr;
}

static void __exit arima_hwVersion_exit(void){ 
	printk(KERN_ERR "[Hw Version] Unloading Arima Hw Version \n");
	platform_driver_unregister( &arima_hwVersion_platform_driver );
}

module_init(arima_hwVersion_init);
module_exit(arima_hwVersion_exit);

MODULE_DESCRIPTION("Arima Hardware version");
MODULE_AUTHOR("Edwin Huang");
MODULE_LICENSE("GPL");

// -----  [5556 Arima] 20160909 Add Hardware Display Function By Edwin
