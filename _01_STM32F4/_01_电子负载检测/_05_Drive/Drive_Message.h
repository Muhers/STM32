/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/11/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 
-------------------------------------------------------------------------------
�����ң���0~MESSAGE_LENTH - 1  
����Ӹߵ���λ�����磬CRC16[0] �� CRC16_H
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_MESSAGE_H
#define __DRIVE_MESSAGE_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Library.h" 

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
//#define MESSAGE_LENTH  				(7+32*4) //ÿ��fft��ռ8byte��������������16byte		��ʼ��ֹ��-2��CRC-2����ַ��-2��ָ����-1��һ��7byte		64��������ֵ
#define MESSAGE_LENTH  				(LOAD_MAX*4*2+7+32*4)  //ÿ��fft��ռ8byte��������������16byte		��ʼ��ֹ��-2��CRC-2����ַ��-2��ָ����-1��һ��7byte		64��������ֵ
#define MESSAGE_BAUD   				115200 //���ڲ�����
#define MESSAGE_GAP   			 	10000 //ÿ���ֽ�֮��ʱ����Ϊ �� 10ms
#define MESSAGE_CODE_CRC	 		0xCACA//CRCУ���� 
#define MESSAGE_ADDRESS_LOCAL	  	(0x02)//������ַ
#define MESSAGE_ADDRESS_RADIO	  	(0xff)//������ַ

#define MESSAGE_MASTER_LENTH  		(8) 

/* �ṹ������ ----------------------------------------------------------------*/  
/* λ ------------------------------------*/
typedef struct
{
	u16  ADDRESS_TARGET;//1.Ŀ���ַ
	u16  ADDRESS_LOCAL;//2.������ַ
	u16  CODE_FUNCTION;//3.������
	u16  DATA_START;//4.����
	u16  CRC16[2];//5.CRC16У���� 
	//˵����0-���λ 
}Struct_MessageByte;

typedef struct
{
	u8  Receive_Buff[MESSAGE_LENTH];     //���ջ���,���USART_REC_LEN���ֽ�. 
	u8  Send_Buff[MESSAGE_LENTH];     //���ջ���,���USART_REC_LEN���ֽ�.   
	u8  Receive_Flag;  //0,���ڽ���		1���������
}Struct_Message;


/* ȫ�ֱ������� --------------------------------------------------------------*/  
extern const Struct_MessageByte MESSAGE_BYTE;
extern Struct_Message Message_USART3;

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void Message_Send_USART3(void); 
void Message_Handle_USART3(void);  
 
#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





































