/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_LoadAnalysis.c
* @Description : None
* @Date        : 2017年7月31日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 数据检测分析 
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_LoadAnalysis.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局变量声明 --------------------------------------------------------------*/ 

u8 PhaseMeasure_State = 0; 

float ADC_Buff_V[ADC_LENTH] = {0};		
float ADC_Buff_I[ADC_LENTH] = {0};		

Type_ADC_Result ADC_Result = {0}; 

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_ADC_Handle()
* @Description   : 测相AD数据采集
* @Data          : 2017年7月29日
* @Explain       : 此函数放入定时器中断中
------------------------------------------------------------------------------*/    
#define ADC_V_CORRECT_MULTIP			(480.9810850135107046352109748493f)  		
#define ADC_I_CORRECT_MULTIP			(8.1212841854934601664684898929845f)     	
//#define ADC_V_CORRECT_MULTIP			(1000.0f)  
//#define ADC_I_CORRECT_MULTIP			(1.0f)  
void PhaseMeasure_ADC_Handle(void)
{  
	static u16 cnt = 0;	   
	
	ADC_Buff_V[cnt] = (Load_Adc_Get(0))*ADC_V_CORRECT_MULTIP;	 
	ADC_Buff_I[cnt] = (Load_Adc_Get(1))*ADC_I_CORRECT_MULTIP;  
	
	cnt ++;	
	if(cnt >= ADC_LENTH) 
	{
		cnt = 0;				
		PhaseMeasure_State = 2;	 		
		PhaseMeasure_End();		
	}  
}

static float Irms_Correct(float value)
{
	float result = value; 
	return result;
}

/**----------------------------------------------------------------------------
* @FunctionName  : PhaseMeasure_ADC_Analysis()
* @Description   : FFT分析
* @Data          : 2017年7月29日
* @Explain       : None
------------------------------------------------------------------------------*/ 
float PHASE_SHIFT_ANGLE = (13.5f);
#define PHASE_SHIFT_BIT  ((int)(PER_POINT/PHASE_SHIFT_ANGLE + 0.5f))
void ADC_Analysis(void)
{ 
    u16 i = 0;
	float temp[ADC_LENTH] = {0};
	static Type_Filter Struct_Filter = {0};
	
    ADC_Result.V_Max = 0;
    ADC_Result.V_Min = 100000;
    ADC_Result.Vrms = 0;

    ADC_Result.I_Max = 0;
    ADC_Result.I_Min = 100000;	
    ADC_Result.Irms = 0;
    ADC_Result.Py = 0;
	ADC_Result.Irms_Sum = 0;
    ADC_Result.Py_Sum = 0;
	
	
	for(i = 0; i < ADC_LENTH; i ++)
	{
		temp[i] = ADC_Buff_I[(i+PHASE_SHIFT_BIT)%ADC_LENTH];
	}
	for(i = 0; i < ADC_LENTH; i ++)
	{
		ADC_Buff_I[i] = temp[i];
	}  
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
        ADC_Result.Irms_Sum += ADC_Buff_I[i] * ADC_Buff_I[i];
		
        ADC_Result.Py_Sum += ADC_Buff_V[i] * ADC_Buff_I[i];
    }  
	
    //有效值
    ADC_Result.Vrms = sqrt(ADC_Result.Vrms / ADC_LENTH) * 2.0f;
	ADC_Result.Irms_Sum = Irms_Correct(sqrt(ADC_Result.Irms_Sum / ADC_LENTH) * 2.0f); 
	
    //视在功率 
	ADC_Result.Ps_Sum = (ADC_Result.Vrms * ADC_Result.Irms_Sum); 
	
    //有功功率
	ADC_Result.Py_Sum = (ADC_Result.Py_Sum / ADC_LENTH) * 4.0f;
    ADC_Result.Py = ADC_Result.Py_Sum - ADC_Result.Py_Other;
	
	//无功功率
	ADC_Result.Pw_Sum = sqrt(pow(ADC_Result.Ps_Sum,2) - pow(ADC_Result.Py_Sum,2));	 
	ADC_Result.Pw =  ADC_Result.Pw_Sum - ADC_Result.Pw_Other;	
	
	ADC_Result.Ps = sqrt(ADC_Result.Pw*ADC_Result.Pw +  ADC_Result.Py* ADC_Result.Py);  
	ADC_Result.Irms = ADC_Result.Ps/ADC_Result.Vrms;	
	
	//功率因数
    ADC_Result.Pf = ADC_Result.Py / ADC_Result.Ps; 
	ADC_Result.Pf_Sum = ADC_Result.Py_Sum / ADC_Result.Ps_Sum; 
	
	//相位差
	ADC_Result.DiffPhase = acos(ADC_Result.Pf)*360.0f/2.0f/PI; 				
	ADC_Result.DiffPhase_Sum = acos(ADC_Result.Pf_Sum)*360.0f/2.0f/PI;   	
	
	//滤波
//	Struct_Filter.Filter_Section = 0.2f;//滤波区间0.3~0.7
//	Struct_Filter.Filter_Mutation = 0.02f;//突变阈值0.3W
//	Struct_Filter.Filter_Depp = FILTER_DEPP_MAX;
//	Struct_Filter.Value = ADC_Result.Py_Sum;
//	Filter_Wind(&Struct_Filter);
//	ADC_Result.Py_Sum = Struct_Filter.Value;
//	ADC_Result.Py = ADC_Result.Py_Sum - ADC_Result.Py_Other;	
	
	if(ADC_Result.Irms < 0.00049f)
	{ 
		ADC_Result.Irms = 0;	 	
		ADC_Result.Py = 0;			
		ADC_Result.Pw = 0;			
		ADC_Result.Ps = 0;			
		ADC_Result.Pf = 1;			
	}
	
}

 


/**----------------------------------------------------------------------------
* @FunctionName  : Others_Analysis()
* @Description   : 计算一次当前电流功率
* @Data          : 2017年7月29日
* @Explain       : None
------------------------------------------------------------------------------*/  
static void Others_Analysis(void)
{ 
    u16 i = 0;
    ADC_Result.V_Max = 0;
    ADC_Result.V_Min = 100000;
    ADC_Result.Vrms = 0;

    ADC_Result.I_Max = 0;
    ADC_Result.I_Min = 100000;	
    ADC_Result.Irms = 0;
    ADC_Result.Py = 0;
	float temp[ADC_LENTH] = {0};
	
	for(i = 0; i < ADC_LENTH; i ++)
	{
		temp[i] = ADC_Buff_I[(i+PHASE_SHIFT_BIT)%ADC_LENTH];
	}
	for(i = 0; i < ADC_LENTH; i ++)
	{
		ADC_Buff_I[i] = temp[i];
	} 

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
    ADC_Result.Irms = Irms_Correct(sqrt(ADC_Result.Irms / ADC_LENTH) * 2.0f);
	  
    //视在功率
    ADC_Result.Ps = (ADC_Result.Vrms * ADC_Result.Irms);
    //有功功率
    ADC_Result.Py = (ADC_Result.Py / ADC_LENTH) * 4.0f;
	//无功功率
	ADC_Result.Pw = sqrt(pow(ADC_Result.Ps,2) - pow(ADC_Result.Py,2));	
    //功率因数
    ADC_Result.Pf = ADC_Result.Py / ADC_Result.Ps; 
	//相位差
	ADC_Result.DiffPhase = acos(ADC_Result.Pf)*360.0f/2.0f/PI; 
	
	
	
	
}

#define OTHERS_GET_NUM			(20)	//平均次数	
#define OTHERS_GET_SECTION		(0.3f)	//取值滤波区间 0~0.4
/**----------------------------------------------------------------------------
* @FunctionName  : Others_Get()
* @Description   : 获取N次排插等电流功率 求平均
* @Data          : 2017年7月29日
* @Explain       : None
------------------------------------------------------------------------------*/  
void Others_Get(void)
{	  
	float Py_Other[OTHERS_GET_NUM] = {0};
	float Pw_Other[OTHERS_GET_NUM] = {0}; 
	float Irms_Other[OTHERS_GET_NUM] = {0};
	float Freq_Sample_Other[OTHERS_GET_NUM] = {0};
	
	float temp_Py = 0; 
	float temp_Pw = 0;
	float temp_Irms = 0;
	float temp_Freq_Sample = 0;
	
	float LastFreq = 0;
		
	u16 Left = OTHERS_GET_NUM*OTHERS_GET_SECTION;
	u16 Right = OTHERS_GET_NUM*(1.0f-OTHERS_GET_SECTION);
	u16 i = 0;
	
	//获得采样频率
	for(i = 0;i < OTHERS_GET_NUM;i ++)
	{
		Freq_Sample_Other[i] = FreqMeasure_Read(); 
		if(Freq_Sample_Other[i]< MAX_FREQ && Freq_Sample_Other[i] > MIN_FREQ) 
		{
			LastFreq = Freq_Sample_Other[i];
		}
		else Freq_Sample_Other[i] = LastFreq;
		
		OSdelay_ms(30); 
		
	}
	Sort_Quick(Freq_Sample_Other,0,OTHERS_GET_NUM);
	for(i = Left;i < Right;i ++)
	{  
		temp_Freq_Sample += Freq_Sample_Other[i]; 
	} 
	ADC_Result.Freq_Sample = temp_Freq_Sample/(float)(Right - Left);
	
	//获得空载参数
	for(i = 0;i < OTHERS_GET_NUM;i ++)
	{ 
		PhaseMeasure_Start(ADC_Result.Freq_Sample);//开始采AD
		while(PhaseMeasure_State != 2){};
		PhaseMeasure_State = 0; 
		Others_Analysis(); 
		Py_Other[i] = ADC_Result.Py; 
		Pw_Other[i] = ADC_Result.Pw; 	
		Irms_Other[i] = ADC_Result.Irms;   
	} 
	Sort_Quick(Py_Other,0,OTHERS_GET_NUM);
	Sort_Quick(Pw_Other,0,OTHERS_GET_NUM);
	Sort_Quick(Irms_Other,0,OTHERS_GET_NUM);
	
	for(i = Left;i < Right;i ++)
	{ 
		temp_Py += Py_Other[i];
		temp_Pw += Pw_Other[i];
		temp_Irms += Irms_Other[i];
		
	} 
	ADC_Result.Py_Other = temp_Py/(float)(Right - Left);
	ADC_Result.Pw_Other = temp_Pw/(float)(Right - Left);
	ADC_Result.Irms_Other = temp_Irms/(float)(Right - Left);
	
	
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
	
	double Fs = freq*PER_POINT;//采样频率
	 
	u16 TIM_Prescaler = 10;//预分频
	u16 TIM_Period = (u16)(1.0f/Fs * OS_FOSC/(double)TIM_Prescaler);//重载值
	
	//配置时钟及初始化预装值
	/*---------------------------------------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE); ///使能 TIMx时钟				   //@
	TIM_TimeBaseStructure.TIM_Period = TIM_Period-1;//重装载值
	TIM_TimeBaseStructure.TIM_Prescaler = TIM_Prescaler-1;//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上累计模式，即从0开始加到溢出值
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);//配置						    		//@
	TIM_ITConfig(TIM10,TIM_IT_Update,ENABLE);//允许定时器 更新中断							//@ 
	/*---------------------------------------------------------------------------------------------*/ 
	
	//配置中断层
	/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM1_UP_TIM10_IRQn; //定时器 x 中断				//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; //抢占优先级 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0 ; //响应优先级  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// 初始化 NVIC
 	TIM_Cmd(TIM10,ENABLE); //使能定时器 x				4								//@
	/*---------------------------------------------------------------------------------------------*/
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
    TIM_Cmd(TIM10, DISABLE);
}



 

/*******************************(C) COPYRIGHT 2017 None *********************************/







