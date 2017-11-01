/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Interrupt.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Interrupt.h"
#include "User_Library.h" 
#include "OS_StartFile.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� -------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_IRQHandler()     
* @Description   : ��ʱ 
* @Data          : 2016/3/19
* @Explain       : 1us * 0xffffffff
------------------------------------------------------------------------------*/ 
//=========================================================================
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //����жϱ�־λ 	
		OS_Clock ++; //��ֹʱ������������������
	}		
}	

/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_IRQHandler()     
* @Description   : ���߳� 
* @Data          : 2016/3/18
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
//=========================================================================
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //����жϱ�־λ
		OSThread_6();
	}		
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_IRQHandler()     
* @Description   : ϵͳ�߳� 
* @Data          : 2016/3/19
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{ 
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //����жϱ�־λ
		OSThread_4(); 
	}
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM1_UP_TIM10_IRQHandler()     
* @Description   : �߳�7���ͼ��̣߳� 
* @Data          : 2016/4/19
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
void TIM1_UP_TIM10_IRQHandler(void)  
{ 
	if(TIM_GetITStatus(TIM10,TIM_IT_Update) != RESET)
	{ 
		TIM_ClearITPendingBit(TIM10,TIM_IT_Update); //����жϱ�־λ	
		OSThread_7();   			
			
			
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM1_BRK_TIM9_IRQHandler()     
* @Description   : ��Ƶ
* @Data          : 2016/4/19
* @Explain       : None
------------------------------------------------------------------------------*/ 
void TIM1_BRK_TIM9_IRQHandler(void)   
{
	static u16 _cnt = 0;
	if(TIM_GetITStatus(TIM9,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM9,TIM_IT_Update); //����жϱ�־λ
 		
		_cnt ++;	
		if(_cnt >= 1000)	
		{   								
			TIM_Cmd(TIM9,DISABLE);  		
			Exti_Disable(4);			
//			g_FreqMod = FREQ_MODE_FREE;
			_cnt = 0;
		}
		 
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM1_TRG_COM_TIM11_IRQHandler()     
* @Description   : �߳�5���м��̣߳� 
* @Data          : 2016/7/20
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
void TIM1_TRG_COM_TIM11_IRQHandler(void)   
{ 
	if(TIM_GetITStatus(TIM11,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM11,TIM_IT_Update); //����жϱ�־λ 
		OSThread_5(); 	
		
		
	}
}
	
	
/**----------------------------------------------------------------------------
* @FunctionName  : TIM8_BRK_TIM12_IRQHandler()     
* @Description   : ����ͨ�ţ�10k�����ʣ�
* @Data          : 2016/7/22
* @Explain       : 10ms/50Hz
------------------------------------------------------------------------------*/ 
void  TIM8_BRK_TIM12_IRQHandler(void)   
{  
	if(TIM_GetITStatus(TIM12,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM12,TIM_IT_Update); //����жϱ�־λ 
//		AD9851_FM(ADC_Result_Get(2,1)*3.3f/4096.0f);    
//		TEST = ~TEST; 
		OSThread_3(); 
	} 
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM8_UP_TIM13_IRQHandler()     
* @Description   : None
* @Data          : 2016/7/20
* @Explain       : None
------------------------------------------------------------------------------*/ 
void  TIM8_UP_TIM13_IRQHandler(void)   
{ 
	if(TIM_GetITStatus(TIM13,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM13,TIM_IT_Update); //����жϱ�־λ 
		
		
	} 
}





/**----------------------------------------------------------------------------
* @FunctionName  : EXTI0_IRQHandler()     
* @Description   : �ⲿ�ж�0������� 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{ 
		
		EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI1_IRQHandler()     
* @Description   : �ⲿ�ж�1������� 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
	{ 
 
		EXTI_ClearITPendingBit(EXTI_Line1); //���LINE1�ϵ��жϱ�־λ 
	}
}
 
/**----------------------------------------------------------------------------
* @FunctionName  : EXTI2_IRQHandler()     
* @Description   : �ⲿ�ж�2������� 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{ 
 
		EXTI_ClearITPendingBit(EXTI_Line2); //���LINE2�ϵ��жϱ�־λ 
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI3_IRQHandler()     
* @Description   : �ⲿ�ж�3������� 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)	
	{ 
 
		EXTI_ClearITPendingBit(EXTI_Line3); //���LINE3�ϵ��жϱ�־λ 
	}
}


/**----------------------------------------------------------------------------
* @FunctionName  : EXTI4_IRQHandler()     
* @Description   : �ⲿ�ж�4������� 
* @Data          : 2016/7/12
* @Explain       : ������Ƶ��PE4��
------------------------------------------------------------------------------*/ 
void EXTI4_IRQHandler(void)
{ 
		
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{ 
		 
		EXTI_ClearITPendingBit(EXTI_Line4); //���LINE4�ϵ��жϱ�־λ 
	}
}
 
/**----------------------------------------------------------------------------
* @FunctionName  : EXTI15_10_IRQHandler()     
* @Description   : �ⲿ�ж�10������� 
* @Data          : 2016/7/23
* @Explain       : ���ڽ��ն�ϢPF10
------------------------------------------------------------------------------*/ 
void EXTI15_10_IRQHandler(void)
{  
	if(EXTI_GetITStatus(EXTI_Line10)!=RESET)	
	{  
		Message_Receive();
		EXTI_ClearITPendingBit(EXTI_Line10); //���LINE3�ϵ��жϱ�־λ 
	}
}










/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





