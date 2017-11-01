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
#include "stm32f4xx.h"

/* 全局优先宏定义 ------------------------------------------------------------*/ 
#define MESSAGE_CH_MAX			(2)		//蓝牙通道数
#define LOAD_MAX				(7)		//负载数
#define WORK_STATE				(4)		//每种负载的工作状态

#define PER_POINT				(256)	//每个周期采集的点数
#define PER_T_CNT				(16)	//采集的周期数
#define ADC_LENTH				(PER_POINT*PER_T_CNT)	 
		 
#define UI_MODE_FIRST  	 		1	//初始界面模式
#define OLED_MODE  	 			1	//1 是 OLED显示 0是LCD显示

#define 	MIN_FREQ 	40
#define 	MAX_FREQ 	60


/* 结构体声明 ----------------------------------------------------------------*/ 

typedef struct
{
    float V_Max;
    float V_Min;
    float I_Max;
    float I_Min;
    float Vpp;
    float Ipp;
    float Vrms;
    float Irms;//用电器有效电流 
	float Irms_Sum;//干线有效电流 
    float V_Shift; //直流偏置
    float I_Shift; //直流偏置
	float Irms_Other;
    float Pf; //用电器功率因数	  				Pf=Py/Ps
	float Pf_Sum; //干线功率因数	  				Pf=Py/Ps
    float Ps; //用电器视在功率  				Ps=Vrms*Irms
	float Ps_Sum; //干线功视在功率  				Ps=Vrms*Irms
    float Py; //用电器有功功率(平均功率)  		Py=积分（电压*电流）/常数 
	float Py_Other; 
	float Py_Sum;//干线有功共率
    float Freq; //频率
	float Freq_Sample; //采样频率
    float DiffPhase;//用电器相位角
	float DiffPhase_Sum;//干线相位角
	float Pw;//用电器无功共率
	float Pw_Sum;//干线无功共率  
	float Pw_Other;
	float Others[LOAD_MAX]; 
} Type_ADC_Result; //ADC


typedef struct  //复数类型
{
    float real;		//实部
    float imag;		//虚部
} complex;


typedef struct
{
    char Name;   
	float Py[WORK_STATE+1]; //积分有功功率
	float Phase[WORK_STATE+1]; //积分功率因数角
    u16 Save_State; //存储状态（Save_State |= (0x01 << 2)）表示存储该设备的2状态已有数据
	
} Type_Recognize; //负载识别

typedef struct
{
    float Similarity; //相似度 
    u8 WorkDevice_State[LOAD_MAX];//工作设备状态(WorkDevice_State[0] = 1)表示设备0的状态为1
	
} Type_Recognize_Result; //负载识别结果



/* 联合体声明 ----------------------------------------------------------------*/
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



/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数声明 --------------------------------------------------------------*/





#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/













