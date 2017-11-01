/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_Filter.h
* @Description : None
* @Date        : 2017��7��31��
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : �����˲�����
*=============================================================================*/
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_FILTER_H
#define __DRIVE_FILTER_H

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "User_Library.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
#define	FILTER_DEPP_MAX		(10)
#define FIR_LENTH			ADC_LENTH

#define	MAX2(x1,x2)			(x1>x2?x1:x2)
#define	MIN2(x1,x2)			(x1<x2?x1:x2)

/* �ṹ������ ----------------------------------------------------------------*/
typedef struct 
{  		 
	float Value;//ֵ
	u16 Filter_Depp;//�˲����,0~FILTER_DEPP_MAX
	float Filter_Mutation;//ͻ����ֵ	
	float Filter_Section;//�˲�����,ȡֵ0~1
	
	float Last_Result[FILTER_DEPP_MAX];//������ù� 
}Type_Filter; //�������	

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ������� --------------------------------------------------------------*/
int Filter_Wind(Type_Filter *Struct_Filter);
void Sort_Quick(float *num, int l, int r);
void Conv(float *output, float *input1, float *input2, int N1, int N2); 
//void FIR(float *input);
float Phase_Limit(float _phase);





#endif
/*******************************(C) COPYRIGHT 2017 None *********************************/







