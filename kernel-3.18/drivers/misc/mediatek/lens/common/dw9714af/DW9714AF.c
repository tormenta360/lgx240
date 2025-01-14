/*
 * DW9714AF voice coil motor driver
 *
 *
 */

#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#include "lens_info.h"


#define AF_DRVNAME "DW9714AF_DRV"
#define AF_I2C_SLAVE_ADDR        0x18

#define AF_DEBUG
#ifdef AF_DEBUG
#define LOG_INF(format, args...) pr_debug(AF_DRVNAME " [%s] " format, __func__, ##args)
#else
#define LOG_INF(format, args...)
#endif


static struct i2c_client *g_pstAF_I2Cclient;
static int *g_pAF_Opened;
static spinlock_t *g_pAF_SpinLock;


static unsigned long g_u4AF_INF;
static unsigned long g_u4AF_MACRO = 1023;
static unsigned long g_u4TargetPosition;
static unsigned long g_u4CurrPosition;

//norman@20161116 for noise start
#define Slew_Rate_Control 1
//norman@20161116 for noise end

static int s4AF_ReadReg(unsigned short *a_pu2Result)
{
	int i4RetValue = 0;
	char pBuff[2];

	g_pstAF_I2Cclient->addr = AF_I2C_SLAVE_ADDR;

	g_pstAF_I2Cclient->addr = g_pstAF_I2Cclient->addr >> 1;

	//+ kylechang 2017.02.06	change I2C speed to 300KHz
	if(g_pstAF_I2Cclient->timing != 300)
	{
	  g_pstAF_I2Cclient->timing = 300;
	  printk("AF_I2C->timing=%d\n",g_pstAF_I2Cclient->timing);
	}
	//- kylechang 2017.02.06	change I2C speed to 300KHz

	i4RetValue = i2c_master_recv(g_pstAF_I2Cclient, pBuff, 2);

	if (i4RetValue < 0) {
		LOG_INF("I2C read failed!!\n");
		return -1;
	}

	*a_pu2Result = (((u16) pBuff[0]) << 4) + (pBuff[1] >> 4);

	return 0;
}

static int s4AF_WriteReg(u16 a_u2Data)
{
	int i4RetValue = 0;

	char puSendCmd[2] = { (char)(a_u2Data >> 4), (char)((a_u2Data & 0xF) << 4) };

	g_pstAF_I2Cclient->addr = AF_I2C_SLAVE_ADDR;

	g_pstAF_I2Cclient->addr = g_pstAF_I2Cclient->addr >> 1;

	//+ kylechang 2017.02.06	change I2C speed to 300KHz
	if(g_pstAF_I2Cclient->timing != 300)
	{
	  g_pstAF_I2Cclient->timing = 300;
	  printk("AF_I2C->timing=%d\n",g_pstAF_I2Cclient->timing);
	}
	//- kylechang 2017.02.06	change I2C speed to 300KHz

	i4RetValue = i2c_master_send(g_pstAF_I2Cclient, puSendCmd, 2);

	if (i4RetValue < 0) {
		LOG_INF("I2C send failed!!\n");
		return -1;
	}

	return 0;
}
static void DW9714AF_init_drv(void)
{
//norman@20161122 for noise start
#if Slew_Rate_Control
	char puSendCmd0[2] = {0xec,0xa3};
	char puSendCmd1[2] = {0xa1,0x0D};
	char puSendCmd2[2] = {0xf2,0x30};
	char puSendCmd3[2] = {0xdc,0x51};
	
	g_pstAF_I2Cclient->addr = AF_I2C_SLAVE_ADDR;
	g_pstAF_I2Cclient->addr = g_pstAF_I2Cclient->addr >> 1;	

	//+ kylechang 2017.02.06	change I2C speed to 300KHz
	if(g_pstAF_I2Cclient->timing != 300)
	{
	  g_pstAF_I2Cclient->timing = 300;
	  printk("AF_I2C->timing=%d\n",g_pstAF_I2Cclient->timing);
	}
	//- kylechang 2017.02.06	change I2C speed to 300KHz
	
	i2c_master_send(g_pstAF_I2Cclient, puSendCmd0, 2);
	i2c_master_send(g_pstAF_I2Cclient, puSendCmd1, 2);
	i2c_master_send(g_pstAF_I2Cclient, puSendCmd2, 2);
	i2c_master_send(g_pstAF_I2Cclient, puSendCmd3, 2);

	// + TD8263, fix the auto focus issue in video mode. By Norman. 2016-12-14
	//s4AF_WriteReg(0);
	// - TD8263, fix the auto focus issue in video mode. By Norman. 2016-12-14
#else
	s4AF_WriteReg(0xECA3);//Ringing Setting ON
	s4AF_WriteReg(0xA105);//DLC MCKL setting
	s4AF_WriteReg(0xDC51);
#endif
//norman@20161122 for noise end
}
static inline int getAFInfo(__user stAF_MotorInfo *pstMotorInfo)
{
	stAF_MotorInfo stMotorInfo;

	stMotorInfo.u4MacroPosition = g_u4AF_MACRO;
	stMotorInfo.u4InfPosition = g_u4AF_INF;
	stMotorInfo.u4CurrentPosition = g_u4CurrPosition;
	stMotorInfo.bIsSupportSR = 1;

	stMotorInfo.bIsMotorMoving = 1;

	if (*g_pAF_Opened >= 1)
		stMotorInfo.bIsMotorOpen = 1;
	else
		stMotorInfo.bIsMotorOpen = 0;

	if (copy_to_user(pstMotorInfo, &stMotorInfo, sizeof(stAF_MotorInfo)))
		LOG_INF("copy to user failed when getting motor information\n");

	return 0;
}

static inline int moveAF(unsigned long a_u4Position)
{
	int ret = 0;

	if ((a_u4Position > g_u4AF_MACRO) || (a_u4Position < g_u4AF_INF)) {
		LOG_INF("out of range\n");
		return -EINVAL;
	}

	if (*g_pAF_Opened == 1) {
		unsigned short InitPos;
		DW9714AF_init_drv();
		ret = s4AF_ReadReg(&InitPos);

		if (ret == 0) {
			LOG_INF("Init Pos %6d\n", InitPos);

			spin_lock(g_pAF_SpinLock);
			g_u4CurrPosition = (unsigned long)InitPos;
			spin_unlock(g_pAF_SpinLock);

		} else {
			spin_lock(g_pAF_SpinLock);
			g_u4CurrPosition = 0;
			spin_unlock(g_pAF_SpinLock);
		}

		spin_lock(g_pAF_SpinLock);
		*g_pAF_Opened = 2;
		spin_unlock(g_pAF_SpinLock);
	}

	if (g_u4CurrPosition == a_u4Position)
		return 0;

	spin_lock(g_pAF_SpinLock);
	g_u4TargetPosition = a_u4Position;
	spin_unlock(g_pAF_SpinLock);

	/* LOG_INF("move [curr] %d [target] %d\n", g_u4CurrPosition, g_u4TargetPosition); */


	if (s4AF_WriteReg((unsigned short)g_u4TargetPosition) == 0) {
		spin_lock(g_pAF_SpinLock);
		g_u4CurrPosition = (unsigned long)g_u4TargetPosition;
		spin_unlock(g_pAF_SpinLock);
	} else {
		LOG_INF("set I2C failed when moving the motor\n");
	}

	return 0;
}

static inline int setAFInf(unsigned long a_u4Position)
{
	spin_lock(g_pAF_SpinLock);
	g_u4AF_INF = a_u4Position;
	spin_unlock(g_pAF_SpinLock);
	return 0;
}

static inline int setAFMacro(unsigned long a_u4Position)
{
	spin_lock(g_pAF_SpinLock);
	g_u4AF_MACRO = a_u4Position;
	spin_unlock(g_pAF_SpinLock);
	return 0;
}

/* ////////////////////////////////////////////////////////////// */
long DW9714AF_Ioctl(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param)
{
	long i4RetValue = 0;

	switch (a_u4Command) {
	case AFIOC_G_MOTORINFO:
		i4RetValue = getAFInfo((__user stAF_MotorInfo *) (a_u4Param));
		break;

	case AFIOC_T_MOVETO:
		i4RetValue = moveAF(a_u4Param);
		break;

	case AFIOC_T_SETINFPOS:
		i4RetValue = setAFInf(a_u4Param);
		break;

	case AFIOC_T_SETMACROPOS:
		i4RetValue = setAFMacro(a_u4Param);
		break;

	default:
		LOG_INF("No CMD\n");
		i4RetValue = -EPERM;
		break;
	}

	return i4RetValue;
}
//norman@20161116 for noise start	
/*
#define BEGIN_STEPS 400
#define END_STEPS 50
#define JUMP_STEPS 20
#define STEP_PERIOD_MS 13
*/
//norman@20161116 for noise end		

/* Main jobs: */
/* 1.Deallocate anything that "open" allocated in private_data. */
/* 2.Shut down the device on last close. */
/* 3.Only called once on last time. */
/* Q1 : Try release multiple times. */
int DW9714AF_Release(struct inode *a_pstInode, struct file *a_pstFile)
{
	LOG_INF("Start\n");

	if (*g_pAF_Opened == 2) {
//norman@20161122 for noise start	
#if Slew_Rate_Control
	if(g_u4CurrPosition > 500)
	{	
		s4AF_WriteReg(500);
		msleep(15);
	}		
	if(g_u4CurrPosition > 400)
	{		
		s4AF_WriteReg(400);
		msleep(15);
	}
	if(g_u4CurrPosition > 350)
	{		
	  s4AF_WriteReg(350);
		msleep(15);
	}
	if(g_u4CurrPosition > 300)
	{		
		s4AF_WriteReg(300);
		msleep(15);
	}
	if(g_u4CurrPosition > 250)
	{		
		s4AF_WriteReg(250);
		msleep(15);
	}		
	if(g_u4CurrPosition > 200)
	{	
		s4AF_WriteReg(200);
		msleep(15);
	}
	if(g_u4CurrPosition > 100)
	{	
		s4AF_WriteReg(100);
		msleep(15);
	}
#else      
   	s4AF_WriteReg(200);
		msleep(20);
		s4AF_WriteReg(100);
		msleep(20);
#endif   
LOG_INF("Wait\n");
//norman@20161122 for noise end				
	}

	if (*g_pAF_Opened) {
		LOG_INF("Free\n");

		spin_lock(g_pAF_SpinLock);
		*g_pAF_Opened = 0;
		spin_unlock(g_pAF_SpinLock);
	}

	LOG_INF("End\n");

	return 0;
}

void DW9714AF_SetI2Cclient(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened)
{
	g_pstAF_I2Cclient = pstAF_I2Cclient;
	g_pAF_SpinLock = pAF_SpinLock;
	g_pAF_Opened = pAF_Opened;
}
