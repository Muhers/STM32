/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸)*********************************/
/**============================================================================
* @FileName    : App_LoadMeasure.c
* @Date        : 2017年7月27日
* @By          : Wind(谢玉伸)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 负载检测
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_LoadMeasure.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define Union32ToSendBuff()				do{ \
											Message_USART3.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[0];byte+=1;	\
											Message_USART3.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[1];byte+=1;	\
											Message_USART3.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[2];byte+=1;	\
											Message_USART3.Send_Buff[MESSAGE_BYTE.DATA_START + byte] = Union32._u8[3];byte+=1;	\
										}while(0)	\


										
/* 私有（静态）函数声明 ------------------------------------------------------*/
static void Message_Updata(void);
static void LoadMeasure_DataShow(void); 
static void UI_Learn(Type_Recognize_Result Recognize_Result);

/* 全局变量定义 --------------------------------------------------------------*/
static Type_Recognize_Result Recognize_Result = {0}; 
float all_py = 0;
	
/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : LoadMeasure()
* @Description   : 负载检测
* @Data          : 2017年7月27日
* @Explain       : None
------------------------------------------------------------------------------*/
int LoadMeasure_Main(void)
{   
	static float LastFreq = 0;
	
	if(PhaseMeasure_State == 0)//空闲状态
	{  
		ADC_Result.Freq = FreqMeasure_Read(); 
		if(ADC_Result.Freq < MAX_FREQ && ADC_Result.Freq > MIN_FREQ) 
		{   
			PhaseMeasure_Start(ADC_Result.Freq_Sample);//开始采AD
			LastFreq = ADC_Result.Freq;
		}
		else ADC_Result.Freq = LastFreq; 
		
	}
	else if(PhaseMeasure_State == 2)//采集完成
	{      
		//显示AD分析结果   
		ADC_Analysis();  
		PhaseMeasure_State = 0;		
	}  
	
    if(UI_Operat.Busy == 0)
    {
		 LoadMeasure_DataShow();
		 Recognize_New_Update();//谐波分析转换成Recognize结构体 
         Recognize_Result = Load_Recognize(Recognize_New);
         UI_Learn(Recognize_Result); 
		 
    }  
	
	if(Message_Update_Flag == 1)
	{
		Message_Updata();
		Message_Update_Flag = 0;//更新完毕
	}
		
    return 0;
}

int LoadMeasure_Start(void)
{
    u16 i = 0;
	OSTask_Creat(&App_UI_Operation);   
	Bluetooth_Init();//蓝牙
	
	FreqMeasure_Init();  
    DataSave_Read();//读取Flash的数据
	ADC1_Init();//测电压
	ADS1271_Init_1();//测电流
	
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
* @Description   : 数据更新
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
	Union32._float = ADC_Result.Freq; //频率 											
	Union32ToSendBuff();
	Union32._float = ADC_Result.DiffPhase; //相位差										
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
	Union32._float = ADC_Result.DiffPhase_Sum; //相位差										
	Union32ToSendBuff();				
	
	for(i = 0;i < LOAD_MAX;i ++)
	{
		Union32._float = ADC_Result.Others[i];							
		Union32ToSendBuff(); 
	}
	
	
	Union32._float = Recognize_Result.Similarity; //相似度									
	Union32ToSendBuff();
	
	for(i = 0;i < LOAD_MAX;i ++)
	{
		Union32._u8[0] = Recognize_Result.WorkDevice_State[i]; //工作设备状态(WorkDevice_State[0] = 1)表示设备0的状态为1										
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
	
	Message_USART3.Send_Buff[MESSAGE_BYTE.ADDRESS_TARGET] = 0x01;//发给主机
	Message_USART3.Send_Buff[MESSAGE_BYTE.CODE_FUNCTION] = 0xff;//全部数据
	
	Message_Send_USART3();//传输数据
	Message_Update_Flag = 0;//更新完毕 
}




/**----------------------------------------------------------------------------
* @FunctionName  : LoadMeasure_DataShow()
* @Description   : 数据显示
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
	
    if(UI_Operat.Order & UI_ORDER_FLASH_LEARN) //学习
    {
        //转移数据  
        Recognize_Source[UI_Operat.Po_x].Py[UI_Operat.Po_y] = ADC_Result.Py;
		Recognize_Source[UI_Operat.Po_x].Phase[UI_Operat.Po_y] = ADC_Result.DiffPhase;
		
        Recognize_Source[UI_Operat.Po_x].Save_State |= (0x01 << UI_Operat.Po_y);//标记学习
		
		LED2 = !LED2; 
		OSdelay_ms(100); 
		LED2 = !LED2; 
		OSdelay_ms(100); 
		LED2 = !LED2; 
		OSdelay_ms(100); 
		LED2 = !LED2;  
		
		UI_Operat.Order &= ~UI_ORDER_FLASH_LEARN;  
    }
    else if(UI_Operat.Order & UI_ORDER_FLASH_WRITE) //Flash写入
    { 
		LED1 = !LED1; 
        DataSave_Write();//将数据写入Flash   
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
    else if(UI_Operat.Order & UI_ORDER_FLASH_READ) //Flash读取
    { 
		LED1 = !LED1; 
        DataSave_Read();//读取Flash的数据  
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
    else if(UI_Operat.Order & UI_ORDER_FLASH_ERASE) //Flash擦除
    {  
		LED1 = !LED1; 
        DataSave_Erase();///Flash擦除
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

    for(i = 0; i < LOAD_MAX; i ++)//横轴
    {   
		temp = '1'+i;
		sprintf(str,"%s ",&temp);				
		OLED_Str_Show(i*2,0,str,2); 
		
    } 
	if(Recognize_Mode == 1) temp = 'F'; 
	else temp = 'P'; 
		
	sprintf(str,"%s ",&temp);				
	OLED_Str_Show(i*2,0,str,2); 
	
    //画负载状态
    for(i = 0; i < LOAD_MAX; i ++)//横轴
	{ 
		//实时显示工作状态
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
		
		//画选择符号
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


/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸)*********************************/







