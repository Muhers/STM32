/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Run.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_StartFile.h"
																		
/* 私有宏定义 ----------------------------------------------------------------*/
											
/* 私有（静态）函数声明 ------------------------------------------------------*/
										
/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/	
 
/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_Free()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : 空闲线程
------------------------------------------------------------------------------*/
void OSThread_Free(void)
{ 
 	Type_AppList *AppRun = &AppHead; 
	unsigned int _BackColor,_TextColor; 
	 
	while(1)
	{   
		if(OS_Msg & OS_BREAK) continue;
		if(AppRun ->next == NULL) AppRun = &AppHead;  
		else 
		{
			AppRun = AppRun ->next;   		
			if(AppRun ->thread != OS_THREAD_FREE) continue; 
			if(AppRun ->loading != 0 )  AppRun ->loading --;
			if(AppRun ->loading == 0 ) 
			{ 
				_TextColor = TextColor;//记录该区的颜色 
				_BackColor = BackColor;	
				
				if(AppRun ->state == OS_STATE_SUSPEND) //挂起
				{ 
					if(AppRun ->AppEnd != NULL) AppRun ->AppEnd();  
					AppRun ->state = OS_STATE_SUSPEND_ON; 	
					AppRun ->loading = AppRun ->reload;	
				}
				else if(AppRun ->state == OS_STATE_SUSPEND_ON)//运行已经挂起的后台程序
				{
					if(AppRun ->AppBack != NULL) AppRun ->AppBack();//运行后台程序
					AppRun ->loading = AppRun ->reload;	
				}	
				else if(AppRun ->state == OS_STATE_ACTIVE) //激活   
				{ 
					if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //运行启动程序  
					AppRun ->state = OS_STATE_ACTIVE_ON; 	
					AppRun ->loading = AppRun ->reload;	
				}					
				else if(AppRun ->state == OS_STATE_ONE_OFF) //一次性的程序  
				{ 				
					if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序  
					AppRun ->state = OS_STATE_CLOSE_ON;  
					AppRun ->loading = AppRun ->reload;	
				} 
				else if(AppRun ->state == OS_STATE_CLOSE)
				{ 
					if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//运行结束程序
					AppRun ->state = OS_STATE_CLOSE_ON;
					AppRun ->loading = AppRun ->reload;	
				}
				else if(AppRun ->state == OS_STATE_ACTIVE_ON)//运行已经激活的主程序
				{
					if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 
					AppRun ->loading = AppRun ->reload;	
				}	
				
					
				OS_TextColor_Set(_TextColor);//还原原来的颜色
				OS_BackColor_Set(_BackColor);	
			} 
			 
		} 
		  
	} 
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_6()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : 主线程（线程6）
------------------------------------------------------------------------------*/
void OSThread_6(void)
{   
	Type_AppList *AppRun = &AppHead;  
	unsigned int _BackColor,_TextColor; 
	if(OS_Msg & OS_BREAK) return;
	
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_6) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;   
		else 
		{
			_TextColor = TextColor;//记录该区的颜色 	
			_BackColor = BackColor;
			
			if(AppRun ->state == OS_STATE_SUSPEND) //挂起
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 
				AppRun ->state = OS_STATE_SUSPEND_ON; 	
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_SUSPEND_ON)//运行已经挂起的后台程序
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//运行后台程序
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_ACTIVE) //激活   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //运行启动程序  
				AppRun ->state = OS_STATE_ACTIVE_ON; 	
				AppRun ->loading = AppRun ->reload;	
			}					
			else if(AppRun ->state == OS_STATE_ONE_OFF) //一次性的程序  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序程序   	
				AppRun ->state = OS_STATE_CLOSE_ON;  	
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)	
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//运行结束程序	
				AppRun ->state = OS_STATE_CLOSE_ON;	
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_ACTIVE_ON)//运行已经激活的主程序		
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 	
				AppRun ->loading = AppRun ->reload;					
			}
			
			 OS_TextColor_Set(_TextColor); //还原原来的颜色		
			 OS_BackColor_Set(_BackColor);									
		}
			   
	} 
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_4()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : 系统线程（线程4）
------------------------------------------------------------------------------*/
void OSThread_4(void)
{
	Type_AppList *AppRun = &AppHead;  
	unsigned int _BackColor,_TextColor;  
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_4) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;     
		else
		{
			_TextColor = TextColor;//记录该区的颜色 
			_BackColor = BackColor;	
			
			if(AppRun ->state == OS_STATE_SUSPEND) //挂起
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 
				AppRun ->state = OS_STATE_SUSPEND_ON; 	
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_SUSPEND_ON)//运行已经挂起的后台程序
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//运行后台程序
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_ACTIVE) //激活   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //运行启动程序  
				AppRun ->state = OS_STATE_ACTIVE_ON; 	
				AppRun ->loading = AppRun ->reload;	
			}					
			else if(AppRun ->state == OS_STATE_ONE_OFF) //一次性的程序  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序程序   
				AppRun ->state = OS_STATE_CLOSE_ON;  
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//运行结束程序
				AppRun ->state = OS_STATE_CLOSE_ON;
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_ACTIVE_ON)//运行已经激活的主程序
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 
				AppRun ->loading = AppRun ->reload;	
			}		
						
			OS_TextColor_Set(_TextColor); //还原原来的颜色
			OS_BackColor_Set(_BackColor);						
		}
			   
	} 
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_7()     
* @Description   : None 
* @Data          : 2016/4/19
* @Explain       : 线程3（低于系统线程）
------------------------------------------------------------------------------*/
void OSThread_7(void)
{
	Type_AppList *AppRun = &AppHead;  
	unsigned int _BackColor,_TextColor;  
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_7) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;     
		else
		{
			_TextColor = TextColor;//记录该区的颜色 
			_BackColor = BackColor;	
			
			if(AppRun ->state == OS_STATE_SUSPEND) //挂起
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 
				AppRun ->state = OS_STATE_SUSPEND_ON; 	
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_SUSPEND_ON)//运行已经挂起的后台程序
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//运行后台程序
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_ACTIVE) //激活   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //运行启动程序  
				AppRun ->state = OS_STATE_ACTIVE_ON; 	
				AppRun ->loading = AppRun ->reload;	
			}					
			else if(AppRun ->state == OS_STATE_ONE_OFF) //一次性的程序  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序程序   
				AppRun ->state = OS_STATE_CLOSE_ON;  
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//运行结束程序
				AppRun ->state = OS_STATE_CLOSE_ON;
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_ACTIVE_ON)//运行已经激活的主程序
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 
				AppRun ->loading = AppRun ->reload;	
			}		
						
			OS_TextColor_Set(_TextColor); //还原原来的颜色
			OS_BackColor_Set(_BackColor);						
		}
			   
	} 
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSThread_5()     
* @Description   : None 
* @Data          : 2016/4/19
* @Explain       : 线程5（低于系统线程 高于主线程）
------------------------------------------------------------------------------*/
void OSThread_5(void)
{
	Type_AppList *AppRun = &AppHead;  
	unsigned int _BackColor,_TextColor;  
	while(1)
	{	
		if(AppRun ->next == NULL) return; 
		
		AppRun = AppRun ->next; 
		
		if(AppRun ->thread != OS_THREAD_5) continue; 
		
		if(AppRun ->loading != 0) AppRun ->loading --;     
		else
		{
			_TextColor = TextColor;//记录该区的颜色 
			_BackColor = BackColor;	
			
			if(AppRun ->state == OS_STATE_SUSPEND) //挂起
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 
				AppRun ->state = OS_STATE_SUSPEND_ON; 	
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_SUSPEND_ON)//运行已经挂起的后台程序
			{
				if(AppRun ->AppBack != NULL) AppRun ->AppBack();//运行后台程序
				AppRun ->loading = AppRun ->reload;	
			}	
			else if(AppRun ->state == OS_STATE_ACTIVE) //激活   
			{ 
				if(AppRun ->AppStart != NULL) AppRun ->AppStart(); //运行启动程序  
				AppRun ->state = OS_STATE_ACTIVE_ON; 	
				AppRun ->loading = AppRun ->reload;	
			}					
			else if(AppRun ->state == OS_STATE_ONE_OFF) //一次性的程序  
			{ 				
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); //运行一次主程序程序   
				AppRun ->state = OS_STATE_CLOSE_ON;  
				AppRun ->loading = AppRun ->reload;	
			} 
			else if(AppRun ->state == OS_STATE_CLOSE)
			{ 
				if(AppRun ->AppEnd != NULL) AppRun ->AppEnd(); 	//运行结束程序
				AppRun ->state = OS_STATE_CLOSE_ON;
				AppRun ->loading = AppRun ->reload;	
			}
			else if(AppRun ->state == OS_STATE_ACTIVE_ON)//运行已经激活的主程序
			{
				if(AppRun ->AppMain != NULL) AppRun ->AppMain(); 
				AppRun ->loading = AppRun ->reload;	
			}		
						
			OS_TextColor_Set(_TextColor); //还原原来的颜色
			OS_BackColor_Set(_BackColor);					
		}
			   
	} 
	
}

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





