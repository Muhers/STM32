/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸)*********************************/
/**============================================================================
* @FileName    : App_UI_Operation.c
* @Date        : 2017年8月8日
* @By          : Wind(谢玉伸)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 用户操作界面
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_UI_Operation.h"


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 
Type_UI_Operat UI_Operat = {0};
u16 Recognize_Mode = 0;

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : UI_Operation()
* @Description   : 用户操作界面
* @Data          : 2017年8月8日
* @Explain       : None
------------------------------------------------------------------------------*/
int UI_Operation_Main(void)
{    
	UI_Operat.Busy = 1;
	
	if(Key_Now_Get(FUNC1,KEY_MODE_LONG))
	{ 
		UI_Operat.UI_Mode = 1;
		OS_LCD_Clear(BLACK);//清屏 
	}
	else if(Key_Now_Get(FUNC2,KEY_MODE_LONG))
	{ 
		UI_Operat.UI_Mode = 2;
		OS_LCD_Clear(BLACK);//清屏 
	} 
	else if(Key_Now_Get(FERASE, KEY_MODE_LONG)) //清空数据
    {  
		UI_Operat.Order |= UI_ORDER_FLASH_ERASE;  
    }
	
	
	if(Key_Get(LEFT, KEY_MODE_SHORT)) //左移
    {
        UI_Operat.Po_x --; 
    }
    else if(Key_Get(RIGHT, KEY_MODE_SHORT)) //右移
    {
        UI_Operat.Po_x ++; 
    }
	else if(Key_Get(UP, KEY_MODE_SHORT)) //上移
    {  
		 UI_Operat.Po_y --; 
    }
	else if(Key_Get(DOWN, KEY_MODE_SHORT))//下移
    {  
		 UI_Operat.Po_y ++; 
    } 
    else if(Key_Get(LEARN, KEY_MODE_SHORT)) //学习
    { 
		UI_Operat.Order |= UI_ORDER_FLASH_LEARN; 
    } 
		if(Key_Get(FSAVE, KEY_MODE_SHORT)) //保存到Flash
    {  
		UI_Operat.Order |= UI_ORDER_FLASH_WRITE;  
    }
	else if(Key_Get(FREAD, KEY_MODE_SHORT)) //读取Flash的数据
    {  
		UI_Operat.Order |= UI_ORDER_FLASH_READ;  
    }
	else if(Key_Get(FUNC1, KEY_MODE_SHORT)) //只识别有功功率
    {  
		Recognize_Mode = 0;	
		LED2 = 1;
    } 
	else if(Key_Get(FUNC2, KEY_MODE_SHORT)) //全识别
    {  
		Recognize_Mode = 1;		
		LED2 = 0;
    }	
	
	UI_Operat.Busy = 0;
	
	//限制位置
	if(UI_Operat.Po_x < 0) UI_Operat.Po_x = LOAD_MAX - 1;
    else if(UI_Operat.Po_x > LOAD_MAX - 1) UI_Operat.Po_x = 0;
	
	if(UI_Operat.Po_y < 0) UI_Operat.Po_y = WORK_STATE - 1;
    else if(UI_Operat.Po_y > WORK_STATE - 1) UI_Operat.Po_y = 0;
	
	Key_Clear(KEY_MODE_SHORT);//清除按键记录  
    return 0;
}	

int UI_Operation_Start(void)
{   
	OSTask_Creat(&App_Key);  //启用按键
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









/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸)*********************************/







