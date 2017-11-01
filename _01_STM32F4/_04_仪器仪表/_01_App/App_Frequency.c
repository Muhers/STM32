/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Frequency.c
* @Description : None
* @Date        : 2016/7/12
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Frequency.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/
u8 Frequency_Mode_High(void);
void Frequency_Mode_Low(void);
void Frequency_Mode_Duty(void);	

/* 全局变量定义 --------------------------------------------------------------*/
u8 g_FreqMod = 0;//测频模式		
u32 g_FreqCnt = 0;				
double g_FreqT = 0;  					
double g_FreqT_H = 0;					
double g_Freq = 0;  
double g_FreqDuty = 0; 

/* 全局变量声明 --------------------------------------------------------------*/
  
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Frequency()     
* @Description   : None 
* @Data          : 2016/7/12
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Frequency_Main(void)		
{    
	double FreqT = 0,FreqT_H = 0;
	static u8 first = 0;
	if(first == 0)
	{
		first ++;
		TIM9_Init();//测频用
		Exti4_Init();	
	}
	
	if(Frequency_Mode_High() == FREQ_MODE_HF)	
	{ 
		FreqT = g_FreqCnt; 
	} 
	else 
	{
		Frequency_Mode_Low();
		FreqT = 1000000.0f/g_FreqT;
//		Frequency_Mode_Duty(); 
		FreqT_H = g_FreqT_H*100.0f/g_FreqT;		
	} 

	if((FreqT - (int)FreqT) < 0.5f) FreqT = (int)FreqT;
	else FreqT = (int)FreqT + 1;
	
	if((FreqT_H - (int)FreqT_H) < 0.5f) FreqT_H = (int)FreqT_H;
	else FreqT_H = (int)FreqT_H + 1;
	
	
	g_Freq =  FreqT;		
	g_FreqDuty = FreqT_H;			
	Measuring.T = g_FreqT;
	

	return 0;																	
}		

 		 				
Type_AppList App_Frequency = {Frequency_Main,NULL,NULL,NULL, \
							  OS_STATE_ACTIVE_ON,OS_THREAD_FREE, \
							  (u8*)"Frequency",100};			
																
					
u8 Frequency_Mode_High(void)
{	
	g_FreqMod = FREQ_MODE_HF;
	g_FreqCnt = 0;	//计数值清零
	TIM_SetCounter(TIM9,0);			
	TIM_Cmd(TIM9,ENABLE);  				
	Exti_Enable(4);	
	while(g_FreqMod != FREQ_MODE_FREE);
	 
	if(g_FreqCnt < 100000) return FREQ_MODE_LF;
	else return FREQ_MODE_HF; 
	 
}					
	 	
void Frequency_Mode_Low(void)
{		
	u16 _cnt = 0;
	g_FreqT = 0;	
	g_FreqMod = FREQ_MODE_LF;		
	Exti_Enable(4);	
	while(g_FreqMod != FREQ_MODE_FREE)
	{
		OSdelay_us(1000);
		_cnt ++;
		if(_cnt > 500){ g_FreqT = 0;break;}
	}		
}


void Frequency_Mode_Duty(void)			
{	
	u16 _cnt = 0;	
	g_FreqT = 0;
	g_FreqT_H = 0;
	g_FreqMod = FREQ_MODE_DUTY;				
	Exti_Enable(0xff);	
	while(g_FreqMod != FREQ_MODE_FREE)
	{
		OSdelay_us(1000);
		_cnt ++;
		if(_cnt > 500) {g_FreqT = 0;g_FreqT_H = 0;break;}
	}		
}													
								
							  
							  
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/


							  
							  



