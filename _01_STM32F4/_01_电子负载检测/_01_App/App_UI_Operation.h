/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸)*********************************/
/**============================================================================
* @FileName    : App_UI_Operation.h
* @Description : None
* @Date        : 2017年8月8日
* @By          : Wind(谢玉伸)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 用户操作界面
*=============================================================================*/
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __APP_UI_OPERATION_H
#define __APP_UI_OPERATION_H

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/
#define UI_ORDER_FLASH_WRITE 		(0x01 << 0) //Flash写入
#define UI_ORDER_FLASH_READ 		(0x01 << 1) //Flash读取
#define UI_ORDER_FLASH_ERASE 		(0x01 << 2)	//Flash擦除
#define UI_ORDER_FLASH_LEARN		(0x01 << 3)	//学习


/* 结构体声明 ----------------------------------------------------------------*/
typedef struct 
{  		     
	int Po_x; //坐标
	int Po_y; //坐标
	u16 UI_Mode;//选择界面
	u16 Order; //指令 
	u8 Busy; //忙碌
}Type_UI_Operat; //ADC

/* 全局变量声明 --------------------------------------------------------------*/ 
extern Type_UI_Operat UI_Operat;

/* 全局函数声明 --------------------------------------------------------------*/
extern Type_AppList App_UI_Operation;


extern u16 Recognize_Mode;








#endif
/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸)*********************************/







