/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/
/**============================================================================
* @FileName    : App_Test.c

*=============================================================================*/ 

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_Test.h"  
 
/* ˽�к궨�� ----------------------------------------------------------------*/
u8 Num[7] = {0};	
u8 Flag=0;
/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֱ������� --------------------------------------------------------------*/
  
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Test()     
* @Description   : None 
* @Data          : 2016/8/8
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Test_Main(void)		
{    
//	static u16 cnt,i;
	
//  	if(SmallCar.Channel_Flag)//���ݸ���
//	{
//				for(i = 0;i<7;i++) //��������
//		{ 	  
//			if(AD_Value[5/2][i] > 500)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),Num[i] = 1;		
//			else SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),Num[i] = 0; 
//		}	
//			SmallCar.Channel_Flag = 0;
//	}
	OS_Decim_Show(0,1,Num[0],1,0);
	OS_Decim_Show(1,1,Num[1],1,0);
	OS_Decim_Show(2,1,Num[2],1,0);
	OS_Decim_Show(3,1,Num[3],1,0);
	OS_Decim_Show(4,1,Num[4],1,0);
	OS_Decim_Show(5,1,Num[5],1,0);
	OS_Decim_Show(6,1,Num[6],1,0);
	
	return 0;																	
}		


////unsigned int Test_Main(void)		
////{ 
////	u8 i;
////	u8 Flag_a=0;
////	if(SmallCar.Channel_Flag)//���ݸ���
////	{
////		Flag=0;
////			for(i=0;i<7;i++)
////		{
////			
////		  if(AD_Value[5/2][i] > 500) 
////			{
////				Flag_a=0;
////			  Flag_a=Flag_a|1<<i;
////				Flag=Flag_a|Flag;
////			}
////			else
////      {
//////				Flag_a=0Xff;
//////			  Flag_a=Flag_a&0<<i;
//////				Flag=Flag_a&Flag;
////			}
////		}
////	SmallCar.Channel_Flag = 0;
////	}
//////	Flag=0x08;
////	for(i=0;i<7;i++)
////	{	
////		if(Flag>>i&0x01)
////		{
////			OS_Decim_Show(i,1,1,1,0);
////		}
////		else
////		{
////			OS_Decim_Show(i,1,0,1,0);
////		}
////	}	
////	return 0;																	
////}		



Type_AppList App_Test = {Test_Main,NULL,NULL,NULL, \
						OS_STATE_ACTIVE_ON,OS_THREAD_FREE, \
						(u8*)"Test",10};			
																
																				
/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/




