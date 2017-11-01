/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/
/**============================================================================
* @FileName    : Drive_SmallCar.h
* @Description : None
* @Date        : 2016/7/23

*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_SMALLCAR_H
#define __DRIVE_SMALLCAR_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h"   
#include "my_pwm.h"		
#include "adc.h"
#include "My_Tim.h"	

/* 结构体声明 ----------------------------------------------------------------*/  	
typedef struct  
{  		 
	 int LeftSpeed;
	 int RightSpeed; 
	 u16 Channel[CHANNEL_LENTH][CHANNEL_NUM];
	 u8  Channel_Flag;
	 
	 u8  LastEvent[100];//记录最近的时间 
	 
	 u8  LastChannelEvent[100]; 
	 u16 Cnt;
	 u16 Thiska_flag;
	 u16 Lastka_flag;
	 u8 fuck_flag;
	 
}Type_SmallCar; //任务队列		
						 
/* 全局变量声明 --------------------------------------------------------------*/ 
extern Type_SmallCar SmallCar;

/* 全局函数声明 --------------------------------------------------------------*/  
void SmallCar_Init(void);
void SmallCar_Behind_Control(int Speed);
void SmallCar_Front_Control(int Speed);
void SmallCar_Right_Control(int Speed);//前电机风速控制
void SmallCar_Left_Control(int Speed);//前电机风速控制






#endif
/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/






















