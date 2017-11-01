/***************************************************************************************************
  * 文    件：My_Tim.c
  * 作    者：guojiang 
  * 开 发 板：stm32f103rc实验室开发板
  * 修改时间：2016.7 

  * 编 译 器: keil.5.20
  *------------------------------------------------------------------------------------------------
  * 简    介：
  *************************************************************************************************/
#include "My_Tim.h"
#include "adc.h"
/*定时器1ms中断,???????*/  
/*File Timer.c */  
 
 u16 flag_change;
 u8 ia=0,change_flag=0;
	extern u8 ADTimePer1s;
unsigned int TimeDelay = 0;  
void TIM8_Configuration(void)  
{  
    NVIC_InitTypeDef NVIC_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  
    TIM_DeInit(TIM8);                                           /*复位TIM8定时器*/  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);       
    TIM_TimeBaseStructure.TIM_Period = 6;                     
    TIM_TimeBaseStructure.TIM_Prescaler = 35999;                    
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /*向上计数*/  
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);  
      
    /* Clear TIM8 update pending flag  清除TIM8溢出标志 */  
    TIM_ClearFlag(TIM8, TIM_FLAG_Update);                 
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;          /*溢出中断*/  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;    
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
    TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);                  /* Enable TIM8 Update interrupt TIM8溢出中断允许*/  
}  
  
void Timer1Config(void)  
{  
    TIM8_Configuration();  
}  
  
void TimeDelayMs(unsigned int Num)  
{     
    TimeDelay = Num;  
    TIM8->CNT = 0;  
    TIM8->CR1 |= TIM_CR1_CEN;                            /*开启Timer8计数*/  
    while(TimeDelay);  
    TIM8->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));   /*关闭Timer8*/      
}  
  
  
/*File stm32f10x_it.c */  
/*中断处理函数*/  
void TIM8_UP_IRQHandler(void)  //每隔？ms检测一次
{  
    TIM_ClearFlag(TIM8, TIM_FLAG_Update); 
			 
   
}  
//定时器6中断服务程序  

void TIM6_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{

			  Get_Adc2_Average(ADC_Channel_0, 10); 
		

	} 
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
				    		  			    	    
}
//基本定时器6中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM6_Int_Init(u16 arr,u16 psc)
{	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig( TIM6,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//使能定时器6更新触发中断
 
	TIM_Cmd(TIM6, ENABLE);  //使能TIMx外设
 	
  	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 								 
}

extern u16 leftAD,rightAD;
u8 SpeedSrongerRush = 0;
void TIM7_IRQHandler(void)  // 100ms
{ 	 
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		 
	} 
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
				    		  			    	    
}
void TIM7_Int_Init(u16 arr,u16 psc)
{	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig( TIM7,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//使能定时器6更新触发中断
 
	TIM_Cmd(TIM7, ENABLE);  //使能TIMx外设
 	
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 								 
}


