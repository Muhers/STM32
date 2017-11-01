/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : My_Timer.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Timer.h"
#include "User_Include.h"  

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 
/* 全局函数编写 --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_Config()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : 用于系统时钟  1us级
------------------------------------------------------------------------------*/
void TIM2_Config(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//配置时钟及初始化预装值
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); ///使能 TIMx时钟				   //@
	TIM_TimeBaseStructure.TIM_Period = 0xffffffff;//重装载值 32位
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//预分频 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上累计模式，即从0开始加到溢出值
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//配置						    		//@
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//允许定时器 更新中断							//@
	
/*---------------------------------------------------------------------------------------------*/ 

//配置中断层
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM2_IRQn; //定时器 x 中断							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 1 ; //抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1 ; //响应优先级  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	
	NVIC_Init(&NVIC_InitStructure);// 初始化 NVIC
 	TIM_Cmd(TIM2,ENABLE); //使能定时器 x												//@
/*---------------------------------------------------------------------------------------------*/
}   

/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_Config()     
* @Description   : None 
* @Data          : 2016/3/18
* @Explain       : OSThread_Primary  1ms时间片
------------------------------------------------------------------------------*/
void TIM3_Config(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//配置时钟及初始化预装值
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); ///使能 TIMx时钟				   //@
	TIM_TimeBaseStructure.TIM_Period =1000-1;//重装载值
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上累计模式，即从0开始加到溢出值
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//配置						    		//@
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//允许定时器9更新中断							//@
	
/*---------------------------------------------------------------------------------------------*/ 

//配置中断层
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM3_IRQn; //定时器 x 中断				//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 6 ; //抢占优先级 6
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1 ; //响应优先级 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// 初始化 NVIC		
 	TIM_Cmd(TIM3,ENABLE); //使能定时器 x												//@
/*---------------------------------------------------------------------------------------------*/
}   
	
/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_Config()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : OSThread_System  1ms时间片
------------------------------------------------------------------------------*/
void TIM4_Config(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//配置时钟及初始化预装值
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); ///使能 TIMx时钟				   //@
	TIM_TimeBaseStructure.TIM_Period =1000-1;//重装载值
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上累计模式，即从0开始加到溢出值
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//配置						    		//@
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//允许定时器 更新中断							//@ 
/*---------------------------------------------------------------------------------------------*/ 

//配置中断层
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM4_IRQn; //定时器 x 中断							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 4 ; //抢占优先级 4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1 ; //响应优先级  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// 初始化 NVIC
 	TIM_Cmd(TIM4,ENABLE); //使能定时器 x				4								//@
/*---------------------------------------------------------------------------------------------*/
}			
	
		
		
/**----------------------------------------------------------------------------
* @FunctionName  : TIM9_Config()     
* @Description   : None 
* @Data          : 2016/4/19
* @Explain       : OS_THREAD_5  1ms时间片
------------------------------------------------------------------------------*/
void TIM9_Config(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//配置时钟及初始化预装值
/*---------------------------------------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE); ///使能 TIMx时钟				   //@
	TIM_TimeBaseStructure.TIM_Period = 1000-1;//重装载值
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上累计模式，即从0开始加到溢出值
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);//配置						    		//@
	TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);//允许定时器 更新中断							//@ 
/*---------------------------------------------------------------------------------------------*/ 

//配置中断层
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM1_BRK_TIM9_IRQn; //定时器 x 中断							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 5 ; //抢占优先级 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1 ; //响应优先级  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// 初始化 NVIC
 	TIM_Cmd(TIM9,ENABLE); //使能定时器 x				4								//@ 
/*---------------------------------------------------------------------------------------------*/
}	

/**----------------------------------------------------------------------------
* @FunctionName  : TIM10_Config()     
* @Description   : None 
* @Data          : 2016/4/19
* @Explain       : OS_THREAD_3  1ms时间片
------------------------------------------------------------------------------*/
void TIM10_Config(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//配置时钟及初始化预装值
/*---------------------------------------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE); ///使能 TIMx时钟				   //@
	TIM_TimeBaseStructure.TIM_Period = 1000-1;//重装载值
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上累计模式，即从0开始加到溢出值
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);//配置						    		//@
	TIM_ITConfig(TIM10,TIM_IT_Update,ENABLE);//允许定时器 更新中断							//@ 
/*---------------------------------------------------------------------------------------------*/ 

//配置中断层
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM1_UP_TIM10_IRQn; //定时器 x 中断							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 3 ; //抢占优先级 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1 ; //响应优先级  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// 初始化 NVIC
 	TIM_Cmd(TIM10,ENABLE); //使能定时器 x				4								//@
/*---------------------------------------------------------------------------------------------*/
}	


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/












