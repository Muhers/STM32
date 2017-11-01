/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/
/**============================================================================
* @FileName    : Drive_EXTI.c
* @Description : 外部中断驱动	

*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_EXTI.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Exti11_Init()
* @Description   : 外部中断初始化
* @Data          : 2016/8/8
* @Explain       : 用于接收短信
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
//void EXTI11_Init(void)
//{ 
// 	EXTI_InitTypeDef EXTI_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure; 
//	GPIO_InitTypeDef GPIO_InitStructure;
// 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIO时钟 
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //设置成输入，悬浮
//	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化GPIO 
//	
//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟 
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);

//  	EXTI_InitStructure.EXTI_Line = EXTI_Line11;	 
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器 
// 
//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//子优先级
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道 
//    NVIC_Init(&NVIC_InitStructure);     
//}

/**************************************************************************
函数功能：外部中断初始化
入口参数：无
返回  值：无 
**************************************************************************/
void MiniBalance_EXTI_Init(void)
{  
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIO端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	            //端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIO
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);

    EXTI_InitStructure.EXTI_Line=EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级2， 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure); 
}

 
/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/





