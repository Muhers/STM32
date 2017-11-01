/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Infrared.c
* @Description : 红外驱动	
* @Date        : 2017/10/13
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Infrared.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
Type_Infrared Infrared = {0};	

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Infrared_Init()
* @Description   : 红外初始化
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void Infrared_Init(void)
{   
	TIM3_PWM_Init();//发送红外用的PWM载波	  
	TIM7_Init();//发送红外用定时器
}	





/**----------------------------------------------------------------------------
* @FunctionName  : Infrared_TimeCode_Send()
* @Description   : 红外发送
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
signed int Infrared_TimeCode_Send(u16 *Buff,u16 Lenth)	
{     
	u16 i = 0; 
	
	Infrared.Lenth = Lenth;
	Infrared.Cnt = 0; 
	Infrared.FSM = 1;//第一个数据发高  Infrared.FSM = 1
	
	for(i = 0;i < Lenth;i ++)
	{	
		Infrared.TimeCode_Buff[i] = Buff[i]; //转移数据
	} 	
	
	TIM7_Time_Set(10);//定时 
	
	return 0;
}	





/**----------------------------------------------------------------------------
* @FunctionName  : Infrared_TimeCodeSend_Handle()
* @Description   : 红外发送处理函数
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void Infrared_TimeCodeSend_Handle(void)
{       
	u16 time = Infrared.TimeCode_Buff[Infrared.Cnt];
	
	if(time == 0)
	{
		time = 1; //防止数据关闭定时器
	}
	
	switch(Infrared.FSM)	
	{	
		case 0:	//低		 
			if(Infrared.Cnt < Infrared.Lenth) 
			{	
				TIM3_PWM_SetH(0);//发送闭合段
				Infrared.FSM = 1; 				 	
			} 
			break;	
			
		case 1:	//高   
			if(Infrared.Cnt < Infrared.Lenth) 
			{
				TIM3_PWM_SetH(33);//发送PWM段	 
				Infrared.FSM = 0; 
				
			}  
			break;  
	}	  
	
	if(Infrared.Cnt >= Infrared.Lenth) 
	{	
		TIM7_Time_Set(0);//关闭定时器
		TIM3_PWM_SetH(0);	 
		Infrared.Lenth = 0;//发送完毕 
		Infrared.Cnt = 0;	
		Infrared.FSM = 0;  	
	}
	else
	{
		Infrared.Cnt ++;  
		TIM7_Time_Set(time);//定时 
	}
	
}	




 
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/




















