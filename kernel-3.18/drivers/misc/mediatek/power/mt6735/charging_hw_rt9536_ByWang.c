// <<< 2016/08/03-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,

#include <linux/printk.h>
#include <linux/delay.h>
#include <mt-plat/charging.h>
// <<< 2016/08/05-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,
#include <mt-plat/upmu_common.h>
// >>> 2016/08/05-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,
// <<< 2016/08/08-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
#include <mt-plat/mt_boot_common.h>
// >>> 2016/08/08-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
#include <rt9536.h>
// <<< 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
#include <mt-plat/mtk_thermal_typedefs.h>
// >>> 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
// <<< 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
#include <linux/reboot.h>
// >>> 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
// <<< 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
#include <mt-plat/charging.h>
#include <linux/mutex.h>

static DEFINE_MUTEX(charging_lock);
// >>> 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery



#define STATUS_OK           0
#define STATUS_UNSUPPORTED -1
#define HIGH 1
#define LOW  0


u32 g_set_cv_voltage = 0;
u32 g_set_cc_current = 0;

#define CHARGE_CURRENT_850_00_MA_PULSE_COUNT  1
#define CHARGE_CURRENT_100_00_MA_PULSE_COUNT  2
#define CHARGE_CURRENT_2300_00_MA_PULSE_COUNT 3
#define CHARGE_CURRENT_500_00_MA_PULSE_COUNT  4




static signed int charging_hw_init(void * data)
{
        signed int status = STATUS_OK;

        return status;
}

static signed int charging_dump_register(void * data)
{
        signed int status = STATUS_OK;

        battery_log(BAT_LOG_FULL, "[%s ()] [charger_rt9536] NO Action! \n", __func__);
        
        return status;
}

static signed int rt9536_disable_charging(void)
{
        signed int status = STATUS_OK;

        rt9536_set_en_set_pin(HIGH);    // EN/SET Off Time (min : 2ms)
        udelay(2100);

        return status;
}

// <<< 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
inline void set_100mA_cc_current_pulse(void)
{
        rt9536_set_en_set_pin(LOW);
        udelay(60);
        rt9536_set_en_set_pin(HIGH);
        udelay(400);
        rt9536_set_en_set_pin(LOW);
        udelay(400);
        rt9536_set_en_set_pin(HIGH);
        udelay(400);
        rt9536_set_en_set_pin(LOW);
        udelay(1600);
}

inline void set_500mA_cc_current_pulse(void)
{
        rt9536_set_en_set_pin(LOW);
        udelay(60);
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
}

inline void set_850mA_cc_current_pulse(void)
{
        rt9536_set_en_set_pin(LOW);
        udelay(100);
        rt9536_set_en_set_pin(HIGH);
        udelay(400);
        rt9536_set_en_set_pin(LOW);
        udelay(1600);
}

inline void set_2300mA_cc_current_pulse(void)
{
        rt9536_set_en_set_pin(LOW);
        udelay(60);
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
}

inline void set_cv_voltage_pulse(void)
{
        if(g_set_cv_voltage == BATTERY_VOLT_04_350000_V) {
                rt9536_set_en_set_pin(HIGH);    // tcv_set (EN/SET Set Time  700us ~ 1ms)
                udelay(850);
                rt9536_set_en_set_pin(LOW);    // EN/SET Lock Time (min : 1500us)
                udelay(1600);
        }
        else {
                udelay(1600);
        }
}

inline void set_cc_curent_pulse(void)
{
        if (g_set_cc_current == CHARGE_CURRENT_100_00_MA)
                set_100mA_cc_current_pulse();
        else if(g_set_cc_current == CHARGE_CURRENT_500_00_MA)
                set_500mA_cc_current_pulse();
        else if(g_set_cc_current == CHARGE_CURRENT_850_00_MA)
                set_850mA_cc_current_pulse();
        else if(g_set_cc_current == CHARGE_CURRENT_2300_00_MA)
                set_2300mA_cc_current_pulse();
		else if(g_set_cc_current==CHARGE_CURRENT_0_00_MA) {
				rt9536_set_en_set_pin(HIGH);    // EN/SET Off Time (min : 2ms)
	        	udelay(1600);
		}
}


static signed int charging_enable(void * data)
{
        signed int status = STATUS_OK;
        u32 enable = 0;
        static u32 old_g_set_cv_voltage = 0xFF;
        static u32 old_g_set_cc_current = 0xFF;

        enable = * (u32 *) data;
        mutex_lock(&charging_lock);
        if(enable) {
	               if ((old_g_set_cv_voltage != g_set_cv_voltage) || (old_g_set_cc_current != g_set_cc_current)) {
                        set_cc_curent_pulse();
                        set_cv_voltage_pulse();
                        old_g_set_cv_voltage = g_set_cv_voltage;
                        old_g_set_cc_current = g_set_cc_current;
                        battery_log(BAT_LOG_CRTI, "change voltage current mode %d  %d\n", g_set_cv_voltage, g_set_cc_current);
                }
                else {
                        battery_log(BAT_LOG_CRTI, "voltage current are the same mode %d  %d \n", g_set_cv_voltage, g_set_cc_current);
                }
        }
        else {
                rt9536_disable_charging();
                old_g_set_cv_voltage = 0;
                old_g_set_cc_current = 0;
                battery_log(BAT_LOG_CRTI, "%s : %d\n",__func__, enable);
        }
        mutex_unlock(&charging_lock);
        
        return status;
}
// >>> 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery

static signed int charging_set_cv_voltage(void * data)
{
        signed int status = STATUS_OK;
        
        g_set_cv_voltage = (*(unsigned int *) data);
        battery_log(BAT_LOG_CRTI, "charging_set_cv_voltage : %d \n", g_set_cv_voltage);

        return status;
}

static signed int charging_get_current(void * data)
{
        signed int status = STATUS_OK;

        return status;
}

static signed int charging_set_current(void * data)
{
        signed int status = STATUS_OK;

        g_set_cc_current = (*(unsigned int *) data);
        battery_log(BAT_LOG_CRTI, "charging_set_current : %d \n", g_set_cc_current);

        return status;
}

static signed int charging_set_input_current(void * data)
{
        signed int status = STATUS_OK;

        battery_log(BAT_LOG_FULL, "[%s ()] [charger_rt9536] NO Action! \n", __func__);

        return status;
}

static signed int charging_get_vbus_error_status(void * data)
{
        signed int status = STATUS_OK;
        u32 pgb_status = 0;
        u32 chgsb_status = 0;
        
        // 1 : Input OVP or Input UVLO
        u32 vbus_error_status = 0;
        
        rt9536_get_pgb_pin(&pgb_status);
        rt9536_get_chgsb_pin(&chgsb_status);

        if (!pgb_status &&  !chgsb_status)
                vbus_error_status = 1;
        else
                vbus_error_status = 0;

        * (u32 *) data = vbus_error_status;
                
        return status;
}


static signed int charging_get_charging_status(void * data)
{
        signed int status = STATUS_OK;
        u32 pgb_status = 0;
        u32 chgsb_status = 0;
        
        // 0 : charging (CC mode and CV mode)
        // 1 : charge done (IFULL)
        u32 charge_done_status = 0;
        
        rt9536_get_pgb_pin(&pgb_status);
        rt9536_get_chgsb_pin(&chgsb_status);

        if (chgsb_status && pgb_status)
                //
                // charging
                //
                charge_done_status = 0;
        else if (!chgsb_status && pgb_status)
                //
                // charge done
                //
                charge_done_status = 1;
        else
                charge_done_status = 0;

        * (u32 *) data = charge_done_status;

        return status;
}

static signed int charging_reset_watch_dog_timer(void * data)
{
        signed int status = STATUS_OK;

        battery_log(BAT_LOG_FULL, "[%s ()] [charger_rt9536] NO Action! \n", __func__);

        return status;
}

static signed int charging_set_hv_threshold(void * data)
{
        signed int status = STATUS_OK;

        return status;
}

static signed int charging_get_hv_status(void * data)
{
        signed int status = STATUS_OK;

        return status;
}

static signed int charging_get_battery_status(void * data)
{
        signed int status = STATUS_OK;
// <<< 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
        *(kal_bool *)(data) = 0;
        battery_log(BAT_LOG_CRTI, "battery exist for evb \n");
#else
        kal_uint32 val = 0;
        val = pmic_get_register_value(PMIC_BATON_TDET_EN);
        if(val) {
                pmic_set_register_value(PMIC_BATON_TDET_EN, 1);
                pmic_set_register_value(PMIC_RG_BATON_EN, 1);
                *(kal_bool *) (data) = pmic_get_register_value(PMIC_RGS_BATON_UNDET);
        }
        else {
                *(kal_bool *) (data) = KAL_FALSE;
        }
#endif
// >>> 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery

        return status;
}

static signed int charging_get_charger_det_status(void * data)
{
        signed int status = STATUS_OK;
// <<< 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
#if defined(CONFIG_MTK_FPGA)
        *(kal_bool *) (data) = 1;
        battery_log(BAT_LOG_CRTI, "chr exist for fpga\n");
#else
        *(kal_bool *) (data) = pmic_get_register_value(PMIC_RGS_CHRDET);
#endif
// >>> 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
        
        return status;
}

// <<< 2016/08/05-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,
static u32 is_chr_det(void)
{
        u32 val = 0;

        val = pmic_get_register_value(PMIC_RGS_CHRDET);

        battery_log(BAT_LOG_CRTI,"[is_chr_det] %d\n", val);

        return val;
}
// >>> 2016/08/05-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,

static signed int charging_get_charger_type(void * data)
{
        signed int status = STATUS_OK;

        // <<< 2016/08/05-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,
        if(is_chr_det() == 0) {
                *(CHARGER_TYPE *)(data) = CHARGER_UNKNOWN;
                battery_log(BAT_LOG_CRTI, "[%s ()] return CHARGER_UNKNOWN \n", __func__);
                return status;
        }
        
        *(CHARGER_TYPE *)(data) = hw_charging_get_charger_type();
		// >>> 2016/08/05-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,

        return status;
}

static signed int charging_get_is_pcm_timer_trigger(void * data)
{
        signed int status = STATUS_OK;

        return status;
}


static signed int charging_set_platform_reset(void * data)
{
        signed int status = STATUS_OK;
        
// <<< 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
        battery_log(BAT_LOG_CRTI, "charging_set_platform_reset \n");
        kernel_restart("battery service reboot system");
#endif
// >>> 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery

        return status;
}

static signed int charging_get_platform_boot_mode(void * data)
{
        signed int status = STATUS_OK;
		// <<< 2016/08/08-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
        #if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
        #else
                *(unsigned int *) (data) = get_boot_mode();

                battery_log(BAT_LOG_CRTI, "get_boot_mode=%d\n", get_boot_mode());
        #endif
		// <<< 2016/08/08-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery

        return status;
}

static signed int charging_set_power_off(void * data)
{
        signed int status = STATUS_OK;

// <<< 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery
#if defined(CONFIG_POWER_EXT) || defined(CONFIG_MTK_FPGA)
#else
        // added dump_stack to see who the caller is
        dump_stack();
        battery_log(BAT_LOG_CRTI, "charging_set_power_off \n");
        kernel_power_off();
#endif
// >>> 2016/08/10-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery

        return status;
}

static signed int charging_set_error_state(void * data)
{
        signed int status = STATUS_OK;

        return status;
}

static signed int charging_enable_safetytimer(void * data)
{
        signed int status = STATUS_OK;

        battery_log(BAT_LOG_FULL, "[%s ()] [charger_rt9536] NO Action! \n", __func__);

        return status;
}

static signed int (*const charging_func[CHARGING_CMD_NUMBER]) (void *data) = {
        charging_hw_init,
        charging_dump_register,
        charging_enable,
        charging_set_cv_voltage,
        charging_get_current,
        charging_set_current,
        charging_set_input_current,
        charging_get_charging_status,
        charging_reset_watch_dog_timer,
        charging_set_hv_threshold,
        charging_get_hv_status,
        charging_get_battery_status,
        charging_get_charger_det_status,
        charging_get_charger_type,
        charging_get_is_pcm_timer_trigger,
        charging_set_platform_reset,
        charging_get_platform_boot_mode,
        charging_set_power_off,
        charging_set_error_state,
        charging_enable_safetytimer,
        charging_get_vbus_error_status
        };


signed int chr_control_interface(CHARGING_CTRL_CMD cmd, void *data)
{
        signed int status;

        if(cmd < CHARGING_CMD_NUMBER) {
                if (charging_func[cmd] != NULL) {
                        status = charging_func[cmd](data);
                }
                else {
                        battery_log(BAT_LOG_CRTI, "[chr_control_interface]cmd:%d not supported \n", cmd);
                        status = STATUS_UNSUPPORTED;
                }
        }
        else {
                battery_log(BAT_LOG_CRTI, "[chr_control_interface] cmd > CHARGING_CMD_NUMBER \n");
                status = STATUS_UNSUPPORTED;
        }

        return status;
}

// >>> 2016/08/03-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,
