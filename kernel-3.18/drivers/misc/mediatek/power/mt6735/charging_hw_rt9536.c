#include <linux/types.h>
#include <mt-plat/charging.h>
#include <mt-plat/upmu_common.h>
#include <mach/upmu_sw.h>
#include <mach/upmu_hw.h>
#include <linux/delay.h>
#include <linux/reboot.h>
#include <mt-plat/mt_gpio.h>
#include <mt-plat/mt_boot.h>
#include <mt-plat/battery_common.h>
#include <mach/mt_charging.h>
#include <mach/mt_pmic.h>
#include "rt9536.h"

// ============================================================ //
// Define
// ============================================================ //
#define STATUS_OK    0
#define STATUS_UNSUPPORTED    -1
#define GETARRAYNUM(array) (sizeof(array)/sizeof(array[0]))

// ============================================================ //
// Global variable
// ============================================================ //

#if defined(MTK_WIRELESS_CHARGER_SUPPORT)
#define WIRELESS_CHARGER_EXIST_STATE 0

    #if defined(GPIO_PWR_AVAIL_WLC)
        unsigned int  wireless_charger_gpio_number = GPIO_PWR_AVAIL_WLC; 
    #else
        unsigned int  wireless_charger_gpio_number = 0; 
    #endif
    
#endif

static CHARGER_TYPE g_charger_type = CHARGER_UNKNOWN;

kal_bool charging_type_det_done = KAL_TRUE;

const unsigned int  VBAT_CV_VTH[]=
{
    BATTERY_VOLT_03_500000_V, BATTERY_VOLT_03_520000_V, BATTERY_VOLT_03_540000_V, BATTERY_VOLT_03_560000_V, BATTERY_VOLT_03_580000_V, 
    BATTERY_VOLT_03_600000_V, BATTERY_VOLT_03_620000_V, BATTERY_VOLT_03_640000_V, BATTERY_VOLT_03_660000_V, BATTERY_VOLT_03_680000_V, 
    BATTERY_VOLT_03_700000_V, BATTERY_VOLT_03_720000_V, BATTERY_VOLT_03_740000_V, BATTERY_VOLT_03_760000_V, BATTERY_VOLT_03_780000_V, 
    BATTERY_VOLT_03_800000_V, BATTERY_VOLT_03_820000_V, BATTERY_VOLT_03_840000_V, BATTERY_VOLT_03_860000_V, BATTERY_VOLT_03_880000_V,
    BATTERY_VOLT_03_900000_V, BATTERY_VOLT_03_920000_V, BATTERY_VOLT_03_940000_V, BATTERY_VOLT_03_960000_V, BATTERY_VOLT_03_980000_V, 
    BATTERY_VOLT_04_000000_V, BATTERY_VOLT_04_020000_V, BATTERY_VOLT_04_040000_V, BATTERY_VOLT_04_060000_V, BATTERY_VOLT_04_080000_V, 
    BATTERY_VOLT_04_100000_V, BATTERY_VOLT_04_120000_V, BATTERY_VOLT_04_140000_V, BATTERY_VOLT_04_160000_V, BATTERY_VOLT_04_180000_V, 
    BATTERY_VOLT_04_200000_V, BATTERY_VOLT_04_220000_V, BATTERY_VOLT_04_240000_V, BATTERY_VOLT_04_260000_V, BATTERY_VOLT_04_280000_V,
    BATTERY_VOLT_04_300000_V, BATTERY_VOLT_04_320000_V, BATTERY_VOLT_04_340000_V, BATTERY_VOLT_04_360000_V, BATTERY_VOLT_04_380000_V, 
    BATTERY_VOLT_04_400000_V, BATTERY_VOLT_04_420000_V, BATTERY_VOLT_04_440000_V, BATTERY_VOLT_04_460000_V, BATTERY_VOLT_04_480000_V,
    BATTERY_VOLT_04_500000_V, BATTERY_VOLT_04_520000_V, BATTERY_VOLT_04_540000_V, BATTERY_VOLT_04_560000_V, BATTERY_VOLT_04_580000_V,
    BATTERY_VOLT_04_600000_V, BATTERY_VOLT_04_620000_V, BATTERY_VOLT_04_640000_V, BATTERY_VOLT_04_660000_V, BATTERY_VOLT_04_680000_V,
    BATTERY_VOLT_04_700000_V, BATTERY_VOLT_04_720000_V, BATTERY_VOLT_04_740000_V, BATTERY_VOLT_04_760000_V    
};

const unsigned int CS_VTH[]=
{
    CHARGE_CURRENT_500_00_MA, CHARGE_CURRENT_600_00_MA, CHARGE_CURRENT_700_00_MA, CHARGE_CURRENT_800_00_MA, CHARGE_CURRENT_900_00_MA,
    CHARGE_CURRENT_1000_00_MA,CHARGE_CURRENT_1100_00_MA,CHARGE_CURRENT_1200_00_MA,CHARGE_CURRENT_1300_00_MA,CHARGE_CURRENT_1400_00_MA,
    CHARGE_CURRENT_1500_00_MA,CHARGE_CURRENT_1600_00_MA,CHARGE_CURRENT_1700_00_MA,CHARGE_CURRENT_1800_00_MA,CHARGE_CURRENT_1900_00_MA,
    CHARGE_CURRENT_2000_00_MA,CHARGE_CURRENT_2100_00_MA,CHARGE_CURRENT_2200_00_MA,CHARGE_CURRENT_2300_00_MA,CHARGE_CURRENT_2400_00_MA,
    CHARGE_CURRENT_2500_00_MA,CHARGE_CURRENT_2600_00_MA,CHARGE_CURRENT_2700_00_MA,CHARGE_CURRENT_2800_00_MA,CHARGE_CURRENT_2900_00_MA,
    CHARGE_CURRENT_3000_00_MA,CHARGE_CURRENT_MAX
    //from datasheet : any setting programmed above 3A selects the 3A setting
}; 

//USB connector (USB or AC adaptor)
const unsigned int INPUT_CS_VTH[]=
{
    CHARGE_CURRENT_100_00_MA, CHARGE_CURRENT_150_00_MA, CHARGE_CURRENT_500_00_MA, CHARGE_CURRENT_900_00_MA, 
    CHARGE_CURRENT_1500_00_MA,CHARGE_CURRENT_1950_00_MA,CHARGE_CURRENT_2500_00_MA,CHARGE_CURRENT_2000_00_MA,
    CHARGE_CURRENT_MAX
}; 

const unsigned int VCDT_HV_VTH[]=
{
    BATTERY_VOLT_04_200000_V, BATTERY_VOLT_04_250000_V,	 BATTERY_VOLT_04_300000_V,	 BATTERY_VOLT_04_350000_V,
	  BATTERY_VOLT_04_400000_V, BATTERY_VOLT_04_450000_V,	 BATTERY_VOLT_04_500000_V,	 BATTERY_VOLT_04_550000_V,
	  BATTERY_VOLT_04_600000_V, BATTERY_VOLT_06_000000_V,	 BATTERY_VOLT_06_500000_V,	 BATTERY_VOLT_07_000000_V,
	  BATTERY_VOLT_07_500000_V, BATTERY_VOLT_08_500000_V,	 BATTERY_VOLT_09_500000_V,	 BATTERY_VOLT_10_500000_V	          
};

 unsigned int g_charging_current = 0;
// ============================================================ //
// function prototype
// ============================================================ //

 
// ============================================================ //
//extern variable
// ============================================================ //

// ============================================================ //
//extern function
// ============================================================ //
extern unsigned int upmu_get_reg_value(unsigned int reg);
extern bool mt_usb_is_device(void);
extern void Charger_Detect_Init(void);
extern void Charger_Detect_Release(void);
extern int hw_charging_get_charger_type(void);
extern void mt_power_off(void);
extern unsigned int mt6311_get_chip_id(void);
extern int is_mt6311_exist(void);
extern int is_mt6311_sw_ready(void);

// ============================================================ //
unsigned int charging_value_to_parameter(const unsigned int *parameter, const unsigned int array_size, const unsigned int val)
{
    if (val < array_size)
    {
        return parameter[val];
    }
    else
    {
        pr_info( "Can't find the parameter \r\n");    
        return parameter[0];
    }
}

 
unsigned int charging_parameter_to_value(const unsigned int *parameter, const unsigned int array_size, const unsigned int val)
{
    unsigned int i;

    for(i=0;i<array_size;i++)
    {
        if (val == *(parameter + i))
        {
                return i;
        }
    }

    pr_info( "NO register value match \r\n");
    //TODO: ASSERT(0);    // not find the value
    return 0;
}


static unsigned int bmt_find_closest_level(const unsigned int *pList,unsigned int number,unsigned int level)
{
    unsigned int i;
    unsigned int max_value_in_last_element;

    if(pList[0] < pList[1])
        max_value_in_last_element = KAL_TRUE;
    else
        max_value_in_last_element = KAL_FALSE;

    if(max_value_in_last_element == KAL_TRUE)
    {
        for(i = (number-1); i != 0; i--)     //max value in the last element
        {
            if(pList[i] <= level)
            {
                return pList[i];
            }      
        }

        pr_info( "Can't find closest level \r\n");    
        return pList[0];
        //return CHARGE_CURRENT_0_00_MA;
    }
    else
    {
        for(i = 0; i< number; i++)  // max value in the first element
        {
            if(pList[i] <= level)
            {
                return pList[i];
            }      
        }

        pr_info( "Can't find closest level \r\n");
        return pList[number -1];
        //return CHARGE_CURRENT_0_00_MA;
    }
}


static unsigned int is_chr_det(void)
{
    unsigned int val = 0;
    //<2016/09/16-nickygao, [LV3][MISC][COMMON][BSP][][]Porting rt9536
    val = pmic_get_register_value(PMIC_RGS_CHRDET);
    //>2016/09/16-nickygao

    pr_info("[is_chr_det] %d\n", val);
    
    return val;
}


static unsigned int charging_hw_init(void *data)
{
    unsigned int status = STATUS_OK;
           
#if defined(MTK_WIRELESS_CHARGER_SUPPORT)
    if(wireless_charger_gpio_number!=0)
    {
        mt_set_gpio_mode(wireless_charger_gpio_number,0); // 0:GPIO mode
        mt_set_gpio_dir(wireless_charger_gpio_number,0); // 0: input, 1: output
    }
#endif
           
    return status;
}


static unsigned int charging_dump_register(void *data)
{
    unsigned int status = STATUS_OK;
   	
    return status;
}    


static unsigned int charging_enable(void *data)
{
    unsigned int status = STATUS_OK;
    unsigned int enable = *(unsigned int *)(data);

    if (KAL_TRUE == enable)
    {
        rt9536_charging_enable(g_charging_current, enable);
    }
    else
    {
        g_charging_current = 0;
        rt9536_charging_enable(g_charging_current, enable);
    }

    pr_info("[%s][charger_rt9536] charger enable = %d, g_charging_current = %d \r\n", __func__, enable, g_charging_current);
        
    return status;
}


static unsigned int charging_set_cv_voltage(void *data)
{
    unsigned int status = STATUS_OK;
    //unsigned int cv_value = *(unsigned int *)(data);

    /* TO DO */
    pr_info("[%s][charger_rt9536] NO Action! \r\n", __func__);
    
    return status;
}     


static unsigned int charging_get_current(void *data)
{
    unsigned int status = STATUS_OK;
    //<2016/09/16-nickygao, [LV3][MISC][COMMON][BSP][][]Battery OTP test
    //*(unsigned int *)data = g_charging_current;
    //<2016/09/16-nickygao
    /* TO DO */
    pr_info("[%s][charger_rt9536] g_charging_current = %d! \r\n", __func__, g_charging_current);
    //<2016/12/02-nickygao, [LV3][MISC][COMMON][BSP][][]Disable function of Thermal Charger control
    #if 0
	// + 20161107 Rody [D6][FEATURE][COMMON][BATTERY][][] Thermal Charger control
    *(unsigned int *)data = g_charging_current;
	// - 20161107 Rody [D6][FEATURE][COMMON][BATTERY][][] Thermal Charger control
    #endif
    //<2016/12/02-nickygao
    
    return status;
}  


static unsigned int charging_set_current(void *data)
{
    unsigned int status = STATUS_OK;
    unsigned int current_value = *(unsigned int *)data;
//<2016/09/16-nickygao, [LV3][MISC][COMMON][BSP][][]Battery OTP test
#if 0	
    if ((current_value == AC_CHARGER_CURRENT) || (current_value == USB_CHARGER_CURRENT))
    {
        g_charging_current = current_value;
    }
    else
    {
        g_charging_current = USB_CHARGER_CURRENT;
    }
#else
        g_charging_current = current_value;
#endif
//<2016/09/16-nickygao
        
    pr_info("[%s][charger_rt9536] current_value = %d, g_charging_current = %d \r\n", __func__, current_value, g_charging_current);
        
    return status;
}     


static unsigned int charging_set_input_current(void *data)
{
    unsigned int status = STATUS_OK;
	unsigned int current_value = *(unsigned int *)data;

    pr_info("[%s][charger_rt9536] input_current_value = %d \r\n", __func__, current_value);
    
    return status;
}     


static unsigned int charging_get_charging_status(void *data)
{
    unsigned int status = STATUS_OK;

    *(unsigned int *)data = rt9536_check_eoc_status();
    
    pr_info("[%s][charger_rt9536] EOC_status = %d \r\n", __func__, *(unsigned int *)data);
   
    return status;
}     


static unsigned int charging_reset_watch_dog_timer(void *data)
{
    unsigned int status = STATUS_OK;

    /* TO DO */
    pr_info("[%s][charger_rt9536] NO Action! \r\n", __func__);
    
    return status;
}
 
 
static unsigned int charging_set_hv_threshold(void *data)
{
	unsigned int status = STATUS_OK;

	unsigned int set_hv_voltage;
	unsigned int array_size;
	unsigned short register_value;
	unsigned int voltage = *(unsigned int *) (data);

	array_size = GETARRAYNUM(VCDT_HV_VTH);
	set_hv_voltage = bmt_find_closest_level(VCDT_HV_VTH, array_size, voltage);
	register_value = charging_parameter_to_value(VCDT_HV_VTH, array_size, set_hv_voltage);
	pmic_set_register_value(PMIC_RG_VCDT_HV_VTH, register_value);

	return status;
}


static unsigned int charging_get_hv_status(void *data)
{
	unsigned int status = STATUS_OK;

	*(kal_bool *) (data) = pmic_get_register_value(PMIC_RGS_VCDT_HV_DET);

	return status;
}


static unsigned int charging_get_battery_status(void *data)
{
	unsigned int status = STATUS_OK;
#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
	unsigned int val = 0;
#endif

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
	*(kal_bool *)(data) = 0;	/* battery exist */
	battery_log(BAT_LOG_CRTI, "bat exist for evb\n");
#else
	val = pmic_get_register_value(PMIC_BATON_TDET_EN);
	battery_log(BAT_LOG_FULL, "[charging_get_battery_status] BATON_TDET_EN = %d\n", val);
	if (val) {
		pmic_set_register_value(PMIC_BATON_TDET_EN, 1);
		pmic_set_register_value(PMIC_RG_BATON_EN, 1);
		*(kal_bool *)(data) = pmic_get_register_value(PMIC_RGS_BATON_UNDET);
		//<2016/09/16-nickygao, [LV3][MISC][COMMON][BSP][][]Add battery detect log
		if (*(kal_bool *)(data) == 1) {
		        battery_log(BAT_LOG_CRTI, "[%s] battery non-exist\n", __func__);
		}
		//<2016/09/16-nickygao
	} else {
		*(kal_bool *)(data) = KAL_FALSE;
		//<2016/09/16-nickygao, [LV3][MISC][COMMON][BSP][][]Add battery detect log
		battery_log(BAT_LOG_FULL, "[%s] battery exist\n", __func__);
		//<2016/09/16-nickygao
	}
#endif

	return status;
 }
 
 #if 1
//<2016/09/15-nickygao, [LV3][FEATURE][COMMON][BSP][][]Decrease the power consumption
extern void wake_up_bat(void);
unsigned int  ext_charger_status = 0;
#endif 
static unsigned int charging_get_charger_det_status(void *data)
{
    unsigned int status = STATUS_OK;
    unsigned int val = 0;

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
    val = 1;
    pr_info("[charging_get_charger_det_status] charger exist for bring up.\n"); 
#else   
    //<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Porting rt9536 for detecting adapter existence or not from MT6735M
    val = pmic_get_register_value_nolock(PMIC_RGS_CHRDET);
    //<2016/09/15-nickygao
#endif
 
    //*(kal_bool *)(data) = val;
#if   0
    if (val == 0) {
        g_charger_type = CHARGER_UNKNOWN;
    }
#else
    //<2016/09/15-nickygao, [LV3][FEATURE][COMMON][BSP][][]Detect charger status
    if (val == 0)   //adapter non-exists
    {
        if (rt9536_check_charger_status() == 0)
	{
	    //that val is 0 indicates that adapter non-exists
	    *(kal_bool *)(data) = 0;
           //adapter non-exists, must disable rt9536
	    charging_ic_deactive();
	    // could use this method, but not make sure if impact sleep current.
	    if (g_charger_type != CHARGER_UNKNOWN) {
                //adapter non-exist and adapter't type doesn't check, wake up BAT_thread
	         wake_up_bat(); 
           }
           //initialize adapter's type
           g_charger_type = CHARGER_UNKNOWN;
           //adapter non-exists, rt9536_check_charger_status doesn't invoke again, only return 0, which shows adapter non-exists
	    ext_charger_status = 0;
        }
	else    //adapter exists
	{
	    //That val is 1 indicates that adapter exists
	    *(kal_bool *)(data) = 1;
	}
	//g_charger_type = CHARGER_UNKNOWN;
    }
    else    //adapter exist
    {
        *(kal_bool *)(data) = 1;
        ext_charger_status = 1;
    }
    //<2016/09/15-nickygao
#endif
    return status;
}
//<2016/09/15-nickygao


kal_bool charging_type_detection_done(void)
{
	return charging_type_det_done;
}


static unsigned int charging_get_charger_type(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
    //<2016/12/02-nickygao, [LV3][MISC][COMMON][BSP][][]Disable function of Thermal Charger control
    #if 0
	// + 20161107 Rody [D6][FEATURE][COMMON][BATTERY][][] Thermal Charger control
    pr_info("[%s][charger_rt9536] get charger type is STANDARD_HOST \r\n", __func__);
	// - 20161107 Rody [D6][FEATURE][COMMON][BATTERY][][] Thermal Charger control
    #endif
    //<2016/12/02-nickygao
	*(CHARGER_TYPE *) (data) = STANDARD_HOST;
#else
    //<2016/12/02-nickygao, [LV3][MISC][COMMON][BSP][][]Disable function of Thermal Charger control
    #if 0
	// + 20161107 Rody [D6][FEATURE][COMMON][BATTERY][][] Thermal Charger control
    pr_info("[%s][charger_rt9536] get charger type is hw_charging_get_charger_type() \r\n", __func__);
	// - 20161107 Rody [D6][FEATURE][COMMON][BATTERY][][] Thermal Charger control
    #endif
    //<2016/12/02-nickygao
	*(CHARGER_TYPE *)(data) = hw_charging_get_charger_type();
#endif

	return status;
}

//<2016/12/15-nickygao, [LV3][MISC][COMMON][BSP][][]Update battery data to upper layers
typedef enum {
	WR_NONE = 0,
	WR_UART_BUSY = 1,
	WR_PCM_ASSERT = 2,
	WR_PCM_TIMER = 3,
	WR_WAKE_SRC = 4,
	WR_UNKNOWN = 5,
} wake_reason_t;

wake_reason_t slp_get_wake_reason(void);
//<2016/12/15-nickygao
static unsigned int charging_get_is_pcm_timer_trigger(void *data)
{
	unsigned int status = STATUS_OK;
//<2016/12/15-nickygao, [LV3][MISC][COMMON][BSP][][]Update battery data to upper layers
#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
	*(kal_bool *) (data) = KAL_FALSE;
#else

	if (slp_get_wake_reason() == WR_PCM_TIMER)
		*(kal_bool *) (data) = KAL_TRUE;
	else
		*(kal_bool *) (data) = KAL_FALSE;

	battery_log(BAT_LOG_CRTI, "slp_get_wake_reason=%d\n", slp_get_wake_reason());

#endif
//<2016/12/15-nickygao
	return status;
}

static unsigned int charging_set_platform_reset(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
	battery_log(BAT_LOG_CRTI, "charging_set_platform_reset\n");

	kernel_restart("battery service reboot system");
	/* arch_reset(0,NULL); */
#endif

	return status;
}

static unsigned int charging_get_platform_boot_mode(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
	*(unsigned int *) (data) = get_boot_mode();

	battery_log(BAT_LOG_CRTI, "get_boot_mode=%d\n", get_boot_mode());
#endif

	return status;
}

static unsigned int charging_set_power_off(void *data)
{
	unsigned int status = STATUS_OK;

#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
	battery_log(BAT_LOG_CRTI, "charging_set_power_off\n");
       //<2016/12/22-nickygao, [LV3][BUG][COMMON][CHARGER][TD8573][]Fix the bug that press the power key but Phone has been displayed in the charging screen while plugging out adapter in KPOC
	kernel_power_off();
	//<2016/12/22-nickygao
#endif

	return status;
}

static unsigned int charging_get_power_source(void *data)
{
	unsigned int status = STATUS_OK;

#if 0				/* #if defined(MTK_POWER_EXT_DETECT) */
	if (MT_BOARD_PHONE == mt_get_board_type())
		*(kal_bool *) data = KAL_FALSE;
	else
		*(kal_bool *) data = KAL_TRUE;
#else
	*(kal_bool *) data = KAL_FALSE;
#endif

	return status;
}

static unsigned int charging_get_csdac_full_flag(void *data)
{
	return STATUS_UNSUPPORTED;	
}

static unsigned int charging_set_ta_current_pattern(void *data)
{
	return STATUS_UNSUPPORTED;	
}

static unsigned int (* const charging_func[CHARGING_CMD_NUMBER])(void *data)=
{
        charging_hw_init
        ,charging_dump_register      
        ,charging_enable
        ,charging_set_cv_voltage
        ,charging_get_current
        ,charging_set_current
        ,charging_set_input_current
        ,charging_get_charging_status
        ,charging_reset_watch_dog_timer
        ,charging_set_hv_threshold
        ,charging_get_hv_status
        ,charging_get_battery_status
        ,charging_get_charger_det_status
        ,charging_get_charger_type
        ,charging_get_is_pcm_timer_trigger
        ,charging_set_platform_reset
        ,charging_get_platform_boot_mode
        ,charging_set_power_off
        ,charging_get_power_source
        ,charging_get_csdac_full_flag
        ,charging_set_ta_current_pattern
};

 
/*
* FUNCTION
*        Internal_chr_control_handler
*
* DESCRIPTION                                                             
*         This function is called to set the charger hw
*
* CALLS  
*
* PARAMETERS
*        None
*     
* RETURNS
*        
*
* GLOBALS AFFECTED
*       None
*/
int chr_control_interface(CHARGING_CTRL_CMD cmd, void *data)
{
    int status;
    if (cmd < CHARGING_CMD_NUMBER)
        status = charging_func[cmd](data);
    else
        return STATUS_UNSUPPORTED;

    return status;
}


