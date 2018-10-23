#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/gpio.h>

struct pinctrl *gpioIdctrl = NULL;
struct pinctrl_state *pcba_id_init = NULL;
struct pinctrl_state *pcba_ver_init = NULL;

static int gpio_id_probe(struct platform_device *pdev);
static int gpio_id_remove(struct platform_device *pdev);

static int gpio_id_pinctrl_select(struct pinctrl *p, struct pinctrl_state *s)
{
	int ret = 0;
	if (p != NULL && s != NULL) {
            ret = pinctrl_select_state(p, s);
	} else {
            ret = -1;
	}
	return ret;
}

static void gpio_func_reset(void) 
{
    int ret=0;

    pcba_id_init = pinctrl_lookup_state(gpioIdctrl, "gpio_id_cfg");  
    if (IS_ERR(pcba_id_init)) 
    {
        pr_debug("%s : pinctrl err, pcba_id init fail \n", __func__);
        return;
    }

    pcba_ver_init = pinctrl_lookup_state(gpioIdctrl, "pstage_id_cfg");
    if (IS_ERR(pcba_ver_init)) 
    {
        pr_debug("%s : pinctrl err, pcba_ver init fail \n", __func__);
        return;
    }

    ret = gpio_id_pinctrl_select(gpioIdctrl, pcba_id_init);
    if(ret<0) 
    {
        pr_debug("%s : pcba_id pinctrl_select error \n", __func__);
        return;
    }

    ret = gpio_id_pinctrl_select(gpioIdctrl, pcba_ver_init);
    if(ret<0) 
    {
        pr_debug("%s : pcba_ver pinctrl_select error \n", __func__);
        return;
    }
}

static ssize_t show_gpio_id_status(struct device_driver *driver, char *buf) 
{
    uint8_t ret = 0;
    int pcba_id_num=0;
    int pcba_id_val[3]={0};
 
    struct device_node *node = of_find_compatible_node(NULL, NULL, "mediatek,gpio_id");
    if (!node) {
        pr_debug("Can't find the node of mediatek,gpio_usage_mapping \n");
        return 0;
    }

    gpio_func_reset();

    of_property_read_u32(node, "pcba_id0-gpio", &pcba_id_num);
    pcba_id_val[0] = __gpio_get_value(pcba_id_num);

    of_property_read_u32(node, "pcba_id1-gpio", &pcba_id_num);
    pcba_id_val[1] = __gpio_get_value(pcba_id_num);

    of_property_read_u32(node, "pcba_id2-gpio", &pcba_id_num);
    pcba_id_val[2] = __gpio_get_value(pcba_id_num);

    printk("[Steven] Read value: PCBA_ID[0]=%d, PCBA_ID[1]=%d, PCBA_ID[2]=%d \n", pcba_id_val[0], pcba_id_val[1], pcba_id_val[2]);

    if(pcba_id_val[0]==0 && pcba_id_val[1]==0 && pcba_id_val[2]==0)
    {
        /* Arima Model: 5554 */
        ret = sprintf(buf, "%s\n\r", "X250k");
    }
    else if(pcba_id_val[0]==0 && pcba_id_val[1]==0 && pcba_id_val[2]==1)
    {
        /* Arima Model: 5555 */
        ret = sprintf(buf, "%s\n\r", "M250y");
    }
    else if(pcba_id_val[0]==0 && pcba_id_val[1]==1 && pcba_id_val[2]==0)
    {
        /* Arima Model: 5556 */
        ret = sprintf(buf, "%s\n\r", "X250z");
    }
    else if(pcba_id_val[0]==0 && pcba_id_val[1]==1 && pcba_id_val[2]==1)
    {
        /* Arima Model: 5557 */
        ret = sprintf(buf, "%s\n\r", "X250h");
    }
    else if(pcba_id_val[0]==1 && pcba_id_val[1]==0 && pcba_id_val[2]==0)
    {
        /* Arima Model: 5558 */
        ret = sprintf(buf, "%s\n\r", "X250f");
    }
    else if(pcba_id_val[0]==1 && pcba_id_val[1]==0 && pcba_id_val[2]==1)
    {
        /* Arima Model: 5559 */
        ret = sprintf(buf, "%s\n\r", "X250ar");
    }
    else if(pcba_id_val[0]==1 && pcba_id_val[1]==1 && pcba_id_val[2]==0)
    {
        /* Arima Model: 5560 */
        ret = sprintf(buf, "%s\n\r", "X250ds");
    }
    else if(pcba_id_val[0]==1 && pcba_id_val[1]==1 && pcba_id_val[2]==1)
    {
        /* Arima Model: 5561 */
        ret = sprintf(buf, "%s\n\r", "X250tr");
    }
    else
        ret = sprintf(buf, "%s\n\r", "Unknown");

    return ret + 1;
}

static ssize_t show_pstage_id_status(struct device_driver *driver, char *buf) 
{
    uint8_t ret = 0;
    int pcba_ver_num=0;
    int pcba_ver_val[3]={0};

    struct device_node *node = of_find_compatible_node(NULL, NULL, "mediatek,gpio_id");
    if (!node) {
        pr_debug("Can't find the node of mediatek,gpio_usage_mapping \n");
        return 0;
    }

    gpio_func_reset();

    of_property_read_u32(node, "pcba_ver0-gpio", &pcba_ver_num);
    pcba_ver_val[0] = __gpio_get_value(pcba_ver_num);

    of_property_read_u32(node, "pcba_ver1-gpio", &pcba_ver_num);
    pcba_ver_val[1] = __gpio_get_value(pcba_ver_num);

    of_property_read_u32(node, "pcba_ver2-gpio", &pcba_ver_num);
    pcba_ver_val[2] = __gpio_get_value(pcba_ver_num);

    printk("[Steven] Read value: PCBA_VER[0]=%d, PCBA_VER[1]=%d, PCBA_VER[2]=%d \n", pcba_ver_val[0], pcba_ver_val[1], pcba_ver_val[2]);

    if( pcba_ver_val[0]==0 && pcba_ver_val[1]==0 && pcba_ver_val[2]==0 )
    {
        /* PP */
        ret = sprintf(buf, "%s\n\r", "001");
    }
    else if( pcba_ver_val[0]==0 && pcba_ver_val[1]==0 && pcba_ver_val[2]==1 )
    {
        /* PP2 */
        ret = sprintf(buf, "%s\n\r", "002"); 
    }
    else if( pcba_ver_val[0]==0 && pcba_ver_val[1]==1 && pcba_ver_val[2]==0 )
    {
        /* DV */
        ret = sprintf(buf, "%s\n\r", "003");
    }
    else if( pcba_ver_val[0]==0 && pcba_ver_val[1]==1 && pcba_ver_val[2]==1 )
    {
        /* PV */
        ret = sprintf(buf, "%s\n\r", "004");
    }
    else
    {
        /* Reserved */
        ret = sprintf(buf, "%s\n\r", "reserved");
    }

    return ret + 1;
}

DRIVER_ATTR(gpio_id, 0644, show_gpio_id_status, NULL);
DRIVER_ATTR(pstage_id, 0644, show_pstage_id_status, NULL);

static const struct of_device_id gpio_id_dev_of_match[] = {
	{.compatible = "mediatek,gpio_id",},
	{},
};

static struct platform_driver gpio_pltform_drv = {
    .probe = gpio_id_probe,
    .remove = gpio_id_remove,
    .driver = {
        .name = "gpio_id",
        .owner = THIS_MODULE,
        .of_match_table = gpio_id_dev_of_match,
    }
};

static struct platform_device gpio_pltform_dev = {
    .name = "gpio_id",
};

static int gpio_id_probe(struct platform_device *pdev) 
{
    int ret = 0;

    /* pinctrl init */
    gpioIdctrl = devm_pinctrl_get(&pdev->dev);
    if (IS_ERR(gpioIdctrl)) {
        dev_err(&pdev->dev, "Cannot find gpio_id pinctrl!");
        ret = PTR_ERR(gpioIdctrl);
	return ret;
    }

    /* Create device node */
    ret = driver_create_file(&gpio_pltform_drv.driver, &driver_attr_gpio_id);
    if (ret) 
    {
        printk(KERN_ERR "gpio_id node create failed \n");
        return ret;
    }

    ret = driver_create_file(&gpio_pltform_drv.driver, &driver_attr_pstage_id);
    if (ret) 
    {
        printk(KERN_ERR "pstage_id node create failed \n");
        return ret;
    }

    printk("gpio id probe success \n");
    return 0;
}

static int gpio_id_remove(struct platform_device *pdev) {
    return 0;
}

static int __init gpio_id_init(void) {
    printk("%s\n\r", __func__);
    platform_device_register(&gpio_pltform_dev);
    platform_driver_register(&gpio_pltform_drv);
    return 0;
}

static void __exit gpio_id_exit(void) {
    platform_device_unregister(&gpio_pltform_dev);
    platform_driver_unregister(&gpio_pltform_drv);
}

module_init(gpio_id_init);
module_exit(gpio_id_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("add show modem auto detect gpio status");
