/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/7/23

*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_MESSAGE_H
#define __DRIVE_MESSAGE_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Library.h"  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/  
#define SEND 	0
#define RECEIVE 1

#define MESSAGE_SEND_PIN 			PBout(10)
#define MESSAGE_RECEIVE_PIN 		PBin(11)

#define	MESSAGE_FREQ				100   //50Hz,20ms
#define	MESSAGE_T					(1000/MESSAGE_FREQ)  //50Hz,20ms

#define	MESSAGE_LENTH				12  //���䳤�� 


#define	MESSAGE_STATE_AUDIO			0
#define	MESSAGE_STATE_PREPARE		1
#define	MESSAGE_STATE_MESSAGE		2 


/* �ṹ������ ----------------------------------------------------------------*/ 
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
	
}Type_Message; //�������		
				
	

/* ȫ�ֱ������� --------------------------------------------------------------*/   
extern Type_Message Message;

/* ȫ�ֺ������� --------------------------------------------------------------*/   
void MessageSend_Init(void);
void Message_SendByte(u8 _Data);

void MessageReceive_Init(void);
void Message_Receive(void);
u8 Message_OEC(u8 _Data);


#endif
/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/



