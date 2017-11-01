/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/
/**============================================================================
* @FileName    : Drive_GPIO.c

*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_GPIO.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : GPIO_Test_Init()
* @Description   : None
* @Data          : 2016/8/7
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void GPIO_Test_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
    GPIO_ResetBits(GPIOC, GPIO_Pin_4); 						 // 

}

/**----------------------------------------------------------------------------
* @FunctionName  : GPIO_Relay_Init()
* @Description   : None
* @Data          : 2016/8/19
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void GPIO_Relay_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
    GPIO_ResetBits(GPIOA, GPIO_Pin_7); 						 // 

}


/**----------------------------------------------------------------------------
* @FunctionName  : GPIO_Key_Init()
* @Description   : �����ĳ�ʼ������ 
* @Data          : 2016/7/19
* @Explain       : None
------------------------------------------------------------------------------*/ 
void GPIO_Key_Init(void)
{ 
    GPIO_InitTypeDef GPIO_InitStructure;
//    EXTI_InitTypeDef EXTI_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIO�˿�ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	            //�˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;         //����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIO
	   
}


/**----------------------------------------------------------------------------
* @FunctionName  : GPIO_Tracking_Init()
* @Description   : None
* @Data          : 2016/8/7
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void GPIO_Tracking_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
    GPIO_ResetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);     // 
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
    GPIO_ResetBits(GPIOA, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);

}
/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/





