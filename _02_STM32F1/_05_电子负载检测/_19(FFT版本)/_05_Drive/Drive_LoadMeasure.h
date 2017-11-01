/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_LoadMeasure.h
* @Description : None
* @Date        : 2017��7��31��
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ���ؼ�����
*=============================================================================*/
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_LOADMEASURE_H
#define __DRIVE_LOADMEASURE_H

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "User_Library.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 
#define PER_POINT		(64)	//ÿ�����ڲɼ��ĵ���
#define PER_T_CNT		(8)		//�ɼ���������
#define ADC_LENTH		(PER_POINT*PER_T_CNT)	

#define PER_FFT_CNT		(PER_T_CNT)		//FFT�����Ƶ�ʼ�� 


/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/  
extern float ADC_Buff_V[ADC_LENTH];
extern float ADC_Buff_I[ADC_LENTH];  
extern Type_ADC_Result ADC_Result;
extern Type_FFT_Result FFT_Result;
extern u8 PhaseMeasure_State;    

/* ȫ�ֺ������� --------------------------------------------------------------*/   
void ADC_Analysis(void);
void FFT_Analysis(void);
void ADC_Shift_Get(void);

void PhaseMeasure_Start(double freq);
void PhaseMeasure_End(void);
void PhaseMeasure_ADC_Handle(void);
 

#endif
/*******************************(C) COPYRIGHT 2017 None *********************************/







