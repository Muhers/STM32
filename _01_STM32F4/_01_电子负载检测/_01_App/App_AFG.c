/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_AFG.c
* @Description : None
* @Date        : 2016/7/10
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_AFG.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
u8 AFG_Mode = AFG_SIN;
 
/* 全局变量声明 --------------------------------------------------------------*/
  
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : AFG()     
* @Description   : None 
* @Data          : 2016/7/15
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int AFG_Main(void)		
{  
	u32 i = 0,Freq = 0;  
	
	if(PS2.UpData == 1)	 
	{
		if(AFG_Mode == AFG_SIN) //正弦波
		{ 
			PS2.UpData = 0;
			
			if((u32)(PS2.Result) > 110000) // >100k
			{
				DAC1_DMA1_Reload(1);  
				Freq = PS2.Result/3500; 
				for(i = 0;i < DAC1_DMA1_LENTH;i++)
					DAC1_DMA1_Buff[i] = (sin(2.0f*PI*i*Freq/DAC1_DMA1_LENTH)+1)*2048; 
			}
			else if((u32)(PS2.Result) > 50000)//  50~100k ,已偏正
			{
				for(i = 0;i < DAC1_DMA1_LENTH;i++)
					DAC1_DMA1_Buff[i] = (sin(2.0f*PI*i*80/DAC1_DMA1_LENTH)+1)*2048;  
				
				Freq = 1600000/PS2.Result; 
				DAC1_DMA1_Reload(Freq);  
			} 
			else if((u32)(PS2.Result) > 10000)//  10k~50k
			{
				for(i = 0;i < DAC1_DMA1_LENTH;i++)
					DAC1_DMA1_Buff[i] = (sin(2.0f*PI*i*80/DAC1_DMA1_LENTH)+1)*2048;  
				
				Freq = 1600000/PS2.Result/0.95; 
				DAC1_DMA1_Reload(Freq);  
			}
			else if((u32)(PS2.Result) > 100)// 100~10k 
			{
				for(i = 0;i < DAC1_DMA1_LENTH;i++)
					DAC1_DMA1_Buff[i] = (sin(2.0f*PI*i*20/DAC1_DMA1_LENTH)+1)*2048;   
				
				Freq = 400000/PS2.Result/0.95; 
				DAC1_DMA1_Reload(Freq);    
			}
			else //<100
			{				
				for(i = 0;i < DAC1_DMA1_LENTH;i++)
					DAC1_DMA1_Buff[i] = (sin(2.0f*PI*i/DAC1_DMA1_LENTH)+1)*2048; 
				
				Freq = 20000/PS2.Result/0.95; 
				DAC1_DMA1_Reload(Freq);  
			}
			
		} 
	} 
	return 0;																	
}		
 	 
unsigned int AFG_Start(void)	
{
	static u8 first = 0;
	if(first == 0)
	{
		first = 1;
		DAC1_DMA1_Init(); 
		DAC1_DMA1_Reload(1);
	}	
	return 0;	
}	
Type_AppList App_AFG = {AFG_Main,NULL,AFG_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"AFG",500};			
																
																				
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





