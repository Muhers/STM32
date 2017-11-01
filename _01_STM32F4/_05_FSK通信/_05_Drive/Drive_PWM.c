/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_PWM.c
* @Description : None
* @Date        : 2016/7/10
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_PWM.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define PWM1_FREQUENCY 	10000//PWM1输出的频率，单位Hz
#define PWM1_PERIOD 	(105000.0f/PWM1_FREQUENCY)

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : PWM1_Init()     
* @Description   : None 
* @Data          : 2016/7/11
* @Explain       : PWM1输出
------------------------------------------------------------------------------*/  
void PWM1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14时钟使能    	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//使能PORTF时钟		
	
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14); //GPIOF9复用为定时器14	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉	
	GPIO_Init(GPIOF,&GPIO_InitStructure);              //初始化PF9	
	  
	TIM_TimeBaseStructure.TIM_Prescaler=15;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=PWM1_PERIOD*100;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);//初始化定时器14   
		
	//初始化TIM14 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
		
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
		
	TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPE使能 	
		
	TIM_Cmd(TIM14, ENABLE);  //使能TIM14	
		
}
	
/**----------------------------------------------------------------------------
* @FunctionName  : PWM1_CCR_Set()     
* @Description   : 设置PWM1占空比	
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/  	 
void PWM1_CCR_Set(double xccr1)
{	
	xccr1 = xccr1*PWM1_PERIOD;	 			
	assert_param(IS_TIM_LIST1_PERIPH(TIM14));		
	TIM14->CCR1 = (u16)xccr1; 		
}	
	
	
	
	
/**----------------------------------------------------------------------------
* @FunctionName  : PWM2_Init()     
* @Description   : PWM通道2
* @Data          : 2016/7/11
* @Explain       : PWM_Cap2捕获     PA1复用位定时器5
------------------------------------------------------------------------------*/  	 
void PWM2_Init(void)
{
	
	TIM_ICInitTypeDef  TIM5_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //GPIOA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA1

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //PA1复用位定时器5
  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=168-1;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=1000000-1;  //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC2映射到TI1上
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
	TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5

 
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
}




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





