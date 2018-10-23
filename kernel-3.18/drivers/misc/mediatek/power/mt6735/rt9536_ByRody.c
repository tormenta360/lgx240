#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <mt-plat/charging.h>
#include <mt-plat/mt_gpio.h>

// <<< 2016/09/01-Rody, [LV3][PORTING][COMMON][BATTERY][][]Add Charger mode
#include <linux/power_supply.h>
#include <linux/gfp.h>
#include <linux/module.h>   /* For MODULE_ marcros  */
// >>> 2016/09/01-Rody, [LV3][PORTING][COMMON][BATTERY][][]Add Charger mode
// <<< 2016/08/03-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,

#include "rt9536.h"

#define GPIO_CHG_EN   (78 | 0x80000000)
#define EINT_CHG_PGB  (68 | 0x80000000)
#define EINT_CHG_STAT (80 | 0x80000000)
#define LOW  0
#define HIGH 1

kal_bool chargin_hw_init_done = KAL_FALSE;

/**
 *	struct qpnp_chg_chip - device information
 *	rt9536_psy:					power supply to export information to userspace
 *	bool chargin_hw_init_done;
 *	UINT32 rt9536_charge_mode;
 */
// <<< 2016/09/01-Rody, [LV3][PORTING][COMMON][BATTERY][][]Add Charger mode
struct richtek_rt9536_chip {
	struct power_supply rt9536_psy;
	bool rt9536_charger_enable;
	bool chargin_hw_init_done;
	unsigned int rt9536_charge_mode;
} ;
// >>> 2016/09/01-Rody, [LV3][PORTING][COMMON][BATTERY][][]Add Charger mode


static enum power_supply_property rt9536_props[] = {
	POWER_SUPPLY_PROP_CHARGE_MODE,
};

enum rt9536_mode {
	V42_USB100_MODE,  // 0
	V42_USB500_MODE,  // 1
	V42_ISET_MODE,    // 2
	V42_FACTORY_MODE, // 3
	V43_USB100_MODE,  // 4
	V43_USB500_MODE,  // 5
	V43_ISET_MODE,    // 6
	V43_FACTORY_MODE, // 7
};

// ++++++++++++++++++++++++++
// +++++ Function Start +++++
// ++++++++++++++++++++++++++
void rt9536_set_en_set_pin(u32 level)
{
        mt_set_gpio_out(GPIO_CHG_EN, level);
}

void rt9536_get_pgb_pin(u32 *level)
{
        *level = (u32) (mt_get_gpio_in(EINT_CHG_PGB) & 0x01 );
}

void rt9536_get_chgsb_pin(u32 *level)
{
        *level = (u32) (mt_get_gpio_in(EINT_CHG_STAT) & 0x01 );
}

// <<< 2016/09/01-DyRo, [LV3][PORTING][COMMON][BATTERY][][]Add Charger mode
// + Set Battery's Voltage to 4.2V
void set_rt9536_V42_USB100_mode(void)
{
	rt9536_set_en_set_pin(LOW);
	udelay(1000);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);
	
}

void set_rt9536_V42_USB500_mode(void)
{
	rt9536_set_en_set_pin(LOW);
	udelay(1000);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);
}

void set_rt9536_V42_ISET_mode(void)
{
	rt9536_set_en_set_pin(LOW);
	udelay(1000);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

}

void set_rt9536_V42_Factory_mode(void)
{
	rt9536_set_en_set_pin(LOW);
	udelay(1000);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);
}
// - Set Battery's Voltage to 4.2V

// + Set Battery's Voltage to 4.35V
void set_rt9536_V43_USB100_mode(void)
{
	rt9536_set_en_set_pin(LOW);
	udelay(1000);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(1600);

	rt9536_set_en_set_pin(HIGH);
	udelay(1000);
	rt9536_set_en_set_pin(LOW);
	udelay(1000);
}

void set_rt9536_V43_USB500_mode(void)
{
	rt9536_set_en_set_pin(LOW);
	udelay(1000);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(1600);

	rt9536_set_en_set_pin(HIGH);
	udelay(1000);
	rt9536_set_en_set_pin(LOW);
	udelay(1000);
}

void set_rt9536_V43_ISET_mode(void)
{
	rt9536_set_en_set_pin(LOW);
	udelay(1000);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(1600);

	rt9536_set_en_set_pin(HIGH);
	udelay(1000);
	rt9536_set_en_set_pin(LOW);
	udelay(1000);
}

void set_rt9536_V43_Factory_mode(void)
{
	rt9536_set_en_set_pin(LOW);
	udelay(1000);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(400);

	rt9536_set_en_set_pin(HIGH);
	udelay(400);
	rt9536_set_en_set_pin(LOW);
	udelay(1600);

	rt9536_set_en_set_pin(HIGH);
	udelay(1000);
	rt9536_set_en_set_pin(LOW);
	udelay(1000);
}
// - Set Battery's Voltage to 4.35V
/* 
 * switch charging mode
 */

unsigned int switch_charging_mode(struct richtek_rt9536_chip *chip, unsigned int mode)
{
	unsigned int ret = 0;
	printk("[charger_rt9536] %s : mode= %d\n",__func__, mode);
	switch( mode ) {
	case V42_USB100_MODE :
		set_rt9536_V42_USB100_mode();
		chip->rt9536_charge_mode = V42_USB100_MODE;
		ret = V42_USB100_MODE;
		break;
	case V42_USB500_MODE :
		set_rt9536_V42_USB500_mode();
		chip->rt9536_charge_mode = V42_USB500_MODE;
		ret = V42_USB500_MODE;
		break;
	case V42_ISET_MODE :
		set_rt9536_V42_ISET_mode();
		chip->rt9536_charge_mode = V42_ISET_MODE;
		ret = V42_ISET_MODE;
		break;
	case V42_FACTORY_MODE :
		set_rt9536_V42_Factory_mode();
		chip->rt9536_charge_mode = V42_FACTORY_MODE;
		ret = V42_FACTORY_MODE;
		break;
	case V43_USB100_MODE :
		set_rt9536_V43_USB100_mode();
		chip->rt9536_charge_mode = V43_USB100_MODE;
		ret = V43_USB100_MODE;
		break;
	case V43_USB500_MODE :
		set_rt9536_V43_USB500_mode();
		chip->rt9536_charge_mode = V43_USB500_MODE;
		ret = V43_USB500_MODE;
		break;
	case V43_ISET_MODE :
		set_rt9536_V43_ISET_mode();
		chip->rt9536_charge_mode = V43_ISET_MODE;
		ret = V43_ISET_MODE;
		break;
	case V43_FACTORY_MODE :
		set_rt9536_V43_Factory_mode();
		chip->rt9536_charge_mode = V43_FACTORY_MODE;
		ret = V43_FACTORY_MODE;
		break;
	default:
		return -EINVAL;
	}
	return ret;
}

/*
 * for struct power_supply
 */
static int rt9536_get_property(struct power_supply *psy,
								enum power_supply_property psp,
								union power_supply_propval *val)
{
	int ret =0;
	struct richtek_rt9536_chip *chip = container_of(psy, struct richtek_rt9536_chip, rt9536_psy);
	
	switch(psp) {
	case POWER_SUPPLY_PROP_CHARGE_MODE:
		val->intval= chip->rt9536_charge_mode;
		break;
	default:
		return -EINVAL;
	}
	return ret;
}

/*
 * power_supply_set_property
 * for struct power_supply
 */
static int rt9536_set_property(struct power_supply *psy,
								enum power_supply_property psp,
								const union power_supply_propval *val)
{
	int ret = 0;
	struct richtek_rt9536_chip *chip = container_of(psy, struct richtek_rt9536_chip, rt9536_psy);

	switch(psp) {
	case POWER_SUPPLY_PROP_CHARGE_MODE:
		switch_charging_mode(chip, val->intval);
		break;
	default:
		return -EINVAL;
	}
	return ret;
}

/*
 * from D5
 */
char rt9536_check_eoc_status(void)
{
//	unsigned char reg_val = 0;
	char eoc_status0, eoc_status1 = 0;
	char pgb_status0, pgb_status1 = 0;

	// TO DO
	mdelay(150);
	eoc_status0 = mt_get_gpio_in(EINT_CHG_STAT);
	mdelay(150);
	eoc_status1 = mt_get_gpio_in(EINT_CHG_STAT);

	mdelay(10);
	pgb_status0 = mt_get_gpio_in(EINT_CHG_PGB);
	
	mdelay(10);
	pgb_status1 = mt_get_gpio_in(EINT_CHG_PGB);

	printk("[charger_rt9536] :: (%s) pgb0=%d, pgb1=%d \n", __func__,   pgb_status0, pgb_status1);
	printk("[charger_rt9536] :: (%s) eoc_status0=%d, eoc_status1=%d \n", __func__,   eoc_status0, eoc_status1);
	if( eoc_status1 && eoc_status0 && pgb_status0==0 && pgb_status1==0) {
//		BMT_status.ICharging = 0;
		printk("[charger_rt9536] :: (%s) eoc_status is not in charging mode(1)\n", __func__ );
		return 1;
	}
	printk("[charger_rt9536] :: (%s) eoc_status is in charging mode (0)\n", __func__ );
	return 0;
}

/*
 *	initialize GPIO_CHG_PGB pin
 */
static int rt9536_gpio_chg_pgb_pin(void)
{
	mt_set_gpio_mode(EINT_CHG_PGB, GPIO_MODE_00);
	mt_set_gpio_pull_enable(EINT_CHG_PGB, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(EINT_CHG_PGB, GPIO_PULL_UP);
	mt_set_gpio_dir(EINT_CHG_PGB, GPIO_DIR_IN);
	
	return 1;
}

/*
 *	initialize EINT_CHG_STAT pin
 */
static int rt9536_eint_chg_stat_pin(void)
{
	mt_set_gpio_mode(EINT_CHG_STAT, GPIO_MODE_00);
	mt_set_gpio_pull_enable(EINT_CHG_STAT, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(EINT_CHG_STAT, GPIO_PULL_UP);
	mt_set_gpio_dir(EINT_CHG_STAT, GPIO_DIR_IN);
	
	return 1;
}

// ----- Function End -----

// rt9536 initialization
static struct richtek_rt9536_chip rt9536_data ={
	.rt9536_psy = {
		.name = "rt9536",
		.type = POWER_SUPPLY_TYPE_RT9536,
		.properties= rt9536_props,
		.num_properties = ARRAY_SIZE(rt9536_props),
		.get_property = rt9536_get_property,
		.set_property = rt9536_set_property,
	},
	.chargin_hw_init_done =1,
	.rt9536_charger_enable =1,
	.rt9536_charge_mode=1,
};

/*
 *
 */
unsigned int switch_charging_mode_to_mtk( unsigned int mode)
{
	int ret =0;
	ret= switch_charging_mode(&rt9536_data, mode);
	if (ret <0) {
		printk("charger_rt9536: can't switch mode");
	}
	printk("charger_rt9536: switch to mode=%d, result= %d", mode, ret);

	return ret;
}

/*
 *
 * from D5 change to youzih
 */
//void charging_ic_deactive(void)
int rt9536_disable_charging(void)
{
	
	rt9536_set_en_set_pin(HIGH);    // EN/SET Off Time (min : 2ms)
	udelay(2100);
	rt9536_data.rt9536_charger_enable =0;
	return 1;
}

/*
 *
 * from D5
 */
void rt9536_charging_enable(unsigned int set_current, unsigned int enable)
{
	if (enable) {
		if ( set_current == AC_CHARGER_CURRENT )
			set_rt9536_V43_ISET_mode();
		else if ( set_current == USB_CHARGER_CURRENT )
			set_rt9536_V43_USB500_mode();
		else if ( set_current == CHARGE_CURRENT_0_00_MA )
			rt9536_disable_charging();
		else
			set_rt9536_V43_USB500_mode();
			printk("[charger_rt9536] : %s, current(%d), enable(%d)\n", __func__, set_current, enable);
	} else {
		rt9536_disable_charging();
		printk("[charger_rt9536] : %s, enable(%d)\n", __func__, enable);
	}
}

/*
 *
 * from D5
 */
//extern unsigned int  ext_charger_status;
/*
int rt9536_check_charger_status(void)
{

	int pgb_status0= 0, pgb_status1 = 0;
	
	if(ext_charger_status==0)
		return 0;
	//mdelay(150);
	mdelay(10);
	pgb_status0 = mt_get_gpio_in(EINT_CHG_PGB);
	//mdelay(150);
	mdelay(10);
	pgb_status1 = mt_get_gpio_in(EINT_CHG_PGB);
	printk("[charger_rt9536] :: (%s) pgb0=%d, pgb1=%d \n", __func__,   pgb_status0,pgb_status1);
	
	if( pgb_status0==0 && pgb_status1==0) {
//		printk("[charger_rt9536] :: (%s) pgb pin shows charger exit, VOL %d \n", __func__,   BMT_status.charger_vol);
		return 1;
	} else if ( pgb_status0==1 && pgb_status1==1) {
//		printk("[charger_rt9536] :: (%s) pgb pin shows charger not exit, VOL %d \n", __func__ ,BMT_status.charger_vol);
		return 0;
	} else {
		return 2; //not valid status, need recheck
	}
}
*/

/*
 *	initialize GPIO_CHG_EN pin
 */
static int rt9536_init_gpio_chg_enable_pin(void)
{
	mt_set_gpio_mode(GPIO_CHG_EN, GPIO_MODE_00);
	mt_set_gpio_pull_enable(GPIO_CHG_EN, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(GPIO_CHG_EN, GPIO_PULL_UP);
	mt_set_gpio_dir(GPIO_CHG_EN, GPIO_DIR_OUT);
	return 1;
}


static struct platform_device rt9536_device = {
        .name = "rt9536",
        .id = -1,
};

static int rt9536_driver_probe(struct platform_device *plat_dev)
{
	struct richtek_rt9536_chip *chip;
	int rc;
	chip = devm_kzalloc(&plat_dev->dev,	sizeof(struct richtek_rt9536_chip), GFP_KERNEL);
	// initialize GPIO_CHG_EN pin
	rc= rt9536_init_gpio_chg_enable_pin();
	
	// disable charging
	rc= rt9536_disable_charging();
	
	// initialize EINT_CHG_PGB pin
	rc= rt9536_gpio_chg_pgb_pin();
	
	// initialize EINT_CHG_STAT pin
	rc= rt9536_eint_chg_stat_pin();

    // setup power_supply
	rc = power_supply_register(&(plat_dev->dev), &rt9536_data.rt9536_psy);
	if (rc) {
		printk("[Rody] power_supply_register rt9536 fail !!\n");
	}
	printk("[Rody] power_supply_register rt9536 ok !!\n");
	
	chip->chargin_hw_init_done = 1;
	chargin_hw_init_done = KAL_TRUE;

	printk( KERN_EMERG "[Rody][rt9536] %s: probe ok\n", __func__);
	return 0;
}

static struct platform_driver rt9536_driver = {
        .driver = {
                .name = "rt9536",
                .owner = THIS_MODULE,
                },
        .probe = rt9536_driver_probe,
};

static int __init rt9536_init(void)
{
	int ret = 0;
	
	ret = platform_device_register(&rt9536_device);
	if (ret) {
		battery_log(BAT_LOG_CRTI, "****[rt9536_init] Unable to register device (%d) \n", ret);
		return ret;
	}

	ret = platform_driver_register(&rt9536_driver);
	if (ret) {
		battery_log(BAT_LOG_CRTI, "****[rt9536_init] Unable to register driver (%d) \n", ret);
		return ret;
	}
	
	return 0;
}

static void __exit rt9536_exit(void)
{
	
	battery_log(BAT_LOG_CRTI, "rt9536_exit \n");
	platform_driver_unregister(&rt9536_driver);
        
}

module_init(rt9536_init);
module_exit(rt9536_exit);
// >>> 2016/08/03-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,
