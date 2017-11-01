/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Infrared.h
* @Description : 红外驱动	
* @Date        : 2017/10/13
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/ 

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_Infrared_H
#define __DRIVE_Infrared_H  

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h"  

/* 全局宏定义 ----------------------------------------------------------------*/  
#define	INFRARED_CODE_MAX		500

/* 结构体声明 ----------------------------------------------------------------*/ 
typedef struct
{  
	u8 FSM;
	u16 Cnt; 
	u16 Lenth; 
	u16 TimeCode_Buff[INFRARED_CODE_MAX];
	
} Type_Infrared;  

/* 全局变量声明 --------------------------------------------------------------*/  	
extern Type_Infrared Infrared;

/* 全局函数声明 --------------------------------------------------------------*/  
void Infrared_Init(void); 
signed int Infrared_TimeCode_Send(u16 *Buff,u16 Lenth);
void Infrared_TimeCodeSend_Handle(void);


#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/



