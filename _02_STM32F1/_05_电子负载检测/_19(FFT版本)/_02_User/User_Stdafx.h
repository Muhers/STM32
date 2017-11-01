/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : User_Stdafx.h
* @Description : None
* @Date        : 2017/8/6
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : 结构体 联合体存放文件
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __USER_STDAFX_H
#define __USER_STDAFX_H

/* 头文件包含 ----------------------------------------------------------------*/
#include "stm32f10x.h"

/* 全局优先宏定义 ------------------------------------------------------------*/
#define PER_FFT_SAVE			(8)		//保存谐波的周期数
#define MESSAGE_CH_MAX			(2)			//蓝牙通道数
#define LOAD_MAX				(7)			//负载数 


/* 结构体声明 ----------------------------------------------------------------*/
typedef struct
{
    float DiffPhase[PER_FFT_SAVE]; //各谐波相位差
    float Py[PER_FFT_SAVE]; //各谐波有功功率

    float All_DiffPhase;//总相位				
    float All_Pf; //功率因数	  				Pf=Py/Ps 
    float All_Py; //有功功率(平均功率)  		Py=积分（电压*电流）/常数
	
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
    float V_Shift; //直流偏置
    float I_Shift; //直流偏置 
    float Pf; //功率因数	  				Pf=Py/Ps
    float Ps; //视在功率  				Ps=Vrms*Irms
    float Py; //有功功率(平均功率)  		Py=积分（电压*电流）/常数
    float Freq; //频率
    float DiffPhase;//总相位
} Type_ADC_Result; //ADC


typedef struct  //复数类型
{
    float real;		//实部
    float imag;		//虚部
} complex;

typedef struct
{
    float Vpp[PER_FFT_SAVE];
    float Ipp[PER_FFT_SAVE];
    float DiffPhase[PER_FFT_SAVE];
    char Name[10];
    float Py; //有功功率(平均功率)
    float Pf; //功率因数	  				PF=Py/Ps

} Type_Recognize; //负载识别

typedef struct
{
    Type_Recognize *Recognize[LOAD_MAX];
    u16 RecognizeNum;//负载数
    float Similarity;
    float Py; //有功功率(平均功率)
    float Pf; //功率因数	  				PF=Py/Ps
} Type_Recognize_Result; //负载识别结果




/* 联合体声明 ----------------------------------------------------------------*/
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



/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数声明 --------------------------------------------------------------*/





#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/













