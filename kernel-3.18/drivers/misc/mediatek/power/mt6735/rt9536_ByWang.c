// <<< 2016/08/03-youchihwang, [LV3][PORTING][COMMON][BATTERY][][]Porting charger, battery,
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <mt-plat/charging.h>
#include <mt-plat/mt_gpio.h>


#define GPIO_CHG_EN   (78 | 0x80000000)
#define EINT_CHG_PGB  (68 | 0x80000000)
#define EINT_CHG_STAT (80 | 0x80000000)

kal_bool chargin_hw_init_done = KAL_FALSE;


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



static struct platform_device rt9536_device = {
        .name = "rt9536",
        .id = -1,
};

static int rt9536_driver_probe(struct platform_device *dev)
{
        //
        // initialize GPIO_CHG_EN pin
        //
        mt_set_gpio_mode(GPIO_CHG_EN, GPIO_MODE_00);
        mt_set_gpio_pull_enable(GPIO_CHG_EN, GPIO_PULL_ENABLE);
        mt_set_gpio_pull_select(GPIO_CHG_EN, GPIO_PULL_UP);
        mt_set_gpio_dir(GPIO_CHG_EN, GPIO_DIR_OUT);
        
        //
        // disable charging
        // set GPIO_CHG_EN pin to high, then wait for at least 2ms
        //
        mt_set_gpio_out(GPIO_CHG_EN, GPIO_OUT_ONE);
        udelay(2100);

        //
        // initialize EINT_CHG_PGB pin
        //
        mt_set_gpio_mode(EINT_CHG_PGB, GPIO_MODE_00);
        mt_set_gpio_pull_enable(EINT_CHG_PGB, GPIO_PULL_ENABLE);
        mt_set_gpio_pull_select(EINT_CHG_PGB, GPIO_PULL_UP);
        mt_set_gpio_dir(EINT_CHG_PGB, GPIO_DIR_IN);

        //
        // initialize EINT_CHG_STAT pin
        //
        mt_set_gpio_mode(EINT_CHG_STAT, GPIO_MODE_00);
        mt_set_gpio_pull_enable(EINT_CHG_STAT, GPIO_PULL_ENABLE);
        mt_set_gpio_pull_select(EINT_CHG_STAT, GPIO_PULL_UP);
        mt_set_gpio_dir(EINT_CHG_STAT, GPIO_DIR_IN);
        
        chargin_hw_init_done = KAL_TRUE;

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