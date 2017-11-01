/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸) *********************************/
/**============================================================================
* @FileName    : Drive_WindCar_Control.h
* @Description : None
* @Date        : 2017年7月10日
* @By          : Wind(谢玉伸)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 风力平衡车控制
*=============================================================================*/
/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_WINDCAR_CONTROL_H
#define __DRIVE_WINDCAR_CONTROL_H

/* 头文件包含 ----------------------------------------------------------------*/
#include "User_Library.h"


/* 全局宏定义 ----------------------------------------------------------------*/
#define FILTRATE_DEEP	20
#define FILTRATE_LEFT	(0.3f)
#define FILTRATE_RIGHT	(0.7f)

/* 结构体声明 ----------------------------------------------------------------*/

/* 全局变量声明 --------------------------------------------------------------*/ 
extern double _kP; //比例放大系数
extern double _kI; //积分放大系数
extern double _kD; //微分放大系数
extern double _u0;  //基值
extern double _eT; //误差
extern int PWM_Pre; 
extern int PWM_Back; 

/* 全局函数声明 --------------------------------------------------------------*/
int WindCar_Control_Init(void);
int PID_Control(void);









#endif
/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸) *********************************/







