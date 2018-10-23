// +++++  [5556 Arima] 20160909 Add Hardware Display Function By Edwin
#include <linux/arima_interface.h>
#include <linux/gpio.h>
#include <linux/types.h>
#include <linux/printk.h>

static int arima_gpio_get_value(unsigned int *gpio_value, int gpio_number, char *label) 
{
    printk("[Hw Version] Get gpio %d \n",gpio_number);
	int err;	
	printk("[Hw Version] gpio_number: %d label: %s\n", gpio_number, label);
	gpio_direction_input(gpio_number);
    
	*gpio_value = gpio_get_value(gpio_number);
	printk("[Hw Version] Get value for GPIO %d: 0x%x\n", gpio_number, *gpio_value);
    
	gpio_free(gpio_number);
    
	return 0;
exit:
	return err;
}

static void arima_gpio_free(int *gpio_array,int *gpio_size)
{
    printk("[Hw Version] arima_gpio_free() \n");   
	int i;
	for(i=0;i<(*gpio_size);i++){
		gpio_free(*(gpio_array+i)); 
	}   
}


int arima_hw_detection(unsigned int *buf , int *gpio_array , int gpio_size)
{
    unsigned int gpio_value = 0x0;
    int i;
	int err;
	*buf = 0x0;
    
	printk("[Hw Version] arima_hw_detection \n"); 
	for(i=0;i<gpio_size;i++)
	{
		err = arima_gpio_get_value(&gpio_value,*(gpio_array+i),"GPIO");
		if(err < 0){
			printk("%s : [Hw Version] arima_gpio_get_value failed \n",__func__);
			goto exit;
		}
        *buf |= gpio_value << i;
	}
exit:
	arima_gpio_free(&gpio_array,&gpio_size);
	return err;
}

// -----  [5556 Arima] 20160909 Add Hardware Display Function By Edwin
