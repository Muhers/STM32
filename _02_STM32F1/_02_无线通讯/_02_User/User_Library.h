/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : User_Library.c
* @Description : None	
* @Date        : 2016/8/7
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : None
*=============================================================================*/ 

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __USER_LIBRARY_H
#define __USER_LIBRARY_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/    

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 
#define	MESSAGE_FREQ				50   //50Hz,20ms
#define	Receive_ID					3	

/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ������� --------------------------------------------------------------*/   
/* ϵͳ�ļ� --------------------------------*/ 
#include <stdlib.h> 		
#include <stdint.h>		
#include <math.h>	
#include <string.h>	
#include "system_stm32f10x.h"		
#include "stm32f10x.h" 	
#include "stm32f10x_gpio.h"	
#include "stm32f10x_tim.h"
#include "stm32f10x_adc.h"	
#include "stm32f10x_dac.h" 	
#include "sys.h"	


/* �����ļ� --------------------------------*/   
#include "Drive_GPIO.h"
#include "Drive_Timer.h"
#include "Drive_EXTI.h"
#include "Drive_Interrupt.h"
#include "Drive_ADC.h"
#include "Drive_DAC.h"
#include "Drive_OLED.h" 
#include "Drive_Message.h"	


/* Ӧ�ó��� --------------------------------*/     
#include "OS_StartFile.h"
#include "App_Test.h"  
#include "App_LED.h"  
#include "App_Message.h"  
#include "App_Key.h"  




#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/













