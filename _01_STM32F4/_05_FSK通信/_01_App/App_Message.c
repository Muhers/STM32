/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Message.c
* @Description : FSK数字通信
* @Date        : 2016/7/23
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : PF9发送    PF10接收， 采用曼彻斯特编码
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Message.h"  
 
/* 私有宏定义 ----------------------------------------------------------------*/ 

/* 私有（静态）函数声明 ------------------------------------------------------*/ 
static void Message_Data_Show(void);
static void Message_UI_Show(void);		
static Type_AppList App_MessageShow;
static Type_AppList App_MessageTouch_Scan;
 
/* 全局变量定义 --------------------------------------------------------------*/ 
Type_Message	Message = {0}; 
u8 ch1[MESSAGE_LENTH] = {"2016年省赛"}; 
u8 ch2[MESSAGE_LENTH] = {"AaBbCcDdEeFf"}; 
u8 ch3[MESSAGE_LENTH] = {"无线传输系统"}; 
u8 ch4[MESSAGE_LENTH] = {"Wind起风了"}; 
u8 ch5[MESSAGE_LENTH] = {"知之为知之"}; 
u8 ch6[MESSAGE_LENTH] = {"0123456789"}; 



Type_Button Button_OK = 		{700,190,24,WHITE,YELLOW,(u8 *)"确认"};  
Type_Button Button_Back = 		{500,190,24,WHITE,YELLOW,(u8 *)"<---"};  
Type_Button Button_Reload = 	{600,190,24,WHITE,YELLOW,(u8 *)"重输"};  
Type_Button Button_Send = 		{700,100,32,GREEN,BLUE,(u8 *)"发送"};  
Type_Button Button_Aa = 		{30,430,32,WHITE,GREEN,(u8 *)" Aa "};  
Type_Button Button_Address = 	{400,60,24,WHITE,GRAY,(u8 *)"从机地址:             "};  
Type_Button Button_Content = 	{400,60+24*2,24,WHITE,GRAY,(u8 *)"发送内容:             "};  

Type_Button Button_Ch1 = 	{20,50,24,WHITE,GRAY,ch1};   
Type_Button Button_Ch2 = 	{20,50+24*2,24,WHITE,GRAY,ch2};   
Type_Button Button_Ch3 = 	{20,50+24*4,24,WHITE,GRAY,ch3};  
Type_Button Button_Ch4 = 	{190,50,24,WHITE,GRAY,ch4}; 
Type_Button Button_Ch5 = 	{220,50+24*2,24,WHITE,GRAY,ch5};  
Type_Button Button_Ch6 = 	{220,50+24*4,24,WHITE,GRAY,ch6}; 


/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Message()     
* @Description   : 通信 
* @Data          : 2016/7/23
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Message_Main(void)		
{  	   
 	 
	if(Message.UpData == 1)
	{
		Message.UpData = 0;  
		Message.SenDate = 0;
		Message.ID %= 16;
		
		Message.SenDate = Message.ID << 4;  
		Message.SenDate |= MESSAGE_MODE_MESSEGE;  
		
		Message_SendString(Message.Ch);  		
		 
	}
 
	return 0;																	
}		

unsigned int Message_Start(void)		
{  
	MessageReceive_Init();  
	MessageSend_Init();  	
	OSTask_Creat(&App_MessageShow);  
	OSTask_Creat(&App_VirtualKeyBoard);//虚拟键盘
	OSTask_Creat(&App_MessageTouch_Scan);//触屏扫描
	Message.Mode = 1; 
    Message.Ch[0] = ' ';
	
	return 0;
}
 
Type_AppList App_Message = {Message_Main,NULL,Message_Start,NULL, \
								OS_STATE_ACTIVE,OS_THREAD_3, \
								(u8*)"Message",90};	

 
/**----------------------------------------------------------------------------
* @FunctionName  : MessageShow()     
* @Description   : 通信显示
* @Data          : 2016/7/23
* @Explain       : None
------------------------------------------------------------------------------*/						
unsigned int MessageShow_Main(void)		
{  
	Message_UI_Show();
	Message_Data_Show();
	
	
	return 0;
}
 
static Type_AppList App_MessageShow = {MessageShow_Main,NULL,NULL,NULL, \
										OS_STATE_ACTIVE_ON,OS_THREAD_PRIMARY, \
										(u8*)"MessageShow",200};	

/**----------------------------------------------------------------------------
* @FunctionName  : Message_UI_Show()     
* @Description   : 显示界面
* @Data          : 2016/7/23
* @Explain       : None
------------------------------------------------------------------------------*/																
static void Message_UI_Show(void)
{   
	OS_String_Show(250,0,(u8*)"单工无线信息传输系统",32,1);   
	
	 
}

/**----------------------------------------------------------------------------
* @FunctionName  : Message_Data_Show()     
* @Description   : 显示数据
* @Data          : 2016/7/23
* @Explain       : None
------------------------------------------------------------------------------*/		 									
static void Message_Data_Show(void)
{
	TextColor = WHITE; 
	BackColor = BLACK;	
		
	OS_String_Show(50,200,VKBoard_ResultCh,24,1);
	
	if(Message.ID == 0)
		OS_String_Show(530,70,(u8*)"  群呼  ",24,1);
	else	OS_Num_Show(530,70,Message.ID,4,24,1);	 
	
		
	
	OS_String_Show(530,115,Message.Ch,24,1);  

	
	 
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : MessageTouch_Scan()     
* @Description   : 触屏扫描
* @Data          : 2016/7/23
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int MessageTouch_Scan_Main(void)		
{    
	u16 i = 0;
	OS_Button_Show(&Button_OK,0);
	OS_Button_Show(&Button_Back,0);
	OS_Button_Show(&Button_Reload,0);
	OS_Button_Show(&Button_Send,0);
	OS_Button_Show(&Button_Address,0);
	OS_Button_Show(&Button_Content,0); 
	OS_Button_Show(&Button_Aa,0); 
	OS_Button_Show(&Button_Ch1,0); 
	OS_Button_Show(&Button_Ch2,0); 
	OS_Button_Show(&Button_Ch3,0); 
	OS_Button_Show(&Button_Ch4,0); 
	OS_Button_Show(&Button_Ch5,0); 
	OS_Button_Show(&Button_Ch6,0); 
	
	/* 确认 ------------------------------*/
	if(Button_OK.LastState == 2)
	{
		if(Message.Mode == 2)//选择输入内容
		{
			Button_OK.LastState = 0;
			for(i = 0;i <= VKBoard_Cnt;i++)
			{  
				Message.Ch[i] = VKBoard_ResultCh[i];  
			} 
			
			VK_Buff_Clear();
			
		}
		else if(Message.Mode == 1)//选择输入地址
		{	
			//转存虚拟键盘输入的内容
			Button_OK.LastState = 0;
			
			Message.ID = 0;
			for(i = 0;i < VKBoard_Cnt;i++)
			{ 
				Message.ID *= 10;
				Message.ID += (VKBoard_ResultCh[i] - '0');
			}
			Message.ID %= 16;
			VK_Buff_Clear();
			
		}
		
		OS_String_Show(50,200,(u8*)"                         ",24,1);   
		OS_String_Show(520,70,(u8*)"              ",24,1);	 
		OS_String_Show(520,115,(u8*)"             ",24,1);
		
//		OS_Rect_Draw(520,115,520 + 12*20,139,1,BLACK); 
//		OS_Rect_Draw(50,200,50 + 12*25,200+24,1,BLACK); 
//		OS_Rect_Draw(520,70,520 + 12*14,94,1,BLACK); 
		
		
	}
	
	/* 回退 ------------------------------*/
	if(Button_Back.LastState == 2)
	{
		Button_Back.LastState = 0;  
		if(VKBoard_Cnt > 0)VKBoard_Cnt --;
		VKBoard_ResultCh[i-1] = ' ';
		
		i = VKBoard_Cnt;
		for(i = VKBoard_Cnt;i < MESSAGE_LENTH;i++)
			VKBoard_ResultCh[i] = 0;  
		  
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
		
	}
	
	/* 重输 ------------------------------*/
	if(Button_Reload.LastState == 2)
	{
		Button_Reload.LastState = 0;
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
		VK_Buff_Clear();
	}
	
	/* 发送 ------------------------------*/
	if(Button_Send.LastState == 2)
	{
		Button_Send.LastState = 0;
		Message.UpData = 1;
	}
	
	/* 地址 ------------------------------*/
	if(Button_Address.LastState == 2)
	{
		Button_Address.LastState = 0;
		Message.Mode = 1;
		
		OS_Rect_Draw(Button_Content.x1,Button_Content.y1,Button_Content.x2,Button_Content.y2,0,GRAY); 
		OS_Rect_Draw(Button_Address.x1,Button_Address.y1,Button_Address.x2,Button_Address.y2,0,GREEN); 
		
		VK_Buff_Clear();
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
	}
	
	/* 内容 ------------------------------*/
	if(Button_Content.LastState == 2)
	{
		Button_Content.LastState = 0;
		Message.Mode = 2;
		
		OS_Rect_Draw(Button_Address.x1,Button_Address.y1,Button_Address.x2,Button_Address.y2,0,GRAY);  
		OS_Rect_Draw(Button_Content.x1,Button_Content.y1,Button_Content.x2,Button_Content.y2,0,GREEN); 
		
		VK_Buff_Clear();
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
	}
	
	/* 大小写 ----------------------------*/
	if(Button_Aa.LastState == 2)
	{
		Button_Aa.LastState = 0; 
		if(VKBoard_Aa == 1) VKBoard_Aa = 0;		
		else VKBoard_Aa = 1;
		VirtualKey_FullShow(1);	
	}
	
	/* 中文语句 --------------------------*/
	if(Button_Ch1.LastState == 2)
	{
		Button_Ch1.LastState = 0; 
		for(i = 0;i < MESSAGE_LENTH;i ++)
		{
			Message.Ch[i] = ch1[i]; 
		}  
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
		OS_String_Show(520,70,(u8*)"              ",24,1);	
		OS_String_Show(520,115,(u8*)"             ",24,1);
		
	}	
	
	if(Button_Ch2.LastState == 2)
	{
		Button_Ch2.LastState = 0; 
		for(i = 0;i < MESSAGE_LENTH;i ++)
		{
			Message.Ch[i] = ch2[i]; 
		}  
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
		OS_String_Show(520,70,(u8*)"              ",24,1);	
		OS_String_Show(520,115,(u8*)"             ",24,1);
	}	
	
	if(Button_Ch3.LastState == 2)
	{
		Button_Ch3.LastState = 0; 
		for(i = 0;i < MESSAGE_LENTH;i ++)
		{
			Message.Ch[i] = ch3[i]; 
		}  
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
		OS_String_Show(520,70,(u8*)"              ",24,1);	
		OS_String_Show(520,115,(u8*)"             ",24,1);
	}	
	
	if(Button_Ch4.LastState == 2)
	{
		Button_Ch4.LastState = 0; 
		for(i = 0;i < MESSAGE_LENTH;i ++)
		{
			Message.Ch[i] = ch4[i]; 
		}  
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
		OS_String_Show(520,70,(u8*)"              ",24,1);	
		OS_String_Show(520,115,(u8*)"             ",24,1);
	}	
	
	if(Button_Ch5.LastState == 2)
	{
		Button_Ch5.LastState = 0; 
		for(i = 0;i < MESSAGE_LENTH;i ++)
		{
			Message.Ch[i] = ch5[i]; 
		}  
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
		OS_String_Show(520,70,(u8*)"              ",24,1);	
		OS_String_Show(520,115,(u8*)"             ",24,1);
	}	
	
	if(Button_Ch6.LastState == 2)
	{
		Button_Ch6.LastState = 0; 
		for(i = 0;i < MESSAGE_LENTH;i ++)
		{
			Message.Ch[i] = ch6[i]; 
		}  
		OS_String_Show(50,200,(u8*)"                         ",24,1); 	
		OS_String_Show(520,70,(u8*)"              ",24,1);	
		OS_String_Show(520,115,(u8*)"             ",24,1);
	}	
	
	
	return 0;
} 

unsigned int MessageTouch_Scan_Start(void)	
{
		
	OS_Button_Show(&Button_OK,1);
	OS_Button_Show(&Button_Back,1);
	OS_Button_Show(&Button_Reload,1);
	OS_Button_Show(&Button_Send,1);
	OS_Button_Show(&Button_Address,1);
	OS_Button_Show(&Button_Content,1);
	OS_Button_Show(&Button_Aa,1); 
	OS_Button_Show(&Button_Ch1,1); 
	OS_Button_Show(&Button_Ch2,1); 
	OS_Button_Show(&Button_Ch3,1); 
	OS_Button_Show(&Button_Ch4,1); 
	OS_Button_Show(&Button_Ch5,1); 
	OS_Button_Show(&Button_Ch6,1); 
	
	App_MessageTouch_Scan.thread = OS_THREAD_SYSTEM;
	
	return 0;
}

static Type_AppList App_MessageTouch_Scan = {MessageTouch_Scan_Main,NULL,MessageTouch_Scan_Start,NULL, \
											OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
											(u8*)"MessageTouch_Scan",50};	

			

			


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



								
								
								
								
								
								


