/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Message.c
* @Description : FSK数字通信
* @Date        : 2016/7/23
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : PF9发送    PF10接收， 采用曼彻斯特编码
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Message.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/ 

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 
 
/* 全局变量声明 --------------------------------------------------------------*/
  
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Message()     
* @Description   : 通信 
* @Data          : 2016/7/23
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Message_Main(void)		
{  	
	u8 i = 0;
	
	for(i = 0;i < MESSAGE_LENTH/2;i++)
		OS_Num_Show(200+100*i,300,(u8)MessageReceiveBuff[i],4,32,1); 
	
	for(i = 0;i < MESSAGE_LENTH/2;i++)
		OS_Num_Show(200+100*i,335,(u8)MessageReceiveBuff[i + MESSAGE_LENTH/2],4,32,1); 
	
	if(PS2.UpData == 1)
	{
		PS2.UpData = 0;
		Message_SendByte((u8)PS2.Result);  
	}
	
	return 0;																	
}		

unsigned int Message_Start(void)		
{
	static u8 first = 0;
	if(first == 0)
	{
		first = 1;   
		MessageReceive_Init();  
		MessageSend_Init();  
	}
	
	return 0;
}
 
Type_AppList App_Message = {Message_Main,NULL,Message_Start,NULL, \
								OS_STATE_ACTIVE,OS_THREAD_SYSTEM, \
								(u8*)"Message",200};	
						
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





