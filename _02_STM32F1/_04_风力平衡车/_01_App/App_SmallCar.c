
/* ͷ�ļ����� ----------------------------------------------------------------*/

#include "App_SmallCar.h"
#include "math.h"
#include "userPID.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_AppList App_SmallCar_ChannelScan;


/* ȫ�ֱ������� --------------------------------------------------------------*/
u8 Blance_GetData_Flag=0;           //�ǶȻ�ȡ��־λ
u8 Stop_Moto = 0;                   //�������(0��1�ر�)
u16 Base_Seed=500;                  //�����ٶ�ֵ
u8 State_flag = 0;                  //������λ�����Ƶ������
u8 Tracking_Open_Flag=0;            //ѭ������(0�ر�ѭ������ƽ�� 1��ѭ��)

/* ȫ�ֺ�����д --------------------------------------------------------------*/
float BB_BasisValue = -100;//max:2400	


/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar()
* @Description   : ͨ��ɨ�����
* @Data          : 2016/8/8
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int SmallCar_BalanceScan_Main(void)
{ 
    int Feedback_Value;
    Revise_PID();                                               //��λ���޸�PID����
    
    if(Tracking_Open_Flag==1)
        Feedback_Value=SmallCar_Tracking();                     //ѭ������
    else
        Feedback_Value=0;                                       
    Balance_Control(Angle_Balance,Gyro_Balance,Feedback_Value); //ƽ�����
    
    if(KEY==0)                                                  //�������
    { 
        Stop_Moto=~Stop_Moto;
        OSdelay_ms(990);
    }        
    return 0;	
	
	
}

static Type_AppList App_SmallCar_ChannelScan = {SmallCar_BalanceScan_Main, NULL, NULL, NULL, \
												OS_STATE_ACTIVE, OS_THREAD_SYSTEM, \
												(u8 *)"SmallCar_ChannelScan", 3
												};
	

/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/




