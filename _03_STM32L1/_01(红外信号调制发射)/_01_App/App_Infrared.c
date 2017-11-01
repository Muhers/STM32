/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Infrared.c
* @Description : None	
* @Date        : 2017/10/13
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/ 

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Infrared.h"  

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 
/* 全局变量声明 --------------------------------------------------------------*/
  
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Infrared()     
* @Description   : None 
* @Data          : 2016/8/8
* @Explain       : 红外遥控发射
------------------------------------------------------------------------------*/
unsigned int Infrared_Main(void)		
{	 
	static u8 cnt = 0,flag = 0; 
	
	if(Key_State_Get(0,KEY_MODE_SHORT))
	{    
		Infrared_TimeCode_Send((u16 *)Infrared_TimeCodeDemo_Buff,sizeof(Infrared_TimeCodeDemo_Buff)/2);	 
		
		LED_Temp_Set(1,100,LED_MODE_FLASH,3);  
		Key_State_Clear(0); 
	}
	
	if(Key_State_Get(0,KEY_MODE_LONG))
	{ 	  
		if(cnt)
			TIM3_PWM_SetH(50);	 
		else
			TIM3_PWM_SetH(0);	 
		
		flag = !flag; 
		
		LED_Temp_Set(3,100,LED_MODE_FLASH,10);  
		
		while(Key_State_Get(0,KEY_MODE_LONG));
	}
	
	
	
	return 0;	
}		


unsigned int Infrared_Start(void)		
{    
	Infrared_Init();	
	return 0;																	
}			

Type_AppList App_Infrared = {Infrared_Main,NULL,Infrared_Start,NULL, \
							OS_STATE_ACTIVE,OS_THREAD_FREE, \
							(uint8_t*)"Infrared",30};			
																
								
							
							
							

						
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/



							
							
							
							
							
							
							
							
							
							

