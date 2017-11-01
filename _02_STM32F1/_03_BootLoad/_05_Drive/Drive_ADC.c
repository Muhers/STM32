/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_ADC.c
* @Description : ADC驱动程序
* @Date        : 2016/8/8
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_ADC.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : ADC1_Init()
* @Description   : ADC1初始化
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void ADC1_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);	 //使能ADC1通道时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

    //PA1 作为模拟通道输入引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    ADC_DeInit(ADC1);  //复位ADC1

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
    ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
    ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
    ADC_ResetCalibration(ADC1);	//使能复位校准
    while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
    ADC_StartCalibration(ADC1);	 //开启AD校准
    while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束

}

/**----------------------------------------------------------------------------
* @FunctionName  : ADC1_Get()
* @Description   : 获得ADC1的值
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
ch:通道值 0~3 
------------------------------------------------------------------------------*/ 
u16 ADC1_Get(void)
{
    ADC_RegularChannelConfig(ADC1, 1, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
    return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

/**----------------------------------------------------------------------------
* @FunctionName  : ADC1_Average_Get()
* @Description   : 获得ADC1平均值
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
cnt:采样次数 
------------------------------------------------------------------------------*/ 
u16 ADC1_Average_Get(u8 cnt)
{
    u32 temp_val = 0;
    u8 t;
    for(t = 0; t < cnt; t++)
    {
        temp_val += ADC1_Get();
    }
    return temp_val / cnt;
}




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





