/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_PWM.c
* @Description : 定时器驱动
* @Date        : 2017/10/14
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_PWM.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
u16 Time3_PWM_Period = 0;

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_PWM_Init()
* @Description   : PWM初始化
* @Data          : 2017/10/13
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);//使能TIM9时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);	//使能GPIOB

    /* GPIO配置 */  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		//选择引脚 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  	//GPIO用作复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//推挽式输出
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM9); //GPIO用作TIM复用功能
	
    /* 时间基数配置 */ 
    TIM_TimeBaseStructure.TIM_Prescaler = 40 - 1;				//预分频器为1 
    TIM_TimeBaseStructure.TIM_Period = 100 - 1;					//自动重装载寄存器周期值为249 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//时钟分割为0 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //增计数模式 
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
	Time3_PWM_Period = TIM_TimeBaseStructure.TIM_Period;
	
    /* 输出比较配置 */ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  							//TIM脉宽调制1模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  				//TIM比较输出使能
    TIM_OCInitStructure.TIM_Pulse = Time3_PWM_Period*0.5f - 1; 	//占空比为50%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   				//*输出比较极性高
    TIM_OC2Init(TIM9, &TIM_OCInitStructure); 
    TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);							//*使能TIM在CRR2上的预装载寄存器
    TIM_ARRPreloadConfig(TIM9, ENABLE);											//*使能TIM在ARR上的预装载寄存
    TIM_Cmd(TIM9, ENABLE);														//*使能外设TIM
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_PWM_SetH()
* @Description   : PWM高电平占空比
* @Data          : 2017/10/13
* @Explain       : None
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void TIM3_PWM_SetH(float _Percent)
{ 
    TIM_OCInitTypeDef TIM_OCInitStructure; 
	
    /* 输出比较配置 */ 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//TIM脉宽调制1模式
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//TIM比较输出使能
    TIM_OCInitStructure.TIM_Pulse = Time3_PWM_Period *_Percent - 1; 	//占空比为50%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//*输出比较极性高
    TIM_OC2Init(TIM9, &TIM_OCInitStructure); 
    TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);	//*使能TIM在CRR2上的预装载寄存器
    TIM_ARRPreloadConfig(TIM9, ENABLE);		//*使能TIM在ARR上的预装载寄存
    TIM_Cmd(TIM9, ENABLE);		//*使能外设TIM

}


/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





