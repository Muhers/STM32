/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : User_Include.h
* @Description : None
* @Date        : 2017/2/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __USER_INCLUDE_H
#define __USER_INCLUDE_H 

/* 头文件包含 ----------------------------------------------------------------*/  
/* uCOS-III ------------------------*/
#include "includes.h"
#include "os_app_hooks.h"

/* 平台自带 ------------------------*/
#include "arm_math.h"
#include "stm32f4xx.h" 
#include "stm32f4xx_exti.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_usart.h"	
#include "stm32f4xx_dma.h"	
#include "stm32f4xx_adc.h"	 
#include "sys.h"
#include "delay.h"
#include "usart.h"	 
#include "OS_Start.h"
#include "sram.h"
#include "touch.h" 
#include "ILI93xx.h" 

/* emWin ---------------------------*/
#include "GUI.h"
 
 /* 驱动 ----------------------------*/ 
#include "Drive_UI.h"
#include "Drive_GPIO.h"


/* 全局宏定义 ----------------------------------------------------------------*/ 

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  



#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/



