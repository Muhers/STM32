/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/11/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F103RC)
* @Explain     : 从机
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Message.h"

/* 私有宏定义 ----------------------------------------------------------------*/ 

/* 私有（静态）函数声明 ------------------------------------------------------*/
static int Message_Analysis(void);

/* 全局变量定义 --------------------------------------------------------------*/  
const Struct_MessageByte MESSAGE_BYTE = \
{
    1,//目标地址
    2,//本机地址
    3,//功能码
    4, //数据起始地址 
    {MESSAGE_LENTH-3, MESSAGE_LENTH-2} //CRC16校验码
}; 

const Struct_MessageByte MESSAGE_MASTER_BYTE = \
{
    1,//目标地址
    2,//本机地址
    3,//功能码
    4, //数据起始地址 
    {MESSAGE_MASTER_LENTH-3, MESSAGE_MASTER_LENTH-2} //CRC16校验码
}; 

Struct_Message Message_USART3 = {0};		  

/* 全局函数编写 --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : Message_CRC16_Count()
* @Description   : CRC16计算
* @Data          : 2016/11/16
* @Explain       : 起始位，CRC校验位，结束位不计入计算
------------------------------------------------------------------------------*/
void Message_CRC16_Send(u8 *buff)
{
    u16 TOPBIT = 0x8000, CRC_Result = MESSAGE_CODE_CRC;
    u8 bit;
    u16 byte, ACC;

    for (byte = MESSAGE_BYTE.ADDRESS_TARGET; byte < MESSAGE_BYTE.CRC16[0]; ++byte)//去掉起始码和终止码,两位CRC码
    {
        ACC = buff[byte];
        CRC_Result ^= (ACC << 8);
        for (bit = 8; bit > 0; --bit)
        {
            if (CRC_Result & TOPBIT)
            {
                CRC_Result = (CRC_Result << 1) ^ 0x8005;
            }
            else
            {
                CRC_Result = (CRC_Result << 1);
            }
        }
    }
    CRC_Result = CRC_Result ^ 0x0000;

    buff[MESSAGE_BYTE.CRC16[1]] = (CRC_Result & 0xff00) >> 8; //CRC高8位
    buff[MESSAGE_BYTE.CRC16[0]] = CRC_Result & 0x00ff; //CRC低8位

}


/**----------------------------------------------------------------------------
* @FunctionName  : Message_CRC16_Receive()
* @Description   : CRC16结果检测
* @Data          : 2016/11/16
* @Explain       : 起始位，CRC校验位，结束位不计入计算；校验成功返回1，否则返回0
------------------------------------------------------------------------------*/
u8 Message_CRC16_Receive(u8 *buff)
{
    u16 TOPBIT = 0x8000, CRC_Result = MESSAGE_CODE_CRC;
    u8 bit;
    u16 byte, ACC;

    for (byte = MESSAGE_MASTER_BYTE.ADDRESS_TARGET; byte < MESSAGE_MASTER_BYTE.CRC16[0]; ++byte)//去掉起始码和终止码,两位CRC码
    {
        ACC = buff[byte];
        CRC_Result ^= (ACC << 8);
        for (bit = 8; bit > 0; --bit)
        {
            if (CRC_Result & TOPBIT)
            {
                CRC_Result = (CRC_Result << 1) ^ 0x8005;
            }
            else
            {
                CRC_Result = (CRC_Result << 1);
            }
        }
    }
    CRC_Result = CRC_Result ^ 0x0000;

    if(buff[MESSAGE_MASTER_BYTE.CRC16[1]] == (CRC_Result & 0xff00) >> 8) //CRC高8位
        if(buff[MESSAGE_MASTER_BYTE.CRC16[0]] == (CRC_Result & 0x00ff)) //CRC低8位
            return 1;

    return 0;
}

/**----------------------------------------------------------------------------
* @FunctionName  : Message_Handle_USART3()
* @Description   : 通信接收
* @Data          : 2016/11/18
* @Explain       : 放置在串口接收中断中
------------------------------------------------------------------------------*/
void Message_Handle_USART3(void)
{
    static u32 time = 0, Clock = 0;
    static u16 Receive_Cnt = 0;

    if(TIM_GetCounter(TIM2) + (OS_Clock - Clock) * 0xffffffff - time > MESSAGE_GAP)
    {
        Receive_Cnt = 0;
        Message_USART3.Receive_Flag = 0;//开始接收 
    }

    Message_USART3.Receive_Buff[Receive_Cnt ++] = USART_ReceiveData(USART3);//读取接收到的数据

    if(Receive_Cnt >= MESSAGE_MASTER_LENTH)
    {
        if(Message_USART3.Receive_Buff[0] == 0xAA)
            if(Message_USART3.Receive_Buff[MESSAGE_MASTER_LENTH - 1] == 0x55)
                if(Message_CRC16_Receive(Message_USART3.Receive_Buff)) //CRC16校验
                    if(Message_USART3.Receive_Buff[MESSAGE_MASTER_BYTE.ADDRESS_TARGET] == MESSAGE_ADDRESS_LOCAL   //判断目标地址是否为自己
                            || Message_USART3.Receive_Buff[MESSAGE_MASTER_BYTE.ADDRESS_TARGET] == MESSAGE_ADDRESS_RADIO)	//判断目标地址是否为广播 
						{
							Message_USART3.Receive_Flag = 1;//接收完毕 
							Message_Analysis(); 
							
						}
						
        Receive_Cnt = 0;
    }
	
    Receive_Cnt %= MESSAGE_MASTER_LENTH;
    Clock = OS_Clock;
    time = TIM_GetCounter(TIM2);
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : Message_Send()
* @Description   : 通信发送
* @Data          : 2016/11/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Message_Send_USART3(void)
{
    int i = 0;
    Message_USART3.Send_Buff[0] = 0xAA;//起始符
    Message_USART3.Send_Buff[MESSAGE_LENTH - 1] = 0x55;//结束符
    Message_USART3.Send_Buff[MESSAGE_BYTE.ADDRESS_LOCAL] = MESSAGE_ADDRESS_LOCAL;//本机地址
	Message_USART3.Send_Buff[MESSAGE_BYTE.ADDRESS_TARGET] = 0x01;//主机
	
    Message_CRC16_Send(Message_USART3.Send_Buff);
	
    for(i = 0; i < MESSAGE_LENTH; i ++)
    {
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET){}; //等待发送结束 	
        USART_SendData(USART3, (u16) Message_USART3.Send_Buff[i]); //向上位机发送数据	
        	
    }
	 
}	
 

/**----------------------------------------------------------------------------
* @FunctionName  : Message_Analysis()
* @Description   : 数据分析
* @Data          : 2017/8/6
* @Explain       : 0,无数据更新		1，数据更新请求
------------------------------------------------------------------------------*/
static int Message_Analysis(void)
{ 	 
	Message_Update_Flag = 1;//要求更新数据
	
	return 0;
} 





/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/




















