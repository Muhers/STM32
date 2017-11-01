/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/
/**============================================================================
* @FileName    : App_LoadMeasure.c
* @Date        : 2017��7��27��
* @By          : Wind(л����)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ���ؼ��
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_LoadMeasure.h"

/* ˽�к궨�� ----------------------------------------------------------------*/
#define Union32ToSendBuff()				do{ \
											Message_USART3.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[0];byte+=1;	\
											Message_USART3.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[1];byte+=1;	\
											Message_USART3.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[2];byte+=1;	\
											Message_USART3.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[3];byte+=1;	\
										}while(0)	\


										
/* ˽�У���̬���������� ------------------------------------------------------*/
static void Message_Updata(void);
static void LoadMeasure_DataShow(void); 
static void UI_Learn(Type_Recognize_Result Recognize_Result);

/* ȫ�ֱ������� --------------------------------------------------------------*/
static Type_Recognize_Result Recognize_Result = {0}; 
float all_py = 0;
	
/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : LoadMeasure()
* @Description   : ���ؼ��
* @Data          : 2017��7��27��
* @Explain       : None
------------------------------------------------------------------------------*/
int LoadMeasure_Main(void)
{   
	static float LastFreq = 0;
	
	if(PhaseMeasure_State == 0)//����״̬
	{  
		ADC_Result.Freq = FreqMeasure_Read(); 
		if(ADC_Result.Freq < MAX_FREQ && ADC_Result.Freq > MIN_FREQ) 
		{   
			PhaseMeasure_Start(ADC_Result.Freq_Sample);//��ʼ��AD
			LastFreq = ADC_Result.Freq;
		}
		else ADC_Result.Freq = LastFreq; 
		
	}
	else if(PhaseMeasure_State == 2)//�ɼ����
	{      
		//��ʾAD�������   
		ADC_Analysis();  
		PhaseMeasure_State = 0;		
	}  
	
    if(UI_Operat.Busy == 0)
    {
		 LoadMeasure_DataShow();
		 Recognize_New_Update();//г������ת����Recognize�ṹ�� 
         Recognize_Result = Load_Recognize(Recognize_New);
         UI_Learn(Recognize_Result); 
		 
    }  
	
	if(Message_Update_Flag == 1)
	{
		Message_Updata();
		Message_Update_Flag = 0;//�������
	}
		
    return 0;
}

int LoadMeasure_Start(void)
{
    u16 i = 0;
	OSTask_Creat(&App_UI_Operation);   
	Bluetooth_Init();//����
	
	FreqMeasure_Init();  
    DataSave_Read();//��ȡFlash������
	ADC1_Init();//���ѹ
	ADS1271_Init_1();//�����
	
    for(i = 0; i < LOAD_MAX; i ++)
    {
        Recognize_Source[i].Name = '1' + i; 
    } 
	Others_Get();
	
    return 0;
}


Type_AppList App_LoadMeasure = {LoadMeasure_Main, NULL, LoadMeasure_Start, NULL, \
                                OS_STATE_ACTIVE, OS_THREAD_FREE, \
                                (u8 *)"LoadMeasure", 10
                               };

							   
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
	
	Union32._float = ADC_Result.Vrms; 
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Irms; 
	Union32ToSendBuff(); 
	Union32._float = ADC_Result.Py; 
	Union32ToSendBuff();     
	Union32._float = ADC_Result.Pw; 
	Union32ToSendBuff();  	
	Union32._float = ADC_Result.Ps;  
	Union32ToSendBuff();        
	Union32._float = ADC_Result.Pf; 
	Union32ToSendBuff();         
	Union32._float = ADC_Result.Freq; //Ƶ�� 											
	Union32ToSendBuff();
	Union32._float = ADC_Result.DiffPhase; //��λ��										
	Union32ToSendBuff();
	
	Union32._float = ADC_Result.Irms_Sum; 
	Union32ToSendBuff();   	
	Union32._float = ADC_Result.Py_Sum;  
	Union32ToSendBuff();   
	Union32._float = ADC_Result.Pw_Sum; 
	Union32ToSendBuff();   
	Union32._float = ADC_Result.Ps_Sum; 
	Union32ToSendBuff();  
	Union32._float = ADC_Result.Pf_Sum; 
	Union32ToSendBuff();   
	Union32._float = ADC_Result.DiffPhase_Sum; //��λ��										
	Union32ToSendBuff();				
	
	for(i = 0;i < LOAD_MAX;i ++)
	{
		Union32._float = ADC_Result.Others[i];							
		Union32ToSendBuff(); 
	}
	
	
	Union32._float = Recognize_Result.Similarity; //���ƶ�									
	Union32ToSendBuff();
	
	for(i = 0;i < LOAD_MAX;i ++)
	{
		Union32._u8[0] = Recognize_Result.WorkDevice_State[i]; //�����豸״̬(WorkDevice_State[0] = 1)��ʾ�豸0��״̬Ϊ1										
		Union32ToSendBuff(); 
	}
	
	for(i = 0;i < LOAD_MAX;i ++)
	{
		Union32._u16[0] = Recognize_Source[i].Save_State; 								
		Union32ToSendBuff(); 
	} 
	
	Union32._u32 = UI_Operat.Po_x; 								
	Union32ToSendBuff();
	
	Union32._u32 = UI_Operat.Po_y; 								
	Union32ToSendBuff();
	
	Message_USART3.Send_Buff[MESSAGE_BYTE.ADDRESS_TARGET] = 0x01;//��������
	Message_USART3.Send_Buff[MESSAGE_BYTE.CODE_FUNCTION] = 0xff;//ȫ������
	
	Message_Send_USART3();//��������
	Message_Update_Flag = 0;//������� 
}




/**----------------------------------------------------------------------------
* @FunctionName  : LoadMeasure_DataShow()
* @Description   : ������ʾ
* @Data          : 2017/8/6
* @Explain       : None
------------------------------------------------------------------------------*/
static void LoadMeasure_DataShow(void)
{
	char str[30] = {0};  
	 
	sprintf(str,"PF:%3.3f ",ADC_Result.Pf);	
	OLED_Str_Show(0,0,str,1); 
	
	sprintf(str,"F:%3.1f",ADC_Result.Freq);	
	OLED_Str_Show(10,0,str,1); 
	
	if(ADC_Result.Irms < 1.0f)
	{  
		sprintf(str,"I:%3.3f mA      ",ADC_Result.Irms*1000.0f);		
		OLED_Str_Show(0,1,str,1);
	}
	else
	{
		sprintf(str,"I:%3.3f A      ",ADC_Result.Irms);		
		OLED_Str_Show(0,1,str,1);
	}
	 
	sprintf(str,"V:%3.3f V       ",ADC_Result.Vrms);				
	OLED_Str_Show(0,2,str,1); 
	
	if(ADC_Result.Py < 1.0f)
	{
		sprintf(str,"P:%3.3f mW       ",ADC_Result.Py*1000.0f);				
		OLED_Str_Show(0,3,str,1); 
	}
	else 
	{
		sprintf(str,"P:%3.3f W       ",ADC_Result.Py);				
		OLED_Str_Show(0,3,str,1); 
	}
	 
}


 


static void UI_Learn(Type_Recognize_Result Recognize_Result)
{
    u16 i = 0;
	char str[30] = {0}; 
	char temp = 0;
	
    if(UI_Operat.Order & UI_ORDER_FLASH_LEARN) //ѧϰ
    {
        //ת������  
        Recognize_Source[UI_Operat.Po_x].Py[UI_Operat.Po_y] = ADC_Result.Py;
		Recognize_Source[UI_Operat.Po_x].Phase[UI_Operat.Po_y] = ADC_Result.DiffPhase;
		
        Recognize_Source[UI_Operat.Po_x].Save_State |= (0x01 << UI_Operat.Po_y);//���ѧϰ
		
		LED2 = !LED2; 
		OSdelay_ms(100); 
		LED2 = !LED2; 
		OSdelay_ms(100); 
		LED2 = !LED2; 
		OSdelay_ms(100); 
		LED2 = !LED2;  
		
		UI_Operat.Order &= ~UI_ORDER_FLASH_LEARN;  
    }
    else if(UI_Operat.Order & UI_ORDER_FLASH_WRITE) //Flashд��
    { 
		LED1 = !LED1; 
        DataSave_Write();//������д��Flash   
		LED1 = !LED1; 
		OSdelay_ms(100); 
		LED1 = !LED1; 
		OSdelay_ms(100); 
		LED1 = !LED1; 
		OSdelay_ms(100); 
		LED1 = !LED1; 
		OSdelay_ms(100); 
        UI_Operat.Order &= ~UI_ORDER_FLASH_WRITE;
    }
    else if(UI_Operat.Order & UI_ORDER_FLASH_READ) //Flash��ȡ
    { 
		LED1 = !LED1; 
        DataSave_Read();//��ȡFlash������  
		LED1 = !LED1; 
		OSdelay_ms(100); 
		LED1 = !LED1; 
		OSdelay_ms(50); 
		LED1 = !LED1; 
		OSdelay_ms(100); 
		LED1 = !LED1; 
		OSdelay_ms(200); 
		LED1 = !LED1; 
		OSdelay_ms(50); 
		LED1 = !LED1; 
		OSdelay_ms(100); 
		LED1 = !LED1; 
		OSdelay_ms(50); 
		LED1 = !LED1; 
		OSdelay_ms(200); 
		
        UI_Operat.Order &= ~UI_ORDER_FLASH_READ;
    }
    else if(UI_Operat.Order & UI_ORDER_FLASH_ERASE) //Flash����
    {  
		LED1 = !LED1; 
        DataSave_Erase();///Flash����
		LED1 = !LED1;
		OSdelay_ms(100);  
		LED1 = !LED1; 
		OSdelay_ms(50);  
		LED1 = !LED1; 
		OSdelay_ms(100);  
		LED1 = !LED1; 
		OSdelay_ms(50);  
		LED1 = !LED1; 
		OSdelay_ms(100);  
		LED1 = !LED1; 
		OSdelay_ms(50);  
		LED1 = !LED1; 
		
        UI_Operat.Order &= ~UI_ORDER_FLASH_ERASE;
    }

    for(i = 0; i < LOAD_MAX; i ++)//����
    {   
		temp = '1'+i;
		sprintf(str,"%s ",&temp);				
		OLED_Str_Show(i*2,0,str,2); 
		
    } 
	if(Recognize_Mode == 1) temp = 'F'; 
	else temp = 'P'; 
		
	sprintf(str,"%s ",&temp);				
	OLED_Str_Show(i*2,0,str,2); 
	
    //������״̬
    for(i = 0; i < LOAD_MAX; i ++)//����
	{ 
		//ʵʱ��ʾ����״̬
		if(Recognize_Result.WorkDevice_State[i] == WORK_STATE || Recognize_Result.WorkDevice_State[i] == 0xff)
		{
			temp = '*';
			sprintf(str,"%s",&temp);				
			OLED_Str_Show(i*2,1,str,2);  
		}
		else 
		{
			temp = 'A'+Recognize_Result.WorkDevice_State[i];
			sprintf(str,"%s",&temp);				
			OLED_Str_Show(i*2,1,str,2);  
		}
		
		//��ѡ�����
		if(i == UI_Operat.Po_x)
		{
			temp = '|';
			sprintf(str,"%s",&temp);				
			OLED_Str_Show(i*2,2,str,2);  
		}
		else
		{
			temp = ' ';
			sprintf(str,"%s",&temp);				
			OLED_Str_Show(i*2,2,str,2); 
		}
		
		if(i == UI_Operat.Po_y)
		{
			temp = 'A'+i;
			sprintf(str,"%s",&temp);				
			OLED_Str_Show(UI_Operat.Po_x*2,3,str,2);  
		}  
		 
	}  
}


/*******************************(C) COPYRIGHT 2017 Wind(л����)*********************************/







