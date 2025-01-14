#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/time.h>
#include "kd_flashlight.h"
#include <asm/io.h>
#include <asm/uaccess.h>
#include "kd_camera_typedef.h"
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/version.h>
#include <linux/mutex.h>
#include <linux/i2c.h>
#include <linux/leds.h>
#include <mt-plat/mt_gpio.h>
#include <mach/gpio_const.h>



/******************************************************************************
 * Debug configuration
******************************************************************************/
/* availible parameter */
/* ANDROID_LOG_ASSERT */
/* ANDROID_LOG_ERROR */
/* ANDROID_LOG_WARNING */
/* ANDROID_LOG_INFO */
/* ANDROID_LOG_DEBUG */
/* ANDROID_LOG_VERBOSE */

#define TAG_NAME "[leds_strobe.c]"
#define PK_DBG_NONE(fmt, arg...)    do {} while (0)
#define PK_DBG_FUNC(fmt, arg...)    pr_debug(TAG_NAME "%s: " fmt, __func__ , ##arg)

#define DEBUG_LEDS_STROBE
#ifdef DEBUG_LEDS_STROBE
#define PK_DBG PK_DBG_FUNC
#else
#define PK_DBG(a, ...)
#endif

/******************************************************************************
 * local variables
******************************************************************************/

static DEFINE_SPINLOCK(g_strobeSMPLock);	/* cotta-- SMP proection */


static u32 strobe_Res;
static u32 strobe_Timeus;
static BOOL g_strobe_On;

static int g_duty = -1;
static int g_timeOutTimeMs;

static DEFINE_MUTEX(g_strobeSem);


#define STROBE_DEVICE_ID 0xC6


static struct work_struct workTimeOut;

/* #define FLASH_GPIO_ENF GPIO12 */
/* #define FLASH_GPIO_ENT GPIO13 */


// <<< 2016/08/02-dangyiwang. Flashlight. Porting LM3648TT driver. setting rear flashlight flash current setting
static int gIsTorch[18] = {   1,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0};
static int gLedDuty[18] = {0x11, 0x29, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; // Modify flash brightness. By Ted Li. 2016-09-06
// >>> 2016/08/02-dangyiwang. Flashlight. Porting LM3648TT driver. setting rear flashlight flash current setting

/*****************************************************************************
Functions
*****************************************************************************/
static void work_timeOutFunc(struct work_struct *data);

// <<< 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. Extern LM3642_i2c_client to kd_flashlightlist.c
struct i2c_client *LM3642_i2c_client;
// >>> 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. Extern LM3642_i2c_client to kd_flashlightlist.c



struct LM3642_platform_data {
	u8 torch_pin_enable;	/* 1:  TX1/TORCH pin isa hardware TORCH enable */
	u8 pam_sync_pin_enable;	/* 1:  TX2 Mode The ENVM/TX2 is a PAM Sync. on input */
	u8 thermal_comp_mode_enable;	/* 1: LEDI/NTC pin in Thermal Comparator Mode */
	u8 strobe_pin_disable;	/* 1 : STROBE Input disabled */
	u8 vout_mode_enable;	/* 1 : Voltage Out Mode enable */
};

struct LM3642_chip_data {
	struct i2c_client *client;

	/* struct led_classdev cdev_flash; */
	/* struct led_classdev cdev_torch; */
	/* struct led_classdev cdev_indicator; */

	struct LM3642_platform_data *pdata;
	struct mutex lock;

	u8 last_flag;
	u8 no_pdata;
};

// <<< 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. Extern LM3642_write_reg to kd_flashlightlist.c
int LM3642_write_reg(struct i2c_client *client, u8 reg, u8 val)
// >>> 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. Extern LM3642_write_reg to kd_flashlightlist.c
{
	int ret = 0;
	struct LM3642_chip_data *chip = i2c_get_clientdata(client);

	mutex_lock(&chip->lock);
	ret = i2c_smbus_write_byte_data(client, reg, val);
	mutex_unlock(&chip->lock);

	if (ret < 0)
		PK_DBG("failed writing at 0x%02x\n", reg);
	return ret;
}

static int LM3642_read_reg(struct i2c_client *client, u8 reg)
{
	int val = 0;
	struct LM3642_chip_data *chip = i2c_get_clientdata(client);

	mutex_lock(&chip->lock);
	val = i2c_smbus_read_byte_data(client, reg);
	mutex_unlock(&chip->lock);


	return val;
}




static int LM3642_chip_init(struct LM3642_chip_data *chip)
{
	// <<< 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. lm3648 driver init
	u8 chip_register_address = 0x00;
	u8 chip_register_value   = 0x00;		
	u8 chip_register_offset  = 0x00;
	PK_DBG ("LM3644 chip init +\n");
        
	//
	// set gpio pin of torch
	//
	mt_set_gpio_mode (GPIO42, GPIO_MODE_GPIO);
	mt_set_gpio_dir  (GPIO42, GPIO_DIR_OUT);
	mt_set_gpio_out  (GPIO42, GPIO_OUT_ZERO);
        
        
	//
	// set gpio pin of strobe
	//
	mt_set_gpio_mode (GPIO43, GPIO_MODE_GPIO);
	mt_set_gpio_dir  (GPIO43, GPIO_DIR_OUT);
	mt_set_gpio_out  (GPIO43, GPIO_OUT_ZERO);

        
	//
	// Timing Configuration Register (0x08)
	// bit07         : RFU
	// bit06 ~ bit04 : Torch Current Ramp Time
	// bit03 ~ bit00 : Flash Time-Out Duration
	//
        
	chip_register_address = 0x08;
	// + Modify the time-out duration for flashlight. By Ted Li. 2016-11-30
	//chip_register_value   = 0x1A;    // Torch Current Ramp Time : 1 ms // Flash Time-Out Duration : 600 ms
	chip_register_value   = 0x1B;    // Torch Current Ramp Time : 1 ms // Flash Time-Out Duration : 800 ms
	// - Modify the time-out duration for flashlight. By Ted Li. 2016-11-30
	LM3642_write_reg (chip->client, chip_register_address, chip_register_value);


	//
	// rear LED flash brightness set
	// LED2 Flash Brightness Register (0x03)
	//
	// Bit 07 ~ 06 : must set '10'
	// Bit 06 ~ 00 : LED Flash Brightness Level
	//
	chip_register_address = 0x03;
	chip_register_offset  = 0x3F;  // for reset bit 07 ~ 06 to 00
	chip_register_value   = 0x29;  // flash current = 983.25 mA = ((Brightness Code * 23.45 mA) + 21.8 mA)
	
	chip_register_value = chip_register_value & chip_register_offset;  //reset bit 07 ~ 06 to 00
	chip_register_value = chip_register_value | 0x80;  //set bit 07 ~ 06 to 10
	
	LM3642_write_reg (chip->client, chip_register_address, chip_register_value);


	//
	// rear LED torch brightness set
	// LED2 Torch Brightness Register (0x05)
	//
	// Bit 07      :must set '1'
	// Bit 06 ~ 00 : LED Torch Brightness Level
	//
	chip_register_address = 0x05;
	chip_register_offset  = 0x7F;  // for reset bit 07 to 0
	chip_register_value   = 0x11;  // torch current = 99.108 mA = (Brightness Code x 5.6 mA) + 3.908 mA
	
	chip_register_value = chip_register_value & chip_register_offset;  //reset bit 07 ~ 06 to 00
	chip_register_value = chip_register_value | 0x80;  //set bit 07 to 1
	
	LM3642_write_reg (chip->client, chip_register_address, chip_register_value);

//<jiezhang 20161205 [D6][PORTING][COMMON][BSP][][]Disable flashlight when the chip init
	chip_register_address = 0x01;
	chip_register_value   = 0x00;
	LM3642_write_reg(chip->client, chip_register_address, chip_register_value);
//>jiezhang 20161205 [D6][PORTING][COMMON][BSP][][]     
   
	PK_DBG ("LM3648 chip init -\n");
	// >>> 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. lm3648 driver init

	return 0;
}

static int LM3642_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct LM3642_chip_data *chip;
	struct LM3642_platform_data *pdata = client->dev.platform_data;

	int err = -1;

	PK_DBG("LM3642_probe start--->.\n");

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		err = -ENODEV;
		PK_DBG("LM3642 i2c functionality check fail.\n");
		return err;
	}

	chip = kzalloc(sizeof(struct LM3642_chip_data), GFP_KERNEL);
	chip->client = client;

	mutex_init(&chip->lock);
	i2c_set_clientdata(client, chip);

	if (pdata == NULL) {	/* values are set to Zero. */
		PK_DBG("LM3642 Platform data does not exist\n");
		pdata = kzalloc(sizeof(struct LM3642_platform_data), GFP_KERNEL);
		chip->pdata = pdata;
		chip->no_pdata = 1;
	}

	chip->pdata = pdata;
	if (LM3642_chip_init(chip) < 0)
		goto err_chip_init;

	LM3642_i2c_client = client;
	PK_DBG("LM3642 Initializing is done\n");

	return 0;

err_chip_init:
	i2c_set_clientdata(client, NULL);
	kfree(chip);
	PK_DBG("LM3642 probe is failed\n");
	return -ENODEV;
}

static int LM3642_remove(struct i2c_client *client)
{
	struct LM3642_chip_data *chip = i2c_get_clientdata(client);

	if (chip->no_pdata)
		kfree(chip->pdata);
	kfree(chip);
	return 0;
}


#define LM3642_NAME "leds-LM3642"
static const struct i2c_device_id LM3642_id[] = {
	{LM3642_NAME, 0},
	{}
};

#ifdef CONFIG_OF
static const struct of_device_id LM3642_of_match[] = {
	{.compatible = "mediatek,strobe_main"},
	{},
};
#endif

static struct i2c_driver LM3642_i2c_driver = {
	.driver = {
		   .name = LM3642_NAME,
#ifdef CONFIG_OF
		   .of_match_table = LM3642_of_match,
#endif
		   },
	.probe = LM3642_probe,
	.remove = LM3642_remove,
	.id_table = LM3642_id,
};
// <<< 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. Create flashlight driver platform data
struct LM3642_platform_data LM3642_pdata = {0, 0, 0, 0, 0};
static struct i2c_board_info __initdata i2c_LM3642 = {
        .type          = LM3642_NAME,
        .addr          = 0x63,
        .platform_data = &LM3642_pdata,
};
// >>> 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. Create flashlight driver platform data
static int __init LM3642_init(void)
{
// <<< 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. Register lm3648 to i2c
	int Status = 0;

	PK_DBG("LM3642_init +\n");
	i2c_register_board_info (1, &i2c_LM3642, 1);
	Status = i2c_add_driver(&LM3642_i2c_driver);
	if (Status == 0) {
		printk("lm3648 add i2c driver success\n");
		PK_DBG("LM3642_init -\n");
		return 0;
	} else {
		printk("lm3648 add i2c driver fail\n");
		PK_DBG("LM3642_init -\n");
		return Status;
	}
// >>> 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. Register lm3648 to i2c
}

static void __exit LM3642_exit(void)
{
	i2c_del_driver(&LM3642_i2c_driver);
}


module_init(LM3642_init);
module_exit(LM3642_exit);

MODULE_DESCRIPTION("Flash driver for LM3642");
MODULE_AUTHOR("pw <pengwei@mediatek.com>");
MODULE_LICENSE("GPL v2");

int readReg(int reg)
{

	int val;

	val = LM3642_read_reg(LM3642_i2c_client, reg);
	return (int)val;
}

int FL_Enable(void)
{
	// <<< 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. rear flashlight enable function
	u8 chip_register_address = 0x00;
	u8 chip_register_value   = 0x00;

	if (gIsTorch[g_duty] == 1) {
		chip_register_address = 0x01;
		chip_register_value   = 0x0B;
	}
	else {
		chip_register_address = 0x01;
		chip_register_value   = 0x0F;
	}
	LM3642_write_reg(LM3642_i2c_client, chip_register_address, chip_register_value);
	// >>> 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. rear flashlight enable function
	PK_DBG(" FL_Enable line=%d\n", __LINE__);
	return 0;
}



int FL_Disable(void)
{
	// <<< 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. rear flashlight disable function.
	u8 chip_register_address = 0x00;
	u8 chip_register_value   = 0x00;
        
	chip_register_address = 0x01;
	chip_register_value   = 0x00;
	LM3642_write_reg(LM3642_i2c_client, chip_register_address, chip_register_value);
	// >>> 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. rear flashlight disable function.
	PK_DBG(" FL_Disable line=%d\n", __LINE__);
	return 0;
}

int FL_dim_duty(kal_uint32 duty)
{
	// <<< 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. rear flashlight duty function FL_dim_duty ()
	u8 chip_register_address = 0x00;
	u8 chip_register_value   = 0x00;
	u8 chip_register_offset  = 0x00;

	// + Modify flash brightness. By Ted Li. 2016-09-06
	/*
	if (duty > 17)
		duty = 17;
	if (duty < 0)
		duty = 0;*/
	if (duty < 0)
		duty = 0;
	else if (duty > 1)
		duty = 1;
	// - Modify flash brightness. By Ted Li. 2016-09-06
        
	g_duty = duty;

	if (gIsTorch[g_duty] == 1) {
		chip_register_address = 0x05;
		chip_register_offset  = 0x7F;  // for reset bit 07 to 0
		chip_register_value   = gLedDuty[g_duty];
		
		chip_register_value = chip_register_value & chip_register_offset;  //reset bit 07 ~ 06 to 00
		chip_register_value = chip_register_value | 0x80;  //set bit 07 ~ 06 to 10
	}
	else {
		chip_register_address = 0x03;
		chip_register_offset  = 0x3F;  // for reset bit 07 ~ 06 to 00
		chip_register_value   = gLedDuty[g_duty];
			
		chip_register_value = chip_register_value & chip_register_offset;  //reset bit 07 ~ 06 to 00
		chip_register_value = chip_register_value | 0x80;  //set bit 07 to 1
	}
	LM3642_write_reg(LM3642_i2c_client, chip_register_address, chip_register_value);
	// >>> 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. rear flashlight duty function FL_dim_duty ()
	PK_DBG(" FL_dim_duty line=%d\n", __LINE__);
	return 0;
}




int FL_Init(void)
{
	// <<< 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. FL_Init ()
	FL_Disable ();
	// >>> 2016/08/05-dangyiwang. Flashlight. Porting LM3648TT driver. FL_Init ()
/*	PK_DBG(" FL_Init line=%d\n", __LINE__); */
	return 0;
}


int FL_Uninit(void)
{
	FL_Disable();
	return 0;
}

/*****************************************************************************
User interface
*****************************************************************************/

static void work_timeOutFunc(struct work_struct *data)
{
	FL_Disable();
	PK_DBG("ledTimeOut_callback\n");
}



enum hrtimer_restart ledTimeOutCallback(struct hrtimer *timer)
{
	schedule_work(&workTimeOut);
	return HRTIMER_NORESTART;
}

static struct hrtimer g_timeOutTimer;
void timerInit(void)
{
	INIT_WORK(&workTimeOut, work_timeOutFunc);
	g_timeOutTimeMs = 1000;
	hrtimer_init(&g_timeOutTimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	g_timeOutTimer.function = ledTimeOutCallback;
}



static int constant_flashlight_ioctl(unsigned int cmd, unsigned long arg)
{
	int i4RetValue = 0;
	int ior_shift;
	int iow_shift;
	int iowr_shift;

	ior_shift = cmd - (_IOR(FLASHLIGHT_MAGIC, 0, int));
	iow_shift = cmd - (_IOW(FLASHLIGHT_MAGIC, 0, int));
	iowr_shift = cmd - (_IOWR(FLASHLIGHT_MAGIC, 0, int));
/*	PK_DBG
	    ("LM3642 constant_flashlight_ioctl() line=%d ior_shift=%d, iow_shift=%d iowr_shift=%d arg=%d\n",
	     __LINE__, ior_shift, iow_shift, iowr_shift, (int)arg);
*/
	switch (cmd) {

	case FLASH_IOC_SET_TIME_OUT_TIME_MS:
		PK_DBG("FLASH_IOC_SET_TIME_OUT_TIME_MS: %d\n", (int)arg);
		g_timeOutTimeMs = arg;
		break;


	case FLASH_IOC_SET_DUTY:
		PK_DBG("FLASHLIGHT_DUTY: %d\n", (int)arg);
		FL_dim_duty(arg);
		break;


	case FLASH_IOC_SET_STEP:
		PK_DBG("FLASH_IOC_SET_STEP: %d\n", (int)arg);

		break;

	case FLASH_IOC_SET_ONOFF:
		PK_DBG("FLASHLIGHT_ONOFF: %d\n", (int)arg);
		if (arg == 1) {

			int s;
			int ms;

			if (g_timeOutTimeMs > 1000) {
				s = g_timeOutTimeMs / 1000;
				ms = g_timeOutTimeMs - s * 1000;
			} else {
				s = 0;
				ms = g_timeOutTimeMs;
			}

			if (g_timeOutTimeMs != 0) {
				ktime_t ktime;

				ktime = ktime_set(s, ms * 1000000);
				hrtimer_start(&g_timeOutTimer, ktime, HRTIMER_MODE_REL);
			}
			FL_Enable();
		} else {
			FL_Disable();
			hrtimer_cancel(&g_timeOutTimer);
		}
		break;
	default:
		PK_DBG(" No such command\n");
		i4RetValue = -EPERM;
		break;
	}
	return i4RetValue;
}




static int constant_flashlight_open(void *pArg)
{
	int i4RetValue = 0;

	PK_DBG("constant_flashlight_open line=%d\n", __LINE__);

	if (0 == strobe_Res) {
		FL_Init();
		timerInit();
	}
	PK_DBG("constant_flashlight_open line=%d\n", __LINE__);
	spin_lock_irq(&g_strobeSMPLock);


	if (strobe_Res) {
		PK_DBG(" busy!\n");
		i4RetValue = -EBUSY;
	} else {
		strobe_Res += 1;
	}


	spin_unlock_irq(&g_strobeSMPLock);
	PK_DBG("constant_flashlight_open line=%d\n", __LINE__);

	return i4RetValue;

}


static int constant_flashlight_release(void *pArg)
{
	PK_DBG(" constant_flashlight_release\n");

	if (strobe_Res) {
		spin_lock_irq(&g_strobeSMPLock);

		strobe_Res = 0;
		strobe_Timeus = 0;

		/* LED On Status */
		g_strobe_On = FALSE;

		spin_unlock_irq(&g_strobeSMPLock);

		FL_Uninit();
	}

	PK_DBG(" Done\n");

	return 0;

}


FLASHLIGHT_FUNCTION_STRUCT constantFlashlightFunc = {
	constant_flashlight_open,
	constant_flashlight_release,
	constant_flashlight_ioctl
};


MUINT32 constantFlashlightInit(PFLASHLIGHT_FUNCTION_STRUCT *pfFunc)
{
	if (pfFunc != NULL)
		*pfFunc = &constantFlashlightFunc;
	return 0;
}



/* LED flash control for high current capture mode*/
ssize_t strobe_VDIrq(void)
{

	return 0;
}
EXPORT_SYMBOL(strobe_VDIrq);
