/***************************************************************************************************
  * ��    ����my_pwm.h
  * ��    �ߣ�guojiang 
  * �� �� �壺stm32f103rcʵ���ҿ�����
  * �޸�ʱ�䣺2016.7 

  * �� �� ��: keil.5.20
  *------------------------------------------------------------------------------------------------
  * ��    �飺
  *************************************************************************************************/
/* ��ֹ�ݹ�����Ķ���-----------------------------------------------------------------------------*/

#ifndef  __MY_PWM_H
#define  __MY_PWM_H

#ifdef __cplusplus
 extern "C" {
#endif 


#include "stm32f10x.h"


void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void AMoto_Inti_select(u8 dir);
void BMoto_Inti_select(u8 dir);
void RighA_Moto_select(u8 dir);
void LeftA_Moto_select(u8 dir);	
void RighB_Moto_select(u8 dir);
void LeftB_Moto_select(u8 dir);	
void RighB_PWM(u16 PWM);
void RighA_PWM(u16 PWM);
void LeftA_PWM(u16 PWM);
void LeftB_PWM(u16 PWM);
#ifdef __cplusplus
}
#endif

#endif 
/******************* (C) ***************************�ļ�����*******************************************/



