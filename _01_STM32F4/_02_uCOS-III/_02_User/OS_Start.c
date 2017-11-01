/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Start.c
* @Description : None
* @Date        : 2017/2/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_Start.h"  
#include "App_Include.h"  

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/  

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Start()     
* @Description   : 系统启动程序
* @Data          : 2017/2/16
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Start(void)		
{
	OS_ERR err;
	 
	CPU_Init(); 
	OSInit(&err);			//初始化UCOSIII  
	GUI_Init();  			//STemWin初始化 
	
	OS_TaskCreate(&App_LED);
	OS_TaskCreate(&App_Test);
	OS_TaskCreate(&App_emWinTest);
	
	OSStart(&err);  //开启UCOSIII					
}	


/**----------------------------------------------------------------------------
* @FunctionName  : OS_TaskCreate()     
* @Description   : 简易创建任务
* @Data          : 2017/2/20
* @Explain       : 返回：err
------------------------------------------------------------------------------*/
OS_ERR OS_TaskCreate(OS_Struct *os_struct)
{ 
	OS_ERR err;
	CPU_SR_ALLOC(); 
	OS_CRITICAL_ENTER();//进入临界区
	OSTaskCreate(//创建任务 
					 (OS_TCB 	* )os_struct->app_tcb,			//任务控制块 
					 (CPU_CHAR	* )os_struct->app_name, 		//任务名字
					 (OS_TASK_PTR )os_struct->app_fun, 			//任务函数
					 (void		* )os_struct->p_arg,			//传递给任务函数的参数
					 (OS_PRIO	  )os_struct->app_prio,   		//任务优先级
					 (CPU_STK   * )os_struct->app_STK,			//任务堆栈基地址
					 (CPU_STK_SIZE)os_struct->app_limit,		//任务堆栈深度限位
					 (CPU_STK_SIZE)os_struct->app_size,			//任务堆栈大小
					 (OS_MSG_QTY  )os_struct->q_size,							//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
					 (OS_TICK	  )os_struct->time_quanta,							//当使能时间片轮转时的时间片长度，为0时为默认长度，
					 (void   	* )os_struct->p_ext,							//用户补充的存储区
					 (OS_OPT      )os_struct->opt, //任务选项
					 (OS_ERR 	* )&err							//存放该函数错误时的返回值
			   );	
	
	OS_CRITICAL_EXIT();	//退出临界区	  
	
	return err;			 
}	



/**----------------------------------------------------------------------------
* @FunctionName  : Num_LenthGet()     
* @Description   : 获取数值的长度
* @Data          : 2017/2/20
* @Explain       : 返回：数值的长度
------------------------------------------------------------------------------*/
u16 Num_LenthGet(u32 num)
{
	u16 cnt = 1;
	while(1)
	{
		num /= 10;
		if(num == 0) break;
		else cnt ++;
	}
	return cnt;
}

																				
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





