/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/*
 * Driver for CAM_CAL
 *
 *
 */

#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/module.h>
#include "kd_camera_hw.h"
#include "cam_cal.h"
#include "cam_cal_define.h"
#include "s5k3l8_eeprom.h"
/* #include <asm/system.h>  // for SMP */
#include <linux/dma-mapping.h>
#ifdef CONFIG_COMPAT
/* 64 bit */
#include <linux/fs.h>
#include <linux/compat.h>
#endif

#define PFX "S5K3L8_EEPROM_FMT"


/* #define CAM_CALGETDLT_DEBUG */
#define CAM_CAL_DEBUG
#ifdef CAM_CAL_DEBUG


#define CAM_CALINF(fmt, arg...)    pr_err("[%s] " fmt, __func__, ##arg)//pr_debug("[%s] " fmt, __func__, ##arg)
#define CAM_CALDB(fmt, arg...)     pr_err("[%s] " fmt, __func__, ##arg)//pr_debug("[%s] " fmt, __func__, ##arg)
#define CAM_CALERR(fmt, arg...)    pr_err("[%s] " fmt, __func__, ##arg)
#else
#define CAM_CALINF(x, ...)
#define CAM_CALDB(x, ...)
#define CAM_CALERR(fmt, arg...)    pr_err("[%s] " fmt, __func__, ##arg)
#endif

    //Neil 20161212   read otp to globle var OTPData[]+

#define YSL_PRE_LOAD_OTP

#ifdef YSL_PRE_LOAD_OTP
extern u8 S5K3L8_OTPData[];
#endif
    //Neil 20161212   read otp to globle var OTPData[]-



static DEFINE_SPINLOCK(g_CAM_CALLock); /* for SMP */


#define USHORT             unsigned short
#define BYTE               unsigned char
#define Sleep(ms) mdelay(ms)

/*******************************************************************************
*
********************************************************************************/
#define CAM_CAL_DRVNAME "CAM_CAL_DRV"
#define CAM_CAL_I2C_GROUP_ID 0
/*******************************************************************************
*
********************************************************************************/


static dev_t g_CAM_CALdevno = MKDEV(CAM_CAL_DEV_MAJOR_NUMBER, 0);
static struct cdev *g_pCAM_CAL_CharDrv;


static struct class *CAM_CAL_class;
static atomic_t g_CAM_CALatomic;

#define I2C_SPEED 300
#define MAX_LSC_SIZE 1024
#define MAX_OTP_SIZE 1100
static int s5k3l8_eeprom_read;

#ifdef simon
#define MAX_OFFSET       0xffff
#define EEPROM_READ_ID  0x5B
BYTE s5k3l8_SPC_data[352]= {0};
#endif

#define EEPROM_WRITE_ID   0x5A

typedef struct mtk_format {
#if 0
	u16    ChipInfo; /* chip id, lot Id, Chip No. Etc */
	u8     IdGroupWrittenFlag;
	/* "Bit[7:6]: Flag of WB_Group_0  00:empty  01: valid group 11 or 10: invalid group" */
	u8     ModuleInfo; /* MID, 0x02 for truly */
	u8     Year;
	u8     Month;
	u8     Day;
	u8     LensInfo;
	u8     VcmInfo;
	u8     DriverIcInfo;
	u8     LightTemp;
#endif
	u8     flag;
	u32    CaliVer;/* 0xff000b01 */
	u16    SerialNum;
	u8     Version;/* 0x01 */
	u8     AwbAfInfo;/* 0xF */
	u8     UnitAwbR;
	u8     UnitAwbGr;
	u8     UnitAwbGb;
	u8     UnitAwbB;
	u8     GoldenAwbR;
	u8     GoldenAwbGr;
	u8     GoldenAwbGb;
	u8     GoldenAwbB;
	u16    AfInfinite;
	u16    AfMacro;
	u16    LscSize;
	u8   Lsc[MAX_LSC_SIZE];
} OTP_MTK_TYPE;

union OTP_DATA {
	u8 Data[MAX_OTP_SIZE];
	OTP_MTK_TYPE       MtkOtpData;
};
#if 0
typedef struct OTP_{
    u8 af[4];
	//u8 awb[8];
	//u8 lsc;
    
} OTP;

OTP OTP_INFO; 
#endif
//#define OTP_SIZE 2048
//extern BYTE OTPData[OTP_SIZE];
static int otp_flag = 0;
#if 0
void otp_clear_flag(void)
{
	spin_lock(&g_CAM_CALLock);
	_otp_read = 0;
	spin_unlock(&g_CAM_CALLock);
}
#endif

union OTP_DATA s5k3l8_eeprom_data = {{0} };

/*LukeHu--150706=For Kernel coding style.
extern int iReadRegI2C(u8 *a_pSendData , u16 a_sizeSendData, u8 *a_pRecvData, u16 a_sizeRecvData, u16 i2cId);
extern int iWriteRegI2C(u8 *a_pSendData , u16 a_sizeSendData, u16 i2cId);
extern void kdSetI2CSpeed(u16 i2cSpeed);
*/
static void write_cmos_sensor(kal_uint16 addr, kal_uint16 para)
{
    char pusendcmd[4] = {(char)(addr >> 8) , (char)(addr & 0xFF) ,(char)(para >> 8),(char)(para & 0xFF)};

    kdSetI2CSpeed(I2C_SPEED); // Add this func to set i2c speed by each sensor
    iWriteRegI2C(pusendcmd , 4, EEPROM_WRITE_ID);
}
static kal_uint16 read_cmos_sensor_otp(kal_uint32 addr)
{
    kal_uint16 get_byte=0;
    char pu_send_cmd[2] = {(char)(addr >> 8), (char)(addr & 0xFF) };

    kdSetI2CSpeed(I2C_SPEED); // Add this func to set i2c speed by each sensor
    iReadRegI2C(pu_send_cmd, 2, (u8*)&get_byte, 1, EEPROM_WRITE_ID);
    return get_byte;
}

int  start_read_otp(int page )
{
		CAM_CALDB("start_read_otp page = 0x%x\n",page);
		
		
		write_cmos_sensor(0x0100, 0x0100);
		write_cmos_sensor(0x0a02, page);
		write_cmos_sensor(0x0a00, 0x0100);
		mdelay(10);
		
		return 0;
}
int  stop_read_otp(void)
{
		CAM_CALDB("stop_read_otp\n");
		write_cmos_sensor(0x0a00, 0x0000);
		
		return 0;
}
int  dump_lsc_data(int page ,int start, int end)
{

	start_read_otp(page);
	while(start <= end )
	{
		CAM_CALDB("page = 0x%x ,read_cmos_sensor(0x%x) = 0x%x\n",page ,start ,read_cmos_sensor_otp(start));
		start = start +1;;
	}
	stop_read_otp();

	return 0;

}

/*
int dump_otp_info(void)
{

	start_read_otp(0x0100);
	 LOG_INF("Calibration Version:\n");
	 LOG_INF("read_cmos_sensor(0x0A05) = 0x%x\n",read_cmos_sensor(0x0A05));
	 LOG_INF("read_cmos_sensor(0x0A06) = 0x%x\n",read_cmos_sensor(0x0A06));
	 LOG_INF("read_cmos_sensor(0x0A07) = 0x%x\n",read_cmos_sensor(0x0A07));
	 LOG_INF("read_cmos_sensor(0x0A08) = 0x%x\n",read_cmos_sensor(0x0A08));
	 
	 LOG_INF("Module ID1:0x%x\n"	,read_cmos_sensor(0x0A09));	
	 LOG_INF("LENS_ID1:0x%x\n"		,read_cmos_sensor(0x0A0A));
	 LOG_INF("VCM_ID1:0x%x\n"		,read_cmos_sensor(0x0A0B));
	 LOG_INF("Driver_ID1:0x%x\n"	,read_cmos_sensor(0x0A0C));
	 stop_read_otp();

	 return 0;

}
*/
#ifdef simonn
bool selective_read_eeprom(kal_uint16 addr, BYTE* data)
{
	char pu_send_cmd[2] = {(char)(addr >> 8) , (char)(addr & 0xFF) };
    if(addr > MAX_OFFSET)
        return false;
	kdSetI2CSpeed(I2C_SPEED);

	if(iReadRegI2C(pu_send_cmd, 2, (u8*)data, 1, EEPROM_READ_ID)<0)
		return false;
    return true;
}
#endif
static int read_cmos_sensor(u16 slave_id, u16 addr, u8 *data)
{
	char pu_send_cmd[2] = {(char)((addr>>8) & 0xFF), (char)(addr & 0xFF) };
	CAM_CALDB("simon read_cmos_sensor\n");
	kdSetI2CSpeed(I2C_SPEED);
	return iReadRegI2C(pu_send_cmd, 2, data, 1, slave_id);/* 0 for good */
}



int read_s5k3l8_eeprom(u8 slv_id, u16 offset, u8 *data)
{
	int ret = 0;
	CAM_CALDB("QQ simon read_s5k3l8_eeprom\n");
	ret = read_cmos_sensor(slv_id, offset, data);
	CAM_CALDB("OTP read slv_id 0x%x offset 0x%x  data 0x%x ret 0x%x\n", slv_id, offset, *data, ret);

	return ret;
}
/*
int read_s5k3l8_eeprom_info(u8 slv_id, u16 offset, u8 *data)
{
	//int  = 0;
	
	int ret = 0;
	CAM_CALDB("simon read_s5k3l8_eeprom_info S\n");
	//read_s5k3l8_eeprom_size(0x5a,0x0a05,data,4);
	ret = read_cmos_sensor(slv_id, offset, data);
	CAM_CALDB("OTP read slv_id 0x%x offset 0x%x  data 0x%x ret 0x%x\n", slv_id, offset, *data, ret);
	CAM_CALDB("simon read_s5k3l8_eeprom_info E\n");

	return 0;
}
*/
int read_s5k3l8_eeprom_size(u8 slv_id, u16 offset, u8 *data, int size)
{
	int i = 0;
	CAM_CALDB("simon read_s5k3l8_eeprom_size\n");
	//write_cmos_sensor(0x0a02, 0x0f);
	//write_cmos_sensor(0x0a00, 0x01);
	//mdelay(10);
	//read_s5k3l8_eeprom_info();
	for (i = 0; i < size; i++) {
		
		if (read_s5k3l8_eeprom(slv_id, offset + i, data + i) != 0){
			return -1;
		}
		CAM_CALDB("data[%d] = %d\n",i,*(data+ i));
	}
	//write_cmos_sensor(0x0a00, 0x00);
	return 0;
}
int read_lsc_otp(u16 addr, unsigned char *iBuffer, unsigned int buffersize)
{
//	u8 readbuffer;
	u16 slave_id = 0x5A;
	int lsc_size =0;
	int i=0;
	lsc_size = 31+(6*64);
	CAM_CALDB("read_lsc_otp otp_flag = %d\n",otp_flag);
	if(otp_flag){
		for(i=0;i<lsc_size;i++)
		{
			//iBuffer[i]=OTPData[i];
		}

	}else{
		start_read_otp(0x1900);
		read_s5k3l8_eeprom_size(slave_id, addr+0x21, iBuffer, 31);
		//stop_read_otp();

		start_read_otp(0x1A00);
		read_s5k3l8_eeprom_size(slave_id, addr, iBuffer+32, buffersize);
		//stop_read_otp();

		start_read_otp(0x1B00);
		read_s5k3l8_eeprom_size(slave_id, addr, iBuffer+(32+64), buffersize);
		//stop_read_otp();

		
		start_read_otp(0x1C00);
		read_s5k3l8_eeprom_size(slave_id, addr, iBuffer+(32+64*2), buffersize);
		//stop_read_otp();

		start_read_otp(0x1D00);
		read_s5k3l8_eeprom_size(slave_id, addr, iBuffer+(32+64*3), buffersize);
		//stop_read_otp();

		start_read_otp(0x1E00);
		read_s5k3l8_eeprom_size(slave_id, addr, iBuffer+(32+64*4), buffersize);
		//stop_read_otp();

		start_read_otp(0x1F00);
		read_s5k3l8_eeprom_size(slave_id, addr, iBuffer+(32+64*5), buffersize);
		stop_read_otp();
	}
	otp_flag = 0;
	return 0;
}


#define CAL_VERSION_MAGIC ""
int read_s5k3l8_eeprom_mtk_fmt(void)
{
	int i = 0;
	int offset = 0;

	CAM_CALINF("OTP readed =%d\n", s5k3l8_eeprom_read);
	if (1 == s5k3l8_eeprom_read) {
		CAM_CALDB("OTP readed ! skip\n");
		return 1;
	}
	spin_lock(&g_CAM_CALLock);
	s5k3l8_eeprom_read = 1;
	spin_unlock(&g_CAM_CALLock);
#if 0
	read_s5k3l8_eeprom_size(0xA0, 0x00, &s5k3l8_eeprom_data.Data[0x00], 1);
#endif

	/* read calibration version 0xff000b01 */
	if (read_s5k3l8_eeprom_size(0xA0, 0x01, &s5k3l8_eeprom_data.Data[0x01], 4) != 0) {
		CAM_CALERR("read s5k3l8_eeprom GT24C16 i2c fail !?\n");
		return -1;
	}

	/* read serial number */
	read_s5k3l8_eeprom_size(0xA0, 0x05, &s5k3l8_eeprom_data.Data[0x05], 2);

	/* read AF config */
	read_s5k3l8_eeprom_size(0xA0, 0x07, &s5k3l8_eeprom_data.Data[0x07], 2);

	/* read AWB */
	read_s5k3l8_eeprom_size(0xA0, 0x09, &s5k3l8_eeprom_data.Data[0x09], 8);

	/* read AF calibration */
	read_s5k3l8_eeprom_size(0xA0, 0x11, &s5k3l8_eeprom_data.Data[0x011], 4);

	/* read LSC size */
	read_s5k3l8_eeprom_size(0xA0, 0x15, &s5k3l8_eeprom_data.Data[0x015], 2);
#if 0
	int size = 0;

	size = s5k3l8_eeprom_data.Data[0x015] + s5k3l8_eeprom_data.Data[0x016] << 4;
#endif


	/* for lsc data */
	read_s5k3l8_eeprom_size(0xA0, 0x17, &s5k3l8_eeprom_data.Data[0x017], (0xFF - 0X17 + 1));
	offset = 256;
	for (i = 0xA2; i < 0xA6; i += 2) {
		read_s5k3l8_eeprom_size(i, 0x00, &s5k3l8_eeprom_data.Data[offset], 256);
		offset += 256;
	}
	read_s5k3l8_eeprom_size(0xA6, 0x00, &s5k3l8_eeprom_data.Data[offset], 0xBA - 0 + 1);
	CAM_CALDB("final offset offset %d !\n", offset + 0xBA);
#if 0
	CAM_CALDB("size %d readed %d!\n", size, offset + 0xBA - 0x17 + 1);
	u8 data[9];

	read_s5k3l8_eeprom_size(0xAA, 0xE0, &data[0], 8);
#endif

	return 0;

}


#ifdef CONFIG_COMPAT
#if 1
static int compat_put_cal_info_struct(
	COMPAT_stCAM_CAL_INFO_STRUCT __user *data32,
	stCAM_CAL_INFO_STRUCT __user *data)
{
#if 1//simon fix compile error
	return 0;
#else

	compat_uptr_t p;
	compat_uint_t i;
	int err;

	err = get_user(i, &data->u4Offset);
	err |= put_user(i, &data32->u4Offset);
	err |= get_user(i, &data->u4Length);
	err |= put_user(i, &data32->u4Length);
	/* Assume pointer is not change */

	err |= get_user(p, &data->pu1Params);
	err |= put_user(p, &data32->pu1Params);
	return err;
#endif
	
}
#endif
static int compat_get_cal_info_struct(
	COMPAT_stCAM_CAL_INFO_STRUCT __user *data32,
	stCAM_CAL_INFO_STRUCT __user *data)
{
	compat_uptr_t p;
	compat_uint_t i;
	int err;

	err = get_user(i, &data32->u4Offset);
	err |= put_user(i, &data->u4Offset);
	err |= get_user(i, &data32->u4Length);
	err |= put_user(i, &data->u4Length);
	err |= get_user(p, &data32->pu1Params);
	err |= put_user(compat_ptr(p), &data->pu1Params);

	return err;
}

static long s5k3l8eeprom_Ioctl_Compat(struct file *filp, unsigned int cmd, unsigned long arg)
{
	long ret;

	COMPAT_stCAM_CAL_INFO_STRUCT __user *data32;
	stCAM_CAL_INFO_STRUCT __user *data;
	int err;

	CAM_CALDB("[CAMERA SENSOR] s5k3l8_eeprom_DEVICE_ID,%p %p %x ioc size %d\n",
	filp->f_op , filp->f_op->unlocked_ioctl, cmd, _IOC_SIZE(cmd));

	if (!filp->f_op || !filp->f_op->unlocked_ioctl)
		return -ENOTTY;

	switch (cmd) {

	case COMPAT_CAM_CALIOC_G_READ: {
		data32 = compat_ptr(arg);
		data = compat_alloc_user_space(sizeof(*data));
		if (data == NULL)
			return -EFAULT;

		err = compat_get_cal_info_struct(data32, data);
		if (err)
			return err;

		ret = filp->f_op->unlocked_ioctl(filp, CAM_CALIOC_G_READ, (unsigned long)data);
		err = compat_put_cal_info_struct(data32, data);


		if (err != 0)
			CAM_CALERR("[CAMERA SENSOR] compat_put_acdk_sensor_getinfo_struct failed\n");
		return ret;
	}
	default:
		return -ENOIOCTLCMD;
	}
}


#endif
#if 0
static bool selective_read_eeprom(u16 addr, BYTE* data)
{	
	char pu_send_cmd[2] = {(char)(addr >> 8) , (char)(addr & 0xFF) };	
	CAM_CALDB("[simon] Start selective_read_eeprom \n");    
	if(addr > IMX230_MAX_OFFSET){		
		CAM_CALDB("[Rick] selective_read_eeprom addr > IMX230_MAX_OFFSET FAIL!! \n");        
		return false;	
	}	
	//kdSetI2CSpeed(IMX230_I2C_SPEED);	
	if(iReadRegI2C(pu_send_cmd, 2, (u8*)data, 1, EEPROM_READ_ID)<0){		
		CAM_CALDB("[simon] selective_read_eeprom iReadRegI2C FAIL!! \n");		
		return false;	
	}	
	CAM_CALDB("[simon] selective_read_eeprom iReadRegI2C OK!! \n");    
return true;
}
#endif
#if 0
int read_otp_af(void)
{
	int temp;
	u8 retry = 3;
	start_read_otp(0x0100);
	OTP_INFO.af[0]=(u8)read_cmos_sensor_otp(0x0a19);
	OTP_INFO.af[1]=(u8)read_cmos_sensor_otp(0x0a1a);
	OTP_INFO.af[2]=(u8)read_cmos_sensor_otp(0x0a1b);
	OTP_INFO.af[3]=(u8)read_cmos_sensor_otp(0x0a1c);
	CAM_CALDB("OTP_INFO.af[0] = 0x%x \n",OTP_INFO.af[0]);
	CAM_CALDB("OTP_INFO.af[1] = 0x%x \n",OTP_INFO.af[1]);
	CAM_CALDB("OTP_INFO.af[2] = 0x%x \n",OTP_INFO.af[2]);
	CAM_CALDB("OTP_INFO.af[3] = 0x%x \n",OTP_INFO.af[3]);
	
	stop_read_otp();
	return 0;
}
#endif

#ifdef YSL_PRE_LOAD_OTP

/*
int selective_read_region(u32 offset, BYTE *data, u16 i2c_id, u32 size)
{
	//u8 lsc_data[2]={0,0}; 
	u16 slave_id = 0x5A;
	write_cmos_sensor(0x0100, 0x0000);//streaming off
	write_cmos_sensor(0x0b00, 0x0100);//shading on/off(0x0000:disable, 0x0100 enable)
	write_cmos_sensor(0x0c20, 0x0100);//sram selection(0x0000:sram, 0x0100 otp)
	
	if(offset == 0x0a04)            //read LSC OTP
    {
   		#if 0
    	start_read_otp(0x0c);
    	CAM_CALDB("selective_read_region--1  offset = %d , i2c_id = 0x%x , size = %d\n",offset,i2c_id,size);
		read_s5k3l8_eeprom_size(slave_id, offset, lsc_data, 2);
	//	printk("lsc size: 0x%x, 0x%x \n", lsc_data[0], lsc_data[1]);
		if( size != ((lsc_data[1]<<8) + lsc_data[0]) )
		{
			return 0;
		}
		
	    read_s5k3l8_eeprom_size(slave_id, offset+2, data, size);
		#endif

		read_lsc_otp(offset, data, size);


		
		
   	}
//Neil 20161027 +	
#if 0	
	else if((offset == 0x0a11) || (offset == 0x0a15) || (offset == 0x0a19))       //read AWB AF OTP 
#else		
	else if((offset == 0x0a11) || (offset == 0x0a15) || (offset == 0x0a19)||(offset == 0x0a2a) || (offset == 0x0a2e) || (offset == 0x0a32))       //read AWB AF OTP 
#endif		
//Neil 20161027 -	

    {	
    	#if 0
    	start_read_otp(1);
    	CAM_CALDB("selective_read_region--2  offset = 0x%x , i2c_id = 0x%x , size = %d\n",offset,i2c_id,size);
		read_s5k3l8_eeprom_size(slave_id, offset, data, size);	
		#endif
		start_read_otp(0x0100);
		read_s5k3l8_eeprom_size(slave_id, offset, data, size);
		stop_read_otp();
   	}
	else if(offset ==0x0a05 || offset ==0x0a1e)//DoCamCalLayoutCheck 
	{
		#if 0
		start_read_otp(1);
		CAM_CALDB("selective_read_region--3  offset = %d , i2c_id = 0x%x , size = %d\n",offset,i2c_id,size);
		read_s5k3l8_eeprom_size(slave_id, offset, data, size);
		#endif
		start_read_otp(0x0100);
		read_s5k3l8_eeprom_size(slave_id, offset, data, size);
		stop_read_otp();
	}
	else
	{
		CAM_CALDB("LSC OTP Data Read Fail!\n");
	}



	
//	memcpy((void *)data, (void *)&s5k3l8_eeprom_data.Data[offset], size);
	CAM_CALDB("selective_read_region offset =%x size %d data read = %d\n", offset, size, *data);
	return size;
}
*/
int selective_read_region(u32 offset, BYTE *data, u16 i2c_id, u32 size){

       int idx=0;
	 int j=0;  
       if(offset <0x0a04) return 0;
       idx=offset-0x0a04;
	   
	 for (j=0;j<size;j++)
	   *data++=S5K3L8_OTPData[idx++];
	 return size;

}


#endif
//Neil 20161212   for first time read OTP to Buffer +
#ifdef YSL_PRE_LOAD_OTP
    
//selective_read_region(ptempbuf->u4Offset, pu1Params,S5K3L8_EEPROM_DEVICE_ID, ptempbuf->u4Length);

int QT_S5K3L8_Raed_OTP_Table(u32 offset, BYTE *data,  u32 size )
{
	u16 slave_id = 0x5A;

      	CAM_CALERR("start read s5k3l8 otp!\n");
	
	write_cmos_sensor(0x0100, 0x0000);//streaming off
	write_cmos_sensor(0x0b00, 0x0100);//shading on/off(0x0000:disable, 0x0100 enable)
	write_cmos_sensor(0x0c20, 0x0100);//sram selection(0x0000:sram, 0x0100 otp)

	start_read_otp(0x0100);
	read_s5k3l8_eeprom_size(slave_id, offset, data, size);
	stop_read_otp();

      	CAM_CALERR("end read s5k3l8 otp!\n");
	return 	size;

}
#endif
//Neil 20161212   for first time read OTP to Buffer -


/*******************************************************************************
*
********************************************************************************/
#define NEW_UNLOCK_IOCTL
#ifndef NEW_UNLOCK_IOCTL
static int CAM_CAL_Ioctl(struct inode *a_pstInode,
			 struct file *a_pstFile,
			 unsigned int a_u4Command,
			 unsigned long a_u4Param)
#else
static long CAM_CAL_Ioctl(
	struct file *file,
	unsigned int a_u4Command,
	unsigned long a_u4Param
)
#endif
{
	int i4RetValue = 0;
	u8 *pBuff = NULL;
	u8 *pu1Params = NULL;
	stCAM_CAL_INFO_STRUCT *ptempbuf;
#ifdef CAM_CALGETDLT_DEBUG
	struct timeval ktv1, ktv2;
	unsigned long TimeIntervalUS;
#endif
/*
	if (_IOC_NONE == _IOC_DIR(a_u4Command)) {
	} else {
*/
	if (_IOC_NONE != _IOC_DIR(a_u4Command)) {
		pBuff = kmalloc(sizeof(stCAM_CAL_INFO_STRUCT), GFP_KERNEL);

		if (NULL == pBuff) {
			CAM_CALERR(" ioctl allocate mem failed\n");
			return -ENOMEM;
		}

		if (_IOC_WRITE & _IOC_DIR(a_u4Command)) {
			if (copy_from_user((u8 *) pBuff , (u8 *) a_u4Param, sizeof(stCAM_CAL_INFO_STRUCT))) {
				/* get input structure address */
				kfree(pBuff);
				CAM_CALERR("ioctl copy from user failed\n");
				return -EFAULT;
			}
		}
	}

	ptempbuf = (stCAM_CAL_INFO_STRUCT *)pBuff;
	pu1Params = kmalloc(ptempbuf->u4Length, GFP_KERNEL);
	if (NULL == pu1Params) {
		kfree(pBuff);
		CAM_CALERR("ioctl allocate mem failed\n");
		return -ENOMEM;
	}


	if (copy_from_user((u8 *)pu1Params , (u8 *)ptempbuf->pu1Params, ptempbuf->u4Length)) {
		kfree(pBuff);
		kfree(pu1Params);
		CAM_CALERR(" ioctl copy from user failed\n");
		return -EFAULT;
	}

	switch (a_u4Command) {
	case CAM_CALIOC_S_WRITE:
		CAM_CALDB("Write CMD\n");
#ifdef CAM_CALGETDLT_DEBUG
		do_gettimeofday(&ktv1);
#endif
		i4RetValue = 0;/* iWriteData((u16)ptempbuf->u4Offset, ptempbuf->u4Length, pu1Params); */
#ifdef CAM_CALGETDLT_DEBUG
		do_gettimeofday(&ktv2);
		if (ktv2.tv_sec > ktv1.tv_sec)
			TimeIntervalUS = ktv1.tv_usec + 1000000 - ktv2.tv_usec;
		else
			TimeIntervalUS = ktv2.tv_usec - ktv1.tv_usec;

		CAM_CALDB("Write data %d bytes take %lu us\n", ptempbuf->u4Length, TimeIntervalUS);
#endif
		break;
	case CAM_CALIOC_G_READ:
		CAM_CALDB("[CAM_CAL] Read CMD\n");
#ifdef CAM_CALGETDLT_DEBUG
		do_gettimeofday(&ktv1);
#endif
		otp_flag = 1;
		CAM_CALDB("ptempbuf->u4Offset = 0x%x, pu1Params= 0x%x,ptempbuf->u4Length= 0x%x\n", ptempbuf->u4Offset, pu1Params,ptempbuf->u4Length);

		i4RetValue = selective_read_region(ptempbuf->u4Offset, pu1Params,S5K3L8_EEPROM_DEVICE_ID, ptempbuf->u4Length);
		//read_s5k3l8_eeprom(0x5a,452,OTPData);
#ifdef CAM_CALGETDLT_DEBUG
		do_gettimeofday(&ktv2);
		if (ktv2.tv_sec > ktv1.tv_sec)
			TimeIntervalUS = ktv1.tv_usec + 1000000 - ktv2.tv_usec;
		else
			TimeIntervalUS = ktv2.tv_usec - ktv1.tv_usec;

		CAM_CALDB("Read data %d bytes take %lu us\n", ptempbuf->u4Length, TimeIntervalUS);
#endif

		break;
	default:
		CAM_CALINF("[CAM_CAL] No CMD\n");
		i4RetValue = -EPERM;
		break;
	}

	if (_IOC_READ & _IOC_DIR(a_u4Command)) {
		/* copy data to user space buffer, keep other input paremeter unchange. */
		if (copy_to_user((u8 __user *) ptempbuf->pu1Params , (u8 *)pu1Params , ptempbuf->u4Length)) {
			kfree(pBuff);
			kfree(pu1Params);
			CAM_CALERR("[CAM_CAL] ioctl copy to user failed\n");
			return -EFAULT;
		}
	}

	kfree(pBuff);
	kfree(pu1Params);
	return i4RetValue;
}


static u32 g_u4Opened;
/* #define */
/* Main jobs: */
/* 1.check for device-specified errors, device not ready. */
/* 2.Initialize the device if it is opened for the first time. */
static int CAM_CAL_Open(struct inode *a_pstInode, struct file *a_pstFile)
{
	CAM_CALDB("CAM_CAL_Open\n");
	spin_lock(&g_CAM_CALLock);
	if (g_u4Opened) {
		spin_unlock(&g_CAM_CALLock);
		CAM_CALERR("Opened, return -EBUSY\n");
		return -EBUSY;
	} /*else {*//*LukeHu--150720=For check fo*/
	if (!g_u4Opened) {/*LukeHu++150720=For check fo*/
		g_u4Opened = 1;
		atomic_set(&g_CAM_CALatomic, 0);
	}
	spin_unlock(&g_CAM_CALLock);
	return 0;
}

/* Main jobs: */
/* 1.Deallocate anything that "open" allocated in private_data. */
/* 2.Shut down the device on last close. */
/* 3.Only called once on last time. */
/* Q1 : Try release multiple times. */
static int CAM_CAL_Release(struct inode *a_pstInode, struct file *a_pstFile)
{
	spin_lock(&g_CAM_CALLock);

	g_u4Opened = 0;

	atomic_set(&g_CAM_CALatomic, 0);

	spin_unlock(&g_CAM_CALLock);

	return 0;
}

static const struct file_operations g_stCAM_CAL_fops = {
	.owner = THIS_MODULE,
	.open = CAM_CAL_Open,
	.release = CAM_CAL_Release,
	/* .ioctl = CAM_CAL_Ioctl */
#ifdef CONFIG_COMPAT
	.compat_ioctl = s5k3l8eeprom_Ioctl_Compat,
#endif
	.unlocked_ioctl = CAM_CAL_Ioctl
};

#define CAM_CAL_DYNAMIC_ALLOCATE_DEVNO 1
/* #define CAM_CAL_DYNAMIC_ALLOCATE_DEVNO 1 */

static inline  int RegisterCAM_CALCharDrv(void)
{
	struct device *CAM_CAL_device = NULL;

	CAM_CALDB("RegisterCAM_CALCharDrv\n");
#if CAM_CAL_DYNAMIC_ALLOCATE_DEVNO
	if (alloc_chrdev_region(&g_CAM_CALdevno, 0, 1, CAM_CAL_DRVNAME)) {
		CAM_CALERR(" Allocate device no failed\n");

		return -EAGAIN;
	}
#else
	if (register_chrdev_region(g_CAM_CALdevno , 1 , CAM_CAL_DRVNAME)) {
		CAM_CALERR(" Register device no failed\n");

		return -EAGAIN;
	}
#endif

	/* Allocate driver */
	g_pCAM_CAL_CharDrv = cdev_alloc();

	if (NULL == g_pCAM_CAL_CharDrv) {
		unregister_chrdev_region(g_CAM_CALdevno, 1);

		CAM_CALERR(" Allocate mem for kobject failed\n");

		return -ENOMEM;
	}

	/* Attatch file operation. */
	cdev_init(g_pCAM_CAL_CharDrv, &g_stCAM_CAL_fops);

	g_pCAM_CAL_CharDrv->owner = THIS_MODULE;

	/* Add to system */
	if (cdev_add(g_pCAM_CAL_CharDrv, g_CAM_CALdevno, 1)) {
		CAM_CALERR(" Attatch file operation failed\n");

		unregister_chrdev_region(g_CAM_CALdevno, 1);

		return -EAGAIN;
	}

	CAM_CAL_class = class_create(THIS_MODULE, "CAM_CALdrv");
	if (IS_ERR(CAM_CAL_class)) {
		int ret = PTR_ERR(CAM_CAL_class);

		CAM_CALERR("Unable to create class, err = %d\n", ret);
		return ret;
	}
	CAM_CAL_device = device_create(CAM_CAL_class, NULL, g_CAM_CALdevno, NULL, CAM_CAL_DRVNAME);

	return 0;
}

static inline void UnregisterCAM_CALCharDrv(void)
{
	/* Release char driver */
	cdev_del(g_pCAM_CAL_CharDrv);

	unregister_chrdev_region(g_CAM_CALdevno, 1);

	device_destroy(CAM_CAL_class, g_CAM_CALdevno);
	class_destroy(CAM_CAL_class);
}

static int CAM_CAL_probe(struct platform_device *pdev)
{

	return 0;/* i2c_add_driver(&CAM_CAL_i2c_driver); */
}

static int CAM_CAL_remove(struct platform_device *pdev)
{
	/* i2c_del_driver(&CAM_CAL_i2c_driver); */
	return 0;
}

/* platform structure */
static struct platform_driver g_stCAM_CAL_Driver = {
	.probe              = CAM_CAL_probe,
	.remove     = CAM_CAL_remove,
	.driver             = {
		.name   = CAM_CAL_DRVNAME,
		.owner  = THIS_MODULE,
	}
};


static struct platform_device g_stCAM_CAL_Device = {
	.name = CAM_CAL_DRVNAME,
	.id = 0,
	.dev = {
	}
};

static int __init CAM_CAL_init(void)
{
	int i4RetValue = 0;

	CAM_CALDB("CAM_CAL_i2C_init\n");
	/* Register char driver */
	i4RetValue = RegisterCAM_CALCharDrv();
	if (i4RetValue) {
		CAM_CALDB(" register char device failed!\n");
		return i4RetValue;
	}
	CAM_CALDB(" Attached!!\n");

	/* i2c_register_board_info(CAM_CAL_I2C_BUSNUM, &kd_cam_cal_dev, 1); */
	if (platform_driver_register(&g_stCAM_CAL_Driver)) {
		CAM_CALERR("failed to register s5k3l8_eeprom driver\n");
		return -ENODEV;
	}

	if (platform_device_register(&g_stCAM_CAL_Device)) {
		CAM_CALERR("failed to register s5k3l8_eeprom driver, 2nd time\n");
		return -ENODEV;
	}

	return 0;
}

static void __exit CAM_CAL_exit(void)
{
	platform_driver_unregister(&g_stCAM_CAL_Driver);
}

module_init(CAM_CAL_init);
module_exit(CAM_CAL_exit);

MODULE_DESCRIPTION("CAM_CAL driver");
MODULE_AUTHOR("Sean Lin <Sean.Lin@Mediatek.com>");
MODULE_LICENSE("GPL");
#ifdef simon
static bool _read_s5k3l8_eeprom_SPC(u16 addr, BYTE* data, u8 size_spc ){
	int i = 0;
	u16 offset = addr;
	//printk("[Rick] enter _read_eeprom spc size_spc = %d\n", size_spc);
	//for(i = 0; i < size_spc; i++) {
	for(i = 0; i < 352; i++) { //Rick test
		printk("[simon] read_eeprom i= %d \n", i);
		if(!selective_read_eeprom(offset, &data[i])){
			//printk("[Rick] read_eeprom, selective_read_eeprom fail \n");
			return false;
		}
		printk("[simon] read_eeprom 0x%0x %d\n",offset, data[i]);
		offset++;
	}
	get_done = true;
	last_size = size_spc;
	last_offset = addr;
    return true;
}

void read_s5k2l8_SPC(BYTE* data){
	//int i;
	int addr = 0x2E8;
	int size_spc = 352;
	
	printk("[simon] read s5k3l8 SPC, size_spc = %d , last_size = %d \n", size_spc, last_size);
	
	if(!get_done || last_size != size_spc || last_offset != addr) {
		if(!_read_s5k3l8_eeprom_SPC(addr, s5k3l8_SPC_data, size_spc)){
			get_done = 0;
            last_size = 0;
            last_offset = 0;
			//return -1;
			return;
		}
	}

	memcpy(data, s5k3l8_SPC_data , size_spc);
    //return 0;
	return;
}
#endif
