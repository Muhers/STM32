/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_VirtualKeyBoard.h
* @Description : None
* @Date        : 2016/8/22
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __APP_VIRTUALKEYBOARD_H
#define __APP_VIRTUALKEYBOARD_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h" 

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
 		 							
/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct 
{  		  
	u16 x1;
	u16 y1;
	u16 x2;
	u16 y2;
	u16 TextColor;
	u16 BackColor;
	u8 State;//��ǰ״̬
	u8 LastState;//�б仯��״̬
	u8 Used; 
	u8 Updata;//���ݸ���
}Type_VKBoard; //����	
				
				

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern u8 VKBoard_Aa;//��Сд 
extern u8 VKBoard_ResultCh[MESSAGE_LENTH];//���
extern u8 VKBoard_Cnt;

/* ȫ�ֺ������� --------------------------------------------------------------*/  
extern Type_AppList App_VirtualKeyBoard;
void VK_Buff_Clear(void);
void VirtualKey_FullShow(u8 Mode);


#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



