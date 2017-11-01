/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_Bluetooth.c
* @Description : None
* @Date        : 2017��8��5��
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ��������
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Bluetooth.h"


/* ˽�к궨�� ----------------------------------------------------------------*/
#define BLUETOOTH_DISCONECT		 PBout(12)
const char *BluetoothMac[MESSAGE_CH_MAX] = 
{
	"884AEA964791",//5��
	"884AEA964968"//8��
//"884AEA964797",//3��
//"884AEA8F3B4A",//4��
};
	
/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Bluetooth_Init(void)
* @Description   : ��������
* @Data          : 2017��8��5��
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
	USART_Str_Send(USART3,(u8*)"884AEA964791"); //5��
//	USART_Str_Send(USART3,(u8*)"884AEA964968"); //8��
	USART_Str_Send(USART3,(u8*)"\r\n");   
	
    return 0;
}	




/**----------------------------------------------------------------------------
* @FunctionName  : Bluetooth_Disconect(void)
* @Description   : �����Ͽ�����
* @Data          : 2017��8��5��
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
* @Description   : ��������
* @Data          : 2017��8��5��
* @Explain       : ch ���� 0��ʼ
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







