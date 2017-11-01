/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/7/23
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_MESSAGE_H
#define __DRIVE_MESSAGE_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h"  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/  
#define SEND 	0
#define RECEIVE 1

#define MESSAGE_SEND_PIN 			PFout(9)
#define MESSAGE_RECEIVE_PIN 		PFin(10)

#define	MESSAGE_FREQ				50  //50Hz,20ms
#define	MESSAGE_LENTH				10  //传输长度 
#define	MESSAGE_TS					(1000/MESSAGE_FREQ)  //50Hz,20ms


/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 
extern u8 MessageSendBuff[10];
extern u8 MessageReceiveBuff[10];
extern u8 MessageCnt; 
extern u32 ReceiveTime[30];

/* 全局函数声明 --------------------------------------------------------------*/   
void MessageSend_Init(void);
void Message_SendByte(u8 _Data);

void MessageReceive_Init(void);
void Message_Receive(void);
u8 Message_OEC(u8 _Data);


#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



