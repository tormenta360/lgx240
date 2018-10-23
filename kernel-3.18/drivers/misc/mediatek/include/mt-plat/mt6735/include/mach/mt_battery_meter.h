#ifndef _CUST_BATTERY_METER_H
#define _CUST_BATTERY_METER_H

#if defined(CONFIG_MTK_BQ24196_SUPPORT) \
	|| defined(CONFIG_MTK_BQ24296_SUPPORT) \
	|| defined(CONFIG_MTK_BQ24261_SUPPORT)
#define SWCHR_POWER_PATH
#define EXTERNAL_SWCHR_SUPPORT
#endif

#if defined(CONFIG_ARCH_MT6735)
/* ============================================================
// define
// ============================================================*/
/*#define SOC_BY_AUXADC*/
#define SOC_BY_HW_FG
/*#define HW_FG_FORCE_USE_SW_OCV*/
/*#define SOC_BY_SW_FG*/

/*
//#define CONFIG_DIS_CHECK_BATTERY
//#define FIXED_TBAT_25
*/

/* ADC resistor  */
#define R_BAT_SENSE 4
#define R_I_SENSE 4
#define R_CHARGER_1 330
#define R_CHARGER_2 39

#define TEMPERATURE_T0 110
#define TEMPERATURE_T1 0
#define TEMPERATURE_T2 25
#define TEMPERATURE_T3 50
#define TEMPERATURE_T 255 /* This should be fixed, never change the value*/

#define FG_METER_RESISTANCE 0


// + 20161005-Rody [D6][PORTING][COMMON][BATTERY][][] apply battery zcv table from MTK
#if 1
/* Qmax for battery  */
#define Q_MAX_POS_50	2473 //2458
#define Q_MAX_POS_25	2432 //2404
#define Q_MAX_POS_0		2248 //1782
#define Q_MAX_NEG_10	1967 //951

#define Q_MAX_POS_50_H_CURRENT	2458 //2473
#define Q_MAX_POS_25_H_CURRENT	2404 //2432
#define Q_MAX_POS_0_H_CURRENT	1782 //2248
#define Q_MAX_NEG_10_H_CURRENT	951 //1967

#else
/* Qmax for battery  */
#define Q_MAX_POS_50 1463
#define Q_MAX_POS_25 1437
#define Q_MAX_POS_0 1220
#define Q_MAX_NEG_10 1137

#define Q_MAX_POS_50_H_CURRENT 1511
#define Q_MAX_POS_25_H_CURRENT 1462
#define Q_MAX_POS_0_H_CURRENT 818
#define Q_MAX_NEG_10_H_CURRENT 149
#endif
// - 20161005-Rody [D6][PORTING][COMMON][BATTERY][][] apply battery zcv table from MTK

/* Discharge Percentage */
#define OAM_D5		 1		/*  1 : D5,   0: D2*/


/* battery meter parameter */
#define CHANGE_TRACKING_POINT
#ifdef CONFIG_MTK_HAFG_20
#define CUST_TRACKING_POINT  0
#else
#define CUST_TRACKING_POINT  1
#endif
#define CUST_R_SENSE 68
#define CUST_HW_CC 0
#define AGING_TUNING_VALUE 103
#define CUST_R_FG_OFFSET 0

#define OCV_BOARD_COMPESATE	0 /*mV */
#define R_FG_BOARD_BASE 1000
#define R_FG_BOARD_SLOPE 1000 /*slope*/
// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify CAR_TUNE_VALUE to 96
//#ifdef CONFIG_MTK_EMI_D1P
//#define CAR_TUNE_VALUE 104 /*1.00*/
//#else
//#define CAR_TUNE_VALUE 86 /*1.00*/
//#endif
#define CAR_TUNE_VALUE 96
// - 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify CAR_TUNE_VALUE to 96

/* HW Fuel gague  */
#define CURRENT_DETECT_R_FG 10  /*1mA*/
#define MinErrorOffset 1000
#define FG_VBAT_AVERAGE_SIZE 18
#define R_FG_VALUE 10 /* mOhm, base is 20*/

/* fg 2.0 */
#define DIFFERENCE_HWOCV_RTC		30
#define DIFFERENCE_HWOCV_SWOCV		10
#define DIFFERENCE_SWOCV_RTC		10
#define MAX_SWOCV			3

#define DIFFERENCE_VOLTAGE_UPDATE	20
#define AGING1_LOAD_SOC			70
#define AGING1_UPDATE_SOC		30
#define BATTERYPSEUDO100		95
#define BATTERYPSEUDO1			4

#define Q_MAX_BY_SYS
#define Q_MAX_SYS_VOLTAGE		3300
#define SHUTDOWN_GAUGE0
// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Turn off condition about gauge 1 %
//#define SHUTDOWN_GAUGE1_XMINS
// - 20161014 Rody, [D6][MISC][COMMON][BSP][][] Turn off condition about gauge 1 %
#define SHUTDOWN_GAUGE1_MINS		60

// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify Shutdown voltage from 3.4V to 3.3V
//#define SHUTDOWN_SYSTEM_VOLTAGE		3400
#define SHUTDOWN_SYSTEM_VOLTAGE		3300
// - 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify Shutdown voltage from 3.4V to 3.3V
#define CHARGE_TRACKING_TIME		60
#define DISCHARGE_TRACKING_TIME		10

#define RECHARGE_TOLERANCE		10
/* SW Fuel Gauge */
#define MAX_HWOCV			5
#define MAX_VBAT			90
#define DIFFERENCE_HWOCV_VBAT		30

/* fg 1.0 */
#define CUST_POWERON_DELTA_CAPACITY_TOLRANCE	40
#define CUST_POWERON_LOW_CAPACITY_TOLRANCE		5
#define CUST_POWERON_MAX_VBAT_TOLRANCE			90
#define CUST_POWERON_DELTA_VBAT_TOLRANCE		30
#define CUST_POWERON_DELTA_HW_SW_OCV_CAPACITY_TOLRANCE	10


/* Disable Battery check for HQA */
#ifdef CONFIG_MTK_DISABLE_POWER_ON_OFF_VOLTAGE_LIMITATION
#define FIXED_TBAT_25
#endif

/* Dynamic change wake up period of battery thread when suspend*/
#define VBAT_NORMAL_WAKEUP		3600
#define VBAT_LOW_POWER_WAKEUP		3500
#define NORMAL_WAKEUP_PERIOD		5400
#define LOW_POWER_WAKEUP_PERIOD		300
#define CLOSE_POWEROFF_WAKEUP_PERIOD	30

#define INIT_SOC_BY_SW_SOC
/*
//#define SYNC_UI_SOC_IMM			//3. UI SOC sync to FG SOC immediately
*/
#define MTK_ENABLE_AGING_ALGORITHM	/*6. Q_MAX aging algorithm*/
#define MD_SLEEP_CURRENT_CHECK	/*5. Gauge Adjust by OCV 9. MD sleep current check*/
/*
//#define Q_MAX_BY_CURRENT		//7. Qmax variant by current loading.
*/
#define FG_BAT_INT
#define IS_BATTERY_REMOVE_BY_PMIC

#elif defined(CONFIG_ARCH_MT6735M)
/* ============================================================
// define
// ============================================================*/
//<2016/10/25-nickygao, [LV3][MISC][COMMON][BSP][][]Use SW fuel gauge
/*#define SOC_BY_AUXADC*/
//#define SOC_BY_HW_FG
/*#define HW_FG_FORCE_USE_SW_OCV*/
#define SOC_BY_SW_FG
//<2016/10/25-nickygao

/*
//#define CONFIG_DIS_CHECK_BATTERY
//#define FIXED_TBAT_25
*/

/* ADC resistor  */
#define R_BAT_SENSE 4
#define R_I_SENSE 4
#define R_CHARGER_1 330
#define R_CHARGER_2 39

//<2016/10/25-nickygao, [LV3][FEATURE][COMMON][BSP][][]Set charging with -20 degree ZCV table
#define TEMPERATURE_T_N20       120
#define TEMPERATURE_T0 -10//110
//<2016/10/25-nickygao
#define TEMPERATURE_T1 0
#define TEMPERATURE_T2 25
#define TEMPERATURE_T3 50
#define TEMPERATURE_T 255 /* This should be fixed, never change the value*/

#define FG_METER_RESISTANCE 0

/* Qmax for battery  */
// + 20161011-Rody [D6][PORTING][COMMON][BATTERY][][] apply battery zcv table from MTK #1
#if 1
/* Qmax for battery  */
#define Q_MAX_POS_50	2473 //2458
#define Q_MAX_POS_25	2432 //2404
#define Q_MAX_POS_0		2248 //1782
#define Q_MAX_NEG_10	1967 //951
//<2016/10/25-nickygao, [LV3][FEATURE][COMMON][BSP][][]Set Q_MAX with -20 degree
#define Q_MAX_NEG_20  1500
//<2016/10/25-nickygao

#define Q_MAX_POS_50_H_CURRENT	2458 //2473
#define Q_MAX_POS_25_H_CURRENT	2404 //2432
#define Q_MAX_POS_0_H_CURRENT	1782 //2248
#define Q_MAX_NEG_10_H_CURRENT	951 //1967
//<2016/10/25-nickygao, [LV3][FEATURE][COMMON][BSP][][]Set Q_MAX with -20 degree
#define Q_MAX_NEG_20_H_CURRENT 636
//<2016/10/25-nickygao

#else
#define Q_MAX_POS_50 1463
#define Q_MAX_POS_25 1437
#define Q_MAX_POS_0 1220
#define Q_MAX_NEG_10 1137

#define Q_MAX_POS_50_H_CURRENT 1511
#define Q_MAX_POS_25_H_CURRENT 1462
#define Q_MAX_POS_0_H_CURRENT 818
#define Q_MAX_NEG_10_H_CURRENT 149
#endif
// - 20161011-Rody [D6][PORTING][COMMON][BATTERY][][] apply battery zcv table from MTK #1

/* Discharge Percentage */
//<2016/09/15-nickygao, [D6][MISC][COMMON][BSP][][]Set discharging with D2
#define OAM_D5		 0/*1*/		/*  1 : D5,   0: D2*/
//<2016/09/15-nickygao


/* battery meter parameter */
#define CHANGE_TRACKING_POINT
#ifdef CONFIG_MTK_HAFG_20
#define CUST_TRACKING_POINT  0
#else
#define CUST_TRACKING_POINT  1
#endif
#define CUST_R_SENSE 68
#define CUST_HW_CC 0
#define AGING_TUNING_VALUE 103
#define CUST_R_FG_OFFSET 0

#define OCV_BOARD_COMPESATE	0 /*mV */
#define R_FG_BOARD_BASE 1000
#define R_FG_BOARD_SLOPE 1000 /*slope*/
// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify CAR_TUNE_VALUE to 96
//#define CAR_TUNE_VALUE 101 /*1.00*/
#define CAR_TUNE_VALUE 96 /*1.00*/
// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify CAR_TUNE_VALUE to 96


/* HW Fuel gague  */
#define CURRENT_DETECT_R_FG 10  /*1mA*/
#define MinErrorOffset 1000
#define FG_VBAT_AVERAGE_SIZE 18
#define R_FG_VALUE 10 /* mOhm, base is 20*/

/* fg 2.0 */
//<2016/10/25-nickygao, [LV3][MISC][COMMON][BSP][][]Modify toltance for power-on fuel gauge
#define DIFFERENCE_HWOCV_RTC		60//30
#define DIFFERENCE_HWOCV_SWOCV		90//10
#define DIFFERENCE_SWOCV_RTC		90//10
#define MAX_SWOCV		90//	3
//<2016/10/25-nickygao

#define DIFFERENCE_VOLTAGE_UPDATE	20
#define AGING1_LOAD_SOC			70
#define AGING1_UPDATE_SOC		30
#define BATTERYPSEUDO100		95
//<2016/10/25-nickygao, [LV3][MISC][COMMON][BSP][][]Modify the speed that battery UI_SOC falls down to 0%
#define BATTERYPSEUDO1		11//	4
//<2016/10/25-nickygao

//<2016/10/25-nickygao, [LV3][MISC][COMMON][BSP][][]Set Q_MAX of system
#define Q_MAX_BY_SYS
#define Q_MAX_SYS_VOLTAGE		3300
//<2016/10/25-nickygao
#define SHUTDOWN_GAUGE0
// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Turn off condition about gauge 1 %
//#define SHUTDOWN_GAUGE1_XMINS
// - 20161014 Rody, [D6][MISC][COMMON][BSP][][] Turn off condition about gauge 1 %
#define SHUTDOWN_GAUGE1_MINS		60

// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify Shutdown voltage from 3.4V to 3.3V
//<2016/10/25-nickygao, [LV3][FEATURE][COMMON][BSP][][]
#define SHUTDOWN_SYSTEM_VOLTAGE		3400
//#define SHUTDOWN_SYSTEM_VOLTAGE		3300
//<2016/10/25-nickygao
// - 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify Shutdown voltage from 3.4V to 3.3V
#define CHARGE_TRACKING_TIME		60
#define DISCHARGE_TRACKING_TIME		10

#define RECHARGE_TOLERANCE		10
/* SW Fuel Gauge */
#define MAX_HWOCV			5
#define MAX_VBAT			90
#define DIFFERENCE_HWOCV_VBAT		30

/* fg 1.0 */
#define CUST_POWERON_DELTA_CAPACITY_TOLRANCE	40
#define CUST_POWERON_LOW_CAPACITY_TOLRANCE		5
#define CUST_POWERON_MAX_VBAT_TOLRANCE			90
//<2017/2/13-nickygao, [LV3][MISC][COMMON][BATTERY][][]Design D6 SW FG same as D5&D3
#define CUST_POWERON_DELTA_VBAT_TOLRANCE		30
//<2017/2/13-nickygao
#define CUST_POWERON_DELTA_HW_SW_OCV_CAPACITY_TOLRANCE	10


/* Disable Battery check for HQA */
#ifdef CONFIG_MTK_DISABLE_POWER_ON_OFF_VOLTAGE_LIMITATION
#define FIXED_TBAT_25
#endif

/* Dynamic change wake up period of battery thread when suspend*/
#define VBAT_NORMAL_WAKEUP		3600
#define VBAT_LOW_POWER_WAKEUP		3500
//<2016/12/15-nickygao, [LV3][FEATURE][COMMON][BSP][][]Wake up battery every 610s
#define NORMAL_WAKEUP_PERIOD		610//200//5400
//<2016/12/15-nickygao
#define LOW_POWER_WAKEUP_PERIOD		300
#define CLOSE_POWEROFF_WAKEUP_PERIOD	30

//<2016/10/25-nickygao, [LV3][MISC][COMMON][BSP][][]Use SW fuel gauge
//#define INIT_SOC_BY_SW_SOC
/*
//#define SYNC_UI_SOC_IMM			//3. UI SOC sync to FG SOC immediately
*/
//#define MTK_ENABLE_AGING_ALGORITHM	/*6. Q_MAX aging algorithm*/
//#define MD_SLEEP_CURRENT_CHECK	/*5. Gauge Adjust by OCV 9. MD sleep current check*/
/*
//#define Q_MAX_BY_CURRENT		//7. Qmax variant by current loading.
*/
//#define FG_BAT_INT
//#define IS_BATTERY_REMOVE_BY_PMIC
//<2016/10/25-nickygao



#elif defined(CONFIG_ARCH_MT6753)
/* ============================================================
// define
// ============================================================*/
/*#define SOC_BY_AUXADC*/
#define SOC_BY_HW_FG
/*#define HW_FG_FORCE_USE_SW_OCV*/
/*#define SOC_BY_SW_FG*/

/*
//#define CONFIG_DIS_CHECK_BATTERY
//#define FIXED_TBAT_25
*/

/* ADC resistor  */
#define R_BAT_SENSE 4
#define R_I_SENSE 4
#define R_CHARGER_1 330
#define R_CHARGER_2 39

#define TEMPERATURE_T0 110
#define TEMPERATURE_T1 0
#define TEMPERATURE_T2 25
#define TEMPERATURE_T3 50
#define TEMPERATURE_T 255 /* This should be fixed, never change the value*/

#define FG_METER_RESISTANCE 0

/* Qmax for battery  */
// + 20161011-Rody [D6][PORTING][COMMON][BATTERY][][] apply battery zcv table from MTK #1
#if 1
/* Qmax for battery  */
#define Q_MAX_POS_50	2473 //2458
#define Q_MAX_POS_25	2432 //2404
#define Q_MAX_POS_0		2248 //1782
#define Q_MAX_NEG_10	1967 //951

#define Q_MAX_POS_50_H_CURRENT	2458 //2473
#define Q_MAX_POS_25_H_CURRENT	2404 //2432
#define Q_MAX_POS_0_H_CURRENT	1782 //2248
#define Q_MAX_NEG_10_H_CURRENT	951 //1967

#else
#define Q_MAX_POS_50 1463
#define Q_MAX_POS_25 1437
#define Q_MAX_POS_0 1220
#define Q_MAX_NEG_10 1137

#define Q_MAX_POS_50_H_CURRENT 1511
#define Q_MAX_POS_25_H_CURRENT 1462
#define Q_MAX_POS_0_H_CURRENT 818
#define Q_MAX_NEG_10_H_CURRENT 149
#endif
// - 20161011-Rody [D6][PORTING][COMMON][BATTERY][][] apply battery zcv table from MTK #1

/* Discharge Percentage */
#define OAM_D5		 1		/*  1 : D5,   0: D2*/


/* battery meter parameter */
#define CHANGE_TRACKING_POINT
#ifdef CONFIG_MTK_HAFG_20
#define CUST_TRACKING_POINT  0
#else
#define CUST_TRACKING_POINT  1
#endif
#define CUST_R_SENSE 68
#define CUST_HW_CC 0
#define AGING_TUNING_VALUE 103
#define CUST_R_FG_OFFSET 0

#define OCV_BOARD_COMPESATE	0 /*mV */
#define R_FG_BOARD_BASE 1000
#define R_FG_BOARD_SLOPE 1000 /*slope*/
// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify CAR_TUNE_VALUE to 96
//#define CAR_TUNE_VALUE 100 /*1.00*/
#define CAR_TUNE_VALUE 96 /*1.00*/
// - 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify CAR_TUNE_VALUE to 96


/* HW Fuel gague  */
#define CURRENT_DETECT_R_FG 10  /*1mA*/
#define MinErrorOffset 1000
#define FG_VBAT_AVERAGE_SIZE 18
#define R_FG_VALUE 10 /* mOhm, base is 20*/

/* fg 2.0 */
#define DIFFERENCE_HWOCV_RTC		30
#define DIFFERENCE_HWOCV_SWOCV		10
#define DIFFERENCE_SWOCV_RTC		10
#define MAX_SWOCV			3

#define DIFFERENCE_VOLTAGE_UPDATE	20
#define AGING1_LOAD_SOC			70
#define AGING1_UPDATE_SOC		30
// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Turn off condition about gauge 1 %
//#define BATTERYPSEUDO100		95
#define BATTERYPSEUDO100		98
// - 20161014 Rody, [D6][MISC][COMMON][BSP][][] Turn off condition about gauge 1 %
#define BATTERYPSEUDO1			4

#define Q_MAX_BY_SYS
#define Q_MAX_SYS_VOLTAGE		3300
#define SHUTDOWN_GAUGE0
// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Turn off condition about gauge 1 %
//#define SHUTDOWN_GAUGE1_XMINS
// - 20161014 Rody, [D6][MISC][COMMON][BSP][][] Turn off condition about gauge 1 %
#define SHUTDOWN_GAUGE1_MINS		60

// + 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify Shutdown voltage from 3.4V to 3.3V
//#define SHUTDOWN_SYSTEM_VOLTAGE		3400
#define SHUTDOWN_SYSTEM_VOLTAGE		3300
// - 20161014 Rody, [D6][MISC][COMMON][BSP][][] Modify Shutdown voltage from 3.4V to 3.3V
#define CHARGE_TRACKING_TIME		60
#define DISCHARGE_TRACKING_TIME		10

#define RECHARGE_TOLERANCE		10
/* SW Fuel Gauge */
#define MAX_HWOCV			5
#define MAX_VBAT			90
#define DIFFERENCE_HWOCV_VBAT		30

/* fg 1.0 */
#define CUST_POWERON_DELTA_CAPACITY_TOLRANCE	40
#define CUST_POWERON_LOW_CAPACITY_TOLRANCE		5
#define CUST_POWERON_MAX_VBAT_TOLRANCE			90
#define CUST_POWERON_DELTA_VBAT_TOLRANCE		30
#define CUST_POWERON_DELTA_HW_SW_OCV_CAPACITY_TOLRANCE	10


/* Disable Battery check for HQA */
#ifdef CONFIG_MTK_DISABLE_POWER_ON_OFF_VOLTAGE_LIMITATION
#define FIXED_TBAT_25
#endif

/* Dynamic change wake up period of battery thread when suspend*/
#define VBAT_NORMAL_WAKEUP		3600
#define VBAT_LOW_POWER_WAKEUP		3500
#define NORMAL_WAKEUP_PERIOD		5400
#define LOW_POWER_WAKEUP_PERIOD		300
#define CLOSE_POWEROFF_WAKEUP_PERIOD	30

#define INIT_SOC_BY_SW_SOC
/*
//#define SYNC_UI_SOC_IMM			//3. UI SOC sync to FG SOC immediately
*/
#define MTK_ENABLE_AGING_ALGORITHM	/*6. Q_MAX aging algorithm*/
#define MD_SLEEP_CURRENT_CHECK	/*5. Gauge Adjust by OCV 9. MD sleep current check*/
/*
//#define Q_MAX_BY_CURRENT		//7. Qmax variant by current loading.
*/
#define FG_BAT_INT
#define IS_BATTERY_REMOVE_BY_PMIC

#endif

#endif	/*#ifndef _CUST_BATTERY_METER_H*/
