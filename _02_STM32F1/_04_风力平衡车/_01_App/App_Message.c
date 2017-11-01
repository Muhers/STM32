/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================

*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Message.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/ 
#define 	RELAY_ON()			PA7 = 1
#define 	RELAY_OFF()			PA7 = 0



/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 
u8 Receive_ID = 0x01;
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
	if(Message.ID == Receive_ID||Message.ID == GROUP_CALL_ID) //判断地址
	{  
		if(Message.State == MESSAGE_STATE_AUDIO)//判断是否是语音数据
		{
			if(Message.Order&MESSAGE_MODE_AUDIO)//连接通信 
			{ 
				RELAY_ON();
				OS_String_Show(0,0,(u8*)"语音信号已接通"); 
				
			}
			else //关闭通信	
			{
				RELAY_OFF();
				OS_String_Show(0,0,(u8*)"语音信号已断开"); 
			}
		}
		 
	}
	else 
	{ 
		RELAY_OFF();//关闭通信	
		OS_String_Show(0,0,(u8*)"语音信号已断开");  
	} 
	 
	OS_String_Show(0,1,(u8*)"从机地址："); OS_Num_Show(5,1,Receive_ID,3);  
	OS_String_Show(0,3,(u8*)"实时数据："); OS_Num_Show(5,3,Message.Data,4); 
	OS_String_Show(0,2,Message.String[Receive_ID]);//显示短消息 	 
	
	if(Key_Get(KEY1,KEY_MODE_SHORT))
	{
		Receive_ID --;
	}	
		
	if(Key_Get(KEY2,KEY_MODE_SHORT))
	{
		Receive_ID ++;
	}
	
	Receive_ID %= 16; 
	Key_Clear(KEY_MODE_SHORT);
	
	
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
								OS_STATE_ACTIVE,OS_THREAD_FREE, \
								(u8*)"Message",10};	

								
								
						
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





