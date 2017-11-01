/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_Bluetooth.c
* @Description : None
* @Date        : 2017��8��5��
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F103RC)
* @Explain     : ��������
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Bluetooth.h"


/* ˽�к궨�� ----------------------------------------------------------------*/
#define BLUETOOTH_DISCONECT		 PBout(1)

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
//    GPIO_InitTypeDef  GPIO_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //�˿�����, �������
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //������� 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
//    GPIO_ResetBits(GPIOB, GPIO_Pin_0); 						 // 
//	BLUETOOTH_DISCONECT = 1;
	
//	Bluetooth_Disconect();//�Ͽ�����
	
	Usart2_Init(115200);	
	
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
    return 0;
}	








/*******************************(C) COPYRIGHT 2017 None *********************************/







