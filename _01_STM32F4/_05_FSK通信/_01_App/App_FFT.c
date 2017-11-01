/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_FFT.c
* @Description : None
* @Date        : 2016/7/10
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_FFT.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/ 

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
u8 FFTSpeed = 0;
unsigned int FFT_Touch_Control(void);
Type_AppList App_FFT_Control;

/* 全局变量声明 --------------------------------------------------------------*/
  
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : FFT()     
* @Description   : None 
* @Data          : 2016/7/10
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int FFT_Main(void)		
{         
	if(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0) == SET) 	
	{    	
		FFT_Exchange(ADC1_DMA2_Buff,ADC1_DMA2_LENTH);  	  
		OS_FFT_Draw(10,55,562,440,ADC1_DMA2_Buff,ADC1_DMA2_LENTH,10.0);   
		ADC1_DMA2_Reload(FFTSpeed);	 
		
	}	 
	return 0;	 													
}		

unsigned int FFT_Start(void)		
{        
	static u8 _first = 0;	
	if(_first == 0) {ADC1_DMA2_Init(); OSTask_Creat(&App_FFT_Control);_first++;}//初始化
	OSTask_State(&App_FFT_Control,OS_STATE_ACTIVE);  
		 
	OS_LCD_Clear(BLACK);  
	
	 
	return 0;	 															
}			
unsigned int FFT_End(void)		
{         
	OS_LCD_Clear(BLACK);  
	OSTask_State(&App_FFT_Control,OS_STATE_CLOSE);  
	
	return 0;	 															
}	 				
						
Type_AppList App_FFT = {FFT_Main,NULL,FFT_Start,FFT_End, \
						OS_STATE_CLOSE_ON,OS_THREAD_PRIMARY, \
						(u8*)"FFT",100};			
																
/**----------------------------------------------------------------------------
* @FunctionName  : FFT_Touch_Control()     
* @Description   : None 
* @Data          : 2016/7/14
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int FFT_Touch_Control(void)
{   
//	 OS_Num_Show(0,0,TouchStruct.NowX,6,24,1);  OS_Num_Show(100,0,TouchStruct.NowY,6,24,1);
	
	 if(Touch_Judge(680,150,780,190) == TOUCH_VALID_FULL)
	 {Ch1_Switch = (Ch1_Switch+1)%2;OSC_Switch();}
	 
	 if(Touch_Judge(680,200,780,240) == TOUCH_VALID_FULL)
	 {Ch2_Switch = (Ch2_Switch+1)%2;OSC_Switch();}
	 
	  if(Touch_Judge(680,270,780,310) == TOUCH_VALID_FULL)
	 {Change_Switch = (Change_Switch+1)%2;OSC_Switch();}
	  
	 if(TouchStart_Judge(60,440,530,480) == TOUCH_VALID) 
	 {
		 if((TouchStruct.NowX - 60)*100/(400) > 3 && (TouchStruct.NowX - 60)*100/(400) < 100)
			OSC_PerX = (TouchStruct.NowX - 60)*100/(400); 
		  
		 OSC_BarX(); 
	 }
	 	 
	 if(TouchStart_Judge(540,80,620,420) == TOUCH_VALID) 
	 {
		 if(100 - (TouchStruct.NowY - 80)*100/(300) >3 &&100 - (TouchStruct.NowY - 80)*100/(300) < 100)
			OSC_PerY = 100 - (TouchStruct.NowY - 80)*100/(300);   
		 
		  OSC_BarY(); 
	 }	
	 
	  
	  if(TouchStart_Judge(700,40,780,120) == TOUCH_VALID) 
	  {
			OS_Picture_Draw(700,40,780,120,gImage_Auto80x80,3);
		     
			if(g_Freq < 10000)	FFTSpeed = 7;  
			else if(g_Freq < 50000)	 FFTSpeed = 3;  
			else FFTSpeed = 0; 
	  }
	  else OS_Picture_Draw(700,40,780,120,gImage_Auto80x80,2);  
	 
	 return 0;
	 
}	

unsigned int FFT_Touch_Start(void)		
{        
	OS_LCD_Clear(BLACK); 
	OSC_BarX(); 
	OSC_BarY(); 
	OSC_Switch(); 
		
	return 0;	 															
}	
unsigned int FFT_Touch_End(void)		
{         
	 
	return 0;	 															
}

Type_AppList App_FFT_Control = {FFT_Touch_Control,NULL,FFT_Touch_Start,FFT_Touch_End, \
								  OS_STATE_CLOSE_ON,OS_THREAD_FREE , \
								  (u8*)"Touch_Control",5};		

								  
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





