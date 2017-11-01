/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Touch.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Touch.h"
#include "User_Library.h" 
#include "touch.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
Type_Touch TouchPoint = {0};

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Drive_GPIO_Init()     
* @Description   : None 
* @Data          : 2016/3/15
* @Explain       : None
------------------------------------------------------------------------------*/
int Drive_Touch_Init(void)
{
	 tp_dev.init(); 
	return 0;
}

/**----------------------------------------------------------------------------  
* @FunctionName  : TouchScan()     
* @Description   : None
* @Data          : 2016/3/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int TouchScan(void)  
{  
//	 u16 tempX = 0xffff,tempY = 0xffff; 
	 
	 GT9147_Scan(0);	
	 TouchPoint._X = tp_dev.x[0];
	 TouchPoint._Y = tp_dev.y[0];
	 
//	 TouchPoint._X = tempX*OS_LCD_WHITH/3600 - 20;//AD转换成坐标
//	 TouchPoint._Y = tempY*OS_LCD_LENTH/3550 - 20;  
	 
	 
	 if(TouchPoint._X <= OS_LCD_WHITH && TouchPoint._Y <= OS_LCD_LENTH)	
	 { 	
		/* 记录实时数据 (即时) -----------------------------------------*/ 
		TouchPoint._BuffX[TouchPoint._CNT] = TouchPoint._X;	
		TouchPoint._BuffY[TouchPoint._CNT] = TouchPoint._Y; 	 
		TouchPoint._State = TOUCH_STATE_ON;
		TouchPoint._CNT = (TouchPoint._CNT + 1)%TOUCH_BUFF_SIZE;
		 
		/* 记录滑动方向 (即时) -----------------------------------------*/ 
		TouchPoint._SlipDirection = TOUCH_SLIP_NULL; 
		if(TouchPoint._LastX - TouchPoint._BuffX[0] < -TOUCH_SLIP_RESPONSE)  TouchPoint._SlipDirection |= TOUCH_SLIP_LEFT,TouchPoint._State = TOUCH_STATE_SLIP;
		if(TouchPoint._LastX - TouchPoint._BuffX[0] > TOUCH_SLIP_RESPONSE)   TouchPoint._SlipDirection |= TOUCH_SLIP_RIGHT,TouchPoint._State = TOUCH_STATE_SLIP; 
		if(TouchPoint._LastY - TouchPoint._BuffY[0] < -TOUCH_SLIP_RESPONSE)  TouchPoint._SlipDirection |= TOUCH_SLIP_UP,TouchPoint._State = TOUCH_STATE_SLIP;
		if(TouchPoint._LastY - TouchPoint._BuffY[0] > TOUCH_SLIP_RESPONSE)   TouchPoint._SlipDirection |= TOUCH_SLIP_DOWN,TouchPoint._State = TOUCH_STATE_SLIP;
		 
		/* 记录缓存数据 (需要手动清除) ----------------------------------*/  
		TouchPoint._LastX = TouchPoint._X;	
		TouchPoint._LastY = TouchPoint._Y; 	 
		TouchPoint._LastSlipDirection =  TouchPoint._SlipDirection;	
		TouchPoint._LastBuffX[TouchPoint._LastCNT] = TouchPoint._X;	
		TouchPoint._LastBuffY[TouchPoint._LastCNT] = TouchPoint._Y;  
		TouchPoint._LastCNT =  (TouchPoint._LastCNT + 1)%TOUCH_BUFF_SIZE;
		
		return 0;	
	 } 
	 else	
	{ 
		
		/* 清除实时数据 (即时) -----------------------------------------*/ 
		if(TouchPoint._State == TOUCH_STATE_ON) TouchPoint._LastState = TOUCH_STATE_ON;
		TouchPoint._X = 0xffff; 
		TouchPoint._Y = 0Xffff; 
		
		TouchPoint._State = TOUCH_STATE_OFF;  
		
		TouchPoint._BuffX[TouchPoint._CNT] = 0xffff;
		TouchPoint._BuffY[TouchPoint._CNT] = 0xffff;
		while(TouchPoint._CNT) 
		{
			TouchPoint._CNT --;
			TouchPoint._BuffX[TouchPoint._CNT] = 0xffff;
			TouchPoint._BuffY[TouchPoint._CNT] = 0xffff;
		}
		
#if USE_OS_DESKTOP == 1		
		if(OS_AppIn.state == OS_STATE_ACTIVE_ON)
		{
			if((TouchPoint._SlipDirection & TOUCH_SLIP_LEFT) == TOUCH_SLIP_LEFT) DeskPage.CurrentPage ++; 
			if((TouchPoint._SlipDirection & TOUCH_SLIP_RIGHT) == TOUCH_SLIP_RIGHT) DeskPage.CurrentPage --; 
			if( DeskPage.CurrentPage < DeskPage.FirstPage) DeskPage.CurrentPage = DeskPage.FirstPage;
			if( DeskPage.CurrentPage > DeskPage.EndPage) DeskPage.CurrentPage = DeskPage.EndPage;
		}
#endif		
		TouchPoint._SlipDirection = TOUCH_SLIP_NULL;
		
		return 1;
	}    
		
		
}  			
//程序注册表 
Type_AppList Drive_TouchScan = {TouchScan,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						(u8*)"TouchScan",TOUCH_SCAN_SPEED};  
		
	

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/

						
						
						




