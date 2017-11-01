#include "PWM.h"



//定时器5中断服务程序	 PA0
// 数据的接收
void TIM5_IRQHandler(void)
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
	TIM_ClearITPendingBit(TIM5,TIM_IT_CC1|TIM_IT_Update);
	
}	
	
	
	
	
void TIM5_PWM_Init(void)
{	

	//定时器5通道1输入捕获配置
	TIM_ICInitTypeDef  TIM5_ICInitStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 清除之前设置  				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  		
	GPIO_Init(GPIOA,&GPIO_InitStructure);				
	GPIO_SetBits(GPIOA,GPIO_Pin_0);						 //PA0 下拉			
	
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Prescaler =72-1; 	//预分频器  
	TIM_TimeBaseStructure.TIM_Period =0xffff; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
   
	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
   	TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
  
	
	
}









