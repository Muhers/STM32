/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_EXTI.c
* @Description : �ⲿ�ж�����	
* @Date        : 2016/8/8
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_EXTI.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Exti11_Init()
* @Description   : �ⲿ�жϳ�ʼ��
* @Data          : 2016/8/8
* @Explain       : ���ڽ��ն���
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void EXTI11_Init(void)
{ 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOʱ�� 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //���ó����룬����
	GPIO_Init(GPIOB,&GPIO_InitStructure);//��ʼ��GPIO 
	
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ�� 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);

  	EXTI_InitStructure.EXTI_Line = EXTI_Line11;	 
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ��� 
 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//���ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//�����ȼ�
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ�� 
    NVIC_Init(&NVIC_InitStructure);     
}


 

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





