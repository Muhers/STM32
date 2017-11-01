/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : User_Stdafx.h
* @Description : None
* @Date        : 2017/8/6
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : �ṹ�� ���������ļ�
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __USER_STDAFX_H
#define __USER_STDAFX_H

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "stm32f10x.h"

/* ȫ�����Ⱥ궨�� ------------------------------------------------------------*/
#define PER_FFT_SAVE			(8)		//����г����������
#define MESSAGE_CH_MAX			(2)			//����ͨ����
#define LOAD_MAX				(7)			//������ 


/* �ṹ������ ----------------------------------------------------------------*/
typedef struct
{
    float DiffPhase[PER_FFT_SAVE]; //��г����λ��
    float Py[PER_FFT_SAVE]; //��г���й�����

    float All_DiffPhase;//����λ				
    float All_Pf; //��������	  				Pf=Py/Ps 
    float All_Py; //�й�����(ƽ������)  		Py=���֣���ѹ*������/����
	
} Type_FFT_Result; //FFT

typedef struct
{
    float V_Max;
    float V_Min;
    float I_Max;
    float I_Min;
    float Vpp;
    float Ipp;
    float Vrms;
    float Irms;
    float V_Shift; //ֱ��ƫ��
    float I_Shift; //ֱ��ƫ�� 
    float Pf; //��������	  				Pf=Py/Ps
    float Ps; //���ڹ���  				Ps=Vrms*Irms
    float Py; //�й�����(ƽ������)  		Py=���֣���ѹ*������/����
    float Freq; //Ƶ��
    float DiffPhase;//����λ
} Type_ADC_Result; //ADC


typedef struct  //��������
{
    float real;		//ʵ��
    float imag;		//�鲿
} complex;

typedef struct
{
    float Vpp[PER_FFT_SAVE];
    float Ipp[PER_FFT_SAVE];
    float DiffPhase[PER_FFT_SAVE];
    char Name[10];
    float Py; //�й�����(ƽ������)
    float Pf; //��������	  				PF=Py/Ps

} Type_Recognize; //����ʶ��

typedef struct
{
    Type_Recognize *Recognize[LOAD_MAX];
    u16 RecognizeNum;//������
    float Similarity;
    float Py; //�й�����(ƽ������)
    float Pf; //��������	  				PF=Py/Ps
} Type_Recognize_Result; //����ʶ����




/* ���������� ----------------------------------------------------------------*/
typedef union
{
    float _float;
    u32	  _u32;
    u8	  _u8[4];
} Union_32;

typedef union
{
    double _double;
    complex _complex;
    u32	  _u32[2];
    u8	  _u8[8];
} Union_64;



/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ������� --------------------------------------------------------------*/





#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/













