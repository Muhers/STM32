/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_VoltageGain.c
* @Description : 电压增益
* @Date        : 2016/7/29
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/ 
#include "App_VoltageGain.h"  
#include <math.h>

/* 私有宏定义 ----------------------------------------------------------------*/ 

/* 私有（静态）函数声明 ------------------------------------------------------*/  
	
/* 全局变量定义 --------------------------------------------------------------*/  
double Volt_Zoom = 0;
	
/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : VoltageGain()     
* @Description   : 电压增益
* @Data          : 2016/7/29
* @Explain       : None
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
unsigned int VoltageGain_Main(void)		
{  	 
	static int Voltage_Gain_Level = 0;
	
	/* 自动换挡 -------------------------------------*/
	if(Voltage_Gain_Level > 0)
		if(Measuring.ReallyVpp > 3.2) Volt_Zoom = Voltage_Gain(--Voltage_Gain_Level);
	
	if(Voltage_Gain_Level < 67)
		if(Measuring.ReallyVpp < 2.5) Volt_Zoom = Voltage_Gain(++Voltage_Gain_Level);
	
	return 0;																	
}		

unsigned int VoltageGain_Start(void)		
{
	static u8 first = 0;
	if(first == 0)
	{ 
		first = 1; 
		PGA2310_Init();  
		Volt_Zoom = Voltage_Gain(0); 
		
	}   
	return 0;
} 
Type_AppList App_VoltageGain = {VoltageGain_Main,NULL,VoltageGain_Start,NULL, \
								OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
								(u8*)"VoltageGain",50};	
						
								
/**----------------------------------------------------------------------------
* @FunctionName  : Voltage_Gain()     
* @Description   : 电压增益
* @Data          : 2016/7/29
* @Explain       : 
-------------------------------------------------------------------------------
_dB: 0~67(对应-4~63dB)	
返回值：放大倍数			
------------------------------------------------------------------------------*/
double Voltage_Gain(int _dB)
{
	double Temp; 
	if(_dB > 67) _dB = 67;	
	else if(_dB < 0) _dB = 0;	
	_dB	-= 4;		
	Temp = pow(10,(double)_dB/20.0f); 
	_dB += 192;//见公式(Page10)  
	PGA2310_Control(_dB,_dB); 
	return Temp;//转换成放大倍数
}	
	
	
								
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/

 

								
								
								

