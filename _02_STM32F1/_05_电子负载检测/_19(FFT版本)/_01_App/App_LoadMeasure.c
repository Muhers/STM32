/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸)*********************************/
/**============================================================================
* @FileName    : App_LoadMeasure.c
* @Date        : 2017年7月27日
* @By          : Wind(谢玉伸)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F103RC)
* @Explain     : 负载检测
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_LoadMeasure.h"


/* 私有宏定义 ----------------------------------------------------------------*/
#define Union32ToSendBuff()				do{ \
											Message_USART2.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[0];byte+=1;	\
											Message_USART2.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[1];byte+=1;	\
											Message_USART2.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[2];byte+=1;	\
											Message_USART2.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[3];byte+=1;	\
										}while(0)	\

/* 私有（静态）函数声明 ------------------------------------------------------*/
static void Message_Updata(void);

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : LoadMeasure()
* @Description   : 负载检测
* @Data          : 2017年7月27日
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int LoadMeasure_Main(void)
{      
	char temp[100] = {0};
//	u16 i = 0; 
	   
	ADC_Result.Freq = FreqMeasure_Read();
	
	if(PhaseMeasure_State == 0)//空闲状态
	{
		PhaseMeasure_Start(ADC_Result.Freq);//开始采AD
	}
	else if(PhaseMeasure_State == 2)//采集完成
	{     
		     
//		for(i = 0;i < ADC_LENTH;i++)//模拟数据
//		{
//			ADC_Buff_I[i] = (sin(2.0f*PI*i*8/ADC_LENTH)+1.0)/2.0f*311;
//			ADC_Buff2[i] = (sin(2.0f*PI*i*8/ADC_LENTH)+1.0)/2.0f*0.32f; 
//		}
		
		//显示AD分析结果   
		ADC_Analysis();
		FFT_Analysis();
		 
		sprintf(temp,"F:%0.2f  ",ADC_Result.Freq);	
		OS_String_Show(0,0,temp);	   
		sprintf(temp,"Ipp:%0.2f  ",ADC_Result.Ipp);	
		OS_String_Show(0,1,temp);	   
		
		PhaseMeasure_State = 0; 
		 
		if(Message_Update_Flag == 1)
		{
			Message_Updata();
			Message_Update_Flag = 0;//更新完毕
		}
	}  
	
    return 0;
}	

unsigned int LoadMeasure_Start(void)
{      
	FreqMeasure_Init();  
	ADC1_Init();
	ADC2_Init();
	GPIO_Relay_Init();//继电器  
	Message_Update_Flag = 1;
	
	RELAY_PIN_SWITCH = 1;//打开开关
	CURRENT_LEVEL(1);//电流模式 （0,亮灯：小电流） 
	
    return 0;
}	


Type_AppList App_LoadMeasure = {LoadMeasure_Main,NULL,LoadMeasure_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_FREE, \
						(u8*)"LoadMeasure",10};


/**----------------------------------------------------------------------------
* @FunctionName  : Message_Updata()
* @Description   : 数据更新
* @Data          : 2017/8/6
* @Explain       : None
------------------------------------------------------------------------------*/ 						
static void Message_Updata(void)
{ 	 
	Union_32 Union32 = {0}; 
	u16 byte = 0;
	
	u16 i = 0;
	for(i = 0;i < PER_FFT_SAVE;i ++)
	{   
		Union32._float = FFT_Result.DiffPhase[i];
		Union32ToSendBuff(); 
		
		Union32._float = FFT_Result.Py[i];
		Union32ToSendBuff();  
	} 
	
	Union32._float = FFT_Result.All_DiffPhase;//总相位
	Union32ToSendBuff();        
	Union32._float = FFT_Result.All_Pf; //功率因数	  				Pf=Py/Ps	
	Union32ToSendBuff();          
	Union32._float = FFT_Result.All_Py; //有功功率(平均功率)  		Py=积分（电压*电流）/常数
	Union32ToSendBuff();   
	
	Union32._float = ADC_Result.V_Max;
	Union32ToSendBuff();        
	Union32._float = ADC_Result.V_Min;
	Union32ToSendBuff();        
	Union32._float = ADC_Result.I_Max;
	Union32ToSendBuff();        
	Union32._float = ADC_Result.I_Min;
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Vpp;
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Ipp;
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Vrms; 
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Irms; 
	Union32ToSendBuff();        
	Union32._float = ADC_Result.V_Shift; //直流偏置  
	Union32ToSendBuff();        
	Union32._float = ADC_Result.I_Shift; //直流偏置   
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Pf; //功率因数	  				Pf=Py/Ps	
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Ps; //视在功率  				Ps=Vrms*Irms
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Py; //有功功率(平均功率)  		Py=积分（电压*电流）/常数
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Freq; //频率 											
	Union32ToSendBuff();
	Union32._float = ADC_Result.DiffPhase; //相位差										
	Union32ToSendBuff();
	
	
	Message_USART2.Send_Buff[MESSAGE_BYTE.ADDRESS_TARGET] = 0x01;
	Message_USART2.Send_Buff[MESSAGE_BYTE.CODE_FUNCTION] = 0xff;//全部数据
	 
	Message_Send_USART2();//传输数据
	Message_Update_Flag = 0;//更新完毕 
} 	

						

/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸)*********************************/







