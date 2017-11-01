/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_LoadMeasure.c
* @Description : None
* @Date        : 2017��7��31��
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ���ؼ�����
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_LoadMeasure.h"

/* ˽�к궨�� ----------------------------------------------------------------*/
#define 	MIN_FREQ 	40
#define 	MAX_FREQ 	60

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

u8 PhaseMeasure_State = 0; 

float ADC_Buff_V[ADC_LENTH] = {0};
float ADC_Buff_I[ADC_LENTH] = {0};

Type_ADC_Result ADC_Result = {0};
Type_FFT_Result FFT_Result = {0};

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_ADC_Handle()
* @Description   : ����AD���ݲɼ�
* @Data          : 2017��7��29��
* @Explain       : �˺������붨ʱ���ж���
------------------------------------------------------------------------------*/    
#define ADC0_CORRECT_MULTIP			(253.36956521739130434782608695652f)  
#define ADC1_CORRECT_MULTIP			(4.8531518624641833810888252148997f)     
//#define ADC0_CORRECT_MULTIP			(1000.0f)  
//#define ADC1_CORRECT_MULTIP			(1000.0f)  

void PhaseMeasure_ADC_Handle(void)
{  
	static u16 cnt = 0;	   

	ADC_Buff_V[cnt] = ADC_Value_Get(0)*ADC0_CORRECT_MULTIP;
	ADC_Buff_I[cnt] = ADC_Value_Get(1)*ADC1_CORRECT_MULTIP;  

	 
	cnt ++;	
	if(cnt >= ADC_LENTH) 
	{
		cnt = 0;				
		PhaseMeasure_State = 2;	 		
		PhaseMeasure_End();		
	}  
}	
 

/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_ADC_Analysis()
* @Description   : FFT����
* @Data          : 2017��7��29��
* @Explain       : None
------------------------------------------------------------------------------*/
void ADC_Analysis(void)
{
//    static Type_Filter Struct_Filter_Vrms0 = {0};
//    static Type_Filter Struct_Filter_Vrms1 = {0};
    u16 i = 0;

    ADC_Result.V_Max = 0;
    ADC_Result.V_Min = 100000;
    ADC_Result.Vrms = 0;

    ADC_Result.I_Max = 0;
    ADC_Result.I_Min = 100000;
    ADC_Result.Irms = 0;
    ADC_Result.Py = 0;
	
    for(i = 0; i < ADC_LENTH; i ++)
    {
        if(ADC_Result.V_Max < ADC_Buff_V[i]) ADC_Result.V_Max = ADC_Buff_V[i];
        if(ADC_Result.V_Min > ADC_Buff_V[i]) ADC_Result.V_Min = ADC_Buff_V[i];

        if(ADC_Result.I_Max < ADC_Buff_I[i]) ADC_Result.I_Max = ADC_Buff_I[i];
        if(ADC_Result.I_Min > ADC_Buff_I[i]) ADC_Result.I_Min = ADC_Buff_I[i];
    }

    //���ֵ
    ADC_Result.Vpp = ADC_Result.V_Max - ADC_Result.V_Min;
    ADC_Result.Ipp = ADC_Result.I_Max - ADC_Result.I_Min;

	
    //ֱ��ƫ��
    ADC_Result.V_Shift= (ADC_Result.V_Max + ADC_Result.V_Min) / 2.0f;
    ADC_Result.I_Shift = (ADC_Result.I_Max + ADC_Result.I_Min) / 2.0f;

    for(i = 0; i < ADC_LENTH; i ++)
    {
        ADC_Buff_V[i] -= ADC_Result.V_Shift;//ȥ��ƫ��
        ADC_Buff_I[i] -= ADC_Result.I_Shift;

        ADC_Result.Vrms += ADC_Buff_V[i] * ADC_Buff_V[i];
        ADC_Result.Irms += ADC_Buff_I[i] * ADC_Buff_I[i];

        ADC_Result.Py += ADC_Buff_V[i] * ADC_Buff_I[i];
    } 

    //��Чֵ
    ADC_Result.Vrms = sqrt(ADC_Result.Vrms / ADC_LENTH) * 2.0f;
    ADC_Result.Irms = sqrt(ADC_Result.Irms / ADC_LENTH) * 2.0f;
	
    //���ڹ���
    ADC_Result.Ps = (ADC_Result.Vrms * ADC_Result.Irms);
    //�й�����
    ADC_Result.Py = -(ADC_Result.Py / ADC_LENTH) * 4;
    //��������
    ADC_Result.Pf = ADC_Result.Py / ADC_Result.Ps; 
	//��λ��
	ADC_Result.DiffPhase = acos(ADC_Result.Pf)*360.0f/2.0f/PI;
	
	
	//�˲�
//	Struct_Filter_Vrms0.Filter_Depp = FILTER_DEPP_MAX;//�˲����
//	Struct_Filter_Vrms0.Filter_Mutation = 0.005f;//ͻ����ֵ 5mA
//	Struct_Filter_Vrms0.Filter_Section = 0.2f;//�˲����� 
//	Struct_Filter_Vrms0.Value = ADC_Result.Vrms;
//	Filter_Wind(&Struct_Filter_Vrms0);
//	ADC_Result.Vrms = Struct_Filter_Vrms0.Value;
//	
//	Struct_Filter_Vrms1.Filter_Depp = FILTER_DEPP_MAX;//�˲����
//	Struct_Filter_Vrms1.Filter_Mutation =  4.0f;//ͻ����ֵ 10V
//	Struct_Filter_Vrms1.Filter_Section = 0.2f;//�˲����� 
//	Struct_Filter_Vrms1.Value = ADC_Result.Irms;
//	Filter_Wind(&Struct_Filter_Vrms1);
//	ADC_Result.Irms = Struct_Filter_Vrms1.Value;
}



/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_FFT_Analysis()
* @Description   : FFT����
* @Data          : 2017��7��29��
* @Explain       : None
------------------------------------------------------------------------------*/
void FFT_Analysis(void)
{
    complex f_V[ADC_LENTH] = {0};
    complex f_I[ADC_LENTH] = {0};
	complex FFT_V[PER_FFT_SAVE] = {0};
	complex FFT_I[PER_FFT_SAVE] = {0};
	float Vpp[PER_FFT_SAVE] = {0};
	float Ipp[PER_FFT_SAVE] = {0};
	
    u16 i = 0; 
	float phase[2] = {0};
		
    //FFT����
    for(i = 0; i < ADC_LENTH; i ++)
    {
        f_V[i].real = ADC_Buff_V[i];
        f_I[i].real = ADC_Buff_I[i];

        f_V[i].imag = 0;
        f_I[i].imag = 0;
    }
    FFT(f_V, ADC_LENTH);
    FFT(f_I, ADC_LENTH);

    //ת��FFT�Ľ��
    for(i = 0; i < PER_FFT_SAVE; i ++)
    {
        FFT_V[i] = f_V[(i+1) * PER_FFT_CNT];
        FFT_I[i] = f_I[(i+1) * PER_FFT_CNT];
    }
	
	FFT_Result.All_Py = 0;
	FFT_Result.All_Pf = 0;
	FFT_Result.All_DiffPhase = 0;
	
    for(i = 0; i < PER_FFT_SAVE; i ++)
    {
		//��λ��
		phase[0] = atan2(FFT_V[i].imag, FFT_V[i].real) * 360.0f / 2.0f / PI;	
		phase[1] = atan2(FFT_I[i].imag ,FFT_I[i].real) * 360.0f / 2.0f / PI;	
		FFT_Result.DiffPhase[i] = phase[1] - phase[0];  
		
		Vpp[i] =  sqrt(FFT_V[i].imag * FFT_V[i].imag+FFT_V[i].real * FFT_V[i].real)*4.0f/ADC_LENTH;
		Ipp[i] =  sqrt(FFT_I[i].imag * FFT_I[i].imag+FFT_I[i].real * FFT_I[i].real)*4.0f/ADC_LENTH;
		
		//�й����� 
		FFT_Result.Py[i] = -Vpp[i] * Ipp[i]/2.0f*cos(FFT_Result.DiffPhase[i] * 2.0f * PI / 360.0f);
		
		//���й�����
		FFT_Result.All_Py += FFT_Result.Py[i];  
    }   
	
	for(i = 0; i < PER_FFT_SAVE; i ++)
	{
		//����λ
		FFT_Result.All_DiffPhase += FFT_Result.DiffPhase[i]*FFT_Result.Py[i]/FFT_Result.All_Py; 
		
	}
	FFT_Result.All_DiffPhase = FFT_Result.All_DiffPhase;
	FFT_Result.All_DiffPhase = Phase_Limit(FFT_Result.All_DiffPhase); 
	
	FFT_Result.All_Py = FFT_Result.All_Py;
    //�ܹ�������
    FFT_Result.All_Pf = cos(FFT_Result.All_DiffPhase*2.0f*PI/360.0f); 
	
}



/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_Start()
* @Description   : ��ʼ����
* @Data          : 2017��7��29��
* @Explain       : freq �ź�Ƶ��
------------------------------------------------------------------------------*/
void PhaseMeasure_Start(double freq)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    if(freq > MAX_FREQ)freq = MAX_FREQ;
    else if(freq < MIN_FREQ)freq = MIN_FREQ;

    double Fs = freq * PER_POINT; //����Ƶ��

    u16 TIM_Prescaler = 1;//Ԥ��Ƶ
    u16 TIM_Period = (u16)(1.0f / Fs * OS_FOSC / (double)TIM_Prescaler); //����ֵ

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��

    //��ʱ��TIM3��ʼ��
    TIM_TimeBaseStructure.TIM_Prescaler = TIM_Prescaler - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_Period = TIM_Period - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); //ʹ��ָ����TIMx�ж�,��������ж�

    //�ж����ȼ�NVIC����
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
    TIM_Cmd(TIM5, ENABLE); //ʹ��TIMx

    PhaseMeasure_State = 1;	//��ʼ�ɼ�

}


/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_Start()
* @Description   : �������
* @Data          : 2017��7��29��
* @Explain       : freq �ź�Ƶ��
------------------------------------------------------------------------------*/
void PhaseMeasure_End(void)
{
    TIM_Cmd(TIM5, DISABLE);
}



 

/*******************************(C) COPYRIGHT 2017 None *********************************/







