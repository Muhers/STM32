/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_LoadMeasure.c
* @Description : None
* @Date        : 2017年7月31日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 负载检测计算
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_LoadMeasure.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define 	MIN_FREQ 	40
#define 	MAX_FREQ 	60

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局变量声明 --------------------------------------------------------------*/ 

u8 PhaseMeasure_State = 0; 

float ADC_Buff_V[ADC_LENTH] = {0};
float ADC_Buff_I[ADC_LENTH] = {0};

Type_ADC_Result ADC_Result = {0};
Type_FFT_Result FFT_Result = {0};

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_ADC_Handle()
* @Description   : 测相AD数据采集
* @Data          : 2017年7月29日
* @Explain       : 此函数放入定时器中断中
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
* @Description   : FFT分析
* @Data          : 2017年7月29日
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

    //峰峰值
    ADC_Result.Vpp = ADC_Result.V_Max - ADC_Result.V_Min;
    ADC_Result.Ipp = ADC_Result.I_Max - ADC_Result.I_Min;

	
    //直流偏置
    ADC_Result.V_Shift= (ADC_Result.V_Max + ADC_Result.V_Min) / 2.0f;
    ADC_Result.I_Shift = (ADC_Result.I_Max + ADC_Result.I_Min) / 2.0f;

    for(i = 0; i < ADC_LENTH; i ++)
    {
        ADC_Buff_V[i] -= ADC_Result.V_Shift;//去除偏置
        ADC_Buff_I[i] -= ADC_Result.I_Shift;

        ADC_Result.Vrms += ADC_Buff_V[i] * ADC_Buff_V[i];
        ADC_Result.Irms += ADC_Buff_I[i] * ADC_Buff_I[i];

        ADC_Result.Py += ADC_Buff_V[i] * ADC_Buff_I[i];
    } 

    //有效值
    ADC_Result.Vrms = sqrt(ADC_Result.Vrms / ADC_LENTH) * 2.0f;
    ADC_Result.Irms = sqrt(ADC_Result.Irms / ADC_LENTH) * 2.0f;
	
    //视在功率
    ADC_Result.Ps = (ADC_Result.Vrms * ADC_Result.Irms);
    //有功功率
    ADC_Result.Py = -(ADC_Result.Py / ADC_LENTH) * 4;
    //功率因数
    ADC_Result.Pf = ADC_Result.Py / ADC_Result.Ps; 
	//相位差
	ADC_Result.DiffPhase = acos(ADC_Result.Pf)*360.0f/2.0f/PI;
	
	
	//滤波
//	Struct_Filter_Vrms0.Filter_Depp = FILTER_DEPP_MAX;//滤波深度
//	Struct_Filter_Vrms0.Filter_Mutation = 0.005f;//突变阈值 5mA
//	Struct_Filter_Vrms0.Filter_Section = 0.2f;//滤波区间 
//	Struct_Filter_Vrms0.Value = ADC_Result.Vrms;
//	Filter_Wind(&Struct_Filter_Vrms0);
//	ADC_Result.Vrms = Struct_Filter_Vrms0.Value;
//	
//	Struct_Filter_Vrms1.Filter_Depp = FILTER_DEPP_MAX;//滤波深度
//	Struct_Filter_Vrms1.Filter_Mutation =  4.0f;//突变阈值 10V
//	Struct_Filter_Vrms1.Filter_Section = 0.2f;//滤波区间 
//	Struct_Filter_Vrms1.Value = ADC_Result.Irms;
//	Filter_Wind(&Struct_Filter_Vrms1);
//	ADC_Result.Irms = Struct_Filter_Vrms1.Value;
}



/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_FFT_Analysis()
* @Description   : FFT分析
* @Data          : 2017年7月29日
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
		
    //FFT计算
    for(i = 0; i < ADC_LENTH; i ++)
    {
        f_V[i].real = ADC_Buff_V[i];
        f_I[i].real = ADC_Buff_I[i];

        f_V[i].imag = 0;
        f_I[i].imag = 0;
    }
    FFT(f_V, ADC_LENTH);
    FFT(f_I, ADC_LENTH);

    //转存FFT的结果
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
		//相位差
		phase[0] = atan2(FFT_V[i].imag, FFT_V[i].real) * 360.0f / 2.0f / PI;	
		phase[1] = atan2(FFT_I[i].imag ,FFT_I[i].real) * 360.0f / 2.0f / PI;	
		FFT_Result.DiffPhase[i] = phase[1] - phase[0];  
		
		Vpp[i] =  sqrt(FFT_V[i].imag * FFT_V[i].imag+FFT_V[i].real * FFT_V[i].real)*4.0f/ADC_LENTH;
		Ipp[i] =  sqrt(FFT_I[i].imag * FFT_I[i].imag+FFT_I[i].real * FFT_I[i].real)*4.0f/ADC_LENTH;
		
		//有功功率 
		FFT_Result.Py[i] = -Vpp[i] * Ipp[i]/2.0f*cos(FFT_Result.DiffPhase[i] * 2.0f * PI / 360.0f);
		
		//总有功功率
		FFT_Result.All_Py += FFT_Result.Py[i];  
    }   
	
	for(i = 0; i < PER_FFT_SAVE; i ++)
	{
		//总相位
		FFT_Result.All_DiffPhase += FFT_Result.DiffPhase[i]*FFT_Result.Py[i]/FFT_Result.All_Py; 
		
	}
	FFT_Result.All_DiffPhase = FFT_Result.All_DiffPhase;
	FFT_Result.All_DiffPhase = Phase_Limit(FFT_Result.All_DiffPhase); 
	
	FFT_Result.All_Py = FFT_Result.All_Py;
    //总功率因数
    FFT_Result.All_Pf = cos(FFT_Result.All_DiffPhase*2.0f*PI/360.0f); 
	
}



/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_Start()
* @Description   : 开始测相
* @Data          : 2017年7月29日
* @Explain       : freq 信号频率
------------------------------------------------------------------------------*/
void PhaseMeasure_Start(double freq)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    if(freq > MAX_FREQ)freq = MAX_FREQ;
    else if(freq < MIN_FREQ)freq = MIN_FREQ;

    double Fs = freq * PER_POINT; //采样频率

    u16 TIM_Prescaler = 1;//预分频
    u16 TIM_Period = (u16)(1.0f / Fs * OS_FOSC / (double)TIM_Prescaler); //重载值

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟使能

    //定时器TIM3初始化
    TIM_TimeBaseStructure.TIM_Prescaler = TIM_Prescaler - 1; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_Period = TIM_Period - 1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); //使能指定的TIMx中断,允许更新中断

    //中断优先级NVIC设置
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
    TIM_Cmd(TIM5, ENABLE); //使能TIMx

    PhaseMeasure_State = 1;	//开始采集

}


/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_Start()
* @Description   : 测相结束
* @Data          : 2017年7月29日
* @Explain       : freq 信号频率
------------------------------------------------------------------------------*/
void PhaseMeasure_End(void)
{
    TIM_Cmd(TIM5, DISABLE);
}



 

/*******************************(C) COPYRIGHT 2017 None *********************************/







