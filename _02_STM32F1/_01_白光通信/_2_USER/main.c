#include "codetab.h"
#include "com.h"
int main(void)
{
	int i,t,bit,max=0,min=99;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//�ж���3||3λ��ռ2λ��Ӧ���ȼ�
	SystemInit();
	delay_init();//��ʱ��ʼ��
	OLED_Init();
	FF_Init();	
//	TIM4_Int_Init();//�����ź�����
//    TIM2_Int_Init();//��ʱ
//	TIM5_PWM_Init();
	GPIO_Configuration();	
	
	
/*����*/
/*================================================================================*/
//	GPIO_Configuration();//PB11
//	while(1)
//	{
//	 if(TIM_GetCounter(TIM2)%100>50) PB11=1;
////	 if(TIM_GetCounter(TIM4)%100>50) PB11=1;
//	 else PB11=0;
//////////	OLED_ShowNum(2,2,Light_Singel);		
//////////	PB11=1;
//////////	PB11=0;
//		
//	}
/*================================================================================*/	
//	 
	
	
	
	
	while(1)
	{


		
		
		if(Singel_Flag)
		{
			
			Decode_Data=0;
			bit=8;//�ȴ���λ
			
			for(i=1;i<=8;i++)
			{
			Decode_Data+=Light_Data[i]*(u32)pow(2,i-1);
			OLED_ShowNum(bit--,2,Light_Data[i]);
			}
			
//			OLED_ShowNum(0,4,Decode_Data);	
			if(Light_Singel<100)	
			if(max<Light_Singel) max=Light_Singel;
			
			if(Light_Singel>1&&Light_Singel<100)
			if(min>Light_Singel) min=Light_Singel;
			
			
			OLED_ShowNum(0,0,min);
			OLED_ShowNum(6,0,max);	
			if(Light_Singel<100)	
			OLED_ShowNum(0,6,Light_Singel);	     
		}
		
	    else if(t==0) 
		{
		OLED_CLS();		
		Decode_Data=0;
		for(i=8;i>0;i--){Light_Data[i]=0;OLED_ShowNum(i,2,Light_Data[i]);}
		
		}			
		t=(t+1)%10000;
	                     
			
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}




















