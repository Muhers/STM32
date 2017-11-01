/*******************************(C) COPYRIGHT 2016 *********************************/
/**============================================================================

*=============================================================================*/ 
							
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __APP_SMALLCAR_H
#define __APP_SMALLCAR_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h" 
/* 全局宏定义 ----------------------------------------------------------------*/
 		 							
/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 
void Wind_Balance_PID(float Angle,float Gyro,int Feedback); //平衡PID
int Wind_Turn_PID(int encoder_left,int encoder_right,float gyro);//转向PID
 
void Balance_Control(float Angle_,float Gyro_B,  int Feedback);//平衡控制
int SmallCar_Tracking(void);//转向循迹控制


/* 全局函数声明 --------------------------------------------------------------*/  
extern Type_AppList App_SmallCar_ChannelScan; 

extern u8 Blance_GetData_Flag;
extern u8 Tracking_Open_Flag;
extern u8 Stop_Moto;
extern u16 Base_Seed;
#endif
/*******************************(C) COPYRIGHT *********************************/


