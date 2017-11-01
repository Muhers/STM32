/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_SmallCar.h
* @Description : None
* @Date        : 2016/7/23
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_SMALLCAR_H
#define __DRIVE_SMALLCAR_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Library.h"   
#include "my_pwm.h"		
#include "adc.h"
#include "My_Tim.h"	

/* �ṹ������ ----------------------------------------------------------------*/  	
typedef struct  
{  		 
	 int LeftSpeed;
	 int RightSpeed; 
	 u16 Channel[CHANNEL_NUM][CHANNEL_LENTH];
	 u8  Channel_Flag;
	 
	 u8  LastEvent[100];//��¼�����ʱ�� 
	 
	 u8  LastChannelEvent[100]; 
	 u16 Cnt;
	 
	 
}Type_SmallCar; //�������		
						 
/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern Type_SmallCar SmallCar;

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void SmallCar_Init(void);
void SmallCar_Right_Control(int Speed);
void SmallCar_Left_Control(int Speed);






#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/






















