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
#include "stm32f4xx.h"

/* ȫ�����Ⱥ궨�� ------------------------------------------------------------*/ 
#define MESSAGE_CH_MAX			(2)		//����ͨ����
#define LOAD_MAX				(7)		//������
#define WORK_STATE				(4)		//ÿ�ָ��صĹ���״̬

#define PER_POINT				(256)	//ÿ�����ڲɼ��ĵ���
#define PER_T_CNT				(16)	//�ɼ���������
#define ADC_LENTH				(PER_POINT*PER_T_CNT)	 
		 
#define UI_MODE_FIRST  	 		1	//��ʼ����ģʽ
#define OLED_MODE  	 			1	//1 �� OLED��ʾ 0��LCD��ʾ

#define 	MIN_FREQ 	40
#define 	MAX_FREQ 	60


/* �ṹ������ ----------------------------------------------------------------*/ 

typedef struct
{
    float V_Max;
    float V_Min;
    float I_Max;
    float I_Min;
    float Vpp;
    float Ipp;
    float Vrms;
    float Irms;//�õ�����Ч���� 
	float Irms_Sum;//������Ч���� 
    float V_Shift; //ֱ��ƫ��
    float I_Shift; //ֱ��ƫ��
	float Irms_Other;
    float Pf; //�õ�����������	  				Pf=Py/Ps
	float Pf_Sum; //���߹�������	  				Pf=Py/Ps
    float Ps; //�õ������ڹ���  				Ps=Vrms*Irms
	float Ps_Sum; //���߹����ڹ���  				Ps=Vrms*Irms
    float Py; //�õ����й�����(ƽ������)  		Py=���֣���ѹ*������/���� 
	float Py_Other; 
	float Py_Sum;//�����й�����
    float Freq; //Ƶ��
	float Freq_Sample; //����Ƶ��
    float DiffPhase;//�õ�����λ��
	float DiffPhase_Sum;//������λ��
	float Pw;//�õ����޹�����
	float Pw_Sum;//�����޹�����  
	float Pw_Other;
	float Others[LOAD_MAX]; 
} Type_ADC_Result; //ADC


typedef struct  //��������
{
    float real;		//ʵ��
    float imag;		//�鲿
} complex;


typedef struct
{
    char Name;   
	float Py[WORK_STATE+1]; //�����й�����
	float Phase[WORK_STATE+1]; //���ֹ���������
    u16 Save_State; //�洢״̬��Save_State |= (0x01 << 2)����ʾ�洢���豸��2״̬��������
	
} Type_Recognize; //����ʶ��

typedef struct
{
    float Similarity; //���ƶ� 
    u8 WorkDevice_State[LOAD_MAX];//�����豸״̬(WorkDevice_State[0] = 1)��ʾ�豸0��״̬Ϊ1
	
} Type_Recognize_Result; //����ʶ����



/* ���������� ----------------------------------------------------------------*/
typedef union
{
    float _float;
    u32	  _u32;
	u16	  _u16[2];
    u8	  _u8[4];
} Union_32;

typedef union
{
    double _double;
    complex _complex;
	u16	  _u16[4];
    u32	  _u32[2];
    u8	  _u8[8];
} Union_64;



/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ������� --------------------------------------------------------------*/





#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/













