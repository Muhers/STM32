/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Message.c
* @Description : None
* @Date        : 2016/8/8
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Message.h"							

/* ˽�к궨�� ----------------------------------------------------------------*/ 
#define FSK_FREQ 	 20000
#define FSK_T		(1000000/FSK_FREQ)

/* ˽�У���̬���������� ------------------------------------------------------*/  
static void MessageSend0(void);
static void MessageSend1(void);
static void MessageSend_Start(void);
static void MessageSend_End(void);	
static void MessageFSK_H(u16 _ms);
static void MessageFSK_L(u16 _ms);

/* ȫ�ֱ������� --------------------------------------------------------------*/    
Type_Message Message = {0}; 
u32 ReceiveTime[30] = {0};
u16 MessageErrorClock = 0; //40��*60ms = 2.4s
u16 MessageErrorFlag = 0; //  

/* ȫ�ֺ�����д --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : MessageSend_Init()     
* @Description   : ���ŷ��ͳ�ʼ������ 
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void MessageSend_Init(void)			
{
	GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //�˿�����, �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
    GPIO_ResetBits(GPIOB, GPIO_Pin_10); 					 //�����
	
	MESSAGE_SEND_PIN = 1; 
}	


/**----------------------------------------------------------------------------
* @FunctionName  : Message_SendByte()     
* @Description   : ���Ŵ���1���ֽ�
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* �ɸ�λ����λ
------------------------------------------------------------------------------*/
void Message_SendByte(u8 _Data)	
{
	u8 i = 0; 
	MessageSend_Start();	//��һ��0����ʼ��
	
	for(i = 0;i < 8;i++)
	{
		if(_Data & (0x80 >> i)) MessageSend1(); //��������
		else MessageSend0(); 
	}
	if(Message_OEC(_Data) == 1) MessageSend1();//������żУ��
	else MessageSend0();  
	
	MessageSend_End(); //��ֹ�� 
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
* @Description   : ���Ž��ճ�ʼ������ 
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
* @Description   : ���Ž��պ���
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
  
	/* �˵�С���� -----------------------------------------*/	
	if(BitTime < MESSAGE_T*1000/2/10) return; //10%
		
	LastTime = TIM_GetCounter(TIM2);
	LastClock = OS_Clock;
	
	
	if(OS_Clock - MessageErrorClock > 40) //����������
	{
		Message.State = MESSAGE_STATE_AUDIO;//���¿�ʼ	
		MessageErrorFlag = 1;//�������	
	} 
	MessageErrorClock = OS_Clock; 

	/* ��ʼ -----------------------------------------------*/	
	if(BitTime > 4.5*MESSAGE_T*1000) 
	{
		BitCnt = 0;
		for(i = 0;i < 22;i ++)ReceiveTime[i] = 0;
		Message.Cnt = 0;  
	}	
 
	/* ��ֹ -----------------------------------------------*/	
	else if(BitTime >2.5*MESSAGE_T*1000 && BitTime <4.5*MESSAGE_T*1000) 
	{
		/* �������� -------------------------*/
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
		
		/* ��Ϣ��ȡ ------------------------*/
		if((ReceiveData&0x01) == Message_OEC(ReceiveData >> 1))//��żУ��
		{
			Temp = ReceiveData >> 1;
			Message.Data = Temp;
			if(Message.State == MESSAGE_STATE_PREPARE)//׼�������ַ���
			{	
				Message.State = 2;
				Message.Lenth = Temp;
				ByteCnt = 0; 
				 
			}
			else if(Message.State == MESSAGE_STATE_MESSAGE)//��ʼ�����ַ���
			{  
				if(ByteCnt < Message.Lenth)
				{ 
					Message.String[Message.ID][ByteCnt] = Temp; 
					
					if(Message.ID == GROUP_CALL_ID)	//Ⱥ��
					{
						for(i = 0;i < 16;i ++)
							Message.String[i][ByteCnt] = Temp;
					}  
					
					ByteCnt ++;  
				}
				if(ByteCnt >= Message.Lenth)//�ں��油�ո�
				{ 
					for(i = ByteCnt;i < MESSAGE_LENTH-1;i ++)
							Message.String[Message.ID][i] = ' ';
					
					if(Message.ID == GROUP_CALL_ID)	//Ⱥ��
						
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
				
				if(Temp&MESSAGE_MODE_MESSEGE) //�ж���Ϣ
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
* @Description   : ��żУ��
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




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





















