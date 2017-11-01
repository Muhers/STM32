/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_ADC.c
* @Description : None
* @Date        : 2016/7/11
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_ADC.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : ADC1_Init()
* @Description   : None
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/
void ADC1_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef       ADC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��
	
    //�ȳ�ʼ��ADC1ͨ��1 IO��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);	//ADC1��λ
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);	//��λ����
	
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //�ر�DMAʹ��
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;//Ԥ��Ƶ2��Ƶ��//ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz
    ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
		
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ	
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
    ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1
    ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
 
    ADC_Cmd(ADC1, ENABLE);//����ADת����	

}

/**----------------------------------------------------------------------------
* @FunctionName  : ADC2_Init()
* @Description   : ADC2��ʼ������
* @Data          : 2016/7/24
* @Explain       : ������Ƶ�ɼ�
------------------------------------------------------------------------------*/
void ADC2_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef       ADC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //ʹ��ADC1ʱ��
	
    //�ȳ�ʼ��ADC1ͨ��1 IO��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PA
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, ENABLE);	//ADC1��λ
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, DISABLE);	//��λ����
	
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //�ر�DMAʹ��
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;//Ԥ��Ƶ2��Ƶ��//ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz
    ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
		
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ	
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
    ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1
    ADC_Init(ADC2, &ADC_InitStructure);//ADC��ʼ��
 
    ADC_Cmd(ADC2, ENABLE);//����ADת����	

}
 
/**----------------------------------------------------------------------------
* @FunctionName  : ADC_Result_Get()
* @Description   : ���ADCֵ
* @Data          : 2016/7/24
* @Explain       : 
------------------------------------------------------------------------------- 
Channel:  ADC_Channel_0~ADC_Channel_18 (��0~18Ҳ��) 
Speed  :  0~7(ԽСԽ��)
����ֵ:ת�����
------------------------------------------------------------------------------*/
u16 ADC_Result_Get(u8 Channel,u8 Speed)
{  
	if(Speed > 7) Speed = 7; 
	if(Channel == 1)
	{
		ADC_RegularChannelConfig(ADC1,Channel, 1, Speed );	 
		ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת���������� 
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������ 
		return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
	}
	else if(Channel == 2)
	{
		ADC_RegularChannelConfig(ADC2,Channel, 1, Speed );	 
		ADC_SoftwareStartConv(ADC2);		//ʹ��ָ����ADC1�����ת���������� 
		while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������ 
		return ADC_GetConversionValue(ADC2);	//�������һ��ADC1�������ת�����  
	}
	else if(Channel == 3)
	{
		ADC_RegularChannelConfig(ADC3,Channel, 1, Speed );	 
		ADC_SoftwareStartConv(ADC3);		//ʹ��ָ����ADC1�����ת���������� 
		while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//�ȴ�ת������ 
		return ADC_GetConversionValue(ADC3);	//�������һ��ADC1�������ת����� 
	}
	else return 0;
}





/**----------------------------------------------------------------------------
* @FunctionName  : Get_ADC_Average()
* @Description   : ����ADC�ɼ���ƽ��ֵ
* @Data          : 2016/7/24
* @Explain       :
-------------------------------------------------------------------------------
��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ��
Channel:ͨ�����
Times:��ȡ����
����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
------------------------------------------------------------------------------*/
u16 ADC_Average_Get(u8 Channel, u8 Times)
{
    u32 Result = 0; 
	while(Times--)
    {
        Result += ADC_Result_Get(Channel,3);
		Result/=2;
        OSdelay_ms(1);
    }
    return Result;
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





