/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_MCP42100.h
* @Description : None
* @Date        : 2016/7/20
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_MCP42100_H
#define __DRIVE_MCP42100_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h"  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/    
#define MCP42100_CS 			PBout(6)//使能
#define MCP42100_SCK 			PCout(10)//使能
#define MCP42100_SI				PCout(11)//使能

#define MCP42100_ENABLE()		MCP42100_CS = 0//使能
#define MCP42100_DISABLE()		MCP42100_CS = 1//使能
#define MCP42100_SCK_H() 		MCP42100_SCK = 1//
#define MCP42100_SCK_L() 		MCP42100_SCK = 0//
#define MCP42100_SI_H() 		MCP42100_SI = 1//
#define MCP42100_SI_L() 		MCP42100_SI = 0//

#define MCP42100_NONE					0x10
#define MCP42100_P0						0x11
#define MCP42100_P1						0x12
#define MCP42100_ALL					0x13

/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/    
void MCP42100_Init(void); 
void MCP42100_Control(u8 _ch,u8 _value);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



