/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_LoadAnalysis.h
* @Description : None
* @Date        : 2017年7月31日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 监测分析
*=============================================================================*/
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_LOADANALYSIS_H
#define __DRIVE_LOADANALYSIS_H

/* 头文件包含 ----------------------------------------------------------------*/
#include "User_Library.h"

/* 全局宏定义 ----------------------------------------------------------------*/ 


/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/  
extern float ADC_Buff_V[ADC_LENTH];
extern float ADC_Buff_I[ADC_LENTH];   
extern Type_ADC_Result ADC_Result; 
   

/* 全局函数声明 --------------------------------------------------------------*/   
void ADC_Analysis(void); 
void ADC_Shift_Get(void);
void Others_Get(void);
	
void PhaseMeasure_Start(double freq);
void PhaseMeasure_End(void);
void PhaseMeasure_ADC_Handle(void);
 

#endif
/*******************************(C) COPYRIGHT 2017 None *********************************/







