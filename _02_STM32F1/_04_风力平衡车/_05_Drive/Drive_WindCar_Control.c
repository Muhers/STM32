/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸) *********************************/
/**============================================================================
* @FileName    : Drive_WindCar_Control.c
* @Description : None
* @Date        : 2017年7月10日
* @By          : Wind(谢玉伸)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 风力平衡车控制
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_WindCar_Control.h"
#include <math.h>

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/  

/* 全局变量定义 --------------------------------------------------------------*/
//double _kP =	(92.0f); //比例放大系数
//double _kI =	(0.0000f); //积分放大系数
//double _kD =	(100000.0f); //微分放大系数
//double _u0 =	(900);  //基值
//double _eT = 0; //误差
//int PWM_Pre = 0; 
//int PWM_Back = 0;  

double _kP =	(50.0f); //比例放大系数
double _kI =	(0.0001f); //积分放大系数
double _kD =	(100000.0f); //微分放大系数
double _u0 =	(1055);  //基值
double _eT = 0; //误差
int PWM_Pre = 0; 
int PWM_Back = 0;  

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
static void PWM_Set(int pre,int back)
{
	if(pre < 0)pre = 0;
	else if(pre >2400)pre = 2400;
	
	if(back < 0)back = 0;
	else if(back >2400)back = 2400;
	
	PWM_Pre = pre;
	PWM_Back = back;
	
	RighA_Moto_select(1);
	RighB_Moto_select(2);
	RighA_PWM(pre);
	RighB_PWM(back);
	
}   

int PID_Control(void)
{    
	static double integral_error = 0.0f; 		
	static double differential_error = 0.0f; 	
	static double last = 0.0f; 
	static u8 state = 0;
	
	float Input = Angle_Balance;
	long int Output = 0;
	
//	if(KEY == 0) 
//	{  
//		OSdelay_ms(100);
//		while(KEY == 0){}
//		state = !state; 
//	}
	
	if(state == 0)
	{
		integral_error += (Input); //误差积分
		differential_error = (Input - last)*1000; //误差微分
		
		Output = (_u0 + Input*_kP + integral_error*_kI + differential_error*_kD);//PID	
		Output /= (cos(fabs(Angle_Balance)*2*3.14159/360)*cos(fabs(Angle_Balance)*2*3.14159/360));
		if(Output > 2400) Output = 2400;
		
//		PWM_Set(_eT + Output,2400-Output); 
		PWM_Set(2400-Output,Output); 
		
		last = Input;
	}
	else 
	{
		RighA_Moto_select(0);
		RighB_Moto_select(0);
	}		
	
	return 0;
}



/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸) *********************************/







