
#ifndef  __MY_TIM_H
#define  __MY_TIM_H
	 
	 
#include "stm32f10x_tim.h"	 
	 
void TIM1_Configuration(void);  
void Timer1Config(void);	 
void TIM6_Int_Init(u16 arr,u16 psc);
void TIM7_Int_Init(u16 arr,u16 psc);
#endif 

