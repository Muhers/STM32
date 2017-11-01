/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_Bluetooth.c
* @Description : None
* @Date        : 2017年8月5日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 蓝牙驱动
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Bluetooth.h"


/* 私有宏定义 ----------------------------------------------------------------*/
#define BLUETOOTH_DISCONECT		 PBout(12)
const char *BluetoothMac[MESSAGE_CH_MAX] = 
{
	"884AEA964791",//5号
	"884AEA964968"//8号
//"884AEA964797",//3号
//"884AEA8F3B4A",//4号
};
	
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
//	GPIO_InitTypeDef GPIO_InitStructure; 
//	
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//	GPIO_Init(GPIOB,&GPIO_InitStructure); 
//	BLUETOOTH_DISCONECT = 1; 
	
	Usart3_Init(115200);	  
	USART_Str_Send(USART3,(u8*)"AT+SPPCONN="); 
	USART_Str_Send(USART3,(u8*)"884AEA964791"); //5号
//	USART_Str_Send(USART3,(u8*)"884AEA964968"); //8号
	USART_Str_Send(USART3,(u8*)"\r\n");   
	
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
	OSdelay_ms(900);		
    return 0;
}	


/**----------------------------------------------------------------------------
* @FunctionName  : Bluetooth_Conect()
* @Description   : 蓝牙连接
* @Data          : 2017年8月5日
* @Explain       : ch 机号 0开始
------------------------------------------------------------------------------*/
int Bluetooth_Conect(u16 ch)
{    
	if(ch > MESSAGE_CH_MAX -1) ch = ch%MESSAGE_CH_MAX;   
//	USART_Str_Send(BLUETOOTH_USARTX,(u8*)"AT+RESTORE\r\n"); OSdelay_ms(100);	
//	USART_Str_Send(BLUETOOTH_USARTX,(u8*)"AT+SCAN=1\r\n"); OSdelay_ms(3000);	
	USART_Str_Send(USART3,(u8*)"AT+SPPCONN="); 
	USART_Str_Send(USART3,(u8*)BluetoothMac[ch]); 
	USART_Str_Send(USART3,(u8*)"\r\n");   
	OSdelay_ms(100);	
    return 0;
}	





/*******************************(C) COPYRIGHT 2017 None *********************************/







