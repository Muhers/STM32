/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Frequency.h
* @Description : None
* @Date        : 2016/7/12
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __APP_FREQUENCY_H
#define __APP_FREQUENCY_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/
#define FREQ_MODE_FREE  0
#define FREQ_MODE_LF   	1
#define FREQ_MODE_HF 	2
#define FREQ_MODE_DUTY 	3

/* 结构体声明 ----------------------------------------------------------------*/ 
																	
/* 全局变量声明 --------------------------------------------------------------*/ 
extern u8 g_FreqMod;
extern u32 g_FreqCnt;
extern u32 g_FreqT;  
extern u32 g_FreqT_H;
extern u32 g_Freq;  
extern u32 g_FreqDuty;

/* 全局函数声明 --------------------------------------------------------------*/  
extern Type_AppList App_Frequency;
void Frequency_Mode_Low(void);
unsigned int Frequency_Main(void);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



