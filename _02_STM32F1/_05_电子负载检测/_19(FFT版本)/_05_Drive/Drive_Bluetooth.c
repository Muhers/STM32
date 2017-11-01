/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_Bluetooth.c
* @Description : None
* @Date        : 2017年8月5日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F103RC)
* @Explain     : 蓝牙驱动
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Bluetooth.h"


/* 私有宏定义 ----------------------------------------------------------------*/
#define BLUETOOTH_DISCONECT		 PBout(1)

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Bluetooth_Init(void)
* @Description   : 蓝牙驱动
* @Data          : 2017年8月5日
* @Explain       : None
------------------------------------------------------------------------------*/
int Bluetooth_Init(void)
{  
//    GPIO_InitTypeDef  GPIO_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //端口配置, 推挽输出
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
//    GPIO_ResetBits(GPIOB, GPIO_Pin_0); 						 // 
//	BLUETOOTH_DISCONECT = 1;
	
//	Bluetooth_Disconect();//断开蓝牙
	
	Usart2_Init(115200);	
	
    return 0;
}	



/**----------------------------------------------------------------------------
* @FunctionName  : Bluetooth_Disconect(void)
* @Description   : 蓝牙断开连接
* @Data          : 2017年8月5日
* @Explain       : None
------------------------------------------------------------------------------*/
int Bluetooth_Disconect(void)
{   
	BLUETOOTH_DISCONECT = 0;	
	OSdelay_ms(85);	
	BLUETOOTH_DISCONECT = 1;	
    return 0;
}	








/*******************************(C) COPYRIGHT 2017 None *********************************/







