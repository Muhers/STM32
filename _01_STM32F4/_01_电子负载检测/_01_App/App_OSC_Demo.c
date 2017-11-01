/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/
/**============================================================================
* @FileName    : App_OSC_Demo.c
* @Date        : 2017��7��13��
* @By          : Wind(л����)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ʾ��������ʹ������
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_OSC_Demo.h"


/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_OSC Struct_OSC_1 = {0};	  
Type_OSC Struct_OSC_2 = {0};	 
Type_OSC Struct_OSC_3 = {0};	
Type_OSC Struct_OSC_4 = {0};	

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OSC_Demo()
* @Description   : ʾ��������ʹ������
* @Data          : 2017��7��13��
* @Explain       : None
------------------------------------------------------------------------------*/
int OSC_Demo_Main(void)
{    
	u8 Buff_Sin_u8[2048];
	u16 Buff_Sin_u16[2048];
	float Buff_Sin_float[2048];
	double Buff_Sin_double[2048];
	
	u16 i = 0;
	static u16 cnt = 0;
	
	for(i = 0;i < 2048;i ++)	
	{	
		Buff_Sin_u8[i] = (sin(2*3.14*(i+cnt)/256.0f)+1)/2.0f*33; //����һ�����Ҳ�	 
		Buff_Sin_u16[i] = (sin(2*3.14*(i-cnt)/256.0f)+1)/2.0f*33; //����һ�����Ҳ�	 
		
		Buff_Sin_float[i] = (sin(2*3.14*(i+cnt)/256.0f))/2.0f*3.3; //����һ�����Ҳ�	 
		Buff_Sin_double[i] = (sin(2*3.14*(i-cnt)/256.0f))/2.0f*3.3; //����һ�����Ҳ�	 
		 
	}	 
	cnt += 10;
	
	Struct_OSC_1.BuffFormat = OSC_FORMAT_FLOAT;  	
	Struct_OSC_1.BuffLenth = 2048;				
	Struct_OSC_1.Buff_float = Buff_Sin_float;	
	
	Struct_OSC_2.BuffFormat = OSC_FORMAT_DOUBLE;  	
	Struct_OSC_2.BuffLenth = 2048;				
	Struct_OSC_2.Buff_double = Buff_Sin_double;	
	
	
	Struct_OSC_3.BuffFormat = OSC_FORMAT_U8;  	
	Struct_OSC_3.BuffLenth = 2048;				
	Struct_OSC_3.Buff_u8 = Buff_Sin_u8;	
	
	Struct_OSC_4.BuffFormat = OSC_FORMAT_U16;  	
	Struct_OSC_4.BuffLenth = 2048;				
	Struct_OSC_4.Buff_u16 = Buff_Sin_u16;	
     
	
	OS_Wave_Draw(&Struct_OSC_1,OSC_MODE_LINE_SHOW);//������	
	OS_Wave_Draw(&Struct_OSC_2,OSC_MODE_LINE_SHOW);//������	
	OS_Wave_Draw(&Struct_OSC_3,OSC_MODE_LINE_SHOW);//������	
	OS_Wave_Draw(&Struct_OSC_4,OSC_MODE_LINE_SHOW);//������	
	
	
    return 0;
}	

int OSC_Demo_Start(void)
{  
	
	Struct_OSC_1.ZoomWindows = 0.4f;
	Struct_OSC_1.BackColor = GRAY;
	Struct_OSC_1.WindowsColor = WHITE;
	Struct_OSC_1.x = 30;
	Struct_OSC_1.y = 30;
	
	Struct_OSC_1.ShiftX = 0;
	Struct_OSC_1.ShiftY = 120;
	Struct_OSC_1.ZoomX = 0.4f;
	Struct_OSC_1.ZoomY = 20.0f;
	Struct_OSC_1.LineColor = YELLOW; 
	Struct_OSC_1.LineSize = 1;
	Struct_OSC_1.Mode = OSC_MODE_NORMAL;  
	 
	Struct_OSC_2.ShiftX = 0;
	Struct_OSC_2.ShiftY = 0;
	Struct_OSC_2.ZoomX = 0.8f;
	Struct_OSC_2.ZoomY = 20.0f;
	Struct_OSC_2.LineColor = RED;
	Struct_OSC_2.LineSize = 1;
	Struct_OSC_2.Mode = OSC_MODE_FFT;  
	
	Struct_OSC_3.ShiftX = 0;
	Struct_OSC_3.ShiftY = 80;
	Struct_OSC_3.ZoomX = 0.7f;
	Struct_OSC_3.ZoomY = 1.5f;
	Struct_OSC_3.LineColor = BLUE;
	Struct_OSC_3.LineSize = 2;
	Struct_OSC_3.Mode = OSC_MODE_NORMAL;  
	
	Struct_OSC_4.ShiftX = 0;
	Struct_OSC_4.ShiftY = 0;
	Struct_OSC_4.ZoomX = 0.5f;
	Struct_OSC_4.ZoomY = 2.0f;
	Struct_OSC_4.LineColor = GREEN;
	Struct_OSC_4.LineSize = 1;
	Struct_OSC_4.Mode = OSC_MODE_FFT;  
	
	
	OS_Wave_Unite(&Struct_OSC_1,&Struct_OSC_2); //��Struct_OSC_1����һ������
	OS_Wave_Unite(&Struct_OSC_1,&Struct_OSC_3); //��Struct_OSC_1����һ������
	OS_Wave_Unite(&Struct_OSC_1,&Struct_OSC_4); //��Struct_OSC_1����һ������ 
	
	OS_Wave_Draw(&Struct_OSC_1,OSC_MODE_WINDOWS_SHOW);//������	 
	
    return 0;
}	

Type_AppList App_OSC_Demo = {OSC_Demo_Main,NULL,OSC_Demo_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"OSC_Demo",500};












/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/







