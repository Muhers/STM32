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
#ifndef __DRIVE_LED_H
#define __DRIVE_LED_H  

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h"  

/* 全局宏定义 ----------------------------------------------------------------*/  
#define LED_ON						(0)
#define LED_OFF						(1)

#define LED_MODE_OFF				(0) 
#define LED_MODE_ON					(1)  
#define LED_MODE_OVER				(2) //翻转  
#define LED_MODE_FLASH				(3) //闪烁


#define LED_R(_VALUE)				P_Out(A,0,_VALUE) //设置值
#define LED_R_Value					P_Out_Value(A,0) //值		

#define LED_G(_VALUE)				P_Out(A,1,_VALUE) //设置值
#define LED_G_Value 				P_Out_Value(A,1) //值		

#define LED_B(_VALUE)				P_Out(B,12,_VALUE) //设置值
#define LED_B_Value 				P_Out_Value(B,12) //值		 
									




/* 结构体声明 ----------------------------------------------------------------*/   

/* 全局变量声明 --------------------------------------------------------------*/  

/* 全局函数声明 --------------------------------------------------------------*/  
void LED_Init(void);    
 
void LED_Temp_Set(u8 LED_n,u16 GapTime,u8 Mode,u8 Cnt);
void LED_Default_Set(u8 LED_n,u16 GapTime,u8 Mode);

void LED_Scan_Handle(void);   
u8 LED_Get(u8 Led_x);
void LED_Set(u8 Led_x,u8 Value);	



#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/



