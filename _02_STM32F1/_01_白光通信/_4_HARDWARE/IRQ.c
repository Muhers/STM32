//*************************************************************(C) COPYRIGHT 2015 WindRises**********************************************************//

#include "IRQ.h"



/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
����ʹ��ʾ��

	TIM_SetCounter(TIM2, 0);//�������ֵ
	TIM_GetCounter(TIM2); //�õ�����ֵ
	TIM_ClearFlag(TIM3, TIM_IT_CC2);//����жϱ�־



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
	//TIM4�����ʼ�� 
	TIM_DeInit(TIM4);  
	TIM_TimeBaseStructure.TIM_Period = 2-1; //����ֵ=2-1 
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //Ԥ��Ƶ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ʱ�ӷָ� 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down; //ģʽ 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //������ʼ��
	TIM_SetCounter(TIM4, 100); //���� TIM4 �������Ĵ���ֵ  
	 //���� TIMx �Զ���װ�ؼĴ���ֵ 
	 TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_SelectInputTrigger(TIM4, TIM_TS_TI2FP2); //��Ϊͨ��1 ����ΪTIM_TS_TI1FP1
	//TIM_SelectInputTrigger(TIM2, TIM_TS_TI1F_ED); 
	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_External1); 
	//TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);
	TIM_SetCompare2(TIM4, 100); //����1ͨ������Ϊ��TIM_SetComper1(TIM4,100);
	TIM_Cmd(TIM4, ENABLE); //����TIM4 
	TIM_ClearFlag(TIM4, TIM_IT_CC2); //����һͨ������˴��ͺ����TIM_IT_CC2����ΪTIM_IT_CC1
	TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);//�ж�����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; // 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //��Ӧ���ȼ�0 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //�����ж� 
	NVIC_Init(&NVIC_InitStructure);    //д������ 

}





void TIM4_IRQHandler(void) //2�������ȥһ��
{
	
	static u8 Flag=0;
	Light_Singel=TIM_GetCounter(TIM2); //�õ�����ֵ	
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
		
	TIM_SetCounter(TIM2,0);//��ռ�����
	if(Flag==0) Light_Transfer_Main();//ת��
	TIM_ClearFlag(TIM4,TIM_IT_CC2);

		
} 


/*=================================================================================================
����˵��

TIM3_CH2 Ϊ���������
1.  ����TIM2  1us��ʱ
  
=================================================================================================*/


void TIM2_Int_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler =71; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_Period =0xffff; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIMx�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx					 
}



//��ʱ��2 ������ʱ
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	    
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx�����жϱ�־ 	
}


























//*************************************************************(C) COPYRIGHT 2015 WindRises**********************************************************//
