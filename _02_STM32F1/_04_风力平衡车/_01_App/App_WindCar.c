/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_WindCar.c
* @Description : None
* @Date        : 2017��7��10��
* @By          : Wind��л���죩
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ƽ�����С��
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_WindCar.h"


/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : App_WindCar()
* @Description   : ƽ�����С��
* @Data          : 2017��7��10��
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int App_WindCar_Main(void)
{    
	char StrBuff[100] = {0};  
	 
	sprintf(StrBuff,"Ang:[%0.2f]%% ",Angle_Balance);
	OS_String_Show(0,0,(u8*)StrBuff); 
	
	sprintf(StrBuff,"Pre:[%0.0f]  ",(float)PWM_Pre);
	OS_String_Show(0,1,(u8*)StrBuff); 
	
	sprintf(StrBuff,"Back:[%0.0f]  ",(float)PWM_Back);
	OS_String_Show(0,2,(u8*)StrBuff); 
	
	sprintf(StrBuff,"��ѹ:[%0.2f]V  ",(float)Get_Adc2_Average(0,10)/4096*3.3*3.4-0.1);
	OS_String_Show(0,3,(u8*)StrBuff); 
	
	  
    return 0;
}	

unsigned int App_WindCar_Start(void)
{   
	OSTask_Creat(&App_WindCar_Control);
//	printf("����С���Ѿ�����������\n");
//	printf("����С���Ѿ�����������\n");
//	printf("����С���Ѿ�����������\n");
	
    return 0;
}	

Type_AppList App_WindCar = {App_WindCar_Main,NULL,App_WindCar_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_FREE, \
						(u8*)"App_WindCar",10};












/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/







