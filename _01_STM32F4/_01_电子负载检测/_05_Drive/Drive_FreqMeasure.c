/*******************************(C) COPYRIGHT 2017 Wind(л����) *********************************/
/**============================================================================
* @FileName    : Drive_FreqMeasure.c
* @Description : None
* @Date        : 2017��7��26��
* @By          : Wind(л����)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ��Ƶ��
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_FreqMeasure.h"

/* ˽�к궨�� ----------------------------------------------------------------*/
#define FREQ_PIN PEin(0)

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
static u32 Freq_Time = 0;

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : FreqMeasure_Init(void)
* @Description   : ��Ƶ��
* @Data          : 2017��7��26��
* @Explain       : None
------------------------------------------------------------------------------*/
int FreqMeasure_Init(void)
{  
	Exti0_Init();//PE0 �趨�������ش���
	TIM5_Init();
	 
    return 0;
}	


/**----------------------------------------------------------------------------
* @FunctionName  : FreqMeasure_IRQHandler(void)
* @Description   : ��Ƶ���жϷ�����
* @Data          : 2017��7��26��
* @Explain       : None
------------------------------------------------------------------------------*/
int FreqMeasure_IRQHandler(void)
{   
	static u32 _TimeLast = 0,_TimeOverLast = 0;    
//	if(FREQ_PIN == 0)
//	{
//		_TimeLast = TIM_GetCounter(TIM5);
//		_TimeOverLast = Time_168M_Over;  
//		return -1;
//	}
	
	Freq_Time = TIM_GetCounter(TIM5) + (Time_168M_Over - _TimeOverLast)*0xffffffff - _TimeLast; 
	
	_TimeLast = TIM_GetCounter(TIM5);
	_TimeOverLast = Time_168M_Over; 
	
    return 0;
}	




/**----------------------------------------------------------------------------
* @FunctionName  : FreqMeasure_Read(void)
* @Description   : ��������Ƶ��
* @Data          : 2017��7��26��
* @Explain       : None
------------------------------------------------------------------------------*/
float FreqMeasure_Read(void)
{    
	float _T = 0;
	float _Freq = 0;
	 
	_T = Freq_Time/168.0f;//us
	_Freq = 1000000.0f/_T;//Hz
	
    return _Freq;
}	



/**----------------------------------------------------------------------------
* @FunctionName  : FreqMeasure_Read(void)
* @Description   : ������������ ��λ:us
* @Data          : 2017��7��26��
* @Explain       : None
------------------------------------------------------------------------------*/
float TMeasure_Read(void)
{    
	float _T = 0; 
	 
	_T = Freq_Time/168.0f;//us 
	
    return _T;
}	



/*******************************(C) COPYRIGHT 2017 Wind(л����) *********************************/







