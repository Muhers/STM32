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

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/   
/* 系统文件 --------------------------------*/ 
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "arm_math.h"						
#include "stm32f4xx.h" 	
#include "User_Stdafx.h"	
#include "stm32f4xx_exti.h"					
#include "stm32f4xx_spi.h"				
#include "stm32f4xx_adc.h"						
#include "stm32f4xx_dma.h"					
#include "stm32f4xx_usart.h"				
#include "stm32f4xx_dma.h"				
#include "stm32f4xx_adc.h"	 
#include "stm32f4xx_syscfg.h"	 
#include "Material.h"	 

/* 平台驱动 -------------------------------*/  
#include "TFT_LCD.h" 	 
#include "my_sys.h"


/* 硬件驱动 -------------------------------*/ 
#include "PS2.h" 
#include "Drive_IIC.h"
#include "W25Q64.h" 
#include "fontupd.h" 
#include "Drive_GPIO.h"	
#include "Drive_Interrupt.h"	
#include "Drive_Timer.h"	 	
#include "Drive_Flash.h"		
#include "Drive_DMA.h"  
#include "Drive_PWM.h"
#include "Drive_ADC.h"
#include "Drive_DAC.h"
#include "Drive_Exti.h" 
#include "Drive_ADS1271.h"  
#include "Drive_LoadAnalysis.h"
#include "Drive_LoadMeasure.h" 
#include "Drive_FreqMeasure.h"
#include "Drive_Filter.h"
#include "Drive_FFT.h"
#include "Drive_DataSave.h"  
#include "Drive_Message.h"
#include "Drive_Usart.h"
#include "Drive_Bluetooth.h"
#include "OLED.h"
//#include "Drive_DutyMeasuring.h"
//#include "Drive_Touch.h"
//#include "Drive_AD9851.h"
//#include "Drive_MCP42100.h"		
//#include "Drive_Message.h"			
//#include "Drive_PGA2310.h"	
//#include "Drive_x9421.h" 

/* 应用程序 --------------------------------*/   
#include "App_LED.h" 
#include "App_Test.h"  
#include "App_LoadMeasure.h"
#include "App_Message.h"
#include "App_Key.h"  
#include "App_UI_Operation.h"
//#include "App_DutyMeasuring.h"
//#include "App_OSC_Demo.h"
//#include "App_OSC_Demo1.h"
//#include "App_OSC_Demo2.h"
//#include "App_OSC_Demo3.h"
//#include "App_OSC.h"  
//#include "App_FFT.h"  
//#include "App_Frequency.h"  
//#include "App_Touch.h"  
//#include "App_AFG.h" 
//#include "App_PS2.h"  
//#include "App_Key.h"  
//#include "App_AD9851.h"  
//#include "App_Message.h"  
//#include "App_Audio.h"  
//#include "App_PhaseShift.h"  
//#include "App_VoltageGain.h"  
//#include "App_Measuring.h"  
//#include "App_FreqMeasure.h"


#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



