 /*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/7/23
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_MESSAGE_H
#define __DRIVE_MESSAGE_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Library.h" 

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/    
#define MESSAGE_SEND_PIN 			PFout(9)
#define MESSAGE_RECEIVE_PIN 		PFin(10)


#define	MESSAGE_T					(1000/MESSAGE_FREQ)  //50Hz,20ms



/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern u8 MessageSendBuff[MESSAGE_LENTH];
extern u8 MessageReceiveBuff[MESSAGE_LENTH];
extern u8 MessageCnt; 
extern u32 ReceiveTime[30];

/* ȫ�ֺ������� --------------------------------------------------------------*/   
void MessageSend_Init(void);
void Message_SendByte(u8 _Data);

void MessageReceive_Init(void);
void Message_Receive(void);
u8 Message_OEC(u8 _Data);
void Message_SendData(u8 _Data);
void Message_SendString(u8 *ch);


#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/































