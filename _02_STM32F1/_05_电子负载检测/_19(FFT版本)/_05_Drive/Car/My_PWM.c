/***************************************************************************************************
  * ��    ����main.c
  * ��    �ߣ�guojiang 
  * �� �� �壺stm32f103rcʵ���ҿ�����
  * �޸�ʱ�䣺2016.7 

  * �� �� ��: keil.5.20
  *------------------------------------------------------------------------------------------------
  * ��    �飺
  *************************************************************************************************/
/*����--------------------------------------------------------------------------------------------*/
#include "my_pwm.h"
/* ˽�ж���ṹ�� --------------------------------------------------------------------------------*/
/* ˽�к�-----------------------------------------------------------------------------------------*/

/* ˽�б��� --------------------------------------------------------------------------------------*/

/* ˽�к���ģ�� ----------------------------------------------------------------------------------*/


/**************************************************************************/
/*  PWM1·��ʼ��ѡ������ת��

*/
/***************************************************************************/
void PWM1_Inti_select(u8 dir)		// 0  0 ֹͣ 0  1��  1  0  ��
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  	   
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_10|GPIO_Pin_11); //
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);		 //�����趨������ʼ��GPIOC.10  PC.11

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
/*  PWM2·��ʼ��ѡ������ת��

*/
/***************************************************************************/


void PWM3_Inti_select(u8 dir)		// 0  0 ֹͣ 0  1��  1  0  ��
{
		 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);     
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_12|GPIO_Pin_13); //
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);		 //�����趨������ʼ��GPIOC.10  PC.11

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
/*  PWM1ѡ������ת��

*/
/***************************************************************************/
void PWM1_Select(u8 dir)		// 0  0 ֹͣ 0  1��  1  0  ��   0ֹͣ,1����,2����
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
/*  PWM2ѡ������ת��

*/
/***************************************************************************/
void PWM3_Select(u8 dir)		// 0  0 ֹͣ 0  1��  1  0  ��
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
/*  ��ʱ��1����

*/
/***************************************************************************/

void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
 
   
}


/**************************************************************** 
 * ��ʱ��3����

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
/******************* (C) ***************************�ļ�����*******************************************/



