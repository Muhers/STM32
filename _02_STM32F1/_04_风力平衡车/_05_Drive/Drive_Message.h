/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/7/23

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

#define MESSAGE_SEND_PIN 			PBout(10)
#define MESSAGE_RECEIVE_PIN 		PBin(11)

#define	MESSAGE_FREQ				100   //50Hz,20ms
#define	MESSAGE_T					(1000/MESSAGE_FREQ)  //50Hz,20ms

#define	MESSAGE_LENTH				12  //传输长度 


#define	MESSAGE_STATE_AUDIO			0
#define	MESSAGE_STATE_PREPARE		1
#define	MESSAGE_STATE_MESSAGE		2 


/* 结构体声明 ----------------------------------------------------------------*/ 
typedef struct 
{  		 
	u8 		Cnt;  
	u8 		Data;
	u8 		State;
	u8 		Lenth;  
	u8 		String[16][MESSAGE_LENTH];	
	u8 		NewMessage[16];
	u8 		ID;
	u8 		Order;
	
}Type_Message; //任务队列		
				
	

/* 全局变量声明 --------------------------------------------------------------*/   
extern Type_Message Message;

/* 全局函数声明 --------------------------------------------------------------*/   
void MessageSend_Init(void);
void Message_SendByte(u8 _Data);

void MessageReceive_Init(void);
void Message_Receive(void);
u8 Message_OEC(u8 _Data);


#endif
/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/



