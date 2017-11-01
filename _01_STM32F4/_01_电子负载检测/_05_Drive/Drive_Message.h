/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/11/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 
-------------------------------------------------------------------------------
从左到右，从0~MESSAGE_LENTH - 1  
代表从高到低位，例如，CRC16[0] 是 CRC16_H
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_MESSAGE_H
#define __DRIVE_MESSAGE_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h" 

/* 全局宏定义 ----------------------------------------------------------------*/
//#define MESSAGE_LENTH  				(7+32*4) //每个fft点占8byte，共两组所以是16byte		起始终止码-2，CRC-2，地址码-2，指令码-1，一共7byte		64个其他的值
#define MESSAGE_LENTH  				(LOAD_MAX*4*2+7+32*4)  //每个fft点占8byte，共两组所以是16byte		起始终止码-2，CRC-2，地址码-2，指令码-1，一共7byte		64个其他的值
#define MESSAGE_BAUD   				115200 //串口波特率
#define MESSAGE_GAP   			 	10000 //每个字节之间时间间隔为 ： 10ms
#define MESSAGE_CODE_CRC	 		0xCACA//CRC校验码 
#define MESSAGE_ADDRESS_LOCAL	  	(0x02)//本机地址
#define MESSAGE_ADDRESS_RADIO	  	(0xff)//本机地址

#define MESSAGE_MASTER_LENTH  		(8) 

/* 结构体声明 ----------------------------------------------------------------*/  
/* 位 ------------------------------------*/
typedef struct
{
	u16  ADDRESS_TARGET;//1.目标地址
	u16  ADDRESS_LOCAL;//2.本机地址
	u16  CODE_FUNCTION;//3.功能码
	u16  DATA_START;//4.数据
	u16  CRC16[2];//5.CRC16校验码 
	//说明：0-最高位 
}Struct_MessageByte;

typedef struct
{
	u8  Receive_Buff[MESSAGE_LENTH];     //接收缓冲,最大USART_REC_LEN个字节. 
	u8  Send_Buff[MESSAGE_LENTH];     //接收缓冲,最大USART_REC_LEN个字节.   
	u8  Receive_Flag;  //0,正在接收		1，接收完毕
}Struct_Message;


/* 全局变量声明 --------------------------------------------------------------*/  
extern const Struct_MessageByte MESSAGE_BYTE;
extern Struct_Message Message_USART3;

/* 全局函数声明 --------------------------------------------------------------*/  
void Message_Send_USART3(void); 
void Message_Handle_USART3(void);  
 
#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





































