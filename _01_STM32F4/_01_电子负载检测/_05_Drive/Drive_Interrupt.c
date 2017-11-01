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
* @FunctionName  : TIM5_IRQHandler()     
* @Description   : 计时 
* @Data          : 2017/7/17
* @Explain       : (1/168) * 0xffffffff us
------------------------------------------------------------------------------*/ 
//=========================================================================
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update); //清除中断标志位 	
		Time_168M_Over ++; 
	}		
}	

/**----------------------------------------------------------------------------
* @FunctionName  : TIM1_UP_TIM10_IRQHandler()     
* @Description   : 定时采集AD
* @Data          : 2016/4/19
* @Explain       : time_gap = （1000000/16.8）* AD_speed us
------------------------------------------------------------------------------*/ 
void TIM1_UP_TIM10_IRQHandler(void)  
{ 
	if(TIM_GetITStatus(TIM10,TIM_IT_Update) != RESET)
	{ 
		TIM_ClearITPendingBit(TIM10,TIM_IT_Update); //清除中断标志位	
		PhaseMeasure_ADC_Handle();
		
			
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
//	static u16 _cnt = 0;
	if(TIM_GetITStatus(TIM9,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM9,TIM_IT_Update); //清除中断标志位
//		_cnt ++;	
//		if(_cnt >= 1000)	
//		{   								
//			TIM_Cmd(TIM9,DISABLE);  	
//			Exti_Disable(4);			
//			g_FreqMod = FREQ_MODE_FREE;	
//			_cnt = 0;	
//		}
		 
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
* @Description   : 仪器仪表
* @Data          : 2016/7/22
* @Explain       : 10ms/50Hz
------------------------------------------------------------------------------*/ 
void  TIM8_BRK_TIM12_IRQHandler(void)   
{  
	if(TIM_GetITStatus(TIM12,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM12,TIM_IT_Update); //清除中断标志位 
//		if(Measuring.ADC_Flag != MEASURING_START) return;
		
//		Measuring.ADC1_Buff[Measuring.ADC_Cnt] = ADC_Result_Get(1,0)*3.3/4096*100; //电压
//		Measuring.ADC2_Buff[Measuring.ADC_Cnt] = ADC_Result_Get(2,0)*3.3/4096*10; //电流
//		Measuring.ADC_Cnt ++;
		
//		if(Measuring.ADC_Cnt >= MEASURING_ADC_LENTH)
//		{
//			Measuring.ADC_Cnt = 0;				
//			Measuring.ADC_Flag = MEASURING_COMPLETE; 
//		}
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
//		DutyMeasuring_IRQHandler(0); 
		FreqMeasure_IRQHandler();
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
		ADS1271_Handle_1();
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
		ADS1271_Handle_2();
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
//	static u32 TimeRecord[3] = {0};		
//	static u8 _cnt = 0,OS_ClockNow;
//	u32 TempTime = 	0;
//	TempTime = TIM_GetCounter(TIM2);
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{ 
//		if(g_FreqMod == FREQ_MODE_HF) //高频测次数				
//		{  	
//			g_FreqCnt ++; 		
//		}
//		
//		else if(g_FreqMod == FREQ_MODE_LF) //低频测时间	
//		{
//			if(_cnt == 0) OS_ClockNow = OS_Clock;	//记录当前溢出值
//			
//			TimeRecord[_cnt++] = TempTime;	//记录时间
//			
//			if(_cnt >= 2)
//			{
//				g_FreqMod = FREQ_MODE_FREE;		
//				_cnt = 0; 	
//				g_FreqT = (OS_Clock - OS_ClockNow)*0xffffffff + TimeRecord[1] - TimeRecord[0];		
//			}			
//		}			
//		 
//		else if(g_FreqMod == FREQ_MODE_DUTY) //测占空比	
//		{
//			if(_cnt == 0) OS_ClockNow = OS_Clock; //记录当前溢出值	
//			
//			TimeRecord[_cnt++] = TempTime; //记录时间	
//			
//			if(_cnt == 2) 
//			{	  
//				g_FreqT_H = (OS_Clock - OS_ClockNow)*0xffffffff + TimeRecord[1] - TimeRecord[0];		 
//			}
//			
//			if(_cnt >= 3) 
//			{	
//				g_FreqMod = FREQ_MODE_FREE;		
//				_cnt = 0; 	
//				g_FreqT = (OS_Clock - OS_ClockNow)*0xffffffff + TimeRecord[2] - TimeRecord[0];		 
//			}	
//				
//		}	
//			
//		else if(g_FreqMod == FREQ_MODE_FREE)	
//		{
//			_cnt = 0; 
//			OS_ClockNow = OS_Clock; 
//			TimeRecord[0] = 0; 
//			TimeRecord[1] = 0; 
//			TimeRecord[2] = 0; 
//			Exti_Disable(4);	
//		}	
//		
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
//		Message_Receive();
		EXTI_ClearITPendingBit(EXTI_Line10); //清除LINE3上的中断标志位 
	}
}






/**----------------------------------------------------------------------------
* @FunctionName  : USART2_IRQHandler()     
* @Description   : 串口2服务程序 
* @Data          : 2016/11/11
* @Explain       : 用于上位机串口线
------------------------------------------------------------------------------*/ 
void USART2_IRQHandler(void)                	//串口1中断服务程序
{   
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{  
		
	} 
	
} 


/**----------------------------------------------------------------------------
* @FunctionName  : USART2_IRQHandler()     
* @Description   : 串口2服务程序 
* @Data          : 2016/11/11
* @Explain       : 用于上位机串口线
------------------------------------------------------------------------------*/ 
void USART3_IRQHandler(void)                	//串口1中断服务程序
{   
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{  
		Message_Handle_USART3();
		
	} 
	
} 



/**----------------------------------------------------------------------------
* @FunctionName  : USART6_IRQHandler() 
* @Description   : 串口6服务程序 
* @Data          : 2016/11/11
* @Explain       : 用于上位机蓝牙
------------------------------------------------------------------------------*/ 
void USART6_IRQHandler(void)                	//串口1中断服务程序
{   
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{   
		
		
		
	}
	
}




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





