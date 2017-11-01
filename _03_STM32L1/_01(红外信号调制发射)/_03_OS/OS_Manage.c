/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Manage.c
* @Description : 系统管理
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
*=============================================================================*/     

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_Manage.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/ 

/* 全局变量定义 --------------------------------------------------------------*/
/* App --------------------------------------------*/
Type_AppList AppHead = {NULL}; //定义任务堆头     

/* 全局函数编写 --------------------------------------------------------------*/ 
/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Creat()     
* @Description   : WinOS任务创建 
* @Data          : 2016/3/16
* @Explain       : 
-------------------------------------------------------------------------------
参数 ： _AppList = 程序地址    
返回值 ： 1 = 任务重复创建，创建失败		 0 = 成功
------------------------------------------------------------------------------*/	
unsigned char OSTask_Creat(Type_AppList *_AppList) 				   
{  
	Type_AppList *Temp = &AppHead;		 
	while(Temp ->next != NULL)
	{
		Temp = Temp ->next;	
		if(Temp == _AppList) return 1; 	
	}	
	 
	Temp ->next = _AppList;       	 
	_AppList ->next = NULL; //堆尾   		
		 				
	return 0;  
}



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Remove()     
* @Description   : WinOS任务删除 
* @Data          : 2016/3/16		
* @Explain       : 参数 ：_AppAddr = 程序地址    
*
*				   返回值 ：1 = 删除任务失败				0 = 成功
------------------------------------------------------------------------------*/	
unsigned char OSTask_Remove(Type_AppList *_AppList)    
{   
	Type_AppList *Temp = &AppHead;	 
	while(Temp ->next != NULL)	
	{
		Temp = Temp ->next;	 
		if(Temp ->next == _AppList) break; //找到 pStruct 上一个按钮的地址
	} 	 
	Temp ->next = _AppList ->next;  	
	free(_AppList);   	 
	_AppList = NULL;
	
	return 0;		
} 



/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_Alter()     
* @Description   : WinOS任务修改
* @Data          : 2016/3/22		
* @Explain       : 参数 ：_AppAddr = 程序地址    
*
*				   返回值 ：1,2,3 = 修改任务失败				0 = 成功
------------------------------------------------------------------------------*/
unsigned char OSTask_Alter(  Type_AppList *_AppList \
						   ,unsigned char *_Name \
						   ,unsigned long int _T \
						   ,unsigned char _state \
						   ,unsigned char _thread \
					      )  
{     
	Type_AppList *pList = &AppHead;    	
	unsigned int _cnt = OS_TASK_MAX;   			
	unsigned char _exist = 0;				
																
	/* 判断任务是否存在 ----------------------------*/				
	while(1)	
	{
		if(pList == _AppList) {_exist = 1;break;}	 
		if(pList->next != NULL) pList = pList->next;		
		else break;   									
	}		 
	if(_exist == 0) return 1;	
				
	/* 修改数据 -----------------------------------*/		
	if(_Name != OS_DEFAULT)	_AppList ->name = _Name;		
	if(_T != OS_DEFAULT)  	_AppList ->reload = _T;		
	if(_state != OS_DEFAULT) 	_AppList ->state = _state;		
	if(_thread != OS_DEFAULT)	_AppList ->thread= _thread;		
																
	_cnt--; 															
    if(_cnt == 0) return 2;  	
	
	return 0;				
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_State()     
* @Description   : WinOS任务状态修改
* @Data          : 2016/3/22		
* @Explain       : 
-------------------------------------------------------------------------------
_AppAddr = 程序地址    
_State	 = 运行状态	
	OS_STATE_SUSPEND   		 	1    //挂起（后台）
	OS_STATE_ACTIVE   		 	2	  //激活 
	OS_STATE_ONE_OFF  	     	3	  //只运行一次 
	OS_STATE_CLOSE   			4    //关闭  
	OS_STATE_ACTIVE_FINISH   	5    //激活完毕  
	OS_STATE_CLOSE_FINISH   	6    //关闭完毕 	
	OS_STATE_SUSPEND_FINISH   	7    //挂起（后台）	

返回值 ：1,2,3 = 修改任务失败				0 = 成功
------------------------------------------------------------------------------*/
unsigned char OSTask_State(Type_AppList *_AppList,unsigned char _State)  
{     
	Type_AppList *pList = &AppHead;       			
	unsigned char _exist = 0;				
																
	/* 判断任务是否存在 ----------------------------*/				
	while(1)	
	{
		if(pList == _AppList) {_exist = 1;break;}	 
		if(pList->next != NULL) pList = pList->next;		
		else break;   									
	}		 
	if(_exist == 0) return 1;	
				
	/* 修改数据 -----------------------------------*/		 	
	_AppList ->state= _State;		
			 
	return 0;				
}

/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_State()     
* @Description   : WinOS任务状态修改
* @Data          : 2016/3/22		
* @Explain       : 
-------------------------------------------------------------------------------
_AppAddr = 程序地址     
返回值 ：1,2,3 = 修改任务失败				0 = 成功
------------------------------------------------------------------------------*/
unsigned char OSTask_Close(Type_AppList *_AppList)  
{     
	Type_AppList *pList = &AppHead;       			
	unsigned char _exist = 0;				
																
	/* 判断任务是否存在 ----------------------------*/				
	while(1)	
	{
		if(pList == _AppList) {_exist = 1;break;}	 
		if(pList->next != NULL) pList = pList->next;		
		else break;   									
	}		 
	if(_exist == 0) return 1;	
				
	/* 修改数据 -----------------------------------*/		 	
	_AppList ->state = OS_STATE_CLOSE;		
			 
	return 0;				
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSTask_State()     
* @Description   : WinOS任务状态修改
* @Data          : 2016/3/22		
* @Explain       : 
-------------------------------------------------------------------------------
_AppAddr = 程序地址     
返回值 ：1,2,3 = 修改任务失败				0 = 成功
------------------------------------------------------------------------------*/
unsigned char OSTask_Active(Type_AppList *_AppList)  
{     
	Type_AppList *pList = &AppHead;       			
	unsigned char _exist = 0;				
																
	/* 判断任务是否存在 ----------------------------*/				
	while(1)	
	{
		if(pList == _AppList) {_exist = 1;break;}	 
		if(pList->next != NULL) pList = pList->next;		
		else break;   									
	}		 
	if(_exist == 0) return 1;	
				
	/* 修改数据 -----------------------------------*/		 	
	_AppList ->state = OS_STATE_ACTIVE;		
			 
	return 0;				
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSRunning_Break()     	
* @Description   : WinOS打断运行	
* @Data          : 2016/3/23		
* @Explain       : None 		
------------------------------------------------------------------------------*/
inline unsigned int OSRunning_Break(void) 
{
	OS_Msg |=  OS_BREAK; 
	return 0;
}
												
											
/**----------------------------------------------------------------------------
* @FunctionName  : OSRunning_GoOn()     
* @Description   : WinOS继续运行		
* @Data          : 2016/3/23		
* @Explain       : None		
------------------------------------------------------------------------------*/
inline unsigned int OSRunning_Continue(void) 
{ 
	OS_Msg &=  ~OS_BREAK; 
	return 0; 
}

 

/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





