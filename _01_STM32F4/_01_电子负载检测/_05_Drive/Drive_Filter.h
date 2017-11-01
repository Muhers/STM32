/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_Filter.h
* @Description : None
* @Date        : 2017年7月31日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 各种滤波函数
*=============================================================================*/
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_FILTER_H
#define __DRIVE_FILTER_H

/* 头文件包含 ----------------------------------------------------------------*/
#include "User_Library.h"

/* 全局宏定义 ----------------------------------------------------------------*/
#define	FILTER_DEPP_MAX		(10)
#define FIR_LENTH			ADC_LENTH

#define	MAX2(x1,x2)			(x1>x2?x1:x2)
#define	MIN2(x1,x2)			(x1<x2?x1:x2)

/* 结构体声明 ----------------------------------------------------------------*/
typedef struct 
{  		 
	float Value;//值
	u16 Filter_Depp;//滤波深度,0~FILTER_DEPP_MAX
	float Filter_Mutation;//突变阈值	
	float Filter_Section;//滤波区间,取值0~1
	
	float Last_Result[FILTER_DEPP_MAX];//这个不用管 
}Type_Filter; //任务队列	

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数声明 --------------------------------------------------------------*/
int Filter_Wind(Type_Filter *Struct_Filter);
void Sort_Quick(float *num, int l, int r);
void Conv(float *output, float *input1, float *input2, int N1, int N2); 
//void FIR(float *input);
float Phase_Limit(float _phase);





#endif
/*******************************(C) COPYRIGHT 2017 None *********************************/







