/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_StartFile.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (TM4C1294NCPDT)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_StartFile.h"


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
u32 OS_Msg = NULL;	
u32 OS_Error = NULL;	
u32 OS_Clock = NULL;
u32 os_fosc = 0;


/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Init()     
* @Description   : WinOS初始化 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Init(void)
{	  
	/* 芯片配置初始化 --------------------------------*/  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
	SystemInit();  
	 
	
	/* 硬件驱动初始化 --------------------------------*/    
	TIM2_Init();
	TIM3_Init();
	TIM4_Init();
	
	
	/* 系统驱动初始化 --------------------------------*/   
	OS_UI_Init(); 		
	
}
			
			
/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()     
* @Description   : WinOSus延时函数 
* @Data          : 2016/3/19		
* @Explain       : 参数 ：_us = 延时时间   
------------------------------------------------------------------------------*/	
void OSdelay_us(unsigned long int _us)    
{     
	unsigned long int _TimeNow = TIM_GetCounter(TIM2),_ClockNow = OS_Clock;  
	while(TIM_GetCounter(TIM2) + (OS_Clock - _ClockNow)*0xffffffff - _TimeNow < _us);  
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()     
* @Description   : WinOSus延时函数 
* @Data          : 2016/3/19		
* @Explain       : 参数 ：_ms = 延时时间   
------------------------------------------------------------------------------*/	
void OSdelay_ms(unsigned long int _ms)    
{       
  	unsigned long int _TimeNow = TIM_GetCounter(TIM2),_ClockNow = OS_Clock; 
	_ms*=1000;	
	while(TIM_GetCounter(TIM2) + (OS_Clock - _ClockNow)*0xffffffff - _TimeNow < _ms);  	
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_s()     
* @Description   : WinOSus延时函数 
* @Data          : 2016/3/19		
* @Explain       : 参数 ：_s = 延时时间   
------------------------------------------------------------------------------*/	
void OSdelay_s(unsigned long int _s)    
{   
	OSdelay_ms(_s*1000); 
}

 


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





