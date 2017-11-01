/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Tools.h
* @Description : 本系统自带的小工具
* @Date        : 2017/9/21
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
*=============================================================================*/            
#ifndef __OS_TOOLS_H
#define __OS_TOOLS_H

/* 头文件包含 ----------------------------------------------------------------*/ 		 
#include "OS_StartFile.h" 

/* 全局宏定义 ----------------------------------------------------------------*/
#define 	OS_TIMER_CNT_MAX			(0xffff)
#define 	OS_Clock_us					(TIM_GetCounter(TIM2))

/* 结构体声明 ---------------------------------------------------------------*/  

/* 全局变量声明 --------------------------------------------------------------*/  

/* 全局函数声明 --------------------------------------------------------------*/   
void OSdelay_us(uint32_t _us);			
void OSdelay_ms(uint32_t _ms);   		
void OSdelay_s(uint32_t _s);	 

uint32_t OStimer_us_Get(void);
uint8_t OStimer_usTimeOver_Is(uint32_t _StartTime,uint32_t _Time);    

uint32_t OStimer_ms_Get(void);
uint8_t OStimer_msTimeOver_Is(uint32_t _StartTime, uint32_t _Time);









void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(uint32_t addr);	//设置堆栈地址 

#endif
/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/





