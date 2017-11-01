/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Measuring.h
* @Description : FM音频通信
* @Date        : 2016/7/29
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __APP_MEASURING_H
#define __APP_MEASURING_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/
#define MEASURING_MODE_PHASE				0
#define MEASURING_MODE_VOLTAGE				1
#define MEASURING_MODE_2					2
#define MEASURING_MODE_3					3
#define MEASURING_MODE_4					4

#define MEASURING_START						0
#define MEASURING_COMPLETE					1 

#define MEASURING_ADC_LENTH					1024

#define ERROR_HANDLE(X)			{OS_Decim_Show(0,460,X,4,0,16,1);}

/* 结构体声明 ----------------------------------------------------------------*/ 
typedef struct 
{   
	double 	Elect_Min;//当前电流最小值 
	double 	Volt_Min;//当前电压最小值 
	double 	g_EffecElect_Min;//全局电流有效值最小值	
	double 	g_EffecVolt_Min;//全局电压有效值最小值	
	double 	g_P_Min;	 		
	double 	g_Q_Min;	
	 
	double 	Elect_Max;//当前电流最大值   
	double 	Volt_Max;//当前电压最大值 
	double 	ReallyVpp;//真实采集的Vpp

	
	double 	CountS;//视在功率 
	double 	CountP;//有功功率 
	double 	CountQ;//无功功率 
	double 	CountPF;//计算出来的功率因数 PF = P/S 
	
	double  EffecVolt;//有效值		
	double  EffecElect;		
	
	double 	g_EffecVolt_Max;	//全局有效值				
	double 	g_EffecElect_Max;		
				 
	double 	g_P_Max;	//全局功率				
	double 	g_Q_Max;		
		  
	u32 	Freq;//频率
	double 	Duty;//占空比
	u32 	T;//频率
	
	u8 		ADC_Flag;//定时器采集ADC标志 
	u16 	ADC_Cnt;//定时器采集ADC计数  
	double 	ADC1_Buff[MEASURING_ADC_LENTH];//0.1ms/Point,2000Point ->200ms 采完 
	double 	ADC2_Buff[MEASURING_ADC_LENTH];//0.1ms/Point,2000Point ->200ms 采完 
	
	u8 		FFT_Flag;//定时器采集ADC标志  
	double  FFT_Basis;//基波
	double  FFT_HarmonicSum;//谐波总和
	
	double  FFT_Buff[MEASURING_ADC_LENTH];
	double  FFT_THD;//失真度
	
	u8 		Show_Flag;//显示标志 
}Type_Measuring;

/* 全局变量声明 --------------------------------------------------------------*/ 
extern u8 MeasuringMode;
extern Type_Measuring Measuring;

/* 全局函数声明 --------------------------------------------------------------*/   
extern Type_AppList App_Measuring;


#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



