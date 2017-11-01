/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================

*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_Message.h"  
 
/* ˽�к궨�� ----------------------------------------------------------------*/ 
#define 	RELAY_ON()			PA7 = 1
#define 	RELAY_OFF()			PA7 = 0



/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
u8 Receive_ID = 0x01;
u8 Receive_Flag = 0;

/* ȫ�ֱ������� --------------------------------------------------------------*/
  
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Message()     
* @Description   : ͨ�� 
* @Data          : 2016/7/23
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Message_Main(void)		
{  	    	
	if(Message.ID == Receive_ID||Message.ID == GROUP_CALL_ID) //�жϵ�ַ
	{  
		if(Message.State == MESSAGE_STATE_AUDIO)//�ж��Ƿ�����������
		{
			if(Message.Order&MESSAGE_MODE_AUDIO)//����ͨ�� 
			{ 
				RELAY_ON();
				OS_String_Show(0,0,(u8*)"�����ź��ѽ�ͨ"); 
				
			}
			else //�ر�ͨ��	
			{
				RELAY_OFF();
				OS_String_Show(0,0,(u8*)"�����ź��ѶϿ�"); 
			}
		}
		 
	}
	else 
	{ 
		RELAY_OFF();//�ر�ͨ��	
		OS_String_Show(0,0,(u8*)"�����ź��ѶϿ�");  
	} 
	 
	OS_String_Show(0,1,(u8*)"�ӻ���ַ��"); OS_Num_Show(5,1,Receive_ID,3);  
	OS_String_Show(0,3,(u8*)"ʵʱ���ݣ�"); OS_Num_Show(5,3,Message.Data,4); 
	OS_String_Show(0,2,Message.String[Receive_ID]);//��ʾ����Ϣ 	 
	
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

								
								
						
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





