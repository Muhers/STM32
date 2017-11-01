/*******************************(C) COPYRIGHT 2016 *********************************/
/**============================================================================

*=============================================================================*/ 
							
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __APP_SMALLCAR_H
#define __APP_SMALLCAR_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Library.h" 
/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
 		 							
/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
void Wind_Balance_PID(float Angle,float Gyro,int Feedback); //ƽ��PID
int Wind_Turn_PID(int encoder_left,int encoder_right,float gyro);//ת��PID
 
void Balance_Control(float Angle_,float Gyro_B,  int Feedback);//ƽ�����
int SmallCar_Tracking(void);//ת��ѭ������


/* ȫ�ֺ������� --------------------------------------------------------------*/  
extern Type_AppList App_SmallCar_ChannelScan; 

extern u8 Blance_GetData_Flag;
extern u8 Tracking_Open_Flag;
extern u8 Stop_Moto;
extern u16 Base_Seed;
#endif
/*******************************(C) COPYRIGHT *********************************/


