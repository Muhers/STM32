

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_USART.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 

	   
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
u8 PID_Mode = 1;       //1P,2I,3D,4_u0,5_eT

void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART2��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//USART2_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART2_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //USART2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���1 

}

//void USART2_IRQHandler(void)                	//����1�жϷ������
//	{
//	u16 Res;

//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
//		
//		if((USART_RX_STA&0x8000)==0)//����δ���
//			{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//				else USART_RX_STA|=0x8000;	//��������� 
//				}
//			else //��û�յ�0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
//						USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//						USART_RX_STA++; 
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}
//				}
//			}
//     } 

//} 


void USART2_IRQHandler(void)                	//����1�жϷ������
{
	u16 Res; 
	static u16 cnt = 0;
	static char NumBuff[100] = {0}; 
	float value = 0;
	static char Step = 0;
	u16 i = 0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{ 
		Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
		
		if(Res == '{') {Step = 1;return;}//���ڽ��� 
		else if(Res == '}') {Step = 0;return;}//�������,��ʼ����  
		else if(Res == '#') {Step = 3;return;}//�������,��ʼ����  
		//   {P 123##}
		
		if(Step == 1)
		{
			if(Res == 'P') PID_Mode = 1; 
			else if(Res == 'I') PID_Mode = 2; 
			else if(Res == 'D') PID_Mode = 3; 
			else if(Res == 'U') PID_Mode = 4; 
			else if(Res == 'E') PID_Mode = 5;  
			cnt = 0; 
			Step = 2;
		}
		else if(Step == 2)//������ֵ
		{
			NumBuff[cnt] = (char)Res;
			cnt ++;
			cnt %= 100; 
		}
		else if(Step == 3)//������ֵ
		{
			printf("���óɹ���\n");
			value = atof(NumBuff);
			if(PID_Mode == 1) {_kP = value;			printf("[_kP]:%0.4f",_kP);}
			else if(PID_Mode == 2) {_kI = value;	printf("[_kI]:%0.4f",_kI);}
			else if(PID_Mode == 3) {_kD = value;	printf("[_kD]:%0.4f",_kD);}
			else if(PID_Mode == 4) {_u0 = value;	printf("[_u0]:%0.4f",_u0);}
			else if(PID_Mode == 5) {_eT = value;	printf("[_eT]:%0.4f",_eT);}
			printf(" \n\n\n\n\n");
			printf("%s",NumBuff);
			printf(" \n\n\n\n\n");
			
			for(i = 0;i < 100 ;i++)
			{
				NumBuff[i] = 0;
			}
			Step = 4;
		}
		
		
     } 

}  
	
u8 reclen=0; 
u8 linshi=0;

void Revise_PID(void)
{
//    static u8 i=1;
//		if(USART_RX_STA&0X8000)			//���յ�һ��������
//		{
////			LcdDisplay_Chinese(0,2,"�յ����ݣ�");
// 			reclen=USART_RX_STA&0X7FFF;	//�õ����ݳ���
//            USART_RX_BUF[reclen]=0;	 	//���������
//// 			LcdDisplay_char(1,1,USART_RX_BUF);//��ʾ���յ�������
// 			USART_RX_STA=0;
//			if(USART_RX_BUF[0]=='s')//�򿪹رյ��
//			{
//                    linshi++;
//                    OS_Decim_Show(1, 0, linshi, 4, 0);
//                    if(linshi%2==1)
//                    {
//                        Stop_Moto=1;
//                        LcdDisplay_Chinese(0,2,(u8*)"�رյ��");
//                    }
//                    else
//                    {
//                        Stop_Moto=0;
//                        LcdDisplay_Chinese(0,2,(u8*)"�򿪵��");
//                        OLED_CLS();	
//                        OS_Decim_Show(1, 0, PID_P, 4, 0);
//                        OS_Decim_Show(1, 1, PID_I, 4, 0);
//                        OS_Decim_Show(1, 2, PID_D, 4, 0);
//                        OS_Decim_Show(1, 3, Base_Seed, 4, 0);
//                    }
//			}
//			else if(USART_RX_BUF[0]=='p')//PID��Pֵ����
//			{
//				PID_P=0;i=1;
//				while(USART_RX_BUF[i]!='\0')
//				{
//						PID_P+=(USART_RX_BUF[i]-'0');
//						PID_P*=10;
//						i++;
//				}
//				PID_P/=10;
//				LcdDisplay_char(0,0,(u8*)"P:");
//				OS_Decim_Show(1, 0, PID_P, 4, 0);
//			}
//			else if(USART_RX_BUF[0]=='i')//PID��Iֵ����
//			{
//				PID_I=0;i=1;
//				while(USART_RX_BUF[i]!='\0')
//				{
//						PID_I+=(USART_RX_BUF[i]-'0');
//						PID_I*=10;
//						i++;
//				}
//				PID_I/=10;
//				LcdDisplay_char(0,1,(u8*)"I:"); 
//				OS_Decim_Show(1, 1, PID_I, 4, 0);
//			}
//			else if(USART_RX_BUF[0]=='d')//PID��Dֵ����
//			{
//				PID_D=0;i=1;
//				while(USART_RX_BUF[i]!='\0')
//				{
//						PID_D+=(USART_RX_BUF[i]-'0');
//						PID_D*=10;
//						i++;
//				}	
//				PID_D/=10;
//				LcdDisplay_char(0,2,(u8*)"D:"); 
//				OS_Decim_Show(1, 2, PID_D, 2, 0);
//			}
//			else if(USART_RX_BUF[0]=='b')//�����ٶȵĸ���
//			{
//				Base_Seed=0;i=1;
//				while(USART_RX_BUF[i]!='\0')
//				{
//						Base_Seed+=(USART_RX_BUF[i]-'0');
//						Base_Seed*=10;
//						i++;
//				}
//				Base_Seed/=10;
//				LcdDisplay_char(0,3,(u8*)"B:");
//				OS_Decim_Show(1, 3, Base_Seed, 4, 0);
//			}
//            Extern_pid_value.kp = PID_P;
//            Extern_pid_value.ki = PID_I;
//            Extern_pid_value.kd = PID_D;
//        }
}

