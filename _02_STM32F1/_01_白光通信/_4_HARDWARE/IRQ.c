//*************************************************************(C) COPYRIGHT 2015 WindRises**********************************************************//

#include "IRQ.h"



/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
函数使用示例

	TIM_SetCounter(TIM2, 0);//清除计数值
	TIM_GetCounter(TIM2); //得到计数值
	TIM_ClearFlag(TIM3, TIM_IT_CC2);//清除中断标志



=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void TIM4_Int_Init(void)
{
	   NVIC_InitTypeDef NVIC_InitStructure;  
	   GPIO_InitTypeDef GPIO_InitStructure;
	   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	   /* TIM4 clock source enable */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	  /* Enable GPIOA, clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//TIM4输出初始化 
	TIM_DeInit(TIM4);  
	TIM_TimeBaseStructure.TIM_Period = 2-1; //计数值=2-1 
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //预分频 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //时钟分割 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down; //模式 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //基本初始化
	TIM_SetCounter(TIM4, 100); //设置 TIM4 计数器寄存器值  
	 //设置 TIMx 自动重装载寄存器值 
	 TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_SelectInputTrigger(TIM4, TIM_TS_TI2FP2); //若为通道1 ，则为TIM_TS_TI1FP1
	//TIM_SelectInputTrigger(TIM2, TIM_TS_TI1F_ED); 
	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_External1); 
	//TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);
	TIM_SetCompare2(TIM4, 100); //若用1通道。则为：TIM_SetComper1(TIM4,100);
	TIM_Cmd(TIM4, ENABLE); //启动TIM4 
	TIM_ClearFlag(TIM4, TIM_IT_CC2); //若用一通道，则此处和后面的TIM_IT_CC2都改为TIM_IT_CC1
	TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);//中断配置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; // 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应优先级0 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //允许中断 
	NVIC_Init(&NVIC_InitStructure);    //写入设置 

}





void TIM4_IRQHandler(void) //2个脉冲进去一次
{
	
	static u8 Flag=0;
	Light_Singel=TIM_GetCounter(TIM2); //得到计数值	
	if(Light_Singel>150)Flag++;
	
	if(Flag>=2) 
	{
	Flag=0;Adjust_Flag=1;
	TIM_SetCounter(TIM2,0);	
	while(TIM_GetCounter(TIM2)>190);	
	TIM_SetCounter(TIM2,0);	
	TIM_ClearFlag(TIM4,TIM_IT_CC2);
	return;
	}
		
	TIM_SetCounter(TIM2,0);//清空计数器
	if(Flag==0) Light_Transfer_Main();//转换
	TIM_ClearFlag(TIM4,TIM_IT_CC2);

		
} 


/*=================================================================================================
函数说明

TIM3_CH2 为脉冲输入口
1.  配置TIM2  1us计时
  
=================================================================================================*/


void TIM2_Int_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Prescaler =71; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_Period =0xffff; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIMx中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}



//定时器2 用来计时
void TIM2_IRQHandler(void)   //TIM2中断
{
	    
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx更新中断标志 	
}


























//*************************************************************(C) COPYRIGHT 2015 WindRises**********************************************************//
