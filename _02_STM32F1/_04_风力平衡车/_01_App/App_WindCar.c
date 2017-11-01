/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_WindCar.c
* @Description : None
* @Date        : 2017年7月10日
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 平衡风力小车
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_WindCar.h"


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : App_WindCar()
* @Description   : 平衡风力小车
* @Data          : 2017年7月10日
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int App_WindCar_Main(void)
{    
	char StrBuff[100] = {0};  
	 
	sprintf(StrBuff,"Ang:[%0.2f]%% ",Angle_Balance);
	OS_String_Show(0,0,(u8*)StrBuff); 
	
	sprintf(StrBuff,"Pre:[%0.0f]  ",(float)PWM_Pre);
	OS_String_Show(0,1,(u8*)StrBuff); 
	
	sprintf(StrBuff,"Back:[%0.0f]  ",(float)PWM_Back);
	OS_String_Show(0,2,(u8*)StrBuff); 
	
	sprintf(StrBuff,"电压:[%0.2f]V  ",(float)Get_Adc2_Average(0,10)/4096*3.3*3.4-0.1);
	OS_String_Show(0,3,(u8*)StrBuff); 
	
	  
    return 0;
}	

unsigned int App_WindCar_Start(void)
{   
	OSTask_Creat(&App_WindCar_Control);
//	printf("风力小车已经启动！！！\n");
//	printf("风力小车已经启动！！！\n");
//	printf("风力小车已经启动！！！\n");
	
    return 0;
}	

Type_AppList App_WindCar = {App_WindCar_Main,NULL,App_WindCar_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_FREE, \
						(u8*)"App_WindCar",10};












/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/







