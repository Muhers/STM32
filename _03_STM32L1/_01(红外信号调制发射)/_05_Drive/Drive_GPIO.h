/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_GPIO.h
* @Description : None	
* @Date        : 2016/8/7
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/ 

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_GPIO_H
#define __DRIVE_GPIO_H  

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h"  

/* 全局宏定义 ----------------------------------------------------------------*/   
#define P_Out(GPIO_X,_BIT,_VALUE)		(_VALUE?GPIO_WriteBit(GPIO##GPIO_X,GPIO_Pin_##_BIT,Bit_SET):GPIO_WriteBit(GPIO##GPIO_X,GPIO_Pin_##_BIT,Bit_RESET))   
#define P_Out_Value(GPIO_X,_BIT)		(GPIO_ReadOutputDataBit(GPIO##GPIO_X,GPIO_Pin_##_BIT)?1:0)   

#define P_In_Value(GPIO_X,_BIT)			(GPIO_ReadInputDataBit(GPIO##GPIO_X,GPIO_Pin_##_BIT)?1:0)   


/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  
void GPIO_Test_Init(void);  
void GPIO_Key_Init(void);
void GPIO_LED_Init(void);  
void GPIO_Infrared_Init(void);
	
#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/



