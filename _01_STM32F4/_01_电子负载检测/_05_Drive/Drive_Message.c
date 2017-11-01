/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/11/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F103RC)
* @Explain     : �ӻ�
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Message.h"

/* ˽�к궨�� ----------------------------------------------------------------*/ 

/* ˽�У���̬���������� ------------------------------------------------------*/
static int Message_Analysis(void);

/* ȫ�ֱ������� --------------------------------------------------------------*/  
const Struct_MessageByte MESSAGE_BYTE = \
{
    1,//Ŀ���ַ
    2,//������ַ
    3,//������
    4, //������ʼ��ַ 
    {MESSAGE_LENTH-3, MESSAGE_LENTH-2} //CRC16У����
}; 

const Struct_MessageByte MESSAGE_MASTER_BYTE = \
{
    1,//Ŀ���ַ
    2,//������ַ
    3,//������
    4, //������ʼ��ַ 
    {MESSAGE_MASTER_LENTH-3, MESSAGE_MASTER_LENTH-2} //CRC16У����
}; 

Struct_Message Message_USART3 = {0};		  

/* ȫ�ֺ�����д --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : Message_CRC16_Count()
* @Description   : CRC16����
* @Data          : 2016/11/16
* @Explain       : ��ʼλ��CRCУ��λ������λ���������
------------------------------------------------------------------------------*/
void Message_CRC16_Send(u8 *buff)
{
    u16 TOPBIT = 0x8000, CRC_Result = MESSAGE_CODE_CRC;
    u8 bit;
    u16 byte, ACC;

    for (byte = MESSAGE_BYTE.ADDRESS_TARGET; byte < MESSAGE_BYTE.CRC16[0]; ++byte)//ȥ����ʼ�����ֹ��,��λCRC��
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

    buff[MESSAGE_BYTE.CRC16[1]] = (CRC_Result & 0xff00) >> 8; //CRC��8λ
    buff[MESSAGE_BYTE.CRC16[0]] = CRC_Result & 0x00ff; //CRC��8λ

}


/**----------------------------------------------------------------------------
* @FunctionName  : Message_CRC16_Receive()
* @Description   : CRC16������
* @Data          : 2016/11/16
* @Explain       : ��ʼλ��CRCУ��λ������λ��������㣻У��ɹ�����1�����򷵻�0
------------------------------------------------------------------------------*/
u8 Message_CRC16_Receive(u8 *buff)
{
    u16 TOPBIT = 0x8000, CRC_Result = MESSAGE_CODE_CRC;
    u8 bit;
    u16 byte, ACC;

    for (byte = MESSAGE_MASTER_BYTE.ADDRESS_TARGET; byte < MESSAGE_MASTER_BYTE.CRC16[0]; ++byte)//ȥ����ʼ�����ֹ��,��λCRC��
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

    if(buff[MESSAGE_MASTER_BYTE.CRC16[1]] == (CRC_Result & 0xff00) >> 8) //CRC��8λ
        if(buff[MESSAGE_MASTER_BYTE.CRC16[0]] == (CRC_Result & 0x00ff)) //CRC��8λ
            return 1;

    return 0;
}

/**----------------------------------------------------------------------------
* @FunctionName  : Message_Handle_USART3()
* @Description   : ͨ�Ž���
* @Data          : 2016/11/18
* @Explain       : �����ڴ��ڽ����ж���
------------------------------------------------------------------------------*/
void Message_Handle_USART3(void)
{
    static u32 time = 0, Clock = 0;
    static u16 Receive_Cnt = 0;

    if(TIM_GetCounter(TIM2) + (OS_Clock - Clock) * 0xffffffff - time > MESSAGE_GAP)
    {
        Receive_Cnt = 0;
        Message_USART3.Receive_Flag = 0;//��ʼ���� 
    }

    Message_USART3.Receive_Buff[Receive_Cnt ++] = USART_ReceiveData(USART3);//��ȡ���յ�������

    if(Receive_Cnt >= MESSAGE_MASTER_LENTH)
    {
        if(Message_USART3.Receive_Buff[0] == 0xAA)
            if(Message_USART3.Receive_Buff[MESSAGE_MASTER_LENTH - 1] == 0x55)
                if(Message_CRC16_Receive(Message_USART3.Receive_Buff)) //CRC16У��
                    if(Message_USART3.Receive_Buff[MESSAGE_MASTER_BYTE.ADDRESS_TARGET] == MESSAGE_ADDRESS_LOCAL   //�ж�Ŀ���ַ�Ƿ�Ϊ�Լ�
                            || Message_USART3.Receive_Buff[MESSAGE_MASTER_BYTE.ADDRESS_TARGET] == MESSAGE_ADDRESS_RADIO)	//�ж�Ŀ���ַ�Ƿ�Ϊ�㲥 
						{
							Message_USART3.Receive_Flag = 1;//������� 
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
* @Description   : ͨ�ŷ���
* @Data          : 2016/11/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Message_Send_USART3(void)
{
    int i = 0;
    Message_USART3.Send_Buff[0] = 0xAA;//��ʼ��
    Message_USART3.Send_Buff[MESSAGE_LENTH - 1] = 0x55;//������
    Message_USART3.Send_Buff[MESSAGE_BYTE.ADDRESS_LOCAL] = MESSAGE_ADDRESS_LOCAL;//������ַ
	Message_USART3.Send_Buff[MESSAGE_BYTE.ADDRESS_TARGET] = 0x01;//����
	
    Message_CRC16_Send(Message_USART3.Send_Buff);
	
    for(i = 0; i < MESSAGE_LENTH; i ++)
    {
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET){}; //�ȴ����ͽ��� 	
        USART_SendData(USART3, (u16) Message_USART3.Send_Buff[i]); //����λ����������	
        	
    }
	 
}	
 

/**----------------------------------------------------------------------------
* @FunctionName  : Message_Analysis()
* @Description   : ���ݷ���
* @Data          : 2017/8/6
* @Explain       : 0,�����ݸ���		1�����ݸ�������
------------------------------------------------------------------------------*/
static int Message_Analysis(void)
{ 	 
	Message_Update_Flag = 1;//Ҫ���������
	
	return 0;
} 





/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/




















