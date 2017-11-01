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
#define 	RELAY_ON()			PA7 = 1
#define 	RELAY_OFF()			PA7 = 0



/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 
//u8 Receive_ID = 0x01;
u8 Receive_Flag = 0;

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
	static u16 cnt = 0;
	
	if(Message.State && (Receive_ID == Message.ID || Message.ID == GROUP_CALL_ID))//有新短消息
	{
		cnt ++;
		cnt %= 5; 
		if(cnt < 3)
			 OS_String_Show(0,0,(u8*)"您有新的短消息！"); 
		else OS_String_Show(0,0,(u8*)"               "); 

	}
	else
	{
				
		if(MessageErrorFlag == 1) //出错
		{ 
			 OS_String_Show(0,0,(u8*)"正在矫正数据！ ");   
		}
		else
		{
			OS_String_Show(0,0,(u8*)"传输系统一切正常");  
		}
		
		OS_String_Show(0,2,Message.String[Receive_ID]);//显示短消息 	 
	}
	
	OS_String_Show(0,1,(u8*)"本机地址："); OS_Num_Show(5,1,Receive_ID,3);  
	OS_String_Show(0,3,(u8*)"实时数据："); OS_Num_Show(5,3,Message.Data,4); 
	
 
   
	return 0;																	
}		
					
					
unsigned int Message_Start(void)		
{
	static u8 first = 0;
	u8 i = 0,j = 0;
	if(first == 0)
	{ 
		first = 1;
		MessageReceive_Init();  
		GPIO_Relay_Init();
		
		for(j = 0;j < 16;j++)
		for(i = 0;i < MESSAGE_LENTH - 1;i ++)
						Message.String[j][i] = ' ';
		
	}
	
	return 0;
}
 
Type_AppList App_Message = {Message_Main,NULL,Message_Start,NULL, \
								OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
								(u8*)"Message",50};	

								
								
						
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





