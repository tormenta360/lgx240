#ifndef _CUST_BAT_H_
#define _CUST_BAT_H_

/* stop charging while in talking mode */
#define STOP_CHARGING_IN_TAKLING
#define TALKING_RECHARGE_VOLTAGE 3800
#define TALKING_SYNC_TIME		   60

//<2016/10/26-nickygao, [LV3][FEATURE][COMMON][BSP][][]Battery OTP test
/* Battery Temperature Protection */
#define BAT_LOW_TEMP_PROTECT_ENABLE
#define MTK_TEMPERATURE_RECHARGE_SUPPORT
#define MAX_CHARGE_TEMPERATURE  55
#define MAX_CHARGE_TEMPERATURE_MINUS_X_DEGREE	52
#define MIN_CHARGE_TEMPERATURE  -10
#define MIN_CHARGE_TEMPERATURE_PLUS_X_DEGREE	-7
#define ERR_CHARGE_TEMPERATURE  0xFF

#define MAX_SECOND_CHARGE_TEMPERATURE  45
#define MAX_SECOND_CHARGE_TEMPERATURE_MINUS_X_DEGREE  42
#define MAX_SECOND_T_BAT_V 4000
#define MAX_BAT_TEMPERATURE 60
#define ALERT_BAT_TEMERATURE 57
//<2016/10/26-nickygao

/* Linear Charging Threshold */
#define V_PRE2CC_THRES 3400
#define V_CC2TOPOFF_THRES		4050
//<2016/10/26-nickygao, [LV3][FEATURE][COMMON][BSP][][]Set recharing voltage changes as 4.28V by SW because RT9536 dosen't have recharging voltage
#define RECHARGING_VOLTAGE      4280//4230 //4110
//>2016/10/26-nickygao
#define CHARGING_FULL_CURRENT    199	//mA
//<2016/09/15-nickygao, [LV3][PORTING][COMMON][BSP][][]Porting rt9536 from D5
/* Charging Current Setting */
#define USB_CHARGER_CURRENT_SUSPEND			0
#define USB_CHARGER_CURRENT_UNCONFIGURED	CHARGE_CURRENT_70_00_MA
#define USB_CHARGER_CURRENT_CONFIGURED		CHARGE_CURRENT_500_00_MA

#define USB_CHARGER_CURRENT					CHARGE_CURRENT_500_00_MA
#define AC_CHARGER_CURRENT					CHARGE_CURRENT_850_00_MA//CHARGE_CURRENT_650_00_MA
#define NON_STD_AC_CHARGER_CURRENT			CHARGE_CURRENT_500_00_MA
#define CHARGING_HOST_CHARGER_CURRENT       CHARGE_CURRENT_650_00_MA
#define APPLE_0_5A_CHARGER_CURRENT          CHARGE_CURRENT_500_00_MA
#define APPLE_1_0A_CHARGER_CURRENT          CHARGE_CURRENT_650_00_MA
#define APPLE_2_1A_CHARGER_CURRENT          CHARGE_CURRENT_800_00_MA
//<2016/09/15-nickygao

/* Precise Tunning */
#define BATTERY_AVERAGE_DATA_NUMBER	3
#define BATTERY_AVERAGE_SIZE 30

//<2016/12/22-nickygao, [LV3][MISC][COMMON][BATTERY][][]Reduce quantity of battery temperature to optimize updating time
#define CUSTOM_BATTERY_AVERAGE_DATA_NUMBER	3
#define CUSTOM_BATTERY_AVERAGE_SIZE	3//5
//<2016/12/22-nickygao

/* charger error check */
#define V_CHARGER_ENABLE 0				/* 1:ON , 0:OFF	*/
#define V_CHARGER_MAX 6500				/* 6.5 V	*/
#define V_CHARGER_MIN 4400				/* 4.4 V	*/

/* Tracking TIME */
#define ONEHUNDRED_PERCENT_TRACKING_TIME	10	/* 10 second	*/
#define NPERCENT_TRACKING_TIME 20	/* 20 second	*/
#define SYNC_TO_REAL_TRACKING_TIME 60	/* 60 second	*/
#define V_0PERCENT_TRACKING							3450 /*3450mV	*/

/* Battery Notify */
#define BATTERY_NOTIFY_CASE_0001_VCHARGER
#define BATTERY_NOTIFY_CASE_0002_VBATTEMP
/*
//#define BATTERY_NOTIFY_CASE_0003_ICHARGING
//#define BATTERY_NOTIFY_CASE_0004_VBAT
//#define BATTERY_NOTIFY_CASE_0005_TOTAL_CHARGINGTIME
*/
/* High battery support */
// + 20161006-Rody,[LV3][PORTING][COMMON][BATTERY][][] Support High battery voltage
#define HIGH_BATTERY_VOLTAGE_SUPPORT
// - 20161006-Rody,[LV3][PORTING][COMMON][BATTERY][][] Support High battery voltage

/* JEITA parameter */
/*#define MTK_JEITA_STANDARD_SUPPORT*/
#define CUST_SOC_JEITA_SYNC_TIME 30
#define JEITA_RECHARGE_VOLTAGE  4110	/* for linear charging */
#ifdef HIGH_BATTERY_VOLTAGE_SUPPORT
#define JEITA_TEMP_ABOVE_POS_60_CV_VOLTAGE		BATTERY_VOLT_04_240000_V
#define JEITA_TEMP_POS_45_TO_POS_60_CV_VOLTAGE		BATTERY_VOLT_04_240000_V
#define JEITA_TEMP_POS_10_TO_POS_45_CV_VOLTAGE		BATTERY_VOLT_04_340000_V
#define JEITA_TEMP_POS_0_TO_POS_10_CV_VOLTAGE		BATTERY_VOLT_04_240000_V
#define JEITA_TEMP_NEG_10_TO_POS_0_CV_VOLTAGE		BATTERY_VOLT_04_040000_V
#define JEITA_TEMP_BELOW_NEG_10_CV_VOLTAGE		BATTERY_VOLT_04_040000_V
#else
#define JEITA_TEMP_ABOVE_POS_60_CV_VOLTAGE		BATTERY_VOLT_04_100000_V
#define JEITA_TEMP_POS_45_TO_POS_60_CV_VOLTAGE	BATTERY_VOLT_04_100000_V
#define JEITA_TEMP_POS_10_TO_POS_45_CV_VOLTAGE	BATTERY_VOLT_04_200000_V
#define JEITA_TEMP_POS_0_TO_POS_10_CV_VOLTAGE	BATTERY_VOLT_04_100000_V
#define JEITA_TEMP_NEG_10_TO_POS_0_CV_VOLTAGE	BATTERY_VOLT_03_900000_V
#define JEITA_TEMP_BELOW_NEG_10_CV_VOLTAGE		BATTERY_VOLT_03_900000_V
#endif
/* For JEITA Linear Charging only */
#define JEITA_NEG_10_TO_POS_0_FULL_CURRENT  120
#define JEITA_TEMP_POS_45_TO_POS_60_RECHARGE_VOLTAGE  4000
#define JEITA_TEMP_POS_10_TO_POS_45_RECHARGE_VOLTAGE  4100
#define JEITA_TEMP_POS_0_TO_POS_10_RECHARGE_VOLTAGE   4000
#define JEITA_TEMP_NEG_10_TO_POS_0_RECHARGE_VOLTAGE   3800
#define JEITA_TEMP_POS_45_TO_POS_60_CC2TOPOFF_THRESHOLD	4050
#define JEITA_TEMP_POS_10_TO_POS_45_CC2TOPOFF_THRESHOLD	4050
#define JEITA_TEMP_POS_0_TO_POS_10_CC2TOPOFF_THRESHOLD	4050
#define JEITA_TEMP_NEG_10_TO_POS_0_CC2TOPOFF_THRESHOLD	3850


/* For CV_E1_INTERNAL */
#define CV_E1_INTERNAL

/* Disable Battery check for HQA */
#ifdef CONFIG_MTK_DISABLE_POWER_ON_OFF_VOLTAGE_LIMITATION
#define CONFIG_DIS_CHECK_BATTERY
#endif

#ifdef CONFIG_MTK_FAN5405_SUPPORT
#define FAN5405_BUSNUM 1
#endif

//<2016/12/24-nickygao, [LV3][MISC][COMMON][BATTERY][][]SW FG doesn't use
//#define MTK_PLUG_OUT_DETECTION
//<2016/12/24-nickygao

#endif /* _CUST_BAT_H_ */
