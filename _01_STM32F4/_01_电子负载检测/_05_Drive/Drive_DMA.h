/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_DMA.h
* @Description : DMA传输测试
* @Date        : 2016/05/22 
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_DMA_H
#define __DRIVE_DMA_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* 全局宏定义 ----------------------------------------------------------------*/ 
//#define 	ADC1_DMA2_LENTH 		4000
//#define 	DAC1_DMA1_LENTH			2000 
#define 	ADC1_DMA2_LENTH 		1
#define 	ADC3_DMA2_LENTH 		1
#define 	DAC1_DMA1_LENTH			1


/* 结构体声明 ----------------------------------------------------------------*/ 
																	
/* 全局变量声明 --------------------------------------------------------------*/ 
extern Type_AppList APP_DMA;
extern u16 ADC1_DMA2_Buff[ADC1_DMA2_LENTH];
extern u16 ADC3_DMA2_Buff[ADC3_DMA2_LENTH];
extern u16 DAC1_DMA1_Buff[DAC1_DMA1_LENTH];



/* 全局函数声明 --------------------------------------------------------------*/    
void ADC1_DMA2_Reload(u8 Speed); 

void ADC3_DMA2_Reload(u8 Speed);
void ADC3_DMA2_Init(void);	

void DAC1_DMA1_Init(void);
void DAC1_DMA1_Reload(u32 speed);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



