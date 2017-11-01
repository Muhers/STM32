/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Touch.h
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_TOUCH_H
#define __DRIVE_TOUCH_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "OS_StartFile.h" 

/* 全局宏定义 ----------------------------------------------------------------*/
#define TOUCH_BUFF_SIZE  		100
#define TOUCH_COLOR			DARKBLUE         
#define TOUCH_SCAN_SPEED 		20  //扫描速度
#define TOUCH_SLIP_RESPONSE 	((OS_LCD_WHITH+OS_LCD_LENTH)/10) //滑动响应点数


#define TOUCH_SLIP_NULL  	 0x00 //没有滑动	
#define TOUCH_SLIP_LEFT		(0x01<<0) //左滑	
#define TOUCH_SLIP_RIGHT	(0x01<<1) //右滑	
#define TOUCH_SLIP_UP  		(0x01<<2) //上滑	
#define TOUCH_SLIP_DOWN  	(0x01<<3) //下滑	
   
   
#define TOUCH_STATE_OFF 	0   //触屏空闲	
#define TOUCH_STATE_ON 		1   //正在触屏	
#define TOUCH_STATE_SLIP	2   //正在滑屏	



/* 结构体声明 ----------------------------------------------------------------*/ 
typedef struct _struct_Touch
{ 
	/* 实时数据 (即时) ----------------------------------*/
	u16 _X; //当前x坐标(即时)
	u16 _Y; //当前y坐标 
	u16 _BuffX[TOUCH_BUFF_SIZE]; //历史坐标(即时) 
	u16 _BuffY[TOUCH_BUFF_SIZE]; //历史坐标 
	u8  _CNT; //历史记录数	
	u8  _State; //触屏状态	
	u8 _SlipDirection; //滑动的方向
  	
	/* 历史数据 (需要手动清除) --------------------------*/	
	u16 _LastX; //上一次x坐标（需要手动清除）
	u16 _LastY; //上一次y坐标
	u16 _LastBuffX[TOUCH_BUFF_SIZE]; //历史坐标(需要手动清除)	
	u16 _LastBuffY[TOUCH_BUFF_SIZE]; //历史坐标  
	u8  _LastCNT; //历史记录数 
	u8  _LastState; //触屏状态	 
	u8  _LastSlipDirection; //滑动过的方向 
	
}Type_Touch;

/* 全局变量声明 --------------------------------------------------------------*/ 
extern Type_Touch TouchPoint;
extern Type_AppList Drive_TouchScan;

/* 全局函数声明 --------------------------------------------------------------*/  
int Drive_Touch_Init(void);

#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



