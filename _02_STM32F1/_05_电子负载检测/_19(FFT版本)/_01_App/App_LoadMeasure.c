/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/
/**============================================================================
* @FileName    : App_LoadMeasure.c
* @Date        : 2017��7��27��
* @By          : Wind(л����)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F103RC)
* @Explain     : ���ؼ��
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_LoadMeasure.h"


/* ˽�к궨�� ----------------------------------------------------------------*/
#define Union32ToSendBuff()				do{ \
											Message_USART2.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[0];byte+=1;	\
											Message_USART2.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[1];byte+=1;	\
											Message_USART2.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[2];byte+=1;	\
											Message_USART2.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[3];byte+=1;	\
										}while(0)	\

/* ˽�У���̬���������� ------------------------------------------------------*/
static void Message_Updata(void);

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : LoadMeasure()
* @Description   : ���ؼ��
* @Data          : 2017��7��27��
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int LoadMeasure_Main(void)
{      
	char temp[100] = {0};
//	u16 i = 0; 
	   
	ADC_Result.Freq = FreqMeasure_Read();
	
	if(PhaseMeasure_State == 0)//����״̬
	{
		PhaseMeasure_Start(ADC_Result.Freq);//��ʼ��AD
	}
	else if(PhaseMeasure_State == 2)//�ɼ����
	{     
		     
//		for(i = 0;i < ADC_LENTH;i++)//ģ������
//		{
//			ADC_Buff_I[i] = (sin(2.0f*PI*i*8/ADC_LENTH)+1.0)/2.0f*311;
//			ADC_Buff2[i] = (sin(2.0f*PI*i*8/ADC_LENTH)+1.0)/2.0f*0.32f; 
//		}
		
		//��ʾAD�������   
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
			Message_Update_Flag = 0;//�������
		}
	}  
	
    return 0;
}	

unsigned int LoadMeasure_Start(void)
{      
	FreqMeasure_Init();  
	ADC1_Init();
	ADC2_Init();
	GPIO_Relay_Init();//�̵���  
	Message_Update_Flag = 1;
	
	RELAY_PIN_SWITCH = 1;//�򿪿���
	CURRENT_LEVEL(1);//����ģʽ ��0,���ƣ�С������ 
	
    return 0;
}	


Type_AppList App_LoadMeasure = {LoadMeasure_Main,NULL,LoadMeasure_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_FREE, \
						(u8*)"LoadMeasure",10};


/**----------------------------------------------------------------------------
* @FunctionName  : Message_Updata()
* @Description   : ���ݸ���
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
	
	Union32._float = FFT_Result.All_DiffPhase;//����λ
	Union32ToSendBuff();        
	Union32._float = FFT_Result.All_Pf; //��������	  				Pf=Py/Ps	
	Union32ToSendBuff();          
	Union32._float = FFT_Result.All_Py; //�й�����(ƽ������)  		Py=���֣���ѹ*������/����
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
	Union32._float = ADC_Result.V_Shift; //ֱ��ƫ��  
	Union32ToSendBuff();        
	Union32._float = ADC_Result.I_Shift; //ֱ��ƫ��   
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Pf; //��������	  				Pf=Py/Ps	
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Ps; //���ڹ���  				Ps=Vrms*Irms
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Py; //�й�����(ƽ������)  		Py=���֣���ѹ*������/����
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Freq; //Ƶ�� 											
	Union32ToSendBuff();
	Union32._float = ADC_Result.DiffPhase; //��λ��										
	Union32ToSendBuff();
	
	
	Message_USART2.Send_Buff[MESSAGE_BYTE.ADDRESS_TARGET] = 0x01;
	Message_USART2.Send_Buff[MESSAGE_BYTE.CODE_FUNCTION] = 0xff;//ȫ������
	 
	Message_Send_USART2();//��������
	Message_Update_Flag = 0;//������� 
} 	

						

/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/







