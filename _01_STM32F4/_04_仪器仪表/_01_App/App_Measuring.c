/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Measuring.c
* @Description : 仪器仪表测量
* @Date        : 2016/7/29
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Measuring.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define SHOW_HANDLE(X)			OS_Decim_Show(16*6,460,X,4,0,16,1)


#define ADC_OVR_CLEAR()			{	ADC1->SR &= ~(0x0001<<5); \
									ADC2->SR &= ~(0x0001<<5); \
									ADC3->SR &= ~(0x0001<<5);	}

#define ADC_OVR	(ADC1->SR << 5 ||ADC2->SR << 5||ADC3->SR << 5)



/* 私有（静态）函数声明 ------------------------------------------------------*/
static Type_AppList App_Measuring_Show;
static Type_AppList App_Measuring_FFT;
static void Measuring_Analysis(void);
static void Measuring_ADC_Spped(u32 T);

/* 全局变量定义 --------------------------------------------------------------*/
u8 	MeasuringMode = 0;
Type_Measuring Measuring = {9999999.9f, 9999999.9f, 9999999.9f, 9999999.9f, 9999999.9f, 9999999.9f}; //将最小值初始化


/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Measuring()
* @Description   : 仪器仪表
* @Data          : 2016/7/29
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Measuring_Main(void)
{
    static u32 LastT = 0;
    u32 tempT = 0;

    if(Measuring.ADC_Flag == MEASURING_COMPLETE)
    {
        Measuring_Analysis();//数据分析
        App_VoltageGain.AppMain();
        tempT = 1000000 / Measuring.Freq;
        if(LastT != tempT)
        {
            LastT = tempT;
            if(Measuring.Freq < 110)
            {
                Measuring_ADC_Spped(tempT);
                OS_String_Show(600, 120, (u8 *)"使用的周期：", 16, 1);
                OS_Num_Show(600 + 16 * 6, 120, tempT, 9, 16, 1);
            }
        }


        Measuring.ADC_Flag = MEASURING_START;//重新开始ADC采集
    }

    return 0;
}

unsigned int Measuring_Start(void)
{
    static u8 first = 0;
    if(first == 0)
    {
        first = 1;
        ADC1_Init();
        ADC2_Init();
        ADC3_DMA2_Init();
        TIM12_Init();//用于采AD
        OSTask_Creat(&App_Measuring_Show);
        OSTask_Creat(&App_Measuring_FFT);
        OSTask_Creat(&App_PhaseShift);	//程控移相
        OSTask_Creat(&App_Frequency);	//测频
        App_VoltageGain.AppStart();

    }
    return 0;
}
Type_AppList App_Measuring = {Measuring_Main, NULL, Measuring_Start, NULL, \
                              OS_STATE_ACTIVE, OS_THREAD_PRIMARY, \
                              (u8 *)"Measuring", 200
                             };


/**----------------------------------------------------------------------------
* @FunctionName  : Measuring_Analysis()
* @Description   : 仪器仪表数据分析
* @Data          : 2016/7/29
* @Explain       : None
------------------------------------------------------------------------------*/
static void Measuring_Analysis(void)
{
    u16 i = 0;
    Measuring.Volt_Max = 0.0f;
    Measuring.Volt_Min = 999999.0f;
    Measuring.Elect_Max = 0.0f;
    Measuring.Elect_Min = 999999.0f;
    Measuring.CountP = 0.0f;

    for(i = 0; i < MEASURING_ADC_LENTH; i++) //查询最大值和最小值
    {
        if(Measuring.Volt_Max < Measuring.ADC1_Buff[i])		   Measuring.Volt_Max = Measuring.ADC1_Buff[i];
        if(Measuring.Volt_Min > Measuring.ADC1_Buff[i])        Measuring.Volt_Min = Measuring.ADC1_Buff[i];

        if(Measuring.Elect_Max < Measuring.ADC2_Buff[i]) 	   Measuring.Elect_Max = Measuring.ADC2_Buff[i];
        if(Measuring.Elect_Min > Measuring.ADC2_Buff[i]) 	   Measuring.Elect_Min = Measuring.ADC2_Buff[i];

    }
    for(i = 0; i < MEASURING_ADC_LENTH; i++) //偏置到0
    {
        Measuring.ADC1_Buff[i] = (Measuring.ADC1_Buff[i] - Measuring.Volt_Min) / Volt_Zoom;
        Measuring.ADC2_Buff[i] = (Measuring.ADC2_Buff[i] - Measuring.Elect_Min) / Volt_Zoom;
    }
    Measuring.ReallyVpp = (Measuring.Volt_Max - Measuring.Volt_Min) / 100.0f;
    Measuring.Volt_Max = (Measuring.Volt_Max - Measuring.Volt_Min) / Volt_Zoom;
    Measuring.Elect_Max = (Measuring.Elect_Max - Measuring.Elect_Min) / Volt_Zoom;
    Measuring.Volt_Min = 0;
    Measuring.Elect_Min = 0;

    Measuring.CountS = ((Measuring.Volt_Max)) * ((Measuring.Elect_Max)) / 8.0f; //视在功率
    for(i = 0; i < MEASURING_ADC_LENTH; i++)
        Measuring.CountP += ((Measuring.ADC1_Buff[i] - Measuring.Volt_Max / 2) * ((Measuring.ADC2_Buff[i] - Measuring.Elect_Max / 2))) / MEASURING_ADC_LENTH; //有功功率(计算)
    Measuring.CountQ = sqrt(Measuring.CountS * Measuring.CountS - Measuring.CountP * Measuring.CountP); //无功功率
    Measuring.CountPF = Measuring.CountP / Measuring.CountS; //功率因数
    Measuring.Freq = g_Freq;//频率
    Measuring.EffecVolt = Measuring.Volt_Max / (2.0f * sqrt(2)); //电压有效值
    Measuring.EffecElect = Measuring.Elect_Max / (2.0f * sqrt(2)); //电流有效值

    if(Measuring.g_EffecVolt_Max < Measuring.EffecVolt)  Measuring.g_EffecVolt_Max = Measuring.EffecVolt;
    if(Measuring.g_EffecVolt_Min > Measuring.EffecVolt)  Measuring.g_EffecVolt_Min = Measuring.EffecVolt;
    if(Measuring.g_EffecElect_Max < Measuring.EffecElect)  Measuring.g_EffecElect_Max = Measuring.EffecElect;
    if(Measuring.g_EffecElect_Min > Measuring.EffecElect) Measuring.g_EffecElect_Min = Measuring.EffecElect;

    if(Measuring.g_P_Max < Measuring.CountP)  Measuring.g_P_Max = Measuring.CountP;
    if(Measuring.g_P_Min > Measuring.CountP)  Measuring.g_P_Min = Measuring.CountP;
    if(Measuring.g_Q_Max < Measuring.CountQ)  Measuring.g_Q_Max = Measuring.CountQ;
    if(Measuring.g_Q_Min > Measuring.CountQ)  Measuring.g_Q_Min = Measuring.CountQ;

    if(Measuring.FFT_Flag == MEASURING_START)//转移数据给FFT
    {
        for(i = 0; i < MEASURING_ADC_LENTH; i++)
            Measuring.FFT_Buff[i] = (Measuring.ADC1_Buff[i]) / 100;

        Measuring.FFT_Flag = MEASURING_COMPLETE;
    }


}

/**----------------------------------------------------------------------------
* @FunctionName  : 仪器仪表FFT程序()
* @Description   : FFT
* @Data          : 2016/7/29
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Measuring_FFT_Main(void)
{
    u16 i = 0, BasisX1 = 1, BasisX2 = 1, BasisX3 = 1, temp = 0;
    u16 PointNum = 1;
    static double LastFFT_THD[2] = {0.0f};
    double  FFT_THD = 0.0f;//失真度
    u8 ERROR_Flag = 0;
    static u8 cnt = 0;

    ERROR_HANDLE(0);
    if(Measuring.FFT_Flag == MEASURING_COMPLETE)
    {
        ERROR_HANDLE(1);
        if(Measuring.Freq > 100)
        {
            if(ADC_OVR) ADC_OVR_CLEAR();//ADC溢出清零

            if(Measuring.Freq < 1500)		ADC3_DMA2_Reload(5);

            else ADC3_DMA2_Reload(0);

            //			while(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1) != SET){}
            ERROR_HANDLE(2);
            OSdelay_ms(100);
            PointNum = ADC_Waveform_Get(ADC3_DMA2_Buff, ADC3_DMA2_LENTH, Measuring.FFT_Buff, MEASURING_ADC_LENTH);
        }
        ERROR_HANDLE(3);
        if(PointNum)//没有点数则不更新数据
        {
            Measuring.FFT_Basis = 0;
            Measuring.FFT_HarmonicSum = 0;
            FFT_Exchange_Measuring();//FFT变换
            ERROR_HANDLE(4);
            for(i = 1; i < MEASURING_ADC_LENTH / 2; i++)
            {
                if(Measuring.FFT_Basis < Measuring.FFT_Buff[i])
                {
                    Measuring.FFT_Basis = Measuring.FFT_Buff[i];
                    BasisX1 = i;
                }

            }
            temp = 0;
            ERROR_HANDLE(5);
            for(i = BasisX1 + 1; i < MEASURING_ADC_LENTH / 2; i++)
            {
                if(temp < Measuring.FFT_Buff[i])
                {
                    temp = Measuring.FFT_Buff[i];
                    BasisX2 = i;
                }

            }
            temp = 0;
            ERROR_HANDLE(6);
            for(i = BasisX2 + 1; i < MEASURING_ADC_LENTH / 2; i++)
            {
                if(temp < Measuring.FFT_Buff[i])
                {
                    temp = Measuring.FFT_Buff[i];
                    BasisX3 = i;
                }

            }
            ERROR_HANDLE(7);


            for(i = BasisX1 * 2; i < MEASURING_ADC_LENTH / 2; i += BasisX1)
            {
                Measuring.FFT_HarmonicSum += pow(Measuring.FFT_Buff[i], 2);
            }


            ERROR_HANDLE(8);
            Measuring.FFT_HarmonicSum = sqrt(Measuring.FFT_HarmonicSum); //谐波总和

            FFT_THD = Measuring.FFT_HarmonicSum / Measuring.FFT_Basis; //失真度补偿

            Measuring.FFT_THD = FFT_THD;

            if(fabs(LastFFT_THD[0] - FFT_THD) > 0.01)//滤掉低频干扰
            {
                if(FFT_THD != LastFFT_THD[1])	ERROR_Flag = 1;
                LastFFT_THD[1] = LastFFT_THD[0];
                LastFFT_THD[0] = FFT_THD;
            }


            if(ERROR_Flag == 0)//没有错误
            {
                OS_FFT_Draw_Double(500, 150, 750, 350, Measuring.FFT_Buff, 1, 1, 1.0f / 1.0f);
                ERROR_HANDLE(9);
                OS_Decim_Show(500, 360, BasisX1, 4, 1, 16, 1);
                ERROR_HANDLE(10);
                OS_Decim_Show(600, 360, BasisX2, 4, 1, 16, 1);
                ERROR_HANDLE(11);
                OS_Decim_Show(700, 360, BasisX3, 4, 1, 16, 1);
                ERROR_HANDLE(12);

                OS_String_Show(500, 400, (u8 *)"基波：", 16, 1);
                OS_Decim_Show(500 + 16 * 5, 400, Measuring.FFT_Basis, 7, 2, 16, 1);
                ERROR_HANDLE(13);
                OS_String_Show(500, 420, (u8 *)"谐波之和：", 16, 1);
                OS_Decim_Show(500 + 16 * 5, 420, Measuring.FFT_HarmonicSum, 7, 2, 16, 1);
                ERROR_HANDLE(14);
                OS_String_Show(500, 440, (u8 *)"失真度：", 16, 1);
                OS_Decim_Show(500 + 16 * 5, 440, FFT_THD, 2, 4, 16, 1);
                ERROR_HANDLE(15);
            }
            ERROR_HANDLE(16);
        }

        OS_Decim_Show(16 * 12, 460, cnt++, 4, 0, 16, 1);

        SHOW_HANDLE(ERROR_Flag);
        Measuring.FFT_Flag = MEASURING_START;//再次开启FFT转换采集
    }

    return 0;
}
static Type_AppList App_Measuring_FFT = {Measuring_FFT_Main, NULL, NULL, NULL, \
                                        OS_STATE_ACTIVE, OS_THREAD_FREE, \
                                        (u8 *)"Measuring_FFT", 10
                                        };



/**----------------------------------------------------------------------------
* @FunctionName  : 仪器仪表显示程序()
* @Description   : 仪器仪表
* @Data          : 2016/7/29
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Measuring_Show_Main(void)
{
    u16 TempColor = TextColor;
    TextColor = WHITE;

    OS_String_Show(300, 20, (u8 *)"仪器仪表", 32, 1);

    //	OS_String_Show(20,60,(u8*)"输入输出：PF1~12  ADC1,2  PE4",24,1);
    //	OS_String_Show(50,90, (u8*)"PF1 | PF2 |  PF3   PF4    |",16,1);
    //	OS_String_Show(50,106,(u8*)"SCL | SDA |  继电器1,2    |",16,1);
    //
    //	OS_String_Show(300,90, (u8*)"ADC1 | ADC2 |  PE4 |   ",16,1);
    //	OS_String_Show(300,106,(u8*)"电压 | 电流 |  测频|  ",16,1);

    //	OS_String_Show(50,130,(u8*)"-------------------------------------------------------",16,1);
    //
    //	OS_String_Show(50,150,(u8*)"     PF5,7,9,11           |",16,1);
    //	OS_String_Show(50,166,(u8*)"电流:MUTE,CLK,SDI,CS      |",16,1);
    //
    //	OS_String_Show(300,150,(u8*)"     PF6,8,10,12      ",16,1);
    //	OS_String_Show(300,166,(u8*)"电压:MUTE,CLK,SDI,CS  ",16,1);
    //
    //	OS_String_Show(20,200,(u8*)"数据显示：",24,1);


    OS_String_Show(50, 230, (u8 *)"视在功率：", 16, 1);
    OS_Decim_Show(50 + 16 * 5, 230, Measuring.CountS, 5, 3, 16, 1);
    OS_String_Show(50, 246, (u8 *)"有功功率：", 16, 1);
    OS_Decim_Show(50 + 16 * 5, 246, Measuring.CountP, 5, 3, 16, 1);
    OS_String_Show(50, 262, (u8 *)"无功功率：", 16, 1);
    OS_Decim_Show(50 + 16 * 5, 262, Measuring.CountQ, 5, 3, 16, 1);
    OS_String_Show(50, 278, (u8 *)"功率因数：", 16, 1);
    OS_Decim_Show(50 + 16 * 5, 278, Measuring.CountPF, 5, 3, 16, 1);

    OS_String_Show(225, 230, (u8 *)"||  电压有效值：", 16, 1);
    OS_Decim_Show(225 + 16 * 8, 230, Measuring.EffecVolt, 5, 3, 16, 1);
    OS_String_Show(225, 246, (u8 *)"||  电流有效值：", 16, 1);
    OS_Decim_Show(225 + 16 * 8, 246, Measuring.EffecElect, 5, 3, 16, 1);
    OS_String_Show(225, 262, (u8 *)"||  电压峰峰值：", 16, 1);
    OS_Decim_Show(225 + 16 * 8, 262, Measuring.Volt_Max, 5, 3, 16, 1);
    OS_String_Show(225, 278, (u8 *)"||  电流峰峰值：", 16, 1);
    OS_Decim_Show(225 + 16 * 8, 278, Measuring.Elect_Max, 5, 3, 16, 1);

    OS_String_Show(50, 310, (u8 *)"电压有效值最大值:", 16, 1);
    OS_Decim_Show(50 + 16 * 9, 310, Measuring.g_EffecVolt_Max, 5, 3, 16, 1);
    OS_String_Show(50, 330, (u8 *)"电压有效值最小值:", 16, 1);
    OS_Decim_Show(50 + 16 * 9, 330, Measuring.g_EffecVolt_Min, 5, 3, 16, 1);
    OS_String_Show(50, 350, (u8 *)"电流有效值最大值:", 16, 1);
    OS_Decim_Show(50 + 16 * 9, 350, Measuring.g_EffecElect_Max, 5, 3, 16, 1);
    OS_String_Show(50, 370, (u8 *)"电流有效值最小值:", 16, 1);
    OS_Decim_Show(50 + 16 * 9, 370, Measuring.g_EffecElect_Min, 5, 3, 16, 1);

    if(Measuring.Volt_Max > 477.0f) OS_String_Show(20 + 5 * 24, 200, (u8 *)"警告！！！ 已超出测量范围 ", 24, 1); //过量程指示
    else									OS_String_Show(20 + 5 * 24, 200, (u8 *)"正在测量中，一切正常......", 24, 1); //过量程指示

    OS_String_Show(600, 50, (u8 *)"频率：", 16, 1);
    OS_Num_Show(600 + 16 * 4, 50, Measuring.Freq , 9, 16, 1);
    OS_String_Show(600, 70, (u8 *)"周期：", 16, 1);
    OS_Num_Show(600 + 16 * 4, 70, Measuring.T, 9, 16, 1);
    OS_String_Show(600, 90, (u8 *)"缩放：", 16, 1);
    OS_Decim_Show(600 + 16 * 3, 90, Volt_Zoom, 5, 3, 16, 1);

    TextColor = TempColor;


    return 0;
}
static Type_AppList App_Measuring_Show = {Measuring_Show_Main, NULL, NULL, NULL, \
        OS_STATE_ACTIVE, OS_THREAD_7, \
        (u8 *)"Measuring_Show", 200
                                         };


static void Measuring_ADC_Spped(u32 T)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    //配置时钟及初始化预装值
    /*---------------------------------------------------------------------------------------------*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE); ///使能 TIMx时钟				   //@
    TIM_TimeBaseStructure.TIM_Period = T * 4 / MEASURING_ADC_LENTH - 1; //重装载值
    TIM_TimeBaseStructure.TIM_Prescaler = 42 - 1;//预分频
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上累计模式，即从0开始加到溢出值
    TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);//配置						    		//@
    TIM_ITConfig(TIM12, TIM_IT_Update, ENABLE); //允许定时器 更新中断							//@
    /*---------------------------------------------------------------------------------------------*/

    //配置中断层
    /*---------------------------------------------------------------------------------------------*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn; //定时器 x 中断			//@
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级 4
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0 ; //响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);// 初始化 NVIC_
    TIM_Cmd(TIM12, ENABLE); //使能定时器 x				4								//@
    /*---------------------------------------------------------------------------------------------*/

}

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/








