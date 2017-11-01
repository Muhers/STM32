/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_Tools.c
* @Description : 系统自带小工具
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32L151CB)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "OS_Tools.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()
* @Description   : WindOS us延时函数
* @Data          : 2016/3/19
* @Explain       : 参数 ：_us = 延时时间
------------------------------------------------------------------------------*/
void OSdelay_us(uint32_t _us)
{
    unsigned long int _TimeNow = OS_Clock_us,  _ClockNow = OS_TimeOver_Cnt; 	

    while(OS_Clock_us + (OS_TimeOver_Cnt - _ClockNow)*OS_TIMER_CNT_MAX - _TimeNow < _us);	
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_us()
* @Description   : WindOS ms延时函数
* @Data          : 2016/3/19
* @Explain       : 参数 ：_ms = 延时时间
------------------------------------------------------------------------------*/
void OSdelay_ms(uint32_t _ms)
{
    unsigned long int _TimeNow = OS_Clock_us, _ClockNow = OS_TimeOver_Cnt;
                     
    _ms *= 1000;

    while(OS_Clock_us + (OS_TimeOver_Cnt - _ClockNow) *OS_TIMER_CNT_MAX - _TimeNow < _ms);
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSdelay_s()
* @Description   : WindOS s延时函数
* @Data          : 2016/3/19
* @Explain       : 参数 ：_s = 延时时间
------------------------------------------------------------------------------*/
inline void OSdelay_s(uint32_t _s)
{
    OSdelay_ms(_s * 1000);
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_us_Get()
* @Description   : 获取当前时间 单位us
* @Data          : 2016/3/19
* @Explain       : 返回 当前时间
------------------------------------------------------------------------------*/
inline uint32_t OStimer_us_Get(void)
{
    return OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_usTimeOver_Is()
* @Description   : 判断定时器是否溢出
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime：开始时间
_Time：需要定时时间(_Time < 2000 s)	单位：us
返回： 溢出 = 1
------------------------------------------------------------------------------*/
uint8_t OStimer_usTimeOver_Is(uint32_t _StartTime, uint32_t _Time)
{
    uint32_t Temp = OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX;
	
    if(Temp < _StartTime)  //越界了
    {	
        _StartTime = 0;					
        Temp += (0xffffffff - _StartTime);	
    }	
	
    return (Temp - _StartTime > _Time) ? 1 : 0; //定时器超时		

}

/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_ms_Get()
* @Description   : 获取当前时间 单位ms
* @Data          : 2016/3/19
* @Explain       : 返回 当前时间
------------------------------------------------------------------------------*/
inline uint32_t OStimer_ms_Get(void)
{	
    return (OS_Clock_us + OS_TimeOver_Cnt * OS_TIMER_CNT_MAX)/1000;	
}	

/**----------------------------------------------------------------------------
* @FunctionName  : OStimer_msTimeOver_Is()
* @Description   : 判断定时器是否溢出
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
_StartTime：开始时间
_Time：需要定时时间(_Time < 2000 s)	单位：ms
返回： 溢出 = 1
------------------------------------------------------------------------------*/
inline uint8_t OStimer_msTimeOver_Is(uint32_t _StartTime, uint32_t _Time)
{ 
	
	return OStimer_usTimeOver_Is(_StartTime*1000,_Time*1000); 

}





/**----------------------------------------------------------------------------
* @FunctionName  : 中断相关函数
* @Description   : None
* @Data          : 2016/3/19
* @Explain       :
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(uint32_t addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}


/*******************************(C) COPYRIGHT 2017 Wind（谢玉伸）*********************************/
















