#include "PWM.h"



//��ʱ��5�жϷ������	 PA0
// ���ݵĽ���
void TIM5_IRQHandler(void)
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
	TIM_ClearITPendingBit(TIM5,TIM_IT_CC1|TIM_IT_Update);
	
}	
	
	
	
	
void TIM5_PWM_Init(void)
{	

	//��ʱ��5ͨ��1���벶������
	TIM_ICInitTypeDef  TIM5_ICInitStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 ���֮ǰ����  				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  		
	GPIO_Init(GPIOA,&GPIO_InitStructure);				
	GPIO_SetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����			
	
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Prescaler =72-1; 	//Ԥ��Ƶ��  
	TIM_TimeBaseStructure.TIM_Period =0xffff; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
   
	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
   	TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
  
	
	
}









