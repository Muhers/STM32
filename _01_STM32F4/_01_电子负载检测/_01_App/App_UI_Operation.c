/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/
/**============================================================================
* @FileName    : App_UI_Operation.c
* @Date        : 2017��8��8��
* @By          : Wind(л����)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : �û���������
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_UI_Operation.h"


/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
Type_UI_Operat UI_Operat = {0};
u16 Recognize_Mode = 0;

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : UI_Operation()
* @Description   : �û���������
* @Data          : 2017��8��8��
* @Explain       : None
------------------------------------------------------------------------------*/
int UI_Operation_Main(void)
{    
	UI_Operat.Busy = 1;
	
	if(Key_Now_Get(FUNC1,KEY_MODE_LONG))
	{ 
		UI_Operat.UI_Mode = 1;
		OS_LCD_Clear(BLACK);//���� 
	}
	else if(Key_Now_Get(FUNC2,KEY_MODE_LONG))
	{ 
		UI_Operat.UI_Mode = 2;
		OS_LCD_Clear(BLACK);//���� 
	} 
	else if(Key_Now_Get(FERASE, KEY_MODE_LONG)) //�������
    {  
		UI_Operat.Order |= UI_ORDER_FLASH_ERASE;  
    }
	
	
	if(Key_Get(LEFT, KEY_MODE_SHORT)) //����
    {
        UI_Operat.Po_x --; 
    }
    else if(Key_Get(RIGHT, KEY_MODE_SHORT)) //����
    {
        UI_Operat.Po_x ++; 
    }
	else if(Key_Get(UP, KEY_MODE_SHORT)) //����
    {  
		 UI_Operat.Po_y --; 
    }
	else if(Key_Get(DOWN, KEY_MODE_SHORT))//����
    {  
		 UI_Operat.Po_y ++; 
    } 
    else if(Key_Get(LEARN, KEY_MODE_SHORT)) //ѧϰ
    { 
		UI_Operat.Order |= UI_ORDER_FLASH_LEARN; 
    } 
		if(Key_Get(FSAVE, KEY_MODE_SHORT)) //���浽Flash
    {  
		UI_Operat.Order |= UI_ORDER_FLASH_WRITE;  
    }
	else if(Key_Get(FREAD, KEY_MODE_SHORT)) //��ȡFlash������
    {  
		UI_Operat.Order |= UI_ORDER_FLASH_READ;  
    }
	else if(Key_Get(FUNC1, KEY_MODE_SHORT)) //ֻʶ���й�����
    {  
		Recognize_Mode = 0;	
		LED2 = 1;
    } 
	else if(Key_Get(FUNC2, KEY_MODE_SHORT)) //ȫʶ��
    {  
		Recognize_Mode = 1;		
		LED2 = 0;
    }	
	
	UI_Operat.Busy = 0;
	
	//����λ��
	if(UI_Operat.Po_x < 0) UI_Operat.Po_x = LOAD_MAX - 1;
    else if(UI_Operat.Po_x > LOAD_MAX - 1) UI_Operat.Po_x = 0;
	
	if(UI_Operat.Po_y < 0) UI_Operat.Po_y = WORK_STATE - 1;
    else if(UI_Operat.Po_y > WORK_STATE - 1) UI_Operat.Po_y = 0;
	
	Key_Clear(KEY_MODE_SHORT);//���������¼  
    return 0;
}	

int UI_Operation_Start(void)
{   
	OSTask_Creat(&App_Key);  //���ð���
	UI_Operat.UI_Mode = UI_MODE_FIRST;
	
//	OS_TextColor_Set(RED);
//    OS_String_Show(630, 5 + FONT1 * 0, FONT1, 1, "PB10 - TX");
//	OS_String_Show(630, 5 + FONT1 * 1, FONT1, 1, "PB11 - RX");
//    OS_String_Show(630, 5 + FONT1 * 2, FONT1, 1, "PB12 - DISCONECT");
	
    return 0;
}	

Type_AppList App_UI_Operation = {UI_Operation_Main,NULL,UI_Operation_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_SYSTEM, \
						(u8*)"UI_Operation",100};









/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/







