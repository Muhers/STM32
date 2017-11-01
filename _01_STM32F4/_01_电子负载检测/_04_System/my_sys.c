//******************************************(c)WindRises*Start File******************************************//

//时钟及分频配置文件
#include "my_sys.h"
#include "User_Library.h"

void RCC_Configuration(void)
{
//配置初始化时钟
//=========================================================================
	RCC_Div(336,8,2,7);//336M分2得168M系统频率//默认HCLK 不分频;APB1 4分频;APB2 2分频.
	RCC_PCLK2Config(RCC_HCLK_Div2);//设置APB2 二分频  用于ADC
	RCC_PCLK1Config(RCC_HCLK_Div2);//设置APB1 二分频（不能一分频，会导致SPI无法正常使用），用于EXTI_Line3
	
	
//=========================================================================
	

}




void RCC_Div(u16 a_pll_N,u16 a_pll_M,u16 a_pll_P,u16 a_pll_Q)
{
	
	

 
    /*配置前将所有RCC重置为初始值*/
     RCC_DeInit();
 
     /*这里选择 外部晶振（HSE）作为 时钟源，因此首先打开外部晶振*/
     RCC_HSEConfig(RCC_HSE_ON);
     /*等待外部晶振进入稳定状态*/
     while( RCC_WaitForHSEStartUp() != SUCCESS );
 
//     
//     我们要选择PLL时钟作为系统时钟，因此这里先要对PLL时钟进行配置
//     
// 
//     选择外部晶振作为PLL的时钟源
//    
//     到这一步为止，已有 HSE_VALUE = 8 MHz.
//     PLL_VCO input clock = (HSE_VALUE or HSI_VALUE / PLL_M)，
//     根据文档，这个值被建议在 1~2MHz，因此我们令 PLL_M = 8，
//     即 PLL_VCO input clock = 1MHz 
     
       //a_pll_M=8; 
//      到这一步为止，已有 PLL_VCO input clock = 1 MHz.
//        PLL_VCO output clock = (PLL_VCO input clock) * PLL_N,
//        这个值要用来计算系统时钟，我们 令 PLL_N = 336,
//        即 PLL_VCO output clock = 336 MHz.     
       // a_pll_N=336;
 
//      到这一步为止，已有 PLL_VCO output clock = 336 MHz.
//        System Clock = (PLL_VCO output clock)/PLL_P ,
//        因为我们要 SystemClock = 168 Mhz，因此令 PLL_P = 2.
       
   // a_pll_P=2;
 
//     这个系数用来配置SD卡读写，USB等功能，暂时不用，根据文档，暂时先设为7

    // a_pll_Q=7;
    
//    配置PLL并将其使能，获得 168Mhz 的 System Clock 时钟

     RCC_PLLConfig(RCC_PLLSource_HSE, a_pll_M, a_pll_N, a_pll_P, a_pll_Q);
     RCC_PLLCmd(ENABLE);
 
//     到了这一步，我们已经配置好了PLL时钟。下面我们配置Syetem Clock
//     选择PLL时钟作为系统时钟源

     RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
 
    
 
 
//    到了这一步，我们已经配置好了系统时钟，频率为 168MHz. 下面我们可以对 AHB，APB，外设等的 时钟进行配置*/
//    时钟的结构请参考用户手册*/
// 
//    首先配置 AHB时钟（HCLK）. 为了获得较高的频率，我们对 SYSCLK 1分频，得到HCLK

     RCC_HCLKConfig(RCC_HCLK_Div1);
 
//     APBx时钟（PCLK）由AHB时钟（HCLK）分频得到，下面我们配置 PCLK
// 
//     APB1时钟配置. 4分频，即 PCLK1 = 42 MHz
//     RCC_PCLK1Config(RCC_HCLK_Div4);
 
//     APB2时钟配置. 2分频，即 PCLK2 = 84 MHz

//     RCC_PCLK2Config(RCC_HCLK_Div2);
 

 

}
















//// 
////对于 RCC_PLLConfig();函数
////其函数原型为：
////void RCC_PLLConfig(uint32_t  RCC_PLLSource,
////                   uint32_t  PLLM,
////                   uint32_t  PLLN,
////                   uint32_t  PLLP,
////                   uint32_t  PLLQ)；
//// 
////迷惑的地方肯定在于后面 4个参数 PLLM / PLLN / PLLP / PLLQ.
//// 
////在库函数源文件 system_stm32f4xx.c 中可以找到这 4个参数的说明，请看下图注释部分:
//// 
////（下面的是从 库函数源文件 stm32f4xx_rcc.c 中找到的。其他函数可以直接去看库函数，注释非常详细）
//// 
/////**
////  * @brief  Configures the main PLL clock source, multiplication and division factors.
////   @简介   配置主PLL时钟源，以及分频因子          (PLL不止一个,还有一个用来为音频处理提供高质量时钟)
////  * @note   This function must be used only when the main PLL is disabled.
////  * @注意   这个函数只能在主PLL失能时才能使用
////  * @param  RCC_PLLSource: specifies the PLL entry clock source.
////   @参数    RCC_PLLSource:选择PLL时钟源
////  *          This parameter can be one of the following values:
////这个参数可以是如下值：
////  *            @arg RCC_PLLSource_HSI: HSI oscillator clock selected as PLL clock entry
//// 选择HSI作为PLL时钟源
////  *            @arg RCC_PLLSource_HSE: HSE oscillator clock selected as PLL clock entry
////选择HSE作为PLL时钟源
////  * @note   This clock source (RCC_PLLSource) is common for the main PLL and PLLI2S. 
////  *  
////  * @param  PLLM: specifies the division factor for PLL VCO input clock
////   @参数    PLLM：设置 PLL VCO 输入时钟的 除法因子（division factor）
////  *          This parameter must be a number between 0 and 63.
////这个参数 范围是 0 ~ 63
////  * @note   You have to set the PLLM parameter correctly to ensure that the VCO input
////  *         frequency ranges from 1 to 2 MHz. It is recommended to select a frequency
////  *         of 2 MHz to limit PLL jitter.
////  * @注意         你需要正确选择 PLLM的值， 使得 VCO输入频率 介于 1~2MHz.
////建议选择 2MHz 来限制PLL震荡（jitter？）
////  * @param  PLLN: specifies the multiplication factor for PLL VCO output clock
////  *          This parameter must be a number between 192 and 432.
////   @参数   PLLN     选择 PLL VCO输出时钟的 乘法因子（multiplication factor ）
////            这个参数的值 介于 192 ~432
////  * @note   You have to set the PLLN parameter correctly to ensure that the VCO
////  *         output frequency is between 192 and 432 MHz.
////  * @注意  你学要正确选PLLN的大小，以保证VCO输出时钟介于 192 ~432MHz 
////  * @param  PLLP: specifies the division factor for main system clock (SYSCLK)
////  *          This parameter must be a number in the range {2, 4, 6, or 8}.
////@参数  PLLP 选择 系统时钟SYSCLK 的除法因子（division factor ），这个
////            值可以是2,4,6,8
////  * @note   You have to set the PLLP parameter correctly to not exceed 168 MHz on
////  *         the System clock frequency.
////  * @注意  你需要正确设置PLLP，确保系统时钟SYSCLK不超过168MHz
////  * @param  PLLQ: specifies the division factor for OTG FS, SDIO and RNG clocks
////  *          This parameter must be a number between 4 and 15.
////@参数  PLLQ 选择给 OTG FS(USB), SDIO(SD卡读写), RNG（随机数发生器）
////        时钟的除法因子，其值介于4~15
////  * @note   If the USB OTG FS is used in your application, you have to set the
////  *         PLLQ parameter correctly to have 48 MHz clock for the USB. However,
////  *         the SDIO and RNG need a frequency lower than or equal to 48 MHz to work
////  *         correctly.
////  * @注意  如果在你的程序中用到 USB OTG FS,你需要正确设置PLLQ，确保USB有
////                 48MHz的时钟。但是对于SDIO，RNG需要一个小于或等于48MHz的时钟  
////  * @retval None

////	
	
	
	
	
	
	
	
	
	








//******************************************(c)WindRises*End File******************************************//

