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

/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/   
extern Type_Recognize Recognize_Source[LOAD_MAX];
extern Type_Recognize Recognize_New; 
extern u8 PhaseMeasure_State;  


/* ȫ�ֺ������� --------------------------------------------------------------*/     
Type_Recognize_Result Load_Recognize(Type_Recognize Recognize_New);
void Recognize_New_Update(void);


#endif
/*******************************(C) COPYRIGHT 2017 None *********************************/







