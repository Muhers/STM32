/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_LoadAnalysis.h
* @Description : None
* @Date        : 2017��7��31��
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ������
*=============================================================================*/
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_LOADANALYSIS_H
#define __DRIVE_LOADANALYSIS_H

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "User_Library.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 


/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/  
extern float ADC_Buff_V[ADC_LENTH];
extern float ADC_Buff_I[ADC_LENTH];   
extern Type_ADC_Result ADC_Result; 
   

/* ȫ�ֺ������� --------------------------------------------------------------*/   
void ADC_Analysis(void); 
void ADC_Shift_Get(void);
void Others_Get(void);
	
void PhaseMeasure_Start(double freq);
void PhaseMeasure_End(void);
void PhaseMeasure_ADC_Handle(void);
 

#endif
/*******************************(C) COPYRIGHT 2017 None *********************************/







