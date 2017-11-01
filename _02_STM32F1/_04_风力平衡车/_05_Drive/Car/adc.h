#ifndef __ADC_H
#define __ADC_H	

#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h" 

#define CHANNEL_LENTH 				5 					//ÿ��ͨ���ɼ�32��
#define CHANNEL_NUM 				8  						 //7��ͨ��
#define ADC1_DR_Address	  0x4001244C
extern u16 AD_Value[CHANNEL_LENTH][CHANNEL_NUM]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
extern u16 After_filter; //�������ƽ��ֵ�Ľ��

void InitAdc_Init(void);
void Adc_Init(void);
void DMA_Configuration(void);
u16  Get_Adc2(u8 ch); 
u16 Get_Adc2_Average(u8 ch,u8 times);
void filter(void);
u16 GetVolt(u16 advalue);
 
#endif 




