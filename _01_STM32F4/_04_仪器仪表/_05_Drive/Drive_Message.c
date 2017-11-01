/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Message.c
* @Description : None
* @Date        : 2016/7/23
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Message.h"							

/* 私有宏定义 ----------------------------------------------------------------*/ 
  
/* 私有（静态）函数声明 ------------------------------------------------------*/  
static void MessageSend0(void);
static void MessageSend1(void);
static void MessageSend_Start(void);
static void MessageSend_End(void);	

/* 全局变量定义 --------------------------------------------------------------*/ 
u8 MessageSendBuff[MESSAGE_LENTH] = {0};
u8 MessageReceiveBuff[MESSAGE_LENTH] = {0};
u8 MessageCnt = 0;  
u32 ReceiveTime[30] = {0};

/* 全局函数编写 --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : MessageSend_Init()     
* @Description   : 短信发送初始化程序 
* @Data          : 2016/7/23
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void MessageSend_Init(void)			
{
    GPIO_InitTypeDef GPIO_InitStructure; 
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	MESSAGE_SEND_PIN = 1; 
}	


/**----------------------------------------------------------------------------
* @FunctionName  : Message_SendByte()     
* @Description   : 短信传输1个字节
* @Data          : 2016/7/23
* @Explain        
-------------------------------------------------------------------------------
* 由高位到低位
------------------------------------------------------------------------------*/
void Message_SendByte(u8 _Data)	
{
	u8 i = 0; 
	MessageSend_Start();	//第一个0是起始码
	
	for(i = 0;i < 8;i++)
		if(_Data & (0x80 >> i))
		{MessageSend1();}
		else MessageSend0(); 
	
	if(Message_OEC(_Data) == 1)MessageSend1();//奇偶校验
	else MessageSend0();  
	
	MessageSend_End();  
}
	
static void MessageSend0(void)			
{ 
	MESSAGE_SEND_PIN = 0; 
	OSdelay_ms(MESSAGE_TS);
	MESSAGE_SEND_PIN = 1; 
	OSdelay_ms(MESSAGE_TS);
}	

static void MessageSend1(void)			
{ 
	MESSAGE_SEND_PIN = 1; 
	OSdelay_ms(MESSAGE_TS);
	MESSAGE_SEND_PIN = 0; 
	OSdelay_ms(MESSAGE_TS);
}	

static void MessageSend_Start(void)			
{ 
	MESSAGE_SEND_PIN = 0; 
	OSdelay_ms(MESSAGE_TS);
	MESSAGE_SEND_PIN = 1; 
	OSdelay_ms(MESSAGE_TS);
}

static void MessageSend_End(void)			
{ 
	MESSAGE_SEND_PIN = 1; 
	OSdelay_ms(MESSAGE_TS*3);
	MESSAGE_SEND_PIN = 0; 
	OSdelay_ms(MESSAGE_TS);
}

/**----------------------------------------------------------------------------
* @FunctionName  : MessageReceive_Init()     
* @Description   : 短信接收初始化程序 
* @Data          : 2016/7/23
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void MessageReceive_Init(void)			
{
	Exti10_Init(); 
}	

/**----------------------------------------------------------------------------
* @FunctionName  : Message_Receive()     
* @Description   : 短信接收函数
* @Data          : 2016/7/23
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void Message_Receive(void)
{
	static u32 LastTime = 0,LastClock = 0; 
	static u8 BitCnt = 0;
	u32 BitTime = 0,i;
	u16 ReceiveData = 0;
	u8 ReceiveBit = 0,LastBit = 0,Twice = 0;
	
	BitTime = TIM_GetCounter(TIM2) + (OS_Clock - LastClock)*0xffffffff - LastTime;
	LastTime = TIM_GetCounter(TIM2);
		 
	if(BitTime > 4.5*MESSAGE_TS*1000) //起始
	{
		BitCnt = 0;
		for(i = 0;i < 22;i ++)ReceiveTime[i] = 0;
	}	
	else if(BitTime >2.5*MESSAGE_TS*1000 && BitTime <4.5*MESSAGE_TS*1000) //终止
	{
		for(i = 1;i < BitCnt;i ++)
		{ 
			if(ReceiveTime[i] > 0.5*MESSAGE_TS*1000&&ReceiveTime[i] < 1.5*MESSAGE_TS*1000) //10ms
			{
				if(Twice)
				{
					if(LastBit) ReceiveData |= (0x100 >> ReceiveBit);		
					ReceiveBit ++;	
				}	
				Twice = ~Twice;				
			}
			else if(ReceiveTime[i] >= 1.5*MESSAGE_TS*1000&&ReceiveTime[i] < 2.5*MESSAGE_TS*1000) //20ms
			{
				LastBit = ~LastBit;
				if(LastBit) ReceiveData |= (0x100 >> ReceiveBit);	
				ReceiveBit ++;
			} 
		}
		
		if((ReceiveData&0x01) == Message_OEC(ReceiveData >> 1))
		{
			MessageReceiveBuff[MessageCnt] = ReceiveData >> 1;
			MessageCnt = (MessageCnt + 1)%MESSAGE_LENTH;
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
	u8 i,P;
	for(i = 0;i < 8;i++)
		if(_Data & (0x80 >> i))P ++; 
	return P%2;
}

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





















