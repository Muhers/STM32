/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_SmallCar.c
* @Description : None
* @Date        : 2016/8/20
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_SmallCar.h"							

/* ˽�к궨�� ----------------------------------------------------------------*/  

/* ˽�У���̬���������� ------------------------------------------------------*/   

/* ȫ�ֱ������� --------------------------------------------------------------*/    
Type_SmallCar SmallCar = {0};

/* ȫ�ֺ�����д --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Init()     
* @Description   : С����ʼ������ 
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/ 
void SmallCar_Init(void)
{
    Adc_Init();																	//ADC��ʼ��
    InitAdc_Init();
    DMA_Configuration();														//DMA��ʼ��
    TIM6_Int_Init(10000 - 1, 7200 - 1); 							 // 10000 * 7200/7200 0000  1a
    PWM1_Inti_select(0);   // �ұ߷���  �ұߵ����ͬ����ռ�ձ��� ת�ٱ����С   RCC_APB2Periph_TIM1
    PWM3_Inti_select(0);	 // ��߷���    RCC_APB1Periph_TIM3

    TIM1_PWM_Init(2400 - 1, 1);											//PWMƵ��=72000000/(9999+1)*(71+1)=100hz  10ms   2400*2/36 72 =
    TIM3_PWM_Init(2400 - 1, 1);											//PWMƵ��=72000000/(9999+1)*(71+1)=100hz

    TIM_SetCompare1(TIM1, 1200);											//TIM1���PWM,��ʼ��ռ�ձ�Ϊ 50%
    TIM_SetCompare1(TIM3, 1200);											//TIM3���PWM,��ʼ��ռ�ձ�Ϊ 50%

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    DMA_Cmd(DMA1_Channel1, ENABLE); 								//����DMA ͨ��

    PWM1_Select(1);
    PWM3_Select(1);

}


/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Left_Control()     
* @Description   : ����С������
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed��-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Left_Control(int Speed)
{
	u8 direct = 0;//ֹͣ
	
    if(Speed > 2400 ) Speed = 2400;
    else if(Speed < -2400) Speed = -2400;

	if(Speed > 0) direct = 1;//����
	else if(Speed < 0) direct = 2;//����
	
	PWM1_Select(direct);
    TIM_SetCompare1(TIM3,abs(Speed));
    SmallCar.LeftSpeed = Speed;
}


/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Right_Control()     
* @Description   : ����С���ҷ��
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed��-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Right_Control(int Speed)
{
    u8 direct = 0;//ֹͣ
	
    if(Speed > 2400 )Speed = 2400;
    else if(Speed < -2400) Speed = -2400;
	
	if(Speed > 0) direct = 1;//����
	else if(Speed < 0) direct = 2;//����
	
	PWM3_Select(direct);	
    TIM_SetCompare1(TIM1,abs(Speed));
    SmallCar.RightSpeed = Speed;
	
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





















