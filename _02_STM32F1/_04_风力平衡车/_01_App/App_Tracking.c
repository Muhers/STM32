
#include "App_SmallCar.h"
 
 
void EasyPID(int State);		
static void quick_sort(u16 num[], int l, int r);
unsigned int SmallCar_ChannelScan_Main(void);
int Wind_Turn_PID(int encoder_left,int encoder_right,float gyro);//ת�����;
/**************************************************************************
�������ܣ�ƽ��PID�㷨
��ڲ������Ƕȡ����ٶȡ�ת��PID����ֵ
����  ֵ��
������
**************************************************************************/
void Wind_Balance_PID(float Angle,float Gyro,int Feedback)
{
   static float now = 0.0f;
//	static float now = 0.0f, old = 0.0f,  temp = 0.0f, Bias,B_Bias;
   static int output = 0.0,B_output=0.0;//balance,B_balance,BasisValue,run=1700,B_run=1700;
//   output=pidLocation(-2,Angle);
    now = pidIncrement(0, -Angle);
    output = -600 + now + Gyro * 1;
//	B_output = 900 - my_pidIncrement(-2,Angle)+Gyro * -1;
   				        //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ��
     
     B_output = 900 + 60 * (Angle) - Gyro * 1;//��700
//    Bias = Angle +2;
//	  balance = 99 * Bias + Gyro * 2;
//    output = -500 + balance;
//    if(State_flag==0)
//       output = -Base_Seed +(Angle+2)*60-Gyro*0.5; //������-3��
//    else
//       output = -Base_Seed +(Angle+2)*60-Gyro*1;   //������-3��
     
	if(output>2400)
	output=2400;
	if(output<-2400)
	output=-2400;
	
	if(B_output>2400)
	B_output=2400;
	if(B_output<-2400)
	B_output=-2400;
   if(Angle<2) 
   SmallCar_Front_Control(output);
   if(Angle>-2)
   SmallCar_Behind_Control(B_output);
   OS_Decim_Show(0, 1, B_output, 5, 0);
//   Wind_Turn_PID(1,2,3);
}
/**************************************************************************
�������ܣ�ƽ�����
��ڲ������Ƕȡ����ٶȡ�ת��PID����ֵ
����  ֵ��ֱ������PWM
������
**************************************************************************/
void Balance_Control(float Angle_,float Gyro_B,  int Feedback_)
{
	if(Blance_GetData_Flag)//ƽ�����
	{
		if((Angle_Balance<20)&&(Angle_Balance>-20)&&(Stop_Moto==0))
		{
			Wind_Balance_PID(Angle_,Gyro_B,Feedback_);
		}
		else
		{
            RighA_Moto_select(0);
            LeftA_Moto_select(0);
            RighB_Moto_select(0);
            LeftB_Moto_select(0);
		}
		Blance_GetData_Flag = 0;
		OS_Decim_Show(0, 0, Angle_Balance, 4, 0);
		OS_Decim_Show(4, 0, Gyro_Balance, 4, 0);
//    OS_Decim_Show(0, 1, Gyro_Turn, 5, 0);
	}
}




/**************************************************************************
�������ܣ�ת�����  �޸�ת���ٶȣ����޸�Turn_Amplitude����
��ڲ���������Z��������
����  ֵ��ת�����PWM
**************************************************************************/
int Wind_Turn_PID(int encoder_left,int encoder_right,float gyro)//ת�����
{
//	 static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
	 static float Turn;
     static int  output_leftPWM=1700,output_rightPWM=1700;
//	  float Turn_Amplitude=88/Flag_sudu,Kp=42,Kd=0;     
//	  //=============ң��������ת����=======================//
//  	if(1==Flag_Left||1==Flag_Right)                      //��һ������Ҫ�Ǹ�����תǰ���ٶȵ����ٶȵ���ʼ�ٶȣ�����С������Ӧ��
//		{
//			if(++Turn_Count==1)
//			Encoder_temp=myabs(encoder_left+encoder_right);
//			Turn_Convert=50/Encoder_temp;
//			if(Turn_Convert<0.6)Turn_Convert=0.6;
//			if(Turn_Convert>3)Turn_Convert=3;
//		}	
//	  else
//		{
//			Turn_Convert=0.9;
//			Turn_Count=0;
//			Encoder_temp=0;
//		}
//		if(1==Flag_Left)	           Turn_Target-=Turn_Convert;
//		else if(1==Flag_Right)	     Turn_Target+=Turn_Convert; 
//		else Turn_Target=0;
//	
//    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===ת���ٶ��޷�
//	  if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
//		if(Flag_Qian==1||Flag_Hou==1)  Kd=0.5;       //0.5 
//		else Kd=0;   //ת���ʱ��ȡ�������ǵľ��� �е�ģ��PID��˼��
//  	//=============ת��PD������=======================//
//		Turn=-Turn_Target*Kp-gyro*Kd;                 //===���Z�������ǽ���PD����
   SmallCar_Left_Control(output_leftPWM);
   SmallCar_Right_Control(output_rightPWM);
	  return Turn;
}

/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar()
* @Description   : ѭ������
* @Data          : 2016/8/8
* @Explain       : ����ֵ����������ƽ��
------------------------------------------------------------------------------*/							
int SmallCar_Tracking(void)
{
	u16 i = 0;
	u8 BitNum[8] = {0};
    if(D0==1)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[0] = 1;
    else        SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[0] = 0;
    if(D1==1)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[1] = 1;
    else        SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[1] = 0;
    if(D2==1)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[2] = 1;
    else        SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[2] = 0;
    if(D3==1)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[3] = 1;
    else        SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[3] = 0;
    if(D4==1)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[4] = 1;
    else        SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[4] = 0;
    if(D5==1)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[5] = 1;
    else        SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[5] = 0; 
    if(D6==1)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[6] = 1;		
    else        SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[6] = 0; 
    if(D7==1)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[7] = 1;		
    else        SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[7] = 0; 
	
    OS_Decim_Show(0,1,BitNum[0],1,0);
	OS_Decim_Show(1,1,BitNum[1],1,0);
	OS_Decim_Show(2,1,BitNum[2],1,0);
	OS_Decim_Show(3,1,BitNum[3],1,0);
	OS_Decim_Show(4,1,BitNum[4],1,0);
	OS_Decim_Show(5,1,BitNum[5],1,0);
	OS_Decim_Show(6,1,BitNum[6],1,0);
	OS_Decim_Show(7,1,BitNum[7],1,0);
////		if(BitNum[0] == 0 && BitNum[1] == 0 && BitNum[2] == 0 && BitNum[3] == 0 && BitNum[4] == 0 && BitNum[5] == 0 && BitNum[6] == 0&& BitNum[7] == 0)//�հ�
////		{
////				EasyPID(0xffff);
////				OS_String_Show(0,2,(u8*)"ȫ��  ");
////				SmallCar.Thiska_flag=1;
////		}
////		else if(BitNum[0] == 1 && BitNum[7] == 1) //����·��
////		{
////			
////			EasyPID(0);
////			OS_String_Show(0,2,(u8*)"����·"); 
////			SmallCar.Thiska_flag=2;
////		}
////		else if(BitNum[0]) //ƫ�����ߣ����ת 
////		{ 
////			EasyPID(-90);
////			OS_String_Show(0,2,(u8*)"���ת"); 						
////			SmallCar.Thiska_flag=3;
////		}
////		else if(BitNum[7])//ƫ�����ߣ��Ҵ�ת
////		{	if(SmallCar.Lastka_flag!=4)	
////			{
////				EasyPID(90);
////				OS_String_Show(0,2,(u8*)"�Ҵ�ת");
////				SmallCar.fuck_flag=0;
////			}
////			SmallCar.Thiska_flag=4;
////		}
////		else if(BitNum[3]|BitNum[4]) //ֱ��
////		{ 
////			
////			EasyPID(0);
////			OS_String_Show(0,2,(u8*)"ֱ��  "); 
////			
////				SmallCar.Thiska_flag=5;
////		}
////		else if(BitNum[2])//����ת
////		{
////			
////			EasyPID(-3);//5
////			OS_String_Show(0,2,(u8*)"����ת"); 
////		
////				SmallCar.Thiska_flag=6;
////		}
////		else if(BitNum[5])//����ת
////		{
////		
////			EasyPID(3);
////			OS_String_Show(0,2,(u8*)"����ת");
////			SmallCar.Thiska_flag=7;
////		}
////		else if(BitNum[1])//��ת
////		{
////		
////			EasyPID(-8);
////			OS_String_Show(0,2,(u8*)"��ת  ");
////						
////			SmallCar.Thiska_flag=8;
////		}
////		else if(BitNum[6])//��ת
////		{
////			
////			EasyPID(8);
////			OS_String_Show(0,2,(u8*)"��ת  ");
////			SmallCar.Thiska_flag=9;
////		}
////		 
////		SmallCar.Cnt ++;
////		SmallCar.Cnt %= 100;
    return 0;
}
		









/*

���³�����ADC��⼤��ѭ����

*/
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar()
* @Description   : ͨ��ɨ�����
* @Data          : 2016/8/8
* @Explain       : None
------------------------------------------------------------------------------*/							
unsigned int SmallCar_ChannelScan_Main(void)
{
	u16 i = 0;
	u8 BitNum[8] = {0};
	
	if(SmallCar.Channel_Flag)//���ݸ���
	{
		for(i = 0;i<CHANNEL_NUM;i++) //��������
		{ 
			quick_sort(SmallCar.Channel[i],0,CHANNEL_LENTH - 1);         
			if(SmallCar.Channel[i][CHANNEL_LENTH/2] > 600)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[i] = 1;		
			else SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[i] = 0; 
		}
        OS_Decim_Show(0,1,BitNum[0],1,0);
        OS_Decim_Show(1,1,BitNum[1],1,0);
        OS_Decim_Show(2,1,BitNum[2],1,0);
        OS_Decim_Show(3,1,BitNum[3],1,0);
        OS_Decim_Show(4,1,BitNum[4],1,0);
        OS_Decim_Show(5,1,BitNum[5],1,0);
        OS_Decim_Show(6,1,BitNum[6],1,0);
        OS_Decim_Show(7,1,BitNum[7],1,0);
		if(BitNum[0] == 0 && BitNum[1] == 0 && BitNum[2] == 0 && BitNum[3] == 0 && BitNum[4] == 0 && BitNum[5] == 0 && BitNum[6] == 0&& BitNum[7] == 0)//�հ�
		{
				EasyPID(0xffff);
				OS_String_Show(0,2,(u8*)"ȫ��  ");
				SmallCar.Thiska_flag=1;
		}
		else if(BitNum[0] == 1 && BitNum[7] == 1) //����·��
		{
			EasyPID(0);
			OS_String_Show(0,2,(u8*)"����·"); 
			SmallCar.Thiska_flag=2;
		}
		else if(BitNum[0]) //ƫ�����ߣ����ת 
		{ 
			EasyPID(-90);
			OS_String_Show(0,2,(u8*)"���ת"); 						
			SmallCar.Thiska_flag=3;
		}
		else if(BitNum[7])//ƫ�����ߣ��Ҵ�ת
		{	if(SmallCar.Lastka_flag!=4)	
			{
				EasyPID(90);
				OS_String_Show(0,2,(u8*)"�Ҵ�ת");
				SmallCar.fuck_flag=0;
			}
			SmallCar.Thiska_flag=4;
		}
		else if(BitNum[3]|BitNum[4]) //ֱ��
		{ 
			
			EasyPID(0);
			OS_String_Show(0,2,(u8*)"ֱ��  "); 
			
				SmallCar.Thiska_flag=5;
		}
		else if(BitNum[2])//����ת
		{
			
			EasyPID(-3);//5
			OS_String_Show(0,2,(u8*)"����ת"); 
		
				SmallCar.Thiska_flag=6;
		}
		else if(BitNum[5])//����ת
		{
		
			EasyPID(3);
			OS_String_Show(0,2,(u8*)"����ת");
			SmallCar.Thiska_flag=7;
		}
		else if(BitNum[1])//��ת
		{
		
			EasyPID(-8);
			OS_String_Show(0,2,(u8*)"��ת  ");
						
			SmallCar.Thiska_flag=8;
		}
		else if(BitNum[6])//��ת
		{
			
			EasyPID(8);
			OS_String_Show(0,2,(u8*)"��ת  ");
			SmallCar.Thiska_flag=9;
		}
		 
		SmallCar.Cnt ++;
		SmallCar.Cnt %= 100;
		SmallCar.Channel_Flag = 0;	
	}
	 
    return 0;
}

												
static void EasyPID(int State)
{
	u16 BasisValue = 1800;//2200
	
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
     if(Stop_Moto==0)
     {
        if(State > 0)//����ƫ
        {
            SmallCar_Right_Control(0);
            SmallCar_Left_Control(2222);
        }
        else if(State < 0)//����ƫ 
        {
            State = -State;
            SmallCar_Right_Control(2222);			
            SmallCar_Left_Control(0); 	
        }
        else//ֱ��
        {
            SmallCar_Right_Control(BasisValue);			
            SmallCar_Left_Control(BasisValue); 	 
        }
     }
}	

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


