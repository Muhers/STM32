/*******************************(C) COPYRIGHT 2017 None*********************************/
/**============================================================================
* @FileName    : App_Message.c
* @Date        : 2017��8��5��
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ͨ��
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_Message.h"

/* ˽�к궨�� ----------------------------------------------------------------*/


/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
u8 Message_Update_Flag = 0;

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Message()
* @Description   : ͨ��
* @Data          : 2017��8��5��
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
//		Message_Update_Flag = 1; //���ڽ���
//		
//	} 
//	else if(Message_Update_Flag == 1)
//	{
//		if(TIM_GetCounter(TIM2) + (OS_Clock - Clock) * 0xffffffff - time > 500000)//500ms��������
//		{   
//			Message_Update_Flag = 0;//��ʱ���·���
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







