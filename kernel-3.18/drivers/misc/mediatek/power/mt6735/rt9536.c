/*
 * Charging IC driver (rt9536)
 *
 * Copyright (C) 2010 LGE, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/kobject.h>
#include <linux/platform_device.h>
#include <asm/atomic.h>
#include <linux/power_supply.h>		// might need to get fuel gauge info
#include <mt-plat/mt_gpio.h>
#include <mt-plat/charging.h>
#include <mt-plat/battery_common.h>
#include <mach/mt_charging.h>
#include "rt9536.h"
#include <linux/gpio.h>
#include <linux/of_gpio.h>

//<2016/12/22 stevenzhang,[LV3][]add spinlock.
static spinlock_t rt9536_irq_lock;
unsigned long rt9536_flags;
//<end

//<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Initialize charger IC rt9536
struct pinctrl *rt9536ctrl = NULL;
struct pinctrl_state *rt9536_set_h = NULL;
struct pinctrl_state *rt9536_set_l = NULL;
struct pinctrl_state *rt9536_eoc_h = NULL;
struct pinctrl_state *rt9536_eoc_l = NULL;
struct pinctrl_state *rt9536_pgb_h = NULL;
struct pinctrl_state *rt9536_pgb_l = NULL;
//<2016/09/15-nickygao

//<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Battery OTP test
#if 0
typedef struct {
	kal_bool bat_exist;
	kal_bool bat_full;
	signed int bat_charging_state;
	unsigned int bat_vol;
	kal_bool bat_in_recharging_state;
	unsigned int Vsense;
	kal_bool charger_exist;
	unsigned int charger_vol;
	signed int charger_protect_status;
	signed int ICharging;
	signed int IBattery;
	signed int temperature;
	signed int temperatureR;
	signed int temperatureV;
	unsigned int total_charging_time;
	unsigned int PRE_charging_time;
	unsigned int CC_charging_time;
	unsigned int TOPOFF_charging_time;
	unsigned int POSTFULL_charging_time;
	unsigned int charger_type;
	signed int SOC;
	signed int UI_SOC;
	signed int UI_SOC2;
	unsigned int nPercent_ZCV;
	unsigned int nPrecent_UI_SOC_check_point;
	unsigned int ZCV;
} PMU_ChargerStruct;

extern PMU_ChargerStruct BMT_status;
#endif
//<2016/09/15-nickygao

//<2016/09/16-nickygao, [LV3][MISC][COMMON][BSP][][]Get rt9536 GPIO node: charger_rt9536_eoc    charger_rt9536_pgb
#if defined(GET_RT9536_GPIO_FROM_DTS)
static int CHARGER_RT9536_EOC;
static int CHARGER_RT9536_PGB;
static int CHARGER_RT9536_SET;

static void rt9536_set_gpio_value(unsigned int GPIO, unsigned int output)
{
        printk("[%s]GPIO=%d\n", __func__, GPIO);
        gpio_direction_output(GPIO, output);
	 gpio_set_value(GPIO, output);
}
#endif
//<2016/09/16-nickygao

static DEFINE_MUTEX(charging_lock);

enum power_supply_type charging_ic_status;

kal_bool chargin_hw_init_done = KAL_FALSE; 

/* Fuction Prototype */
static void charging_ic_initialize(void);
static irqreturn_t charging_ic_interrupt_handler(int irq, void *data);

struct timer_list charging_timer;

enum power_supply_type get_charging_ic_status(void)
{
    return charging_ic_status;
}

// USB500 mode charging
//Stevenzhang 20170122,[LV3][]add usb100,
extern unsigned int g_bcct_flag;
//Stevenzhang 20170122
//<add by xuqin 2017/01/23
extern int arima_usb100_usb500_cycle_flag;

void charging_ic_active_default(void)
{ 
    if (charging_ic_status == POWER_SUPPLY_TYPE_USB)
    {
        printk("[charger_rt9536] :: it's already %s mode!!\n", __func__);
        return;
    }

    if (charging_ic_status != POWER_SUPPLY_TYPE_BATTERY)
    {
        charging_ic_deactive();
    }

    mutex_lock(&charging_lock);
//<2016/12/22 stevenzhang,[LV3][]add spinlock.
	spin_lock_irqsave(&rt9536_irq_lock, rt9536_flags);
//<end
//<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Enable high voltage battery charging: 4.35v USB500mode
#if defined(GET_RT9536_GPIO_FROM_DTS)    //gpio_set_value
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    udelay(400);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(400);  // about 400 us
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    udelay(400);  // about 400 us
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(400);  // about 400 us
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    udelay(400);  // about 400 us
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(400);  // about 400 us
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    udelay(400);  // about 400 us
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(400);  // about 400 us
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    mdelay(2); 
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(850);  // about 400 us
    // 4.35v USB500mode
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    udelay(1500);
#else    //pinctrl_select_state
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(400);
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(400);  // about 400 us
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(400);  // about 400 us
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(400);  // about 400 us
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(400);  // about 400 us
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(400);  // about 400 us
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(400);  // about 400 us
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(400);  // about 400 us
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    mdelay(2); 
    //udelay(2000); 
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(850);  // about 400 us
    // 4.35v USB500mode
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(1500);
#endif
//<2016/09/15-nickygao

    charging_ic_status = POWER_SUPPLY_TYPE_USB;
	
    //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Add charging current
    //BMT_status.ICharging = 500;
    //<2016/09/15-nickygao
//<2016/12/22 stevenzhang,[LV3][]add spinlock.	
	spin_unlock_irqrestore(&rt9536_irq_lock, rt9536_flags);
//<end
    mutex_unlock(&charging_lock);

    printk("[charger_rt9536][v3] :: %s : \n", __func__);

}
EXPORT_SYMBOL(charging_ic_active_default);
// TA connection, ISET mode

void charging_ic_usb100(void)
{ 
    if (charging_ic_status == POWER_SUPPLY_TYPE_WIRELESS)
    {
        printk("[charger_rt9536] :: it's already %s mode!!\n", __func__);
        return;
    }

    if (charging_ic_status != POWER_SUPPLY_TYPE_BATTERY)
    {
        charging_ic_deactive();
    }

    mutex_lock(&charging_lock);
//<2016/12/22 stevenzhang,[LV3][]add spinlock.
	spin_lock_irqsave(&rt9536_irq_lock, rt9536_flags);
//<end
		pinctrl_select_state(rt9536ctrl, rt9536_set_l);
		udelay(400);
		pinctrl_select_state(rt9536ctrl, rt9536_set_h);
		udelay(400);  // about 400 us
		pinctrl_select_state(rt9536ctrl, rt9536_set_l);
		udelay(400);  // about 400 us
		pinctrl_select_state(rt9536ctrl, rt9536_set_h);
		udelay(400);  // about 400 us
		pinctrl_select_state(rt9536ctrl, rt9536_set_l);
		mdelay(2); 
		//udelay(2000); 
		pinctrl_select_state(rt9536ctrl, rt9536_set_h);
		udelay(850);  // about 400 us
		// 4.35v USB500mode
		pinctrl_select_state(rt9536ctrl, rt9536_set_l);
		udelay(1500);
	
    charging_ic_status = POWER_SUPPLY_TYPE_WIRELESS;
	
//<2016/12/22 stevenzhang,[LV3][]add spinlock.	
	spin_unlock_irqrestore(&rt9536_irq_lock, rt9536_flags);
//<end
    mutex_unlock(&charging_lock);

    printk("[charger_rt9536][v3] :g_bcct_flag = %d : %s : \n",g_bcct_flag,__func__);

}
EXPORT_SYMBOL(charging_ic_usb100);






void charging_ic_set_ta_mode(void)
{

    if (charging_ic_status == POWER_SUPPLY_TYPE_MAINS)
    {
        printk("[charger_rt9536] :: it's already %s mode!! : \n", __func__);
        return;
    }

    if (charging_ic_status != POWER_SUPPLY_TYPE_BATTERY)
    {
        charging_ic_deactive();
    }

    mutex_lock(&charging_lock);
//<2016/12/22 stevenzhang,[LV3][]add spinlock.
	spin_lock_irqsave(&rt9536_irq_lock, rt9536_flags);
//<end

//<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Enable high voltage battery charging: 4.35v ISET mode
#if defined(GET_RT9536_GPIO_FROM_DTS)    //gpio_set_value
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    udelay(400);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(400);  // about 400 us
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    mdelay(2); 
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(850);  // about 400 us
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    udelay(1500);
#else    //pinctrl_select_state
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(400);
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(400);  // about 400 us
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    mdelay(2); 
    //udelay(2000);
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(850);  // about 400 us
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(1500);
#endif
//<2016/09/15-nickygao

    //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Add charging current indicator
    //BMT_status.ICharging = 850;
    //<2016/09/15-nickygao

    charging_ic_status = POWER_SUPPLY_TYPE_MAINS;
//<2016/12/22 stevenzhang,[LV3][]add spinlock.	
	spin_unlock_irqrestore(&rt9536_irq_lock, rt9536_flags);
//<end
    mutex_unlock(&charging_lock);

    printk("[charger_rt9536] :: %s : \n", __func__);
}

void charging_ic_set_usb_mode(void)
{
    charging_ic_active_default();
}

void charging_ic_set_factory_mode(void)
{

#if 0
    if(charging_ic_status == POWER_SUPPLY_TYPE_FACTORY)
    {
        printk("Power/Charger", "[charger_rt9536] :: it's already %s mode!! : \n", __func__);
        return;
    }
#endif /* 0 */

    //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Power on without battery
    if (charging_ic_status == POWER_SUPPLY_TYPE_UPS)
    {
        printk("[charger_rt9536] :: it's already %s mode!! : \n", __func__);
        return;
    }

    if (charging_ic_status != POWER_SUPPLY_TYPE_BATTERY)
    {
        charging_ic_deactive();
    }

    mutex_lock(&charging_lock);
//<2016/12/22 stevenzhang,[LV3][]add spinlock.
	spin_lock_irqsave(&rt9536_irq_lock, rt9536_flags);
//<end    
    charging_ic_status =  POWER_SUPPLY_TYPE_UPS;
    	
#if defined(GET_RT9536_GPIO_FROM_DTS)    //gpio_set_value
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    mdelay(10);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(400);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    udelay(400);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(400);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    udelay(400);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(400);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    //mdelay(3);
    udelay(3000);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    udelay(850);//udelay(400);
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 0);
    mdelay(10);
#else    //pinctrl_select_state
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    mdelay(10);
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(400);
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(400);
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(400);
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(400);
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(400);
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    udelay(3000);
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    udelay(850);
    pinctrl_select_state(rt9536ctrl, rt9536_set_l);
    mdelay(10);
#endif
//<2016/09/15-nickygao

#if 0
    charging_ic_status = POWER_SUPPLY_TYPE_FACTORY;
#endif /* 0 */
//<2016/12/22 stevenzhang,[LV3][]add spinlock.	
		spin_unlock_irqrestore(&rt9536_irq_lock, rt9536_flags);
//<end
    mutex_unlock(&charging_lock);

    printk("[charger_rt9536] :: %s : \n", __func__);
}

void charging_ic_deactive(void)
{

    if (charging_ic_status == POWER_SUPPLY_TYPE_BATTERY)
    {
        printk("[charger_rt9536] :: it's already %s mode!! : \n", __func__);
        return;
    }

    mutex_lock(&charging_lock);

    //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Disable charger IC
    #if defined(GET_RT9536_GPIO_FROM_DTS)    //gpio_set_value
    rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
    #else    //pinctrl_select_state
    pinctrl_select_state(rt9536ctrl, rt9536_set_h);
    #endif
    //<2016/09/15-nickygao
    udelay(2000);

    charging_ic_status = POWER_SUPPLY_TYPE_BATTERY;
    //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Add charging current indicator
    //BMT_status.ICharging = 0;
    //<2016/09/15-nickygao
    mutex_unlock(&charging_lock);

    printk("[charger_rt9536] :: %s : \n", __func__);
}
EXPORT_SYMBOL(charging_ic_deactive);

void rt9536_charging_enable(unsigned int set_current, unsigned int enable)
{
    if (enable)
    {
        if (set_current == AC_CHARGER_CURRENT)
            charging_ic_set_ta_mode();
        else if (set_current == USB_CHARGER_CURRENT)
            charging_ic_set_usb_mode();
        //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Battery OTP test
        else if ( set_current == CHARGE_CURRENT_0_00_MA )
            charging_ic_deactive();		
        //<2016/09/15-nickygao
        else if ( set_current == CHARGE_CURRENT_100_00_MA )
            charging_ic_usb100();		
		else
            charging_ic_active_default();

        printk("[charger_rt9536] :: %s, current(%d), enable(%d)\n", __func__, set_current, enable);
    }
    else
    {
        charging_ic_deactive();
        printk("[charger_rt9536] :: %s, enable(%d)\n", __func__, enable);        
    }
    
}

unsigned char rt9536_check_eoc_status(void)
{
    //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Fix issue which status is not stable 
    unsigned char reg_val = 0;
    unsigned char eoc_status0, eoc_status1 = 0;
    unsigned char pgb_status0, pgb_status1 = 0;

    #if !defined(GET_RT9536_GPIO_FROM_DTS)
    //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Add PGB status check
    //mdelay(150);
    mdelay(10);
    pgb_status0 = gpio_get_value(PGB_N);
    //mdelay(150);
    mdelay(10);
    pgb_status1 = gpio_get_value(PGB_N);
    //<2016/09/15-nickygao

    mdelay(150);
    //mdelay(10);
    eoc_status0 = gpio_get_value(CHG_EOC_N);
    mdelay(150);
    //mdelay(10);
    eoc_status1 = gpio_get_value(CHG_EOC_N);

    #else    /* gpio_request */
    //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Add PGB status check
    //mdelay(150);
    mdelay(10);
    pgb_status0 = gpio_get_value(CHARGER_RT9536_PGB);
    //mdelay(150);
    mdelay(10);
    pgb_status1 = gpio_get_value(CHARGER_RT9536_PGB);
    //<2016/09/15-nickygao

    mdelay(150);
    //mdelay(10);
    eoc_status0 = gpio_get_value(CHARGER_RT9536_EOC);
    mdelay(150);
    //mdelay(10);
    eoc_status1 = gpio_get_value(CHARGER_RT9536_EOC);
    #endif

    printk("[charger_rt9536] :: (%s) pgb0=%d, pgb1=%d \n", __func__, pgb_status0, pgb_status1);
    printk("[charger_rt9536] :: (%s) eoc_status0=%d, eoc_status1=%d \n", __func__, eoc_status0, eoc_status1);
    if (eoc_status1 && eoc_status0 
		//<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Add PGB status check
		&& pgb_status0 == 0 && pgb_status1 == 0)
		//<2016/09/15-nickygao
		
    {
        //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Add charging current indicator
        //BMT_status.ICharging = 0; 
        //<2016/09/15-nickygao
        printk("[charger_rt9536] :: (%s) eoc_status is not in charging mode(1)\n", __func__ );
        return 1;
    }
    printk("[charger_rt9536] :: (%s) eoc_status is in charging mode (0)\n", __func__ );
    return 0;
    //<2016/09/15-nickygao
}

#if 1
//<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Add PGB status check
extern unsigned int  ext_charger_status;
unsigned char rt9536_check_charger_status(void)
{
   if (ext_charger_status == 0) 
       return 0;
    unsigned char pgb_status0 = 0; 
    unsigned char pgb_status1 = 0;

    #if !defined(GET_RT9536_GPIO_FROM_DTS)
    //mdelay(150);
    mdelay(10);
    pgb_status0 = gpio_get_value(PGB_N);
    //mdelay(150);
    mdelay(10);
    pgb_status1 = gpio_get_value(PGB_N);

    #else    /* gpio_request */
    //mdelay(150);
    mdelay(10);
    pgb_status0 = gpio_get_value(CHARGER_RT9536_PGB);
    //mdelay(150);
    mdelay(10);
    pgb_status1 = gpio_get_value(CHARGER_RT9536_PGB);
    #endif

    printk("[charger_rt9536] :: (%s) pgb0=%d, pgb1=%d \n", __func__,   pgb_status0, pgb_status1);
	
    if (pgb_status0 == 0 && pgb_status1 == 0)
    {
         printk("[charger_rt9536] :: (%s) pgb pin shows charger exit, VOL %d \n", __func__, BMT_status.charger_vol);
         return 1;
   }
   else if (pgb_status0 == 1 && pgb_status1 == 1)
   {
       printk("[charger_rt9536] :: (%s) pgb pin shows charger not exit, VOL %d \n", __func__ , BMT_status.charger_vol);
       return 0;
   }
   else
   {
       return 2; //not valid status, need recheck
   }
}
//<2016/09/15-nickygao
#endif

static void charging_ic_initialize(void)
{
    //<2016/12/24-nickygao, [LV3][BUG][COMMON][BATTERY][TD8586][]Fix the bug
    //charging_ic_status = POWER_SUPPLY_TYPE_BATTERY;
    charging_ic_status = POWER_SUPPLY_TYPE_UNKNOWN;
    //<2016/12/24-nickygao
}

static irqreturn_t charging_ic_interrupt_handler(int irq, void *data)
{
    ;
}

static void charging_timer_work(struct work_struct *work)
{
    ;
}

//<2016/09/16-nickygao, [LV3][MISC][COMMON][BSP][][]Get rt9536 GPIO node: charger_rt9536_eoc    charger_rt9536_pgb
#if defined(GET_RT9536_GPIO_FROM_DTS)
void get_rt9536_gpio_node(void)
{
        int ret = 0;
	 static struct device_node *node = NULL;
	 
        printk("[%s]start\n", __func__);
    
	 node = of_find_compatible_node(NULL, NULL, "mediatek,battery");
	 if (!node) {
                printk("node = %p\n", node);
	 }
    
	 CHARGER_RT9536_EOC = of_get_named_gpio(node, "charger_rt9536_eoc", 0);
	 CHARGER_RT9536_PGB = of_get_named_gpio(node, "charger_rt9536_pgb", 0);
	 CHARGER_RT9536_SET = of_get_named_gpio(node, "charger_rt9536_set", 0);

	 if (CHARGER_RT9536_EOC < 0 || CHARGER_RT9536_PGB < 0 || CHARGER_RT9536_SET < 0) {
                printk("EOC=%d PGB=%d SET=%d\n",CHARGER_RT9536_EOC, CHARGER_RT9536_PGB, CHARGER_RT9536_SET);
	 }
     
        
        ret = gpio_request(CHARGER_RT9536_EOC, "CHARGER_RT9536_EOC");
	 if (ret < 0) {
	         printk("gpio_request failed %d\n", ret);
	 }
	 
	 ret = gpio_request(CHARGER_RT9536_PGB, "CHARGER_RT9536_PGB");
	 if (ret < 0) {
	         printk("gpio_request failed %d\n", ret);
	 }

	 ret = gpio_request(CHARGER_RT9536_SET, "CHARGER_RT9536_SET");
	 if (ret < 0) {
	         printk("gpio_request failed %d\n", ret);
	 }
}
#endif
//<2016/09/16-nickygao

//<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Initialize charger IC rt9536
void charger_ic_rt96536_initialize(struct platform_device *dev)
{
            int ret = 0;
	   		//<2016/12/22 stevenzhang,[LV3][]add spinlock.
	    	spin_lock_init(&rt9536_irq_lock);
	    	//<end

	     //<2016/09/16-nickygao, [LV3][MISC][COMMON][BSP][][]Get rt9536 GPIO node: charger_rt9536_eoc    charger_rt9536_pgb
	     #if !defined(GET_RT9536_GPIO_FROM_DTS)
            rt9536ctrl = devm_pinctrl_get(&dev->dev);
            pr_info("rt9536ctrl = %p\n", rt9536ctrl);
            if (IS_ERR(rt9536ctrl)) {
                dev_err(&dev->dev, "Cannot find rt9536 pinctrl!");
                ret = PTR_ERR(rt9536ctrl);
            }
            /*rt9536 EN/SET pin*/
            rt9536_set_h = pinctrl_lookup_state(rt9536ctrl, "rt9536_set1");
            pr_info("rt9536_set_h = %p\n", rt9536_set_h);
            if (IS_ERR(rt9536_set_h)) {
                ret = PTR_ERR(rt9536_set_h);
                pr_debug("%s : pinctrl err, rt9536_set_h\n", __func__);
            }
            /*rt9536 EN/SET pin*/
            rt9536_set_l = pinctrl_lookup_state(rt9536ctrl, "rt9536_set0");
            pr_info("rt9536_set_l = %p\n", rt9536_set_l);
            if (IS_ERR(rt9536_set_l)) {
                ret = PTR_ERR(rt9536_set_l);
                pr_debug("%s : pinctrl err, rt9536_set_l\n", __func__);
            }

            /*rt9536 CHGSB pin*/
            rt9536_eoc_h = pinctrl_lookup_state(rt9536ctrl, "rt9536_eoc1");
            pr_info("rt9536_eoc_h = %p\n", rt9536_eoc_h);
            if (IS_ERR(rt9536_eoc_h)) {
                ret = PTR_ERR(rt9536_eoc_h);
                pr_debug("%s : pinctrl err, rt9536_eoc_h\n", __func__);
            }
            /*rt9536 CHGSB pin*/
            rt9536_eoc_l = pinctrl_lookup_state(rt9536ctrl, "rt9536_eoc0");
            pr_info("rt9536_eoc_l = %p\n", rt9536_eoc_l);
            if (IS_ERR(rt9536_eoc_l)) {
                ret = PTR_ERR(rt9536_eoc_l);
                pr_debug("%s : pinctrl err, rt9536_eoc_l\n", __func__);
            }
        
            /*rt9536 PGB pin*/
            rt9536_pgb_h = pinctrl_lookup_state(rt9536ctrl, "rt9536_pgb1");
            pr_info("rt9536_pgb_h = %p\n", rt9536_pgb_h);
            if (IS_ERR(rt9536_pgb_h)) {
                ret = PTR_ERR(rt9536_pgb_h);
                pr_debug("%s : pinctrl err, rt9536_pgb_h\n", __func__);
            }
            /*rt9536 PGB pin*/
            rt9536_pgb_l = pinctrl_lookup_state(rt9536ctrl, "rt9536_pgb0");
            pr_info("rt9536_pgb_l = %p\n", rt9536_pgb_l);
            if (IS_ERR(rt9536_pgb_l )) {
                ret = PTR_ERR(rt9536_pgb_l );
                pr_debug("%s : pinctrl err, rt9536_pgb_l\n", __func__);
            }
            
            //CHGSB status: default(plug in charger: 0; otherwise 1)
            //pinctrl_select_state(rt9536ctrl, rt9536_eoc_l);
            pr_info("CHGSB = %d\n", gpio_get_value(CHG_EOC_N));

            //PGB status: default(plug in charger: 0; otherwise 1)
            //pinctrl_select_state(rt9536ctrl, rt9536_pgb_l);
            pr_info("PGB = %d\n", gpio_get_value(PGB_N));
            
            //EN/ISET status
            //<2016/12/24-nickygao, [LV3][BUG][COMMON][BATTERY][TD8586][]Fix the bug that Power off charge, charge to 22%, unplug the charger, about 5 seconds plug in the charger, plug in the charger, power becomes 8
            //pinctrl_select_state(rt9536ctrl, rt9536_set_h);
            //gpio_set_value(CHG_EN_SET_N, 1);
            //<2016/12/24-nickygao
            udelay(2000);

            pr_info("EN/ISET = %d\n", gpio_get_value(CHG_EN_SET_N));
            pr_info("CHGSB = %d\n", gpio_get_value(CHG_EOC_N));
            pr_info("PGB = %d\n", gpio_get_value(PGB_N));
            #endif 
	     //<2016/09/16-nickygao
	     
	     //<2016/09/16-nickygao, [LV3][MISC][COMMON][BSP][][]Get rt9536 GPIO node: charger_rt9536_eoc    charger_rt9536_pgb
	     #if defined(GET_RT9536_GPIO_FROM_DTS)
	     get_rt9536_gpio_node();
	     rt9536_set_gpio_value(CHARGER_RT9536_SET, 1);
	     #endif
	     //<2016/09/16-nickygao
            
            //initialize power supply mode
            charging_ic_initialize();
            //charger IC rt9536 initialization flag
            chargin_hw_init_done = KAL_TRUE;
            pr_info("[charger_rt9536] :: charging IC Initialization is done\n");
}
//<2016/09/15-nickygao

static int charging_ic_probe(struct platform_device *dev)
{
#if 0
            //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Initialize charger IC rt9536
            int ret = 0;
    
            rt9536ctrl = devm_pinctrl_get(&dev->dev);
            pr_info("rt9536ctrl = %p\n", rt9536ctrl);
            if (IS_ERR(rt9536ctrl)) {
                dev_err(&dev->dev, "Cannot find rt9536 pinctrl!");
                ret = PTR_ERR(rt9536ctrl);
            }
            /*rt9536 EN/SET pin*/
            rt9536_set_h = pinctrl_lookup_state(rt9536ctrl, "rt9536_set1");
            pr_info("rt9536_set_h = %p\n", rt9536_set_h);
            if (IS_ERR(rt9536_set_h)) {
                ret = PTR_ERR(rt9536_set_h);
                pr_debug("%s : pinctrl err, rt9536_set_h\n", __func__);
            }
                /*rt9536 EN/SET pin*/
            rt9536_set_l = pinctrl_lookup_state(rt9536ctrl, "rt9536_set0");
            pr_info("rt9536_set_l = %p\n", rt9536_set_l);
            if (IS_ERR(rt9536_set_l)) {
                ret = PTR_ERR(rt9536_set_l);
                pr_debug("%s : pinctrl err, rt9536_set_l\n", __func__);
            }
        
                /*rt9536 CHGSB pin*/
            rt9536_eoc_h = pinctrl_lookup_state(rt9536ctrl, "rt9536_eoc1");
            pr_info("rt9536_eoc_h = %p\n", rt9536_eoc_h);
            if (IS_ERR(rt9536_eoc_h)) {
                ret = PTR_ERR(rt9536_eoc_h);
                pr_debug("%s : pinctrl err, rt9536_eoc_h\n", __func__);
            }
                /*rt9536 CHGSB pin*/
            rt9536_eoc_l = pinctrl_lookup_state(rt9536ctrl, "rt9536_eoc0");
            pr_info("rt9536_eoc_l = %p\n", rt9536_eoc_l);
            if (IS_ERR(rt9536_eoc_l)) {
                ret = PTR_ERR(rt9536_eoc_l);
                pr_debug("%s : pinctrl err, rt9536_eoc_l\n", __func__);
            }
        
            /*rt9536 PGB pin*/
            rt9536_pgb_h = pinctrl_lookup_state(rt9536ctrl, "rt9536_pgb1");
            pr_info("rt9536_pgb_h = %p\n", rt9536_pgb_h);
            if (IS_ERR(rt9536_pgb_h)) {
                ret = PTR_ERR(rt9536_pgb_h);
                pr_debug("%s : pinctrl err, rt9536_pgb_h\n", __func__);
            }
                /*rt9536 PGB pin*/
            rt9536_pgb_l = pinctrl_lookup_state(rt9536ctrl, "rt9536_pgb0");
            pr_info("rt9536_pgb_l = %p\n", rt9536_pgb_l);
            if (IS_ERR(rt9536_pgb_l )) {
                ret = PTR_ERR(rt9536_pgb_l );
                pr_debug("%s : pinctrl err, rt9536_pgb_l\n", __func__);
            }
            
            /***************config rt9536****************/
            //CHGSB status: default(plug in charger: 0; otherwise 1)
            pinctrl_select_state(rt9536ctrl, rt9536_eoc_l);
            pr_info("CHGSB = %d\n", gpio_get_value(CHG_EOC_N));

            //PGB status: default(plug in charger: 0; otherwise 1)
            pinctrl_select_state(rt9536ctrl, rt9536_pgb_l);
            pr_info("PGB = %d\n", gpio_get_value(PGB_N));
            
            //EN/ISET status
            pinctrl_select_state(rt9536ctrl, rt9536_set_h);

            pr_info("EN/ISET = %d\n", gpio_get_value(CHG_EN_SET_N));
            pr_info("CHGSB = %d\n", gpio_get_value(CHG_EOC_N));
            pr_info("PGB = %d\n", gpio_get_value(PGB_N));
            
            udelay(2000);
            //initialize power supply mode
            charging_ic_initialize();
            //charger IC rt9536 initialization flag
            chargin_hw_init_done = KAL_TRUE;
            pr_info("[charger_rt9536] :: charging IC Initialization is done\n");
            //<2016/09/15-nickygao
#endif
            //gpio_set_value(CHG_EN_SET_N, 1);
    return 0;
}

static int charging_ic_remove(struct platform_device *dev)
{
    charging_ic_deactive();

    return 0;
}

static int charging_ic_suspend(struct platform_device *dev, pm_message_t state)
{
    printk("[charger_rt9536] :: charging_ic_suspend \n");
    dev->dev.power.power_state = state;
    return 0;
}

static int charging_ic_resume(struct platform_device *dev)
{
    printk("[charger_rt9536] :: charging_ic_resume \n");
    dev->dev.power.power_state = PMSG_ON;
    return 0;
}

static struct platform_driver charging_ic_driver = {
    .probe = charging_ic_probe,
    .remove = charging_ic_remove,
    //.suspend = charging_ic_suspend,
    //.resume = charging_ic_resume,
    .driver = {
        .name = "ext_charger",
        .owner = THIS_MODULE,            
    },
};

static struct platform_device charger_ic_dev = {
	.name = "ext_charger",
	.id   = -1,
};


static int __init charging_ic_init(void)
{
    int ret=0;
    
    printk("[charger_rt9536] Charging IC Driver Init \n");
    
    ret = platform_device_register(&charger_ic_dev);
    if (ret) {
        printk("[charger_rt9536] Unable to device register(%d)\n", ret);
        return ret;
    }    
    
    return platform_driver_register(&charging_ic_driver);
}

static void __exit charging_ic_exit(void)
{
    printk("[charger_rt9536] Charging IC Driver Exit \n");
    platform_driver_unregister(&charging_ic_driver);
}

module_init(charging_ic_init);
module_exit(charging_ic_exit);
