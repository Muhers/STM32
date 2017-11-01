/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Interrupt.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Interrupt.h"
#include "User_Library.h" 
#include "OS_StartFile.h" 

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_IRQHandler()     
* @Description   : 计时 
* @Data          : 2016/3/19
* @Explain       : 1us * 0xffffffff
------------------------------------------------------------------------------*/ 
//=========================================================================
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //清除中断标志位 	
		OS_Clock ++; //防止时钟溢出，特设溢出次数
	}		
}	

/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_IRQHandler()     
* @Description   : 主线程 
* @Data          : 2016/3/18
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
//=========================================================================
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //清除中断标志位
		OSThread_6();
	}		
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_IRQHandler()     
* @Description   : 系统线程 
* @Data          : 2016/3/19
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{ 
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //清除中断标志位
		OSThread_4(); 
	}
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM1_UP_TIM10_IRQHandler()     
* @Description   : 线程7（低级线程） 
* @Data          : 2016/4/19
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
void TIM1_UP_TIM10_IRQHandler(void)  
{ 
	if(TIM_GetITStatus(TIM10,TIM_IT_Update) != RESET)
	{ 
		TIM_ClearITPendingBit(TIM10,TIM_IT_Update); //清除中断标志位	
		OSThread_7();   			
			
			
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM1_BRK_TIM9_IRQHandler()     
* @Description   : 测频
* @Data          : 2016/4/19
* @Explain       : None
------------------------------------------------------------------------------*/ 
void TIM1_BRK_TIM9_IRQHandler(void)   
{
	static u16 _cnt = 0;
	if(TIM_GetITStatus(TIM9,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM9,TIM_IT_Update); //清除中断标志位
 		
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
* @Description   : 线程5（中级线程） 
* @Data          : 2016/7/20
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
void TIM1_TRG_COM_TIM11_IRQHandler(void)   
{ 
	if(TIM_GetITStatus(TIM11,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM11,TIM_IT_Update); //清除中断标志位 
		OSThread_5(); 	
		
		
	}
}
	
	
/**----------------------------------------------------------------------------
* @FunctionName  : TIM8_BRK_TIM12_IRQHandler()     
* @Description   : 语音通信（10k采样率）
* @Data          : 2016/7/22
* @Explain       : 10ms/50Hz
------------------------------------------------------------------------------*/ 
void  TIM8_BRK_TIM12_IRQHandler(void)   
{  
	if(TIM_GetITStatus(TIM12,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM12,TIM_IT_Update); //清除中断标志位 
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
		TIM_ClearITPendingBit(TIM13,TIM_IT_Update); //清除中断标志位 
		
		
	} 
}





/**----------------------------------------------------------------------------
* @FunctionName  : EXTI0_IRQHandler()     
* @Description   : 外部中断0服务程序 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{ 
		
		EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI1_IRQHandler()     
* @Description   : 外部中断1服务程序 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
	{ 
 
		EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE1上的中断标志位 
	}
}
 
/**----------------------------------------------------------------------------
* @FunctionName  : EXTI2_IRQHandler()     
* @Description   : 外部中断2服务程序 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{ 
 
		EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE2上的中断标志位 
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI3_IRQHandler()     
* @Description   : 外部中断3服务程序 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)	
	{ 
 
		EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE3上的中断标志位 
	}
}


/**----------------------------------------------------------------------------
* @FunctionName  : EXTI4_IRQHandler()     
* @Description   : 外部中断4服务程序 
* @Data          : 2016/7/12
* @Explain       : 用来测频（PE4）
------------------------------------------------------------------------------*/ 
void EXTI4_IRQHandler(void)
{ 
		
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{ 
		 
		EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE4上的中断标志位 
	}
}
 
/**----------------------------------------------------------------------------
* @FunctionName  : EXTI15_10_IRQHandler()     
* @Description   : 外部中断10服务程序 
* @Data          : 2016/7/23
* @Explain       : 用于接收短息PF10
------------------------------------------------------------------------------*/ 
void EXTI15_10_IRQHandler(void)
{  
	if(EXTI_GetITStatus(EXTI_Line10)!=RESET)	
	{  
		Message_Receive();
		EXTI_ClearITPendingBit(EXTI_Line10); //清除LINE3上的中断标志位 
	}
}










/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





