/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_StartFile.h
* @Description : None
* @Date        : 2016/3/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (TM4C1294NCPDT)
* @Explain     : None
*=============================================================================*/             
#ifndef __OS_STARTFILE_H
#define __OS_STARTFILE_H

/* 结构体声明 ---------------------------------------------------------------*/ 
typedef unsigned int(CreatFun)(void); //App 函数定义必须是 unsigned int XXX(void)  

 
typedef struct __AppList
{  		 
	CreatFun *AppMain;  //主程序的地址   		
	CreatFun *AppBack;  //后台程序的地址  	
	CreatFun *AppStart; //初始化程序的地址 	 	
	CreatFun *AppEnd;   //结束程序的地址  
	
	volatile unsigned char state;//运行状态	
	unsigned char thread;//线程 	
	
	unsigned char *name;    		
    unsigned long int reload;//程序重载值      
 	
	unsigned long int loading;//运行槽   
	struct __AppList *next;   		
}Type_AppList; //任务队列		
				
				
					 
/* User宏定义 ---------------------------------------------------------------*/		
/* 时间片定义 ----------------------------*/	
#define OS_TIME_SLICE 1000//1ms	

/* 晶振定义 ------------------------------*/	
#define OS_FOSC 72000000   //系统时钟

/* 显示屏定义 ----------------------------*/		
#define USE_OS_DESKTOP  	1	 //使用系统桌面
 
/* 最大任务数 ----------------------------*/	
#define OS_TASK_MAX  10000	

/* 自定义线程 ------------------------------*/	
#define OS_THREAD_FREE  	     0xfe  			  //空闲线程		
#define OS_THREAD_PRIMARY 	 	 OS_THREAD_6	  //主线程  
#define OS_THREAD_SYSTEM  	     OS_THREAD_4	  //系统线程	

/* RAM地址 -------------------------------*/ 	
#define OS_RAM_SIZE  0x8000	
	 
/* WindOS宏定义 --------------------------------------------------------------*/		
/* _state -------------------------------*/				
#define OS_STATE_SUSPEND   		 1    //挂起（后台）
#define OS_STATE_ACTIVE   		 2	  //激活 
#define OS_STATE_ONE_OFF  	     3	  //只运行一次 
#define OS_STATE_CLOSE   		 4    //关闭  
#define OS_STATE_ACTIVE_ON   	 5    //激活完毕  
#define OS_STATE_CLOSE_ON   	 6    //关闭完毕 	
#define OS_STATE_SUSPEND_ON   	 7    //挂起（后台）	
		
																	
/* prioity -----------------------------*/
#define OS_THREAD_0  	     	 0x00	 
#define OS_THREAD_1  	     	 0x01		
#define OS_THREAD_2  	     	 0x02
#define OS_THREAD_3 	     	 0x03   
#define OS_THREAD_4 	     	 0x04	//已开启	 OS_THREAD_SYSTEM
#define OS_THREAD_5  	     	 0x05	//已开启 
#define OS_THREAD_6  	     	 0x06	//已开启 OS_THREAD_PRIMARY
#define OS_THREAD_7  	     	 0x07	//已开启  
#define OS_THREAD_8  	     	 0x08
#define OS_THREAD_9	     	 	 0x09
#define OS_THREAD_10  	     	 0x0A
#define OS_THREAD_11  	     	 0x0B
#define OS_THREAD_12  	     	 0x0C
#define OS_THREAD_13  	     	 0x0D
#define OS_THREAD_14  	     	 0x0E
#define OS_THREAD_15  	     	 0x0F


/* OS_MSG -------------------------------*/			
#define OS_BREAK 	     	     (0x01<<0)	  //立即中断所有程序的运行 	
 
/* OS_ERROR -----------------------------*/			
#define OS_ERROR_MALLOC	         (0x01<<0)	 //内存申请错误	
 
/* 其他 ---------------------------------*/
#define OS_DEFAULT 	     	     NULL	  //缺省值
		
/* 头文件包含 ----------------------------------------------------------------*/ 		
#include "User_Library.h"  
#include "OS_Manage.h"
#include "OS_UI.h" 	 
#include "OS_Run.h"


/* 全局变量声明 --------------------------------------------------------------*/ 
/* 系统消息 --------------------------------*/ 
extern u32 OS_Msg;			
extern u32 OS_Error;
extern u32 OS_Clock;
extern u32 os_fosc;

/* 全局函数声明 --------------------------------------------------------------*/  
void OS_Init(void);  	 
void OSdelay_us(unsigned long int _us);			
void OSdelay_ms(unsigned long int _ms);   		
void OSdelay_s(unsigned long int _s);	 

 
#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





