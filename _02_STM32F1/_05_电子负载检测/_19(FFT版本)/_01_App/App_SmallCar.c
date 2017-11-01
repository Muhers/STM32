/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_SmallCar.c
* @Description : С��
* @Date        : 2016/8/20
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_SmallCar.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/ 
 
/* ȫ�ֱ������� --------------------------------------------------------------*/
static Type_AppList App_SmallCar_ChannelScan; 	
static void EasyPID(int State);	

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar()
* @Description   : С��������
* @Data          : 2016/8/8
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int SmallCar_Main(void)
{
    static u16 cnt = 0; 
	u8 i = 0;
	 
    cnt += 50;
    cnt %= 2400;
    OS_Num_Show(0, 0, SmallCar.LeftSpeed, 5);
    OS_Num_Show(5, 0, SmallCar.RightSpeed, 5);
	 
	for(i = 0;i < 7;i ++)
	{
		if(SmallCar.LastChannelEvent[SmallCar.Cnt] & 0x01 << i) OS_Num_Show(i, 1, 1, 1); 
		else OS_Num_Show(i, 1, 0, 1); 
		 
	} 
	 
	
    return 0;
}

unsigned int SmallCar_Start(void)
{
    SmallCar_Init();
	OSTask_Creat(&App_SmallCar_ChannelScan);  
	
    return 0;
}


Type_AppList App_SmallCar = {SmallCar_Main, NULL, SmallCar_Start, NULL, \
                             OS_STATE_ACTIVE, OS_THREAD_PRIMARY, \
                             (u8 *)"SmallCar", 100
                            };


							
//���������㷨
static void quick_sort(u16 num[], int l, int r)  
{  
    int i, j, x;  
    if (l < r)  
    {  
        i = l;  
        j = r;  
        x = num[i];  
        while (i < j)  
        {  
            while(i < j && num[j] > x)   
                j--; /* ���������ҵ�һ��С��x���� */  
            if(i < j)   
                num[i++] = num[j];  
      
  
            while(i < j && num[i] < x)   
                i++; /* ���������ҵ�һ������x���� */  
            if(i < j)   
                num[j--] = num[i];  
  
        }  
        num[i] = x;  
        quick_sort(num, l, i-1); /* �ݹ���� */  
        quick_sort(num, i+1, r);  
    }  
}  

 
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar()
* @Description   : ͨ��ɨ��
* @Data          : 2016/8/8
* @Explain       : None
------------------------------------------------------------------------------*/							
unsigned int SmallCar_ChannelScan_Main(void)
{
	u16 i = 0; 						
	u8 BitNum[7] = {0};			
	
	
	if(SmallCar.Channel_Flag)//���ݸ���
	{
		for(i = 0;i<CHANNEL_NUM;i++) //��������
		{ 
			quick_sort(SmallCar.Channel[i],0,CHANNEL_LENTH - 1);	  
			if(SmallCar.Channel[i][CHANNEL_LENTH/2] > 500)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[i] = 1;		
			else SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[i] = 0; 
			 
		}	
		 
		
		
		if(BitNum[0] == 0 && BitNum[1] == 0 && BitNum[2] == 0 && BitNum[3] == 0 && BitNum[4] == 0 && BitNum[5] == 0 && BitNum[6] == 0)//�հ�
		{
			OS_String_Show(0,2,(u8*)"ȫ��  ");   
			EasyPID(0xffff); 
		}
		else if(BitNum[0] == 1 && BitNum[6] == 1) //����·��
		{
			EasyPID(0);
			OS_String_Show(0,2,(u8*)"����·");   
		}
		else if(BitNum[0]) //ƫ�����ߣ����ת 
		{ 
			EasyPID(-90);
			OS_String_Show(0,2,(u8*)"���ת");  
		}
		else if(BitNum[6])//ƫ�����ߣ��Ҵ�ת
		{	
			EasyPID(90);
			OS_String_Show(0,2,(u8*)"�Ҵ�ת"); 
		}
		else if(BitNum[3]) //ֱ��
		{ 
			EasyPID(0);
			OS_String_Show(0,2,(u8*)"ֱ��  "); 
			
		}
		else if(BitNum[2])//����ת
		{
			EasyPID(-5);
			OS_String_Show(0,2,(u8*)"����ת"); 
		}
		else if(BitNum[4])//����ת
		{
			EasyPID(5);
			OS_String_Show(0,2,(u8*)"����ת"); 	
		}
		else if(BitNum[1])//��ת
		{
			EasyPID(-10);
			OS_String_Show(0,2,(u8*)"��ת  "); 
		}
		else if(BitNum[5])//��ת
		{
			EasyPID(10);
			OS_String_Show(0,2,(u8*)"��ת  "); 
			
			
		}
		 
		SmallCar.Cnt ++;
		SmallCar.Cnt %= 100;
		SmallCar.Channel_Flag = 0;	
	}
	 
    return 0;
}
static Type_AppList App_SmallCar_ChannelScan = {SmallCar_ChannelScan_Main, NULL, NULL, NULL, \
												OS_STATE_ACTIVE, OS_THREAD_SYSTEM, \
												(u8 *)"SmallCar_ChannelScan", 1
												};
	
												
static void EasyPID(int State)
{
	u16 BasisValue = 2200;
	
	static int LastState = 0xfffe,Integral = 0;  
	
	if(State == 0xffff) State = LastState;
	
	if(LastState == State)
	{
		Integral +=10;
		if(Integral > 200) Integral = 200;
	}
	else 
	{
		Integral --;
	}
	LastState = State;
	
	if(State > 100) State = 100;		
	else if(State < -100) State = -100;		
 
	if(State > 0)//����ƫ
	{ 
		SmallCar_Right_Control(BasisValue - State*BasisValue*2/100 - Integral);			
		SmallCar_Left_Control(BasisValue + Integral); 	
	}
	else if(State < 0)//����ƫ 
	{
		State = -State;
		 
		SmallCar_Right_Control(BasisValue + Integral);			
		SmallCar_Left_Control(BasisValue - State*BasisValue*2/100 - Integral); 	
	}
	else//ֱ��
	{
		SmallCar_Right_Control(BasisValue);			
		SmallCar_Left_Control(BasisValue); 	 
	}
	
}	

 

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							

