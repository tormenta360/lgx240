#include <linux/string.h>
#include <linux/kernel.h>
#include <lcm_drv.h>

// ---------------------------------------------------------------------------
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/module.h>  
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/irq.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>           //Edwin ++ 

#ifdef CONFIG_MTK_LEGACY
#include <mach/mt_gpio.h>
#include <cust_gpio_usage.h>
#include <cust_i2c.h>
#else
#include <mt-plat/mt_gpio.h>
#endif

//  Local Constants
// ---------------------------------------------------------------------------
#define	FRAME_WIDTH			(720)
#define FRAME_HEIGHT		(1280)

#define   LCM_HSYNC_NUM		(36)//(36)  
#define   LCM_HBP_NUM		(85)//(42) //(100)  
#define   LCM_HFP_NUM		(85)//(44) //(100)

#define   LCM_VSYNC_NUM		(2)  
#define   LCM_VBP_NUM		(16)  
#define   LCM_VFP_NUM		(9)   

#define   LCM_LINE_BYTE		((FRAME_WIDTH+LCM_HSYNC_NUM+LCM_HBP_NUM+LCM_HFP_NUM)*3)

#define REGFLAG_DELAY		0XFE
#define REGFLAG_END_OF_TABLE	0xFF   // END OF REGISTERS MARKER

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#ifndef BUILD_LK
//static unsigned int lcm_esd_test = FALSE;      ///only for ESD test
#endif
// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util;

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------
#define dsi_set_cmdq_V3(para_tbl,size,force_update)  lcm_util.dsi_set_cmdq_V3(para_tbl,size,force_update)
#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)

#define wrtie_cmd(cmd)			       lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)     lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)			       lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)  lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

#define set_gpio_lcd_enp(cmd) \
		lcm_util.set_gpio_lcd_enp_bias(cmd)
#define set_gpio_lcd_enn(cmd) \
		lcm_util.set_gpio_lcd_enn_bias(cmd)

#define   LCM_DSI_CMD_MODE	0

#define GPIO_LCD_BIAS_ENP_PIN	(100|0x80000000)
#define GPIO_LCD_BIAS_ENN_PIN	(108|0x80000000)

static bool is_lcm_suspend = 0;
//<2016/08/10-stevenchen, Fix system reboot when suspend
//static struct delayed_work lcm_work;
//static struct workqueue_struct *lcm_wq = NULL;
//>2016/08/10-stevenchen

#if 0
extern int tpd_lcm_resume();
extern int tpd_lcm_suspend();

static void tp_control_func(struct work_struct *work) {
    printk("hx8394f tp_control_func\n\r");
    if (is_lcm_suspend == 1) {
        printk("hx8394f tp suspend\n\r");
        tpd_lcm_suspend();
    }
    else if (is_lcm_suspend == 0) {
        printk("hx8394f tp resume\n\r");
        tpd_lcm_resume();
    }
}
#endif


/*****************************************************************************
** Gate driver function
******************************************************************************/
#include <linux/module.h>
int lcm_gate_write_bytes(unsigned char addr, unsigned char value);

static void lcm_gate_enable(int enable)
{
    int ret;
    unsigned char cmd, data;
    
    printk("[Steven] %s = %d \n", __func__, enable);
    if( TRUE == enable )
    {
    	mt_set_gpio_mode(GPIO_LCD_BIAS_ENP_PIN, GPIO_MODE_00);
		mt_set_gpio_dir(GPIO_LCD_BIAS_ENP_PIN, GPIO_DIR_OUT);
		mt_set_gpio_out(GPIO_LCD_BIAS_ENP_PIN, GPIO_OUT_ONE);
        MDELAY(5);
		mt_set_gpio_mode(GPIO_LCD_BIAS_ENN_PIN, GPIO_MODE_00);
		mt_set_gpio_dir(GPIO_LCD_BIAS_ENN_PIN, GPIO_DIR_OUT);
		mt_set_gpio_out(GPIO_LCD_BIAS_ENN_PIN, GPIO_OUT_ONE);
        MDELAY(5);

        cmd  = 0x00;
        data = 0x0F;
        ret = lcm_gate_write_bytes(cmd, data);
	if(ret<0)
            printk("lcm gate I2C write cmd=%0x error \n", cmd);

        cmd  = 0x01;
        data = 0x0F;
        ret = lcm_gate_write_bytes(cmd, data);
	if(ret<0)
            printk("lcm gate I2C write cmd=%0x error \n", cmd);
    }
    else
    {
		mt_set_gpio_mode(GPIO_LCD_BIAS_ENN_PIN, GPIO_MODE_00);
		mt_set_gpio_dir(GPIO_LCD_BIAS_ENN_PIN, GPIO_DIR_OUT);
		//<2016/09/22-tracychui,[D6][BUG][COMMON][LCM][][]Close Gate IC BIAS GPIO when phone suspend
		//mt_set_gpio_out(GPIO_LCD_BIAS_ENN_PIN, GPIO_OUT_ONE);
		mt_set_gpio_out(GPIO_LCD_BIAS_ENN_PIN, GPIO_OUT_ZERO);
        MDELAY(5);
    	mt_set_gpio_mode(GPIO_LCD_BIAS_ENP_PIN, GPIO_MODE_00);
		mt_set_gpio_dir(GPIO_LCD_BIAS_ENP_PIN, GPIO_DIR_OUT);
		//mt_set_gpio_out(GPIO_LCD_BIAS_ENP_PIN, GPIO_OUT_ONE);
		mt_set_gpio_out(GPIO_LCD_BIAS_ENP_PIN, GPIO_OUT_ZERO);
		//>2016/09/22-tracychui
        MDELAY(5);
    }
}

struct LCM_setting_table {
	unsigned int cmd;
	unsigned char count;
	unsigned char para_list[64];
};
//<2016/12/21-EdwinHuang, Create the second source table. 
static struct LCM_setting_table lcm_init_setting_second[] = 
{
	{ 0xb9, 3 , { 0xff, 0x83, 0x94 }},
    { 0xba, 6 , { 0x63, 0x03, 0x68, 0x6b, 0xb2, 0xc0 }},
    //<20170424 tracy, Optimized LCM initial code by vendor for desence
	//<20170410 tracy, Optimized LCM initial code by vendor for desence
	{ 0xb1, 10, { 0x48, 0x10, 0x70, 0x09, 0x33, 0x54, 0xb1, 0x31, 0x6b, 0x2f }},
	//{ 0xb1, 10, { 0x48, 0x10, 0x70, 0x09, 0x33, 0x22, 0xb0, 0x30, 0x6b, 0x2f }},
	//{ 0xb1, 10, { 0x48, 0x12, 0x72, 0x09, 0x33, 0x22, 0xb1, 0x31, 0x6b, 0x2f }},
	//>20170410 tracy
	//>20170410 tracy
    { 0xb2, 6 , { 0x00, 0x80, 0x64, 0x0e, 0x0d, 0x2f }},
    { 0xb4, 21, { 0x73, 0x74, 0x73, 0x74, 0x73, 0x74, 0x01, 0x0c, 0x86, 0x75, 0x00,
                  0x3f, 0x73, 0x74, 0x73, 0x74, 0x73, 0x74, 0x01, 0x0c, 0x86 }},
    { 0xb6, 2 , { 0x6e, 0x6e }},
    { 0xd3, 33, { 0x00, 0x00, 0x07, 0x07, 0x40, 0x07, 0x10, 0x00, 0x08, 0x10, 0x08,
                  0x00, 0x08, 0x54, 0x15, 0x0e, 0x05, 0x0e, 0x02, 0x15, 0x06, 0x05,
                  0x06, 0x47, 0x44, 0x0a, 0x0a, 0x4b, 0x10, 0x07, 0x07, 0x0e, 0x40 }},
    //<20170509 tracy, Optimized LCM initial code by vendor for display issue at high temperature and humidity        
    //{ 0xd5, 44, { 0x1a, 0x1a, 0x1b, 0x1b, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,             
    { 0xd5, 44, { 0x19, 0x19, 0x18, 0x18, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                  0x07, 0x08, 0x09, 0x0a, 0x0b, 0x24, 0x25, 0x18, 0x18, 0x26, 0x27,
                  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
                  0x18, 0x18, 0x18, 0x18, 0x18, 0x20, 0x21, 0x18, 0x18, 0x18, 0x18 }},
    //>20170509 tracy            
    { 0xd6, 44, { 0x1a, 0x1a, 0x1b, 0x1b, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05,
                  0x04, 0x03, 0x02, 0x01, 0x00, 0x21, 0x20, 0x18, 0x18, 0x21, 0x20,
                  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
                  0x18, 0x18, 0x18, 0x18, 0x18, 0x25, 0x24, 0x18, 0x18, 0x18, 0x18 }},
    { 0xe0, 58, { 0x00, 0x19, 0x22, 0x29, 0x2b, 0x2f, 0x32, 0x2f, 0x60, 0x6f,
                  0x7c, 0x79, 0x7e, 0x8e, 0x91, 0x92, 0x9c, 0x9d, 0x97, 0xa6,
                  0xb4, 0x58, 0x57, 0x5a, 0x5d, 0x61, 0x69, 0x7b, 0x7F, 0x00,
                  0x18, 0x22, 0x29, 0x2b, 0x2f, 0x32, 0x2f, 0x60, 0x6f,
                  0x7c, 0x79, 0x7e, 0x8e, 0x91, 0x92, 0x9c, 0x9d, 0x97, 0xa6,
                  0xb4, 0x58, 0x57, 0x5a, 0x5d, 0x61, 0x69, 0x7b, 0x7F}},
    { 0xcc, 1 , { 0x0B }},
    { 0xc0, 2 , { 0x1f, 0x31 }},
    { 0xd4, 1 , { 0x02 }},
    { 0xbd, 1 , { 0x02}},
    { 0xd8, 12, { 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}},
    { 0xbd, 1 , { 0x01}},
    { 0xb1, 1 , { 0x00}},
    { 0xbd, 1 , { 0x00}},
    { 0xc6, 1 , { 0xef}},
    { 0x11, 0 , { 0x00}},//sleep out
    //delay(120),
    { REGFLAG_DELAY , 120 , {}},
    { 0x29, 0 , { 0x00}},//display on
    //delay(20) , 
    { REGFLAG_DELAY , 20  , {}}
};
//>2016/12/21-EdwinHuang
//<2016/08/15-stevenchen, Optimized LCM initial code by vendor.
static struct LCM_setting_table lcm_init_setting_main[] = 
{
  /*
  Note :

  Data ID will depends on the following rule.
	
	count of parameters > 1	=> Data ID = 0x39
	count of parameters = 1	=> Data ID = 0x15
	count of parameters = 0	=> Data ID = 0x05

  Structure Format :

  {DCS command, count of parameters, {parameter list}}
  {REGFLAG_DELAY, milliseconds of time, {}},

  ...

  Setting ending by predefined flag
	
  {REGFLAG_END_OF_TABLE, 0x00, {}}
  */
  //Set,0xEXTC
  {0xB9,3,{0xFF ,0x83 ,0x94 }},

//<2016/09/01-stevenchen, Reduce LCM noise for Touch performance
  //Set,0xPower
  {0xB1,10,{0x50,0x12,0x72,0x09,0x32,0x22,0x71,0x31,0x45,0x2F }},
//>2016/09/01-stevenchen

  //Set,0xMIPI
  {0xBA,6,{0x63, 0x03, 0x68, 0x6B, 0xB2, 0xC0 }},

  //Set,0xD2
  {0xD2,1,{0x55 }},

  //Set,0xDisplay
  {0xB2,5,{0x00, 0x80, 0x64, 0x10, 0x07 }},

//<2016/09/01-stevenchen, Reduce LCM noise for Touch performance
  //Set,0xCYC
  {0xB4,21,{0x2C,0x74,0x2C,0x74,0x2C,0x74,0x01,0x0C,0x86,0x75,0x00,0x3F,0x2C,0x74,0x2C,0x74,0x2C,0x74,0x01,0x0C,0x86 }},

  //Set,0xD3
  {0xD3,33,{0x00,0x00,0x0F,0x0F,0x40,0x1E,0x08,0x00,0x32,0x10,0x08,0x00,0x08,0x54,0x15,0x10,0x05,0x04,0x02,0x12,0x10,0x05,0x07,0x23,0x23,0x0C,0x0C,0x27,0x10,0x07,0x07,0x10,0x40 }},
//>2016/09/01-stevenchen

  //Set,0xGIP
  {0xD5,44,{0x19,0x19,0x18,0x18,0x1B,0x1B,0x1A,0x1A,0x04,0x05,0x06,0x07,0x00,0x01,0x02,0x03,0x20,0x21,0x18,0x18,0x22,0x23,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18 }},

  //Set,0xD6
  {0xD6,44,{0x18,0x18,0x19,0x19,0x1B,0x1B,0x1A,0x1A,0x03,0x02,0x01,0x00,0x07,0x06,0x05,0x04,0x23,0x22,0x18,0x18,0x21,0x20,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18 }},

//<20161129 tracy, Update Gamma curve
//<20161031 tracy, Update Gamma curve
//<2016/09/01-stevenchen, Update Gamma curve
  //GAMMA SET
  // 20161021 calvin ++, Update Gamma curve
  //{0xE0,58,{0x00,0x01,0x03,0x04,0x06,0x08,0x0A,0x08,0x10,0x1F,0x2F,0x33,0x41,0x5C,0x6C,0x7C,0x8F,0x98,0x91,0xA9,0xB4,0x5A,0x59,0x5F,0x64,0x68,0x71,0x7C,0x7F,0x00,0x01,0x03,0x04,0x06,0x08,0x0A,0x08,0x10,0x1F,0x2F,0x33,0x41,0x5C,0x6C,0x7C,0x8F,0x98,0x91,0xA9,0xB4,0x5A,0x59,0x5F,0x64,0x69,0x71,0x7C,0x7F}},
  //{0xE0,58,{0x00,0x01,0x03,0x04,0x06,0x08,0x0A,0x08,0x10,0x1F,0x2F,0x33,0x41,0x5C,0x6C,0x7C,0x8F,0x9A,0x91,0xA9,0xB4,0x5A,0x59,0x5F,0x64,0x68,0x71,0x7C,0x7F,0x00,0x01,0x03,0x04,0x06,0x08,0x0A,0x08,0x10,0x1F,0x2F,0x33,0x41,0x5C,0x6C,0x7C,0x8F,0x9A,0x91,0xA9,0xB4,0x5A,0x59,0x5F,0x64,0x69,0x71,0x7C,0x7F}},
  //{0xE0,58,{0x05,0x07,0x08,0x0a,0x0C,0x0D,0x0F,0x0B,0x15,0x28,0x38,0x3C,0x47,0x62,0x70,0x7F,0x95,0xA8,0xA8,0xB2,0xBC,0x62,0x55,0x62,0x64,0x68,0x71,0x7C,0x7F,0x06,0x07,0x08,0x0A,0x0C,0x0D,0x0F,0x0B,0x15,0x28,0x38,0x3C,0x47,0x62,0x70,0x7F,0x95,0xA8,0xA8,0xB2,0xBC,0x62,0x55,0x62,0x64,0x69,0x71,0x7C,0x7F}},  
 {0xE0,58,{0x00,0x02,0x08,0x0B,0x0D,0x10,0x13,0x0D,0x20,0x2F,0x3F,0x3F,0x49,0x5D,0x65,0x6B,0x7D,0x7F,0x7F,0x9B,0xAA,0x56,0x52,0x56,0x56,0x56,0x56,0x57,0x7F,
           0x00,0x02,0x08,0x0B,0x0D,0x10,0x13,0x0D,0x20,0x2F,0x3F,0x3F,0x49,0x5D,0x65,0x6B,0x7D,0x7F,0x7F,0x9B,0xAA,0x56,0x52,0x56,0x56,0x56,0x56,0x57,0x7F}},  
// 20161021 calvin --, Update Gamma curve      
//>2016/09/01-stevenchen
//>20161031 tracy
//>20161129 tracy

  {0xCC,1,{0x0B }},
  {0xC0,2,{0x1F ,0x31 }},
  {0xB6,2,{0x9D ,0x9D }},
  {0xD4,1,{0x02 }},
  {0xBD,1,{0x01 }},
  {0xB1,1,{0x00 }},
  {0xBD,1,{0x00 }},
  {0xBD,1,{0x00 }},
  {0xC1,1,{0x00 }},

  //Sleep Out
  
  //<20161107 tracy, modify delay time for decrease wake up time
  //{0x11, 0, {}},
  //{REGFLAG_DELAY, 200, {}}, 
  {0x11, 0, {}},
  {REGFLAG_DELAY, 120, {}}, 
  
  //Display ON
  //{0x29, 0, {}},
  //{REGFLAG_DELAY, 50, {}}, 
  {0x29, 0, {}},
  {REGFLAG_DELAY, 20, {}}, 
  //>20161107 tracy
  
  // Setting ending by predefined flag
  {REGFLAG_END_OF_TABLE, 0x00, {}}
};
//>2016/08/15-stevenchen

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

    for(i = 0; i < count; i++) {
		
        unsigned cmd;
        cmd = table[i].cmd;
		
        switch (cmd) {
			
            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;
				
            case REGFLAG_END_OF_TABLE :
                break;
				
            default:
		dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
       	}
    }
	
}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
    memset(params, 0, sizeof(LCM_PARAMS));
	
    params->type   = LCM_TYPE_DSI;

    params->width  = FRAME_WIDTH;
    params->height = FRAME_HEIGHT;
	//<20170222 tracy, add physical size value for DPI
	params->physical_height=111;
	params->physical_width=62;
	//>20170222 tracy

    #if (LCM_DSI_CMD_MODE)
        params->dsi.mode   = CMD_MODE;
    #else
        params->dsi.mode   = BURST_VDO_MODE; //SYNC_PULSE_VDO_MODE;//BURST_VDO_MODE; 
    #endif
	
    // DSI
    /* Command mode setting */
    //1 Three lane or Four lane
    params->dsi.LANE_NUM		= LCM_FOUR_LANE;
    //The following defined the fomat for data coming from LCD engine.
    params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

    // Video mode setting		
    params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;

    params->dsi.vertical_sync_active	= LCM_VSYNC_NUM;
    params->dsi.vertical_backporch	= LCM_VBP_NUM;
    params->dsi.vertical_frontporch	= LCM_VFP_NUM;
    params->dsi.vertical_active_line	= FRAME_HEIGHT; 

    params->dsi.horizontal_sync_active	= LCM_HSYNC_NUM;
    params->dsi.horizontal_backporch	= LCM_HBP_NUM;
    params->dsi.horizontal_frontporch	= LCM_HFP_NUM;
    params->dsi.horizontal_active_pixel	= FRAME_WIDTH;

    //params->dsi.LPX=8; 

    // Bit rate calculation
    params->dsi.ssc_range 	= 4;
    params->dsi.ssc_disable	= 1;
	//<2016/09/21-tracychui,[D6][MISC][COMMON][LCM][][]modify LCM to 60FPS
    params->dsi.PLL_CLOCK	= 231;//234;//200;//185; //191;//231;
    //>2016/09/21-tracychui
}

static void lcm_init(void)
{
    int panel_type = 0;
    
	lcm_gate_enable(1);

    //<20161107 tracy, modify delay time for decrease wake up time
    //SET_RESET_PIN(1);
    //MDELAY(10); 
    SET_RESET_PIN(0);
    //MDELAY(20); 
    MDELAY(5);
    SET_RESET_PIN(1);
    //MDELAY(100);
    MDELAY(55); 
    //>20161107 tracy
    gpio_direction_input(67);
	panel_type = gpio_get_value(67);
	gpio_free(67);
    //printk("[Edwin] - panel_type = %d \n",panel_type);	
	if(panel_type)
    {
    	push_table(lcm_init_setting_second, sizeof(lcm_init_setting_second) / sizeof(struct LCM_setting_table), 1);
    }else
    {
    	push_table(lcm_init_setting_main, sizeof(lcm_init_setting_main) / sizeof(struct LCM_setting_table), 1);
	}
    //dsi_set_cmdq_V3(lcm_init_setting,sizeof(lcm_init_setting)/sizeof(lcm_init_setting[0]),1);
    //printk("lcm init in kernel is done \n");
}

static void lcm_suspend(void)
{
    unsigned int data_array[16];

    data_array[0]=0x00280500; // Display Off
    dsi_set_cmdq(data_array, 1, 1);
	
    data_array[0] = 0x00100500; // Sleep In
    dsi_set_cmdq(data_array, 1, 1);
	
    SET_RESET_PIN(1);
    MDELAY(10);
    SET_RESET_PIN(0);
    MDELAY(10);	
    SET_RESET_PIN(1);
    MDELAY(120);     

    printk("[Kernel] %s \n", __func__);
    is_lcm_suspend = 1;
    //<2016/08/10-stevenchen, Fix system reboot when suspend
    //queue_delayed_work(lcm_wq, &lcm_work, msecs_to_jiffies(20));
    //>2016/08/10-stevenchen

    lcm_gate_enable(0);
}


static void lcm_resume(void)
{
    lcm_init();
    is_lcm_suspend = 0;
    //<2016/08/10-stevenchen, Fix system reboot when suspend
    //queue_delayed_work(lcm_wq, &lcm_work, msecs_to_jiffies(20));
    //>2016/08/10-stevenchen
    printk("[Kernel] %s \n",__func__);
}
         
#if (LCM_DSI_CMD_MODE)
static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	dsi_set_cmdq(data_array, 3, 1);
	
	data_array[0]= 0x00053902;
	data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[2]= (y1_LSB);
	dsi_set_cmdq(data_array, 3, 1);

	data_array[0]= 0x002c3909;
	dsi_set_cmdq(data_array, 1, 0);

}
#endif

static unsigned int lcm_compare_id(void)
{
     return 1;
}

#if 0
static unsigned int lcm_esd_check(void)
{
  #ifndef BUILD_LK
	char  buffer[3];
	int   array[4];

	if(lcm_esd_test)
	{
		lcm_esd_test = FALSE;
		return TRUE;
	}

	array[0] = 0x00013700;
	dsi_set_cmdq(array, 1, 1);

	read_reg_v2(0x36, buffer, 1);
	if(buffer[0]==0x90)
	{
		return FALSE;
	}
	else
	{			 
		return TRUE;
	}
#else
	return FALSE;
#endif

}

static unsigned int lcm_esd_recover(void)
{
	lcm_init();
	lcm_resume();

	return TRUE;
}
#endif


LCM_DRIVER hx8394f_hd720_dsi_vdo_lcm_drv = 
{
    .name			= "hx8394f_hd720_dsi_vdo",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id     = lcm_compare_id,
	//.esd_check = lcm_esd_check,
	//.esd_recover = lcm_esd_recover,
#if (LCM_DSI_CMD_MODE)
    .update         = lcm_update,
#endif
    };
