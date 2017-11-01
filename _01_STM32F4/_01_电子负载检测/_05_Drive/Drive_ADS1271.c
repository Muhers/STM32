/*******************************(C) COPYRIGHT 2017 Wind(л����) *********************************/
/**============================================================================
* @FileName    : Drive_ADS1271.c
* @Description : None
* @Date        : 2017��7��27��
* @By          : Wind(л����)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 24λ����ADC
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_ADS1271.h"


/* ˽�к궨�� ----------------------------------------------------------------*/
#define ADS1271_SCLK1  	PEout(1) 
#define ADS1271_SDAT1  	PFin(2)

#define ADS1271_SCLK2  	PFout(3) 
#define ADS1271_SDAT2  	PFin(4) 


#define ADS1271_DELAY() 	__NOP();__NOP();__NOP()


/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
static float ADS1271_value1 = 0.0f;
static float ADS1271_value2 = 0.0f;
static float ADC_value = 0.0f;
	
/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : ADS1271_Init(void)
* @Description   : 24λ����ADC��ʼ��
* @Data          : 2017��7��27��
* @Explain       : None
------------------------------------------------------------------------------*/
int ADS1271_Init_1(void)
{   
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_Init(GPIOE,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_Init(GPIOF,&GPIO_InitStructure); 
	
	ADS1271_SCLK1 = 0;	 
	
	Exti1_Init();//PE1 �ⲿ�ж� 
	
    return 0;
}	


/**----------------------------------------------------------------------------
* @FunctionName  : ADS1271_Init(void)
* @Description   : 24λ����ADC��ʼ��
* @Data          : 2017��7��27��
* @Explain       : None
------------------------------------------------------------------------------*/
int ADS1271_Init_2(void)
{   
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_Init(GPIOF,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_Init(GPIOF,&GPIO_InitStructure); 
	
	ADS1271_SCLK2 = 0;	 
	
	Exti2_Init();//PE1 �ⲿ�ж� 
	
    return 0;
}	

/**----------------------------------------------------------------------------
* @FunctionName  : ADS1271_Read(void)
* @Description   : ��ȡ24λ����ADC��ֵ
* @Data          : 2017��7��27��
* @Explain       : ch ͨ��  	return ���
------------------------------------------------------------------------------*/
float ADS1271_Read(u8 ch)
{    
	if(ch == 1)
		return ADS1271_value1;
	else if(ch == 2)
		return ADS1271_value2;
	else return 0;  
}	

/**----------------------------------------------------------------------------
* @FunctionName  : ADS1271_Read_1(void)
* @Description   : ��ȡ24λ����ADC��ֵ
* @Data          : 2017��7��27��
* @Explain       : return ���
------------------------------------------------------------------------------*/
float ADS1271_Read_1(void)
{    
	return ADS1271_value1;   
}	

/**----------------------------------------------------------------------------
* @FunctionName  : ADS1271_Read_2(void)
* @Description   : ��ȡ24λ����ADC��ֵ
* @Data          : 2017��7��27��
* @Explain       : return ���
------------------------------------------------------------------------------*/
float ADS1271_Read_2(void)
{    
	return ADS1271_value2;  
}	

/**----------------------------------------------------------------------------
* @FunctionName  : ADS1271_Handle()
* @Description   : ADS1271�ⲿ�ɼ��ж�
* @Data          : 2017��7��29��
* @Explain       : ch ͨ�� 
------------------------------------------------------------------------------*/
#define ADS1271_V_RANGE_1		(2.5f) 
#define ADS1271_V_SHIFT_1		(0.0145f)
void ADS1271_Handle_1(void)
{   
	u8 cnt = 0;
	long int temp = 0;  
		
	ADS1271_SCLK1 = 0;		
	ADS1271_DELAY();	 
	for(cnt = 0;cnt < 24;cnt ++)	
	{
		ADS1271_SCLK1 = 1;	
		ADS1271_DELAY();	
		
		if(ADS1271_SDAT1) temp |= (0x800000>>cnt);	 
		
		ADS1271_SCLK1 = 0;	
		ADS1271_DELAY();	
	}  
	
	ADS1271_value1 = temp * ADS1271_V_RANGE_1/0x7FFFFF + ADS1271_V_SHIFT_1; //����
	ADC_value = ADC1_Get();	//��ѹ	
	
    return;
}	
 
#define ADS1271_V_RANGE_2		(2.5f) 
#define ADS1271_V_SHIFT_2		(-0.045f)
void ADS1271_Handle_2(void)
{   
	u8 cnt = 0;
	long int temp = 0;  
		  
		
	ADS1271_SCLK2 = 0;		
	ADS1271_DELAY();	 
	for(cnt = 0;cnt < 24;cnt ++)	
	{
		ADS1271_SCLK2 = 1;	
		ADS1271_DELAY();	
		
		if(ADS1271_SDAT2) temp |= (0x800000>>cnt);	 
		
		ADS1271_SCLK2 = 0;	
		ADS1271_DELAY();	
	}  
	 
	ADS1271_value2 = temp * ADS1271_V_RANGE_2/0x7FFFFF + ADS1271_V_SHIFT_2; 	   
    return;
}	

/**----------------------------------------------------------------------------
* @FunctionName  : Load_Adc_Get(void)
* @Description   : ��ѹ������ȡ
* @Data          : 2017��7��27��
* @Explain       : ch ͨ��  	return ���
------------------------------------------------------------------------------*/
float Load_Adc_Get(u8 ch)
{    
	if(ch == 0)
		return ADC_value;//��ѹ
	else if(ch == 1)
		return ADS1271_value1;//����
	else return 0;  
}	


/*******************************(C) COPYRIGHT 2017 Wind(л����) *********************************/












