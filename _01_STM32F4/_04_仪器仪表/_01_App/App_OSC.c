/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_OSC.c
* @Description : None
* @Date        : 2016/7/10
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_OSC.h"  

/* 私有宏定义 ----------------------------------------------------------------*/
#define DEFAULT_OSC_SHIFTX 			(500)				//值越大越往左移
#define DEFAULT_OSC_SHIFTY 			(100)  				//值越大越往上移
#define DEFAULT_OSC_ZOOMX 			(100)			
#define DEFAULT_OSC_ZOOMY			(100)		
#define DEFAULT_OSC_VPP 			0
#define DEFAULT_OSC_T 				0
#define DEFAULT_OSC_MAXVALUE 		0
#define DEFAULT_OSC_MINVALUE		0xffff

Type_OSC Struct_OSC = {DEFAULT_OSC_SHIFTX,DEFAULT_OSC_SHIFTY,DEFAULT_OSC_ZOOMX,DEFAULT_OSC_ZOOMY, \
					   DEFAULT_OSC_VPP,DEFAULT_OSC_T,DEFAULT_OSC_MAXVALUE,DEFAULT_OSC_MINVALUE };

/* 私有（静态）函数声明 ------------------------------------------------------*/  
					   
/* 全局变量定义 --------------------------------------------------------------*/
u8 OSC_PerX = 33;
u8 OSC_PerY = 33;
u8 Ch1_Switch = 1, Ch2_Switch = 0,Change_Switch = 0; 	
u8 Speed = 0;
					   
/* 全局变量声明 --------------------------------------------------------------*/
Type_AppList App_Touch_Control;
					   
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OSC()     
* @Description   : None 
* @Data          : 2016/7/10
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int OSC_Main(void)		
{      
	if(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0) == SET) 
	{       
		OS_OSC_Draw1(10,55,562,440,ADC1_DMA2_Buff,ADC1_DMA2_LENTH,10.0,&Struct_OSC,GREEN);  
		ADC1_DMA2_Reload(Speed);  
	}
	return 0;					
	 																
}	 

unsigned int OSC_Start(void)		
{     
	static u8 _first = 0;	
	OS_LCD_Clear(BLACK);
	
	if(_first == 0) {ADC1_DMA2_Reload(0); _first++;OSTask_Creat(&App_Touch_Control);OSTask_Creat(&App_Frequency);}//初始化 
	OSTask_State(&App_Touch_Control,OS_STATE_ACTIVE); 
	OSTask_State(&App_Frequency,OS_STATE_ACTIVE); 
	return 0;	 															
}	

unsigned int OSC_End(void)		
{        
	OSTask_State(&App_Touch_Control,OS_STATE_CLOSE); 
	
	OSTask_Alter(&App_Frequency,NULL,NULL,OS_STATE_CLOSE,NULL);
	
	return 0;	 															
}

Type_AppList App_OSC = {OSC_Main,NULL,OSC_Start,OSC_End, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"OSC",100};		

						
/**----------------------------------------------------------------------------
* @FunctionName  : OSC_Touch_Control()     
* @Description   : None 
* @Data          : 2016/7/14
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int OSC_Touch_Control(void)
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
	 
	 if(TouchStart_Judge(10,55,540,420) == TOUCH_VALID) 
	 {  
		 Struct_OSC.ShiftX += (TouchStruct.StartX - TouchStruct.NowX); 
		 Struct_OSC.ShiftY += (TouchStruct.StartY - TouchStruct.NowY)*100/Struct_OSC.ZoomY*3; 
		 
		 TouchStruct.StartX = TouchStruct.NowX;		
		 TouchStruct.StartY = TouchStruct.NowY;	 	
	 }
	 
	  if(TouchStart_Judge(700,40,780,120) == TOUCH_VALID) 
	  {
			OS_Picture_Draw(700,40,780,120,gImage_Auto80x80,3);
		     
			if(g_Freq < 10000)	Speed = 7;  
			else if(g_Freq < 50000)	 Speed = 3;  
			else Speed = 0; 
	  }
	  else OS_Picture_Draw(700,40,780,120,gImage_Auto80x80,2); 
	 OSC_Data_Show(); 
	 	
	
	 return 0;
	 
}	

unsigned int OSC_Touch_Start(void)		
{      
	OS_LCD_Clear(BLACK);	
	OSC_Switch();  	
	OSC_BarX();		
	OSC_BarY();		
	
	return 0;	 															
}	
unsigned int OSC_Touch_End(void)		
{         
	 
	return 0;	 															
}

Type_AppList App_Touch_Control = {OSC_Touch_Control,NULL,OSC_Touch_Start,OSC_Touch_End, \
								  OS_STATE_CLOSE_ON,OS_THREAD_7, \
								  (u8*)"Touch_Control",5};		

/**----------------------------------------------------------------------------
* @FunctionName  : OSC_ZoomX()     
* @Description   : None 
* @Data          : 2016/7/13
* @Explain       : None
------------------------------------------------------------------------------*/
void OSC_BarX(void)
{  
	static u8 LastPer = 0xff;	
	u8 per = OSC_PerX;
	 
	Struct_OSC.ZoomX = per*3;
	if(OSC_PerX > 100) return; 
	
	if(LastPer != per)
	{
		OS_Rect_Draw(50+LastPer*4,445,130+LastPer*4,475,1,BLACK); //删除上一次的位置	
		LastPer = per;		  
	}
	OS_Rect_Draw(80,455,50+per*4,465,1,BLUE);		
	OS_Rect_Draw(130+per*4,455,510,465,1,BLUE);		
	OS_Rect_Draw(80,459,510,461,1,GREEN);			
	OS_Picture_Draw(50+per*4,445,130+per*4,475,gImage_BarX80x30,2);   
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSC_ZoomY()     
* @Description   : None 
* @Data          : 2016/7/13
* @Explain       : None
------------------------------------------------------------------------------*/
void OSC_BarY(void)
{ 
	static u8 LastPer = 0xff; 
	u8 per = OSC_PerY;
	
	Struct_OSC.ZoomY = per*3;   
	if(per > 100) return;
	per = 100 - per;
	
	if(LastPer != per )
	{
		OS_Rect_Draw(570,70+LastPer*3,600,150+LastPer*3,1,BLACK); //删除上一次的位置
		LastPer = per; 
	}
	OS_Rect_Draw(582,100,592,70+per*3,1,BLUE); 
	OS_Rect_Draw(582,150+per*3,592,410,1,BLUE); 
	OS_Rect_Draw(586,100,588,410,1,YELLOW); 
	OS_Picture_Draw(570,70+per*3,600,150+per*3,gImage_BarY30x80,2);  
	
	 
}


/**----------------------------------------------------------------------------
* @FunctionName  : OSC_CH_Switch()     
* @Description   : None 
* @Data          : 2016/7/13
* @Explain       : None
------------------------------------------------------------------------------*/
void OSC_Switch(void)
{ 
	
	if(Ch1_Switch == 1)
			OS_Picture_Draw(680,150,780,190,gImage_ON100x40,2);  
	else if(Ch1_Switch == 0)
			OS_Picture_Draw(680,150,780,190,gImage_OFF100x40,2);  
	
	if(Ch2_Switch == 1)
			OS_Picture_Draw(680,200,780,240,gImage_ON100x40,2);
	if(Ch2_Switch == 0)	 
			OS_Picture_Draw(680,200,780,240,gImage_OFF100x40,2);  
 
	if(Change_Switch == 0)
			OS_Picture_Draw(680,270,780,310,gImage_x1_100x40,2);
	if(Change_Switch == 1)
			OS_Picture_Draw(680,270,780,310,gImage_x10_100x40,2);
}

 


/**----------------------------------------------------------------------------
* @FunctionName  : OSC_Auto()     
* @Description   : None 
* @Data          : 2016/7/13
* @Explain       : None
------------------------------------------------------------------------------*/
//void OSC_Auto(void)
//{   
//	 
//}



/**----------------------------------------------------------------------------
* @FunctionName  : OSC_Data_Show()     
* @Description   : None 
* @Data          : 2016/7/13
* @Explain       : None
------------------------------------------------------------------------------*/
void OSC_Data_Show(void)
{ 
//	 OS_Num_Show(0,0,Struct_OSC.MinValue,3,24,1);  	 					OS_Num_Show(100,0,Struct_OSC.MaxValue,3,24,1);     
	 OS_String_Show(0,0,(u8*)"Vpp:",24,1); 								OS_String_Show(150,0,(u8*)"Max:",24,1); 				   	     OS_String_Show(300,0,(u8*)"Min:",24,1); 	
	 OS_Decim_Show(12*4,0,Struct_OSC.Vpp*3.3/256,2,2,24,1);  			OS_Decim_Show(150+12*4,0,Struct_OSC.MaxValue*3.3/256,2,2,24,1);  OS_Decim_Show(300+12*4,0,Struct_OSC.MinValue*3.3/256,2,2,24,1); 
	 OS_String_Show(450,0,(u8*)"Virt:",24,1); OS_Decim_Show(450+12*4,0,Struct_OSC.Vpp*3.3/256/1.4142f,2,2,24,1);  
	
	 OS_String_Show(0,24,(u8*)"Freq:",24,1);	 OS_Num_Show(0+12*5,24,g_Freq,8,24,1);  	OS_String_Show(12*8+12*5,24,(u8*)"Hz",24,1);
	 OS_String_Show(300,24,(u8*)"Duty:",24,1);	 OS_Decim_Show(300+12*5,24,Struct_OSC.Duty,3,2,24,1); OS_String_Show(300+12*10,24,(u8*)"%",24,1);	 
	
//	 OS_Num_Show(200,0,Struct_OSC.ShiftX,6,24,1);  						OS_Num_Show(300,0,Struct_OSC.ShiftY,6,24,1);
//	 OS_Decim_Show(200,24,Struct_OSC.ZoomX/100.0f,2,2,24,1);  			OS_Decim_Show(300,24,Struct_OSC.ZoomY/100.0f,2,2,24,1); 
	
}				




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/










