/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_DAC.c
* @Description : None
* @Date        : 2016/7/10
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_DAC.h"


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : DAC1_Init()     
* @Description   : None 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void DAC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//①使能 PA 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//②使能 DAC 时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//①初始化 GPIO
	DAC_InitType.DAC_Trigger=DAC_Trigger_None; //不使用触发功能 TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0; //屏蔽、幅值设置
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;//输出缓存关闭
	DAC_Init(DAC_Channel_1,&DAC_InitType); //③初始化 DAC 通道 1
	DAC_Cmd(DAC_Channel_1, ENABLE); //④使能 DAC 通道 1
	DAC_SetChannel1Data(DAC_Align_12b_R , 0); //⑤12 位右对齐数据格式
	 
}


/**----------------------------------------------------------------------------
* @FunctionName  : Get_ADC_Average()
* @Description   : None
* @Data          : 2016/7/11
* @Explain       :
-------------------------------------------------------------------------------
设置通道 1(PA4) 输出电压
vol 0~3.3V
------------------------------------------------------------------------------*/
void DAC1_Vol_Set(u16 vol)
{
//	double temp = vol*4096/3.3; 
	DAC_SetChannel1Data(DAC_Align_12b_R,vol);//12 位右对齐数据格式
}



/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





