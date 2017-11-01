
/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_SmallCar.h"							

/* 私有宏定义 ----------------------------------------------------------------*/  

/* 私有（静态）函数声明 ------------------------------------------------------*/   

/* 全局变量定义 --------------------------------------------------------------*/    
Type_SmallCar SmallCar = {0};

/* 全局函数编写 --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Init()
* @Description   : 小车初始化程序
* @Data          : 2016/8/8
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/ 
void SmallCar_Init(void)
{
    u16 Voltage;	
	InitAdc_Init(); 	                               //PA0  		电池电压检测	
    OS_String_Show(0,3,(u8 *)"电压：");                
	Voltage=Get_Adc2_Average(0,10);                     
	OS_Decim_Show(3, 3,(double)Voltage/4096*3.3, 2, 2); 
    
//	uart_init(9600);									//PA2 	PA3 	上位机通信
    GPIO_Key_Init();                                    //PB6           按键
    AMoto_Inti_select(0);   							//PC10  PC11(left) 	PC5  PC4(righ)	A边风扇    右边电机在同样的占空比下 转速比左边小   RCC_APB2Periph_TIM1
	BMoto_Inti_select(0);	 							//PC12  PC13(left) 	PC8  PC9(righ)	B边风扇    RCC_APB1Periph_TIM3

    TIM3_PWM_Init(2400 - 1, 1);						//PA6（1） PA7（2）   PWM频率=72 000 000/(9999+1)*(71+1)=100hz   当前设置为 845Hz
	TIM1_PWM_Init(2400 - 1, 1);						//PA8（1） PA9（2）   PWM频率=72000000/(9999+1)*(71+1)=100hz   当前设置为 845Hz
    
//      TIM6_Int_Init(10000 - 1, 7200 - 1); 							 // 10000 * 7200/7200 0000  1a
//		TIM8_Configuration();
    IIC_Init();                     			        //PB10  PB11 =====IIC初始化	
    MPU6050_initialize();           			        //=====MPU6050初始化	
    DMP_Init();                    			            //=====初始化DMP
    MiniBalance_EXTI_Init();       			            //PB5=====MPU6050 5ms定时中断初始化
    
    GPIO_Tracking_Init();                               //PC0 PC1 PC2 PC3  PA1 PA4 PA5 PA0  激光八路IO口输入
//    Adc_Init();
//	  DMA_Configuration();
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//    DMA_Cmd(DMA1_Channel1, ENABLE); 								//启动DMA 通道

    
//		while(((double)Voltage/4096*3.3*3.4-0.2)<7.8)
//		{
//			OS_String_Show(0,0,(u8 *)"电压电量过低！");
//			OS_String_Show(0,1,(u8 *)"请充电！！！");
//		}
}


/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Behind_Control()
* @Description   : 控制小车左右风机
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed：-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Behind_Control(int Speed)
{
	  u8 direct = 0;//停止
	
    if(Speed > 2400 ) Speed = 2400;
    else if(Speed < -2400) Speed = -2400;

	  if(Speed > 0) direct = 2;//正向
	  else if(Speed < 0) direct = 0;//反向
	
	RighB_Moto_select(direct);
    RighB_PWM(abs(Speed));
}
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Right_Control()
* @Description   : 控制小车前面风机
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed：-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Front_Control(int Speed)//前电机风速控制
{
    u8 direct = 0;//停止
    if(Speed > 2400 )Speed = 2400;
    else if(Speed < -2400) Speed = -2400;
	
	if(Speed > 0) direct = 0;//正向
	else if(Speed < 0) direct = 1;//反向
	
	RighA_Moto_select(direct);
    RighA_PWM(abs(Speed));//正前方风机
   
}
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Right_Control()     
* @Description   : 控制小车左边风机
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed：-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Left_Control(int Speed)//前电机风速控制
{
      u8 direct = 0;//停止
      if(Speed > 2400 )Speed = 2400;
      else if(Speed < -2400) Speed = -2400;
	
      if(Speed > 0) direct = 1;//正向
      else if(Speed < 0) direct = 0;//反向
    
	  LeftA_Moto_select(direct);	
      LeftA_PWM(abs(Speed));	//右后方风机      


      SmallCar.RightSpeed = Speed;
	
}
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar_Right_Control()     
* @Description   : 控制小车右边风机
* @Data          : 2016/8/8
* @Explain        
-------------------------------------------------------------------------------
* Speed：-2400~+2400
------------------------------------------------------------------------------*/ 
void SmallCar_Right_Control(int Speed)//前电机风速控制
{
    u8 direct = 0;//停止
    if(Speed > 2400 )Speed = 2400;
    else if(Speed < -2400) Speed = -2400;
	
	  if(Speed > 0) direct = 1;//正向
	  else if(Speed < 0) direct = 0;//反向
	  
      LeftB_Moto_select(direct);	
      LeftB_PWM(abs(Speed));	//左后方风机
  
	  SmallCar.RightSpeed = Speed;
	
}








