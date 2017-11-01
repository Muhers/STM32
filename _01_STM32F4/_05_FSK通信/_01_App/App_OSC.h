/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_OSC.h
* @Description : None
* @Date        : 2016/3/10
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __App_OSC_H
#define __App_OSC_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"
#include "OS_UI.h" 	

/* 全局宏定义 ----------------------------------------------------------------*/
 		 							
/* 结构体声明 ----------------------------------------------------------------*/ 
																	
/* 全局变量声明 --------------------------------------------------------------*/ 
extern u8 OSC_PerX;
extern u8 OSC_PerY;
extern u8 Ch1_Switch, Ch2_Switch,Change_Switch; 

/* 全局函数声明 --------------------------------------------------------------*/  
extern Type_AppList App_OSC;
void OSC_BarX(void);
void OSC_BarY(void);
void OSC_CH_Switch(u8 ch,u8 sw);	
void OSC_Auto(void);
void OSC_ShiftX(u16 x);
void OSC_Data_Show(void);
void OSC_Switch(void);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



