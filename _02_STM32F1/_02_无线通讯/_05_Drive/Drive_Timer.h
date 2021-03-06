/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Timer.h
* @Description : 定时器驱动	
* @Date        : 2016/8/8
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : None
*=============================================================================*/ 

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_TIMER_H
#define __DRIVE_TIMER_H  

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h"  

/* 全局宏定义 ----------------------------------------------------------------*/  

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  
void TIM2_Init(void);
void TIM3_Init(void);
void TIM4_Init(void);
void TIM5_Init(void);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



