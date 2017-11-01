/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : User_Library.h
* @Description : None
* @Date        : 2016/7/10
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __USER_LIBRARY_H
#define __USER_LIBRARY_H 

/* 头文件包含 ----------------------------------------------------------------*/    

/* 全局宏定义 ----------------------------------------------------------------*/ 
#define	MESSAGE_LENTH				16  //传输长度 
#define SIMULATION    				1	//1模拟，0实际
#define	MESSAGE_FREQ				50  //50Hz,20ms


/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/   
/* 系统文件 --------------------------------*/ 
#include <stdlib.h>
#include "arm_math.h"						
#include "stm32f4xx.h" 							
#include "stm32f4xx_exti.h"					
#include "stm32f4xx_spi.h"				
#include "stm32f4xx_adc.h"						
#include "stm32f4xx_dma.h"					
#include "stm32f4xx_usart.h"				
#include "stm32f4xx_dma.h"				
#include "stm32f4xx_adc.h"	 
#include "stm32f4xx_syscfg.h"	 



/* 硬件驱动 -------------------------------*/ 
#include "TFT_LCD.h" 	 
#include "my_sys.h"
#include "PS2.h" 
#include "W25Q64.h" 
#include "fontupd.h" 
#include "Drive_GPIO.h"	
#include "Drive_Interrupt.h"	
#include "Drive_Timer.h"	 	
#include "Drive_Flash.h"	 
#include "Drive_Exti.h"
#include "Drive_Touch.h" 	
#include "Drive_Message.h"	



/* 应用程序 --------------------------------*/   
#include "App_LED.h" 
#include "App_Test.h"   
#include "App_Touch.h"   
#include "App_PS2.h"  
#include "App_Key.h"   
#include "App_Message.h"   
#include "App_VirtualKeyBoard.h"  






#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/











