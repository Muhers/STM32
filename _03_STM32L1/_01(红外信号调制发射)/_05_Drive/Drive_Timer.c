/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Timer.c
* @Description : 定时器驱动	
* @Date        : 2017/10/13
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Timer.h"

/* 私有宏定义 ----------------------------------------------------------------*/ 

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 
u16 Time3_PWM_Period = 0;

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_Init()
* @Description   : 定时器初始化
* @Data          : 2017/10/13
* @Explain       : 用于时钟 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM2_Init(void)
{ 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Prescaler = 48 - 1; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Period = 0xffff - 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //使能指定的TIMx中断,允许更新中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_Init()
* @Description   : 定时器初始化
* @Data          : 2017/10/13
* @Explain       : 用于主线程
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM4_Init(void)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Prescaler = 48 - 1; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE - 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //使能指定的TIMx中断,允许更新中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_THREAD_PRIMARY;  //先占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM4, ENABLE);  //使能TIMx	
}	


/**----------------------------------------------------------------------------
* @FunctionName  : TIM6_Init()
* @Description   : 定时器初始化
* @Data          : 2017/10/13
* @Explain       : 用于系统线程 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM6_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能
	
	//定时器TIM6初始化
	TIM_TimeBaseStructure.TIM_Prescaler = 48 - 1; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE - 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //使能指定的TIMx中断,允许更新中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_THREAD_SYSTEM;  //先占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM6, ENABLE);  //使能TIMx	
	
} 


/**----------------------------------------------------------------------------
* @FunctionName  : TIM9_PWM_Init()
* @Description   : PWM初始化
* @Data          : 2017/10/14
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM3_PWM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
	
    /* 使能外设时钟 */  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能TIM时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	//使能GPIO

    /* GPIO配置 */  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		//选择引脚 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  	//GPIO用作复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//推挽式输出
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3); //GPIO用作TIM复用功能
	
    /* 时间基数配置 */ 
    TIM_TimeBaseStructure.TIM_Prescaler = 48 - 1;	//预分频器为 
    TIM_TimeBaseStructure.TIM_Period = 26 - 1;	//自动重装载寄存器周期值为26us
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//时钟分割为0 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //增计数模式 
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	Time3_PWM_Period = TIM_TimeBaseStructure.TIM_Period;
	
    /* 输出比较配置 */ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//TIM脉宽调制1模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//TIM比较输出使能
    TIM_OCInitStructure.TIM_Pulse = Time3_PWM_Period*0/100;	//占空比为0%	
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//*输出比较极性高	
    TIM_OC1Init(TIM3, &TIM_OCInitStructure); 	
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	//*使能TIM在CRR2上的预装载寄存器
    TIM_ARRPreloadConfig(TIM3, ENABLE);	//*使能TIM在ARR上的预装载寄存
    TIM_Cmd(TIM3, ENABLE);	//*使能外设TIM
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM9_PWM_SetH()
* @Description   : PWM高电平占空比
* @Data          : 2017/10/14
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM3_PWM_SetH(u8 _Percent)
{ 
    TIM_OCInitTypeDef TIM_OCInitStructure;  
	
    /* 输出比较配置 */ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//TIM脉宽调制1模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//TIM比较输出使能
    TIM_OCInitStructure.TIM_Pulse = Time3_PWM_Period*_Percent/100;	//占空比为50%	
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//*输出比较极性高
    TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);	//*使能TIM在CRR2上的预装载寄存器
    TIM_ARRPreloadConfig(TIM3, ENABLE);	//*使能TIM在ARR上的预装载寄存 
    TIM_Cmd(TIM3, ENABLE);	//*使能外设TIM 
	
}




/**----------------------------------------------------------------------------
* @FunctionName  : TIM7_Init()
* @Description   : 定时器初始化
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void TIM7_Init(void)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;  
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能
	 
	//定时器TIM6初始化
	TIM_TimeBaseStructure.TIM_Prescaler = 48 - 1; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Period = 0xffff - 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //使能指定的TIMx中断,允许更新中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = OS_THREAD_PRIMARY - 1;  //先占优先级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_ARRPreloadConfig(TIM7, DISABLE);      //不允许自动重载功能 
	TIM_Cmd(TIM7, DISABLE);  //使能TIMx	 
	
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : TIM7_Time_Set()
* @Description   : 定时器设置定时时间
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
Time	:定时时间	0.关闭定时器
------------------------------------------------------------------------------*/ 
void TIM7_Time_Set(u16 Time)
{   
	TIM_Cmd(TIM7, DISABLE);  //失能TIMx	 
	
	if(Time == 0)  return;  
	TIM_SetAutoreload(TIM7,Time);	
	TIM_SetCounter(TIM7,0);			
	
	TIM_Cmd(TIM7, ENABLE);  //失能TIMx	 
}


/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





