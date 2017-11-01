

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_USART.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif 

	   
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
u8 PID_Mode = 1;       //1P,2I,3D,4_u0,5_eT

void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART2，GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//USART2_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART2_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //USART2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口1 

}

//void USART2_IRQHandler(void)                	//串口1中断服务程序
//	{
//	u16 Res;

//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//		{
//		Res =USART_ReceiveData(USART2);	//读取接收到的数据
//		
//		if((USART_RX_STA&0x8000)==0)//接收未完成
//			{
//			if(USART_RX_STA&0x4000)//接收到了0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
//				else USART_RX_STA|=0x8000;	//接收完成了 
//				}
//			else //还没收到0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
//						USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//						USART_RX_STA++; 
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
//					}
//				}
//			}
//     } 

//} 


void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	u16 Res; 
	static u16 cnt = 0;
	static char NumBuff[100] = {0}; 
	float value = 0;
	static char Step = 0;
	u16 i = 0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{ 
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		
		if(Res == '{') {Step = 1;return;}//正在接收 
		else if(Res == '}') {Step = 0;return;}//接收完毕,开始分析  
		else if(Res == '#') {Step = 3;return;}//接收完毕,开始分析  
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
		else if(Step == 2)//计算数值
		{
			NumBuff[cnt] = (char)Res;
			cnt ++;
			cnt %= 100; 
		}
		else if(Step == 3)//计算数值
		{
			printf("设置成功！\n");
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
//		if(USART_RX_STA&0X8000)			//接收到一次数据了
//		{
////			LcdDisplay_Chinese(0,2,"收到数据：");
// 			reclen=USART_RX_STA&0X7FFF;	//得到数据长度
//            USART_RX_BUF[reclen]=0;	 	//加入结束符
//// 			LcdDisplay_char(1,1,USART_RX_BUF);//显示接收到的数据
// 			USART_RX_STA=0;
//			if(USART_RX_BUF[0]=='s')//打开关闭电机
//			{
//                    linshi++;
//                    OS_Decim_Show(1, 0, linshi, 4, 0);
//                    if(linshi%2==1)
//                    {
//                        Stop_Moto=1;
//                        LcdDisplay_Chinese(0,2,(u8*)"关闭电机");
//                    }
//                    else
//                    {
//                        Stop_Moto=0;
//                        LcdDisplay_Chinese(0,2,(u8*)"打开电机");
//                        OLED_CLS();	
//                        OS_Decim_Show(1, 0, PID_P, 4, 0);
//                        OS_Decim_Show(1, 1, PID_I, 4, 0);
//                        OS_Decim_Show(1, 2, PID_D, 4, 0);
//                        OS_Decim_Show(1, 3, Base_Seed, 4, 0);
//                    }
//			}
//			else if(USART_RX_BUF[0]=='p')//PID的P值更改
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
//			else if(USART_RX_BUF[0]=='i')//PID的I值更改
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
//			else if(USART_RX_BUF[0]=='d')//PID的D值更改
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
//			else if(USART_RX_BUF[0]=='b')//基础速度的更改
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

