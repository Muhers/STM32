/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_emWinTest.c
* @Description : None
* @Date        : 2017/2/20
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_emWinTest.h"   
#include "DIALOG.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/
void numdisplay_demo(u16 x,u16 y);
extern WM_HWIN CreateFramewin(void);
extern WM_HWIN CreateWindow(void);

/* 全局变量定义 --------------------------------------------------------------*/  

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : emWinTest()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
void emWinTest(void *p_arg)		
{       
	u16 cnt = 0;
	WM_HWIN hWin_Window; 
	WM_HWIN hWin_Framewin; 
	WM_HWIN hItem;
	
	GUI_CURSOR_Show();  
	
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX); 
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX); 
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX); 
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);    
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	 
	hWin_Window = CreateWindow();
	hWin_Framewin = CreateFramewin(); 
	
	hItem = WM_GetDialogItem(hWin_Framewin, GUI_ID_USER + 0x12);
	
	p_arg = p_arg; 
	while(1)
	{   
		GUI_Delay(100);  
		PROGBAR_SetValue(hItem,cnt++);	
		 
	}
	
}	

/* App 注册 -----------------------------*/ 
#define  APP_STK_SIZE 		2048  //任务堆栈大小	 
static OS_TCB	 APP_TaskTCB;
static CPU_STK	 APP_STK[APP_STK_SIZE]; 

OS_Struct App_emWinTest =
{
	emWinTest, "emWinTest", 7,
	&APP_TaskTCB, APP_STK,
	APP_STK_SIZE, APP_STK_SIZE/10,
	0,0,NULL,NULL,OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR 
};														
																				
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/

 

