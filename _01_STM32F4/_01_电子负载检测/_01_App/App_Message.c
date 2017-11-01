/*******************************(C) COPYRIGHT 2017 None*********************************/
/**============================================================================
* @FileName    : App_Message.c
* @Date        : 2017年8月5日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 通信
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Message.h"

/* 私有宏定义 ----------------------------------------------------------------*/


/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
u8 Message_Update_Flag = 0;

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Message()
* @Description   : 通信
* @Data          : 2017年8月5日
* @Explain       : None
------------------------------------------------------------------------------*/
int Message_Main(void)
{         
//	static u32 time = 0, Clock = 0;
	
//	if(Message_Update_Flag == 0)
//	{ 
//		Message_Send_USART3();  
//		
//		Clock = OS_Clock;
//		time = TIM_GetCounter(TIM2); 
//		Message_Update_Flag = 1; //正在接收
//		
//	} 
//	else if(Message_Update_Flag == 1)
//	{
//		if(TIM_GetCounter(TIM2) + (OS_Clock - Clock) * 0xffffffff - time > 500000)//500ms重新连接
//		{   
//			Message_Update_Flag = 0;//超时重新发送
//		} 
//	}
	 
    return 0;
}	

int Message_Start(void)
{  
	Bluetooth_Init();
	
    return 0;
}	

Type_AppList App_Message = {Message_Main,NULL,Message_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_FREE, \
						(u8*)"Message",10};












/*******************************(C) COPYRIGHT 2017 None*********************************/







