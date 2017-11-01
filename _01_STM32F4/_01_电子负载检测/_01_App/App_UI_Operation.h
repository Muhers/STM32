/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/
/**============================================================================
* @FileName    : App_UI_Operation.h
* @Description : None
* @Date        : 2017��8��8��
* @By          : Wind(л����)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : �û���������
*=============================================================================*/
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __APP_UI_OPERATION_H
#define __APP_UI_OPERATION_H

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
#define UI_ORDER_FLASH_WRITE 		(0x01 << 0) //Flashд��
#define UI_ORDER_FLASH_READ 		(0x01 << 1) //Flash��ȡ
#define UI_ORDER_FLASH_ERASE 		(0x01 << 2)	//Flash����
#define UI_ORDER_FLASH_LEARN		(0x01 << 3)	//ѧϰ


/* �ṹ������ ----------------------------------------------------------------*/
typedef struct 
{  		     
	int Po_x; //����
	int Po_y; //����
	u16 UI_Mode;//ѡ�����
	u16 Order; //ָ�� 
	u8 Busy; //æµ
}Type_UI_Operat; //ADC

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern Type_UI_Operat UI_Operat;

/* ȫ�ֺ������� --------------------------------------------------------------*/
extern Type_AppList App_UI_Operation;


extern u16 Recognize_Mode;








#endif
/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/







