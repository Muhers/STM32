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

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/   
extern Type_Recognize Recognize_Source[LOAD_MAX];
extern Type_Recognize Recognize_New; 
extern u8 PhaseMeasure_State;  


/* 全局函数声明 --------------------------------------------------------------*/     
Type_Recognize_Result Load_Recognize(Type_Recognize Recognize_New);
void Recognize_New_Update(void);


#endif
/*******************************(C) COPYRIGHT 2017 None *********************************/







