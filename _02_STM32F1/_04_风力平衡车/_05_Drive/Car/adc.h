#ifndef __ADC_H
#define __ADC_H	

#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h" 

#define CHANNEL_LENTH 				5 					//每个通道采集32次
#define CHANNEL_NUM 				8  						 //7个通道
#define ADC1_DR_Address	  0x4001244C
extern u16 AD_Value[CHANNEL_LENTH][CHANNEL_NUM]; //用来存放ADC转换结果，也是DMA的目标地址
extern u16 After_filter; //用来存放平均值的结果

void InitAdc_Init(void);
void Adc_Init(void);
void DMA_Configuration(void);
u16  Get_Adc2(u8 ch); 
u16 Get_Adc2_Average(u8 ch,u8 times);
void filter(void);
u16 GetVolt(u16 advalue);
 
#endif 




