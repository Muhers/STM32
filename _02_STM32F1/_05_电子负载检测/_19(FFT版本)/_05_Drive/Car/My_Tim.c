/***************************************************************************************************
  * ��    ����My_Tim.c
  * ��    �ߣ�guojiang 
  * �� �� �壺stm32f103rcʵ���ҿ�����
  * �޸�ʱ�䣺2016.7 

  * �� �� ��: keil.5.20
  *------------------------------------------------------------------------------------------------
  * ��    �飺
  *************************************************************************************************/
#include "My_Tim.h"
#include "adc.h"
/*��ʱ��1ms�ж�,???????*/  
/*File Timer.c */  
 
 u16 flag_change;
 u8 ia=0,change_flag=0;
	extern u8 ADTimePer1s;
unsigned int TimeDelay = 0;  
void TIM8_Configuration(void)  
{  
    NVIC_InitTypeDef NVIC_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  
    TIM_DeInit(TIM8);                                           /*��λTIM8��ʱ��*/  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);       
    TIM_TimeBaseStructure.TIM_Period = 6;                     
    TIM_TimeBaseStructure.TIM_Prescaler = 35999;                    
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;             
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /*���ϼ���*/  
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);  
      
    /* Clear TIM8 update pending flag  ���TIM8�����־ */  
    TIM_ClearFlag(TIM8, TIM_FLAG_Update);                 
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;          /*����ж�*/  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;    
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
    TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);                  /* Enable TIM8 Update interrupt TIM8����ж�����*/  
}  
  
void Timer1Config(void)  
{  
    TIM8_Configuration();  
}  
  
void TimeDelayMs(unsigned int Num)  
{     
    TimeDelay = Num;  
    TIM8->CNT = 0;  
    TIM8->CR1 |= TIM_CR1_CEN;                            /*����Timer8����*/  
    while(TimeDelay);  
    TIM8->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));   /*�ر�Timer8*/      
}  
  
  
/*File stm32f10x_it.c */  
/*�жϴ�����*/  
void TIM8_UP_IRQHandler(void)  //ÿ����ms���һ��
{  
    TIM_ClearFlag(TIM8, TIM_FLAG_Update); 
			 
   
}  
//��ʱ��6�жϷ������  

void TIM6_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{

			  Get_Adc2_Average(ADC_Channel_0, 10); 
		

	} 
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
				    		  			    	    
}
//������ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM6_Int_Init(u16 arr,u16 psc)
{	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig( TIM6,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//ʹ�ܶ�ʱ��6���´����ж�
 
	TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx����
 	
  	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 								 
}

extern u16 leftAD,rightAD;
u8 SpeedSrongerRush = 0;
void TIM7_IRQHandler(void)  // 100ms
{ 	 
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		 
	} 
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
				    		  			    	    
}
void TIM7_Int_Init(u16 arr,u16 psc)
{	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig( TIM7,TIM_IT_Update|TIM_IT_Trigger,ENABLE);//ʹ�ܶ�ʱ��6���´����ж�
 
	TIM_Cmd(TIM7, ENABLE);  //ʹ��TIMx����
 	
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 								 
}


