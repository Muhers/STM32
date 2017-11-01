/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Message.c
* @Description : None
* @Date        : 2016/8/8
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Message.h"							

/* 私有宏定义 ----------------------------------------------------------------*/ 
#define FSK_FREQ 	 20000
#define FSK_T		(1000000/FSK_FREQ)

/* 私有（静态）函数声明 ------------------------------------------------------*/  
static void MessageSend0(void);
static void MessageSend1(void);
static void MessageSend_Start(void);
static void MessageSend_End(void);	
static void MessageFSK_H(u16 _ms);
static void MessageFSK_L(u16 _ms);

/* 全局变量定义 --------------------------------------------------------------*/    
Type_Message Message = {0}; 
u32 ReceiveTime[30] = {0};
u16 MessageErrorClock = 0; //40次*60ms = 2.4s
u16 MessageErrorFlag = 0; //  

/* 全局函数编写 --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : MessageSend_Init()     
* @Description   : 短信发送初始化程序 
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void MessageSend_Init(void)			
{
	GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
    GPIO_ResetBits(GPIOB, GPIO_Pin_10); 					 //输出高
	
	MESSAGE_SEND_PIN = 1; 
}	


/**----------------------------------------------------------------------------
* @FunctionName  : Message_SendByte()     
* @Description   : 短信传输1个字节
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* 由高位到低位
------------------------------------------------------------------------------*/
void Message_SendByte(u8 _Data)	
{
	u8 i = 0; 
	MessageSend_Start();	//第一个0是起始码
	
	for(i = 0;i < 8;i++)
	{
		if(_Data & (0x80 >> i)) MessageSend1(); //发送数据
		else MessageSend0(); 
	}
	if(Message_OEC(_Data) == 1) MessageSend1();//发送奇偶校验
	else MessageSend0();  
	
	MessageSend_End(); //终止码 
	OSdelay_ms(200);
}
	
static void MessageSend0(void)			
{  
	MessageFSK_L(MESSAGE_T); 
	MessageFSK_H(MESSAGE_T);
}	

static void MessageSend1(void)			
{ 
	MessageFSK_H(MESSAGE_T); 
	MessageFSK_L(MESSAGE_T);
}	

static void MessageSend_Start(void)			
{ 
	MessageFSK_L(MESSAGE_T);
	MessageFSK_H(MESSAGE_T);
}

static void MessageSend_End(void)			
{  
	MessageFSK_H(MESSAGE_T*3); 
	MessageFSK_L(MESSAGE_T);
}

static void MessageFSK_H(u16 _ms)
{
	u16 i = 0;
	for(i = 0;i < _ms*1000/FSK_T;i ++)
	{
		MESSAGE_SEND_PIN = 1; 
		OSdelay_us(FSK_T/2);  
		MESSAGE_SEND_PIN = 0; 
		OSdelay_us(FSK_T/2);  
	}
}

static void MessageFSK_L(u16 _ms)
{
	MESSAGE_SEND_PIN = 0; 
	OSdelay_ms(_ms); 
}

/**----------------------------------------------------------------------------
* @FunctionName  : MessageReceive_Init()     
* @Description   : 短信接收初始化程序 
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void MessageReceive_Init(void)			
{   
	EXTI11_Init();   
}	


/**----------------------------------------------------------------------------
* @FunctionName  : Message_Receive()     
* @Description   : 短信接收函数
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void Message_Receive(void)
{
	static u32 LastTime = 0,LastClock = 0; 
	static u8 BitCnt = 0;
	static u8 ByteCnt = 0;

		
	u32 BitTime = 0,i = 0,j = 0;
	u16 ReceiveData = 0;
	u8 ReceiveBit = 0,LastBit = 0,Twice = 0;
	u8 Temp = 0;
	
	BitTime = TIM_GetCounter(TIM2) - LastTime + (OS_Clock - LastClock)*0xffff;
  
	/* 滤掉小噪声 -----------------------------------------*/	
	if(BitTime < MESSAGE_T*1000/2/10) return; //10%
		
	LastTime = TIM_GetCounter(TIM2);
	LastClock = OS_Clock;
	
	
	if(OS_Clock - MessageErrorClock > 40) //传输错误矫正
	{
		Message.State = MESSAGE_STATE_AUDIO;//重新开始	
		MessageErrorFlag = 1;//传输出错	
	} 
	MessageErrorClock = OS_Clock; 

	/* 起始 -----------------------------------------------*/	
	if(BitTime > 4.5*MESSAGE_T*1000) 
	{
		BitCnt = 0;
		for(i = 0;i < 22;i ++)ReceiveTime[i] = 0;
		Message.Cnt = 0;  
	}	
 
	/* 终止 -----------------------------------------------*/	
	else if(BitTime >2.5*MESSAGE_T*1000 && BitTime <4.5*MESSAGE_T*1000) 
	{
		/* 分析数据 -------------------------*/
		for(i = 1;i < BitCnt;i ++)
		{ 
			if(ReceiveTime[i] > 0.5*MESSAGE_T*1000&&ReceiveTime[i] < 1.5*MESSAGE_T*1000) //T 
			{
				if(Twice)
				{
					if(LastBit) ReceiveData |= (0x100 >> ReceiveBit);		
					ReceiveBit ++;	
				}	
				Twice = ~Twice;				
			}
			else if(ReceiveTime[i] >= 1.5*MESSAGE_T*1000&&ReceiveTime[i] < 2.5*MESSAGE_T*1000) //2T
			{
				LastBit = ~LastBit;
				if(LastBit) ReceiveData |= (0x100 >> ReceiveBit);	
				ReceiveBit ++;
			} 
		}
		
		/* 消息提取 ------------------------*/
		if((ReceiveData&0x01) == Message_OEC(ReceiveData >> 1))//奇偶校验
		{
			Temp = ReceiveData >> 1;
			Message.Data = Temp;
			if(Message.State == MESSAGE_STATE_PREPARE)//准备接收字符串
			{	
				Message.State = 2;
				Message.Lenth = Temp;
				ByteCnt = 0; 
				 
			}
			else if(Message.State == MESSAGE_STATE_MESSAGE)//开始接收字符串
			{  
				if(ByteCnt < Message.Lenth)
				{ 
					Message.String[Message.ID][ByteCnt] = Temp; 
					
					if(Message.ID == GROUP_CALL_ID)	//群呼
					{
						for(i = 0;i < 16;i ++)
							Message.String[i][ByteCnt] = Temp;
					}  
					
					ByteCnt ++;  
				}
				if(ByteCnt >= Message.Lenth)//在后面补空格
				{ 
					for(i = ByteCnt;i < MESSAGE_LENTH-1;i ++)
							Message.String[Message.ID][i] = ' ';
					
					if(Message.ID == GROUP_CALL_ID)	//群呼
						
					for(j = 0;j < 16;j ++) 
					{
						for(i = ByteCnt;i < MESSAGE_LENTH-1;i ++)
							Message.String[j][i] = ' ';
					}
					Message.State = MESSAGE_STATE_AUDIO; 
				}
				 
			}
			else if(Message.State == MESSAGE_STATE_AUDIO)
			{  
				Message.ID = Temp >>4;
				Message.Order = Temp&0x0f; 
				
				if(Temp&MESSAGE_MODE_MESSEGE) //有短消息
				{   
					MessageErrorFlag = 0;  
					 
					Message.State = MESSAGE_STATE_PREPARE;
					Message.Cnt = 0;
				}
			}
			
			
			
			
		}
	}  
	ReceiveTime[BitCnt] = BitTime; 
	BitCnt = (BitCnt+1)%30;	 
	 
}

 
/**----------------------------------------------------------------------------
* @FunctionName  : Message_OEC()     
* @Description   : 奇偶校验
* @Data          : 2016/7/23
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
u8 Message_OEC(u8 _Data)
{
	u8 i,P = 0;
	for(i = 0;i < 8;i++)
		if(_Data & (0x80 >> i))P ++; 
	return P%2;
}




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





















