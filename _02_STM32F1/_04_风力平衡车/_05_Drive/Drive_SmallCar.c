
/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_SmallCar.h"							

/* ˽�к궨�� ----------------------------------------------------------------*/  

/* ˽�У���̬���������� ------------------------------------------------------*/   

/* ȫ�ֱ������� --------------------------------------------------------------*/    
Type_SmallCar SmallCar = {0};

/* ȫ�ֺ�����д --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Init()
* @Description   : С����ʼ������
* @Data          : 2016/8/8
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/ 
void SmallCar_Init(void)
{
    u16 Voltage;	
	InitAdc_Init(); 	                               //PA0  		��ص�ѹ���	
    OS_String_Show(0,3,(u8 *)"��ѹ��");                
	Voltage=Get_Adc2_Average(0,10);                     
	OS_Decim_Show(3, 3,(double)Voltage/4096*3.3, 2, 2); 
    
//	uart_init(9600);									//PA2 	PA3 	��λ��ͨ��
    GPIO_Key_Init();                                    //PB6           ����
    AMoto_Inti_select(0);   							//PC10  PC11(left) 	PC5  PC4(righ)	A�߷���    �ұߵ����ͬ����ռ�ձ��� ת�ٱ����С   RCC_APB2Periph_TIM1
	BMoto_Inti_select(0);	 							//PC12  PC13(left) 	PC8  PC9(righ)	B�߷���    RCC_APB1Periph_TIM3

    TIM3_PWM_Init(2400 - 1, 1);						//PA6��1�� PA7��2��   PWMƵ��=72 000 000/(9999+1)*(71+1)=100hz   ��ǰ����Ϊ 845Hz
	TIM1_PWM_Init(2400 - 1, 1);						//PA8��1�� PA9��2��   PWMƵ��=72000000/(9999+1)*(71+1)=100hz   ��ǰ����Ϊ 845Hz
    
//      TIM6_Int_Init(10000 - 1, 7200 - 1); 							 // 10000 * 7200/7200 0000  1a
//		TIM8_Configuration();
    IIC_Init();                     			        //PB10  PB11 =====IIC��ʼ��	
    MPU6050_initialize();           			        //=====MPU6050��ʼ��	
    DMP_Init();                    			            //=====��ʼ��DMP
    MiniBalance_EXTI_Init();       			            //PB5=====MPU6050 5ms��ʱ�жϳ�ʼ��
    
    GPIO_Tracking_Init();                               //PC0 PC1 PC2 PC3  PA1 PA4 PA5 PA0  �����·IO������
//    Adc_Init();
//	  DMA_Configuration();
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//    DMA_Cmd(DMA1_Channel1, ENABLE); 								//����DMA ͨ��

    
//		while(((double)Voltage/4096*3.3*3.4-0.2)<7.8)
//		{
//			OS_String_Show(0,0,(u8 *)"��ѹ�������ͣ�");
//			OS_String_Show(0,1,(u8 *)"���磡����");
//		}
}


/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Behind_Control()
* @Description   : ����С�����ҷ��
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed��-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Behind_Control(int Speed)
{
	  u8 direct = 0;//ֹͣ
	
    if(Speed > 2400 ) Speed = 2400;
    else if(Speed < -2400) Speed = -2400;

	  if(Speed > 0) direct = 2;//����
	  else if(Speed < 0) direct = 0;//����
	
	RighB_Moto_select(direct);
    RighB_PWM(abs(Speed));
}
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Right_Control()
* @Description   : ����С��ǰ����
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed��-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Front_Control(int Speed)//ǰ������ٿ���
{
    u8 direct = 0;//ֹͣ
    if(Speed > 2400 )Speed = 2400;
    else if(Speed < -2400) Speed = -2400;
	
	if(Speed > 0) direct = 0;//����
	else if(Speed < 0) direct = 1;//����
	
	RighA_Moto_select(direct);
    RighA_PWM(abs(Speed));//��ǰ�����
   
}
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Right_Control()     
* @Description   : ����С����߷��
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed��-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Left_Control(int Speed)//ǰ������ٿ���
{
      u8 direct = 0;//ֹͣ
      if(Speed > 2400 )Speed = 2400;
      else if(Speed < -2400) Speed = -2400;
	
      if(Speed > 0) direct = 1;//����
      else if(Speed < 0) direct = 0;//����
    
	  LeftA_Moto_select(direct);	
      LeftA_PWM(abs(Speed));	//�Һ󷽷��      


      SmallCar.RightSpeed = Speed;
	
}
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Right_Control()     
* @Description   : ����С���ұ߷��
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed��-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Right_Control(int Speed)//ǰ������ٿ���
{
    u8 direct = 0;//ֹͣ
    if(Speed > 2400 )Speed = 2400;
    else if(Speed < -2400) Speed = -2400;
	
	  if(Speed > 0) direct = 1;//����
	  else if(Speed < 0) direct = 0;//����
	  
      LeftB_Moto_select(direct);	
      LeftB_PWM(abs(Speed));	//��󷽷��
  
	  SmallCar.RightSpeed = Speed;
	
}








