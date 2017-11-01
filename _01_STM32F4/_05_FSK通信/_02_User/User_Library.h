/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : User_Library.h
* @Description : None
* @Date        : 2016/7/10
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __USER_LIBRARY_H
#define __USER_LIBRARY_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/    

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 
#define	MESSAGE_LENTH				16  //���䳤�� 
#define SIMULATION    				1	//1ģ�⣬0ʵ��
#define	MESSAGE_FREQ				50  //50Hz,20ms


/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ������� --------------------------------------------------------------*/   
/* ϵͳ�ļ� --------------------------------*/ 
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



/* Ӳ������ -------------------------------*/ 
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



/* Ӧ�ó��� --------------------------------*/   
#include "App_LED.h" 
#include "App_Test.h"   
#include "App_Touch.h"   
#include "App_PS2.h"  
#include "App_Key.h"   
#include "App_Message.h"   
#include "App_VirtualKeyBoard.h"  






#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/











