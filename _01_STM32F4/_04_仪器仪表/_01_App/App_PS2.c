/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_PS2.c
* @Description : PS2键盘
* @Date        : 2016/7/16
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_PS2.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/
 
/* 私有（静态）函数声明 ------------------------------------------------------*/
Type_AppList App_PS2_Scan; 
static u8 PS2_Exchage(void);
static void PS2_Num_Input(u16 x,u16 y);
static void PS2_Control(void);

/* 全局变量定义 --------------------------------------------------------------*/
Type_PS2 PS2 = {0};

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : PS2()     
* @Description   : PS2键盘 
* @Data          : 2016/7/16
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int PS2_Main(void)		
{      
	static u8 first = 0;  
	
	if(first == 0)
	{
		first ++;
		PS2_Keyboard_Init();
		OSTask_Creat(&App_PS2_Scan);	
	}  
	 
	PS2_Num_Input(385,378); 
	PS2_Control();
	
	return 0;																	
}	 						
						
Type_AppList App_PS2 = {PS2_Main,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_PRIMARY, \
						(u8*)"PS2",100};			
								
						
unsigned int PS2_Scan_Main(void)		
{    
	PS2_Exchage();			
	Key_StateSweep(&Key_FSM_PS2);   
	return 0;																	
}	 	 				
Type_AppList App_PS2_Scan = {PS2_Scan_Main,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_SYSTEM, \
						(u8*)"PS2_Scan",5};			

				 
						
static u8 PS2_Exchage(void)
{ 
		if(Key_Num_0)
		{  PS2.Now=0,Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Num_1)
			{PS2.Now=1;Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Num_2)
			{PS2.Now=2;Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Num_3)
			{PS2.Now=3;Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Num_4)
			{PS2.Now=4;Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Num_5)
			{PS2.Now=5;Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Num_6)
			{PS2.Now=6;Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Num_7)
			{PS2.Now=7;Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Num_8)
			{PS2.Now=8;Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Num_9)
			{PS2.Now=9;Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Enter)
			{PS2.Now='E';Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Add)
			{PS2.Now='+';Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Minus)
			{PS2.Now='-';Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Ride)
			{PS2.Now='*';Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Div)
			{PS2.Now='/';Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_NumLock)
			{PS2.Now='N';Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Point)
			{PS2.Now='.';Key_FSM_PS2.Key_Mode = 0;}
		else if(Key_Back)
			{PS2.Now='B';Key_FSM_PS2.Key_Mode = 0;}
	    else Key_FSM_PS2.Key_Mode = 0;
		
		return PS2.Now;
}	

			 
static void PS2_Num_Input(u16 x,u16 y)
{
	uint16_t  Temp_TextColor = TextColor; 
	uint16_t  Temp_BackColor = BackColor;
	static u32 NumBuff = 0,DecimBuff = 0;  
	static u8 NumBit = 0,DecimBit = 0,NumDecim = 0;
	static double num = 0.0f;
	x += 16*7;
	y += 52;
	
	if(PS2.State == PS2_STATE_FREE) 
	{
		if(PS2.Now == 'N')  
		{ 
			PS2.State = PS2_STATE_INPUT; //输入开始 
			PS2.Now = PS2_NUM_INVALID; 
			
			NumBuff = 0; 
			DecimBuff = 0;
			
			NumBit = 0;
			DecimBit = 0;
			 
			NumDecim = 0;
			
			num = 0;
			
			OS_Rect_Draw(x-16*7-20,y - 52,x+300,y+35+10,1,MAGENTA); 
			
			TextColor = WHITE;BackColor = MAGENTA; 
			OS_String_Show(x-16*7,y-37,(u8*)"Result:",32,1);  
			
			TextColor = RED;BackColor = YELLOW; 
			OS_Rect_Draw(x,y-40,x+280,y-5,1,YELLOW); 
			OS_Decim_Show(x+10+16*4,y-37,PS2.Result,9,2,32,1); 
			
			OS_Rect_Draw(x,y,x+280,y+35,1,WHITE); 
			
			TextColor = WHITE;BackColor = MAGENTA; 
			OS_String_Show(x-16*7,y,(u8*)"Input:",32,1); 
		} 
	}
	else if(PS2.State == PS2_STATE_INPUT)
	{
		if(PS2.Now == 'N')	 
		{
			TextColor = WHITE;
			BackColor = GRAY;
			PS2.State = PS2_STATE_FREE;//输入取消  
			OS_Rect_Draw(x,y,x+280,y+35,1,GRAY);
			OS_String_Show(x+10,y,(u8*)"Iuput Cancel    ",32,1); 
			PS2.Now = PS2_NUM_INVALID; 
			 	
		}
		else if(PS2.Now == 'E')	 
		{ 
			TextColor = BLACK;
			BackColor = GREEN;
			PS2.State = PS2_STATE_FREE;//输入结束
			PS2.Result = num; 
			PS2.UpData = 1;//数据更新
			OS_Rect_Draw(x,y,x+280,y+35,1,GREEN);	
			OS_String_Show(x+10,y,(u8*)"Loading Success ",32,1);
			
			TextColor = WHITE;BackColor = MAGENTA; 
			OS_String_Show(x-16*7,y-37,(u8*)"Result:",32,1); 
			
			TextColor = RED;BackColor = YELLOW; 
			OS_Rect_Draw(x,y-40,x+280,y-5,1,YELLOW); 
			OS_Decim_Show(x+10+16*4,y-37,PS2.Result,9,2,32,1); 
			
			PS2.Now = PS2_NUM_INVALID; 
			 
		}
		else if((PS2.Now < 10 && NumBit < 9 && DecimBit <2 )|| PS2.Now == '.') 
		{ 
			TextColor = BLACK;
			BackColor = WHITE;
			if(PS2.Now == '.') {NumDecim =1; OS_String_Show(x+218,y,(u8*)".",32,1);}
			else if(NumDecim == 0) 
			{
				NumBuff = NumBuff*10 + PS2.Now; 
				NumBit ++;	 
			}
			else if(NumDecim == 1)
			{
				DecimBuff = DecimBuff*10 + PS2.Now;
				DecimBit ++; 	
			}  
			num = NumBuff + DecimBuff*1.0f/pow(10,DecimBit);
			OS_Decim_Show(x+10+16*4,y,num,9,DecimBit,32,1); 
			PS2.Now = PS2_NUM_INVALID;  
			
			
		}
	}
	
	TextColor = Temp_TextColor;
	BackColor = Temp_BackColor;
	 
}
	

static void PS2_Control(void)
{  
	if(PS2.State == PS2_STATE_FREE) 
	{
		
		if(PS2.Now == 0)
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = 0;
		} 
		
		else if(PS2.Now == 1)
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = 1;
		} 
		
		else if(PS2.Now == 2)//Dowm
		{
			PS2.Now = PS2_NUM_INVALID;
			PS2.Posi++; 
			if(PS2.Posi > KEY_POSI_MAX) PS2.Posi = KEY_POSI_MAX;
			PS2.Select = 2;
		} 
		
		else if(PS2.Now == 3)
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = 3;
		} 
		
		else if(PS2.Now == 4)//Right
		{
			PS2.Now = PS2_NUM_INVALID;
			PS2.Posi++;
			if(PS2.Posi > KEY_POSI_MAX) PS2.Posi = KEY_POSI_MAX;
			PS2.Select = 4;
		} 
		
		else if(PS2.Now == 5)
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = 5;
		} 
		
		else if(PS2.Now == 6)//Left
		{
			PS2.Now = PS2_NUM_INVALID;
			PS2.Posi--;
			if(PS2.Posi < 0) PS2.Posi = 0;
			PS2.Select = 6;
		} 
		
		else if(PS2.Now == 7)
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = 7;
		} 
		
		else if(PS2.Now == 8)//Up
		{
			PS2.Now = PS2_NUM_INVALID;
			PS2.Posi--; 
			if(PS2.Posi < 0) PS2.Posi = 0; 
			PS2.Select = 8;
		} 
		
		else if(PS2.Now == 9)
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = 9;
		} 
		
		else if(PS2.Now == '+')
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = '+';
		} 
		
		else if(PS2.Now == '-')
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = '-';
		} 
		
		else if(PS2.Now == '/')
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = '/';
		} 
		
		else if(PS2.Now == '*')
		{
			PS2.Now = PS2_NUM_INVALID; 
			PS2.Select = '*';
		} 
		
		else if(PS2.Now == 'E')//Enter
		{
			PS2.Now = PS2_NUM_INVALID;	
			PS2.UpData = 1;//数据更新   
		} 
		
	}
	
}

 

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/


















