
/* 头文件包含 ----------------------------------------------------------------*/

#include "App_SmallCar.h"
#include "math.h"
#include "userPID.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
Type_AppList App_SmallCar_ChannelScan;


/* 全局变量声明 --------------------------------------------------------------*/
u8 Blance_GetData_Flag=0;           //角度获取标志位
u8 Stop_Moto = 0;                   //电机开关(0打开1关闭)
u16 Base_Seed=500;                  //基础速度值
u8 State_flag = 0;                  //用于上位机控制电机开关
u8 Tracking_Open_Flag=0;            //循迹开关(0关闭循迹保留平衡 1打开循迹)

/* 全局函数编写 --------------------------------------------------------------*/
float BB_BasisValue = -100;//max:2400	


/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar()
* @Description   : 通道扫描高速
* @Data          : 2016/8/8
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int SmallCar_BalanceScan_Main(void)
{ 
    int Feedback_Value;
    Revise_PID();                                               //上位机修改PID参数
    
    if(Tracking_Open_Flag==1)
        Feedback_Value=SmallCar_Tracking();                     //循迹控制
    else
        Feedback_Value=0;                                       
    Balance_Control(Angle_Balance,Gyro_Balance,Feedback_Value); //平衡控制
    
    if(KEY==0)                                                  //电机开关
    { 
        Stop_Moto=~Stop_Moto;
        OSdelay_ms(990);
    }        
    return 0;	
	
	
}

static Type_AppList App_SmallCar_ChannelScan = {SmallCar_BalanceScan_Main, NULL, NULL, NULL, \
												OS_STATE_ACTIVE, OS_THREAD_SYSTEM, \
												(u8 *)"SmallCar_ChannelScan", 3
												};
	

/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/




