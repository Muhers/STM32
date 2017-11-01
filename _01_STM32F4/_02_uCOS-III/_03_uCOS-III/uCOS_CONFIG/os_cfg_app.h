/*
************************************************************************************************************************
*                                                      uC/OS-III
*                                                 The Real-Time Kernel
*
*                                  (c) Copyright 2009-2012; Micrium, Inc.; Weston, FL
*                           All rights reserved.  Protected by international copyright laws.
*
*                                       OS CONFIGURATION (APPLICATION SPECIFICS)
*
* File    : OS_CFG_APP.H
* By      : JJL
* Version : V3.03.01
*
* LICENSING TERMS:
* ---------------
*           uC/OS-III is provided in source form for FREE short-term evaluation, for educational use or
*           for peaceful research.  If you plan or intend to use uC/OS-III in a commercial application/
*           product then, you need to contact Micrium to properly license uC/OS-III for its use in your
*           application/product.   We provide ALL the source code for your convenience and to help you
*           experience uC/OS-III.  The fact that the source is provided does NOT mean that you can use
*           it commercially without paying a licensing fee.
*
*           Knowledge of the source code may NOT be used to develop a similar product.
*
*           Please help us continue to provide the embedded community with the finest software available.
*           Your honesty is greatly appreciated.
*
*           You can contact us at www.micrium.com, or by phone at +1 (954) 217-2036.
************************************************************************************************************************
*/

#ifndef OS_CFG_APP_H
#define OS_CFG_APP_H

/*
************************************************************************************************************************
*                                                      CONSTANTS
************************************************************************************************************************
*/

 #define OS_CFG_MSG_POOL_SIZE 100u //��Ϣ����
#define OS_CFG_ISR_STK_SIZE 128u //�ж������ջ��С

//�����ջ��ȣ����統����Ϊ 10 ʱ��ʾ�������ջʣ��ٷ�֮ 10%ʱ��˵����ջΪ��
#define OS_CFG_TASK_STK_LIMIT_PCT_EMPTY 10u

//*********************��������*************************
#define OS_CFG_IDLE_TASK_STK_SIZE 128u //�������ջ��С

//********************�жϷ����������*****************
#define OS_CFG_INT_Q_SIZE 10u //�ж϶��д�С
#define OS_CFG_INT_Q_TASK_STK_SIZE 128u //�жϷ�����������С

//********************ͳ������**************************
//ͳ���������ȼ��������ڶ������ȼ������һ�����ȼ��ǿ�������ġ�
#define OS_CFG_STAT_TASK_PRIO (OS_CFG_PRIO_MAX-2u)

// OS_CFG_STAT_TASK_RATE_HZ ����ͳ��������� CPU ʹ���ʣ�ͳ������ͨ��ͳ����
//(1/ OS_CFG_STAT_TASK_RATE_HZ)���ʱ���� OSStatTaskCtr �ܹ��ﵽ�����ֵ���õ�
//CPU ʹ���ʣ�OS_CFG_STAT_TASK_RATE_HZ ֵӦ���� 1~10Hz
#define OS_CFG_STAT_TASK_RATE_HZ 10u
#define OS_CFG_STAT_TASK_STK_SIZE 128u //ͳ�������ջ

//******************ʱ�ӽ�������***********************
#define OS_CFG_TICK_RATE_HZ 1000u //ϵͳʱ�ӽ���Ƶ��
//ʱ�ӽ�������һ������һ����Խϸߵ����ȼ�
#define OS_CFG_TICK_TASK_PRIO 1u
#define OS_CFG_TICK_TASK_STK_SIZE 128u //ʱ�ӽ��������ջ��С
#define OS_CFG_TICK_WHEEL_SIZE 17u //ʱ�ӽ����б��С

//************************��ʱ����************************
#define OS_CFG_TMR_TASK_PRIO 2u //��ʱ�������ȼ�
#define OS_CFG_TMR_TASK_RATE_HZ 100u //��ʱƵ�ʣ�һ��Ϊ 100Hz
#define OS_CFG_TMR_TASK_STK_SIZE 128u //��ʱ�����ջ��С
#define OS_CFG_TMR_WHEEL_SIZE 17u //��ʱ���б�����


#endif
