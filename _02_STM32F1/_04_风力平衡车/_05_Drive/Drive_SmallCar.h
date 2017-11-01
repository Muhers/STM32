/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/
/**============================================================================
* @FileName    : Drive_SmallCar.h
* @Description : None
* @Date        : 2016/7/23

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
	 u16 Channel[CHANNEL_LENTH][CHANNEL_NUM];
	 u8  Channel_Flag;
	 
	 u8  LastEvent[100];//��¼�����ʱ�� 
	 
	 u8  LastChannelEvent[100]; 
	 u16 Cnt;
	 u16 Thiska_flag;
	 u16 Lastka_flag;
	 u8 fuck_flag;
	 
}Type_SmallCar; //�������		
						 
/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern Type_SmallCar SmallCar;

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void SmallCar_Init(void);
void SmallCar_Behind_Control(int Speed);
void SmallCar_Front_Control(int Speed);
void SmallCar_Right_Control(int Speed);//ǰ������ٿ���
void SmallCar_Left_Control(int Speed);//ǰ������ٿ���






#endif
/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/






















