/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_StartFile.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "User_Library.h" 
#include "OS_StartFile.h"


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
u32 OS_Msg = NULL;	
u32 OS_Error = NULL;	
u32 OS_Clock = NULL;

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Init()     
* @Description   : WinOS初始化 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Init(void)
{	
	/* 系统必要驱动初始化 ----------------------------*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//终端组4位抢占0位响应优先级,全抢占式系统
	RCC_Configuration();//初始化时钟
	delay_init(168);	//初始化延时函数
	
	/* 芯片配置初始化 --------------------------------*/  
	TIM2_Init(); //时钟
	TIM3_Init(); //线程6(主线程)
	TIM4_Init(); //线程4(系统线程)
	TIM10_Init(); //线程7（低级线程） 
	TIM11_Init(); //线程5（中级线程）   
	TIM12_Init();//线程3（高级级线程）   
 
		 
	/* 硬件驱动初始化 --------------------------------*/
	OS_LCD_Init();	 
	GPIO_LED_Init();  	 

	
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

/**----------------------------------------------------------------------------
* @FunctionName  : App_End()     
* @Description   : 一般App结束函数
* @Data          : 2016/7/12		
* @Explain       : None 
------------------------------------------------------------------------------*/	
unsigned int App_End(void)		
{        
	OS_LCD_Clear(BLACK);
	return 0;	 																
}


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





