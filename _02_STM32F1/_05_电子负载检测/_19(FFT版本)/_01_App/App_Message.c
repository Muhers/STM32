/*******************************(C) COPYRIGHT 2017 None*********************************/
/**============================================================================
* @FileName    : App_Message.c
* @Date        : 2017年8月5日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F103RC)
* @Explain     : 通信
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Message.h"


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/
u8 Message_Update_Flag = 1;

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Message()
* @Description   : 通信
* @Data          : 2017年8月5日
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Message_Main(void)
{     
//	static u32 time = 0, Clock = 0;
	
//	if(Message_Update_Flag == 1)
//	{
//		Clock = OS_Clock;
//		time = TIM_GetCounter(TIM2); 
//	}
//	if(Message_Update_Flag == 0)
//	{
//		if(TIM_GetCounter(TIM2) + (OS_Clock - Clock) * 0xffff - time > 5000000)//5s自动断开
//		{
//			Bluetooth_Disconect();//断开蓝牙
//		} 
//	}
	
    return 0;
}	

unsigned int Message_Start(void)
{  
	Bluetooth_Init(); 
	
    return 0;
}	

Type_AppList App_Message = {Message_Main,NULL,Message_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"Message",300};











/*******************************(C) COPYRIGHT 2017 None*********************************/







