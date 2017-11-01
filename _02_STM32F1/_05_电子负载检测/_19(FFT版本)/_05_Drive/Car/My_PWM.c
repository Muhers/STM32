/***************************************************************************************************
  * 文    件：main.c
  * 作    者：guojiang 
  * 开 发 板：stm32f103rc实验室开发板
  * 修改时间：2016.7 

  * 编 译 器: keil.5.20
  *------------------------------------------------------------------------------------------------
  * 简    介：
  *************************************************************************************************/
/*包含--------------------------------------------------------------------------------------------*/
#include "my_pwm.h"
/* 私有定义结构体 --------------------------------------------------------------------------------*/
/* 私有宏-----------------------------------------------------------------------------------------*/

/* 私有变量 --------------------------------------------------------------------------------------*/

/* 私有函数模型 ----------------------------------------------------------------------------------*/


/**************************************************************************/
/*  PWM1路初始化选择正反转向

*/
/***************************************************************************/
void PWM1_Inti_select(u8 dir)		// 0  0 停止 0  1正  1  0  反
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  	   
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_10|GPIO_Pin_11); //
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);		 //根据设定参数初始化GPIOC.10  PC.11

	if(dir==0)
	{ 
		GPIO_ResetBits(GPIOC,GPIO_Pin_10); 
		GPIO_ResetBits(GPIOC,GPIO_Pin_11); 
	}	
	else if(dir==1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_10);
		GPIO_ResetBits(GPIOC,GPIO_Pin_11); 
	}
	else if(dir==2)
	{	
		GPIO_ResetBits(GPIOC,GPIO_Pin_10);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
	
	}
}
/**************************************************************************/
/*  PWM2路初始化选择正反转向

*/
/***************************************************************************/


void PWM3_Inti_select(u8 dir)		// 0  0 停止 0  1正  1  0  反
{
		 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);     
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_12|GPIO_Pin_13); //
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);		 //根据设定参数初始化GPIOC.10  PC.11

	if(dir==0)
	{ 
		GPIO_ResetBits(GPIOC,GPIO_Pin_12); 
		GPIO_ResetBits(GPIOC,GPIO_Pin_13); 
	}	
	else if(dir==1)
	{
			GPIO_ResetBits(GPIOC,GPIO_Pin_12);
			GPIO_SetBits(GPIOC,GPIO_Pin_13);	
	}
	else if(dir==2)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13); 
	}
}

/**************************************************************************/
/*  PWM1选择正反转向

*/
/***************************************************************************/
void PWM1_Select(u8 dir)		// 0  0 停止 0  1正  1  0  反   0停止,1正向,2反向
{
	if(dir == 0)
	{ 
		GPIO_ResetBits(GPIOC,GPIO_Pin_10); 
		GPIO_ResetBits(GPIOC,GPIO_Pin_11); 
	}	
	else if(dir == 1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_10);
		GPIO_ResetBits(GPIOC,GPIO_Pin_11); 
	}
	else if(dir == 2)
	{	
		GPIO_ResetBits(GPIOC,GPIO_Pin_10);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
	
	}
}
/**************************************************************************/
/*  PWM2选择正反转向

*/
/***************************************************************************/
void PWM3_Select(u8 dir)		// 0  0 停止 0  1正  1  0  反
{
			if(dir == 0)
	{ 
		GPIO_ResetBits(GPIOC,GPIO_Pin_12); 
		GPIO_ResetBits(GPIOC,GPIO_Pin_13); 
	}	
	else if(dir == 1)
	{	
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);	
	}
	else if(dir == 2)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13); 
	}
}

/**************************************************************************/
/*  定时器1配置

*/
/***************************************************************************/

void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
 
   
}


/**************************************************************** 
 * 定时器3配置

 ***************************************************************/  
void TIM3_PWM_Init(u16 arr,u16 psc)  
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  

	  GPIO_InitTypeDef GPIO_InitStructure; 
 
  /* GPIOA and GPIOB clock enable */ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  
 
  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */ 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ; //| GPIO_Pin_7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           // ?????? 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
    /*PCLK1??2?????TIM3??????72MHz*/  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  
    /* Time base configuration */                                            
    TIM_TimeBaseStructure.TIM_Period =arr;  
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                                    //?????:???=2,??72/3=24MHz  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                //????????:???  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 //????????  
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
    /* PWM1 Mode configuration: Channel1 */  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           //???PWM??1  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
    TIM_OCInitStructure.TIM_Pulse = 0;                                       //?????,???????????,??????  
    TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_High;                    //?????????CCR1?????  
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);                                    //????1      
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  
//    /* PWM1 Mode configuration: Channel2 */  
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
//    TIM_OCInitStructure.TIM_Pulse = 0;                                       //????2??????,??????????PWM  
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                    //?????????CCR2????? 
//    TIM_OC2Init(TIM3, &TIM_OCInitStructure);                                    //????2  
//    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
//    TIM_ARRPreloadConfig(TIM3, ENABLE);                                         //??TIM3?????ARR  
    /* TIM3 enable counter */  
    TIM_Cmd(TIM3, ENABLE);                                                      //??TIM3   
}
/******************* (C) ***************************文件结束*******************************************/



