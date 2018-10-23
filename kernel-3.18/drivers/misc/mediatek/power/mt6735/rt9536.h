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

#ifndef __LINUX_RT9536_CHARGER_H
#define __LINUX_RT9536_CHARGER_H

 //<2016/09/15-nickygao, [E0][PORTING][COMMON][BSP][][]Porting rt9536
#define CHG_EN_SET_N                         78//(GPIO78| 0x80000000)//GPIO_SWCHARGER_EN_PIN
#define CHG_EN_MODE                          GPIO17_MODE//GPIO_SWCHARGER_EN_PIN_M_GPIO
#define CHG_EN_DIR                               GPIO17_DIR//GPIO32_DIR
#define CHG_EN_DATA_OUT                 GPIO17_DATAOUT
 //#define CHG_EN_PULL_ENABLE        GPIO35_PULLEN
 //#define CHG_EN_PULL_SELECT        GPIO35_PULL

 #define CHG_EOC_N                               80//(GPIO80| 0x80000000)//GPIO_EINT_CHG_STAT_PIN
 #define CHG_EOC_MODE                       GPIO18_MODE//GPIO_EINT_CHG_STAT_PIN_M_GPIO
 #define CHG_EOC_DIR                            GPIO18_DIR//GPIO35_DIR
 #define CHG_EOC_PULL_ENABLE         GPIO18_PULLEN//GPIO35_PULLEN
 #define CHG_EOC_PULL_SELECT         GPIO18_PULL//GPIO35_PULL

 #define PGB_N                                          68//(GPIO68| 0x80000000)//GPIO_EINT_CHG_STAT_PIN
 #define PGB_MODE                                  GPIO15_MODE//GPIO_MODE_00 //GPIO_EINT_CHG_STAT_PIN_M_GPIO
 #define PGB_DIR                                       GPIO15_DIR//GPIO0_DIR// GPIO119_DIR
 #define PGB_PULL_ENABLE                   GPIO15_PULLEN//GPIO0_PULLEN// GPIO119_PULLEN
 #define PGB_PULL_SELECT                   GPIO15_PULL//GPIO0_PULL//  GPIO119_PULL
 //<2016/09/15-nickygao

/* Function Prototype */
//enum power_supply_type get_charging_ic_status(void);

extern void charging_ic_active_default(void);
//void charging_ic_set_ta_mode(void);
//void charging_ic_set_usb_mode(void);
extern void charging_ic_deactive(void);
//void charging_ic_set_factory_mode(void);
extern void rt9536_charging_enable(unsigned int set_current, unsigned int enable);
extern unsigned char rt9536_check_eoc_status(void);

//<2016/09/15-nickygao, [LV3][MISC][COMMON][BSP][][]Detect charger status
extern unsigned char rt9536_check_charger_status(void);
//<2016/09/15-nickygao

#endif /* __LINUX_MAX8971_CHARGER_H */
