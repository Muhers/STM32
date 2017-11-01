/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_SmallCar.c
* @Description : None
* @Date        : 2016/8/20
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_SmallCar.h"							

/* 私有宏定义 ----------------------------------------------------------------*/  

/* 私有（静态）函数声明 ------------------------------------------------------*/   

/* 全局变量定义 --------------------------------------------------------------*/    
Type_SmallCar SmallCar = {0};

/* 全局函数编写 --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Init()     
* @Description   : 小车初始化程序 
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/ 
void SmallCar_Init(void)
{
    Adc_Init();																	//ADC初始化
    InitAdc_Init();
    DMA_Configuration();														//DMA初始化
    TIM6_Int_Init(10000 - 1, 7200 - 1); 							 // 10000 * 7200/7200 0000  1a
    PWM1_Inti_select(0);   // 右边风扇  右边电机在同样的占空比下 转速比左边小   RCC_APB2Periph_TIM1
    PWM3_Inti_select(0);	 // 左边风扇    RCC_APB1Periph_TIM3

    TIM1_PWM_Init(2400 - 1, 1);											//PWM频率=72000000/(9999+1)*(71+1)=100hz  10ms   2400*2/36 72 =
    TIM3_PWM_Init(2400 - 1, 1);											//PWM频率=72000000/(9999+1)*(71+1)=100hz

    TIM_SetCompare1(TIM1, 1200);											//TIM1输出PWM,初始化占空比为 50%
    TIM_SetCompare1(TIM3, 1200);											//TIM3输出PWM,初始化占空比为 50%

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    DMA_Cmd(DMA1_Channel1, ENABLE); 								//启动DMA 通道

    PWM1_Select(1);
    PWM3_Select(1);

}


/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Left_Control()     
* @Description   : 控制小车左风机
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed：-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Left_Control(int Speed)
{
	u8 direct = 0;//停止
	
    if(Speed > 2400 ) Speed = 2400;
    else if(Speed < -2400) Speed = -2400;

	if(Speed > 0) direct = 1;//正向
	else if(Speed < 0) direct = 2;//反向
	
	PWM1_Select(direct);
    TIM_SetCompare1(TIM3,abs(Speed));
    SmallCar.LeftSpeed = Speed;
}


/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Right_Control()     
* @Description   : 控制小车右风机
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed：-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Right_Control(int Speed)
{
    u8 direct = 0;//停止
	
    if(Speed > 2400 )Speed = 2400;
    else if(Speed < -2400) Speed = -2400;
	
	if(Speed > 0) direct = 1;//正向
	else if(Speed < 0) direct = 2;//反向
	
	PWM3_Select(direct);	
    TIM_SetCompare1(TIM1,abs(Speed));
    SmallCar.RightSpeed = Speed;
	
}




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





















