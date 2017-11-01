/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_VirtualKeyBoard.h
* @Description : None
* @Date        : 2016/8/22
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __APP_VIRTUALKEYBOARD_H
#define __APP_VIRTUALKEYBOARD_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h" 

/* 全局宏定义 ----------------------------------------------------------------*/
 		 							
/* 结构体声明 ----------------------------------------------------------------*/ 
typedef struct 
{  		  
	u16 x1;
	u16 y1;
	u16 x2;
	u16 y2;
	u16 TextColor;
	u16 BackColor;
	u8 State;//当前状态
	u8 LastState;//有变化的状态
	u8 Used; 
	u8 Updata;//数据更新
}Type_VKBoard; //键盘	
				
				

/* 全局变量声明 --------------------------------------------------------------*/ 
extern u8 VKBoard_Aa;//大小写 
extern u8 VKBoard_ResultCh[MESSAGE_LENTH];//结果
extern u8 VKBoard_Cnt;

/* 全局函数声明 --------------------------------------------------------------*/  
extern Type_AppList App_VirtualKeyBoard;
void VK_Buff_Clear(void);
void VirtualKey_FullShow(u8 Mode);


#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



