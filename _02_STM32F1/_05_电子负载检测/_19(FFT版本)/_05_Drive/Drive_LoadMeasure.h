/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_LoadMeasure.h
* @Description : None
* @Date        : 2017年7月31日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 负载检测计算
*=============================================================================*/
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_LOADMEASURE_H
#define __DRIVE_LOADMEASURE_H

/* 头文件包含 ----------------------------------------------------------------*/
#include "User_Library.h"

/* 全局宏定义 ----------------------------------------------------------------*/ 
#define PER_POINT		(64)	//每个周期采集的点数
#define PER_T_CNT		(8)		//采集的周期数
#define ADC_LENTH		(PER_POINT*PER_T_CNT)	

#define PER_FFT_CNT		(PER_T_CNT)		//FFT结果的频率间隔 


/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/  
extern float ADC_Buff_V[ADC_LENTH];
extern float ADC_Buff_I[ADC_LENTH];  
extern Type_ADC_Result ADC_Result;
extern Type_FFT_Result FFT_Result;
extern u8 PhaseMeasure_State;    

/* 全局函数声明 --------------------------------------------------------------*/   
void ADC_Analysis(void);
void FFT_Analysis(void);
void ADC_Shift_Get(void);

void PhaseMeasure_Start(double freq);
void PhaseMeasure_End(void);
void PhaseMeasure_ADC_Handle(void);
 

#endif
/*******************************(C) COPYRIGHT 2017 None *********************************/







