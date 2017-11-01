/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Start.h
* @Description : None
* @Date        : 2017/2/16
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __OS_START_H
#define __OS_START_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/ 
#include "User_Include.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 	 

/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct 
{ 
	OS_TASK_PTR 	app_fun;
	CPU_CHAR  	   *app_name; 
	OS_PRIO 		app_prio;
	OS_TCB  	   *app_tcb;
	CPU_STK 	   *app_STK;
	CPU_STK_SIZE  	app_size; 
	CPU_STK_SIZE   	app_limit;
	OS_MSG_QTY     	q_size;
	OS_TICK         time_quanta;
	void           *p_ext;
	void           *p_arg;
	OS_OPT          opt;
	
}OS_Struct;

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void OS_Start(void);
OS_ERR OS_TaskCreate(OS_Struct *os_struct);
u16 Num_LenthGet(u32 num);

#endif
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/



