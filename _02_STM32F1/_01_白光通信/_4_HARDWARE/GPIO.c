#include "GPIO.h"


//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//GPIO初始化

void GPIO_Configuration(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_11);						 //PB.5 输出高
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //端口配置, 推挽输出
 GPIO_Init(GPIOC,&GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz 
 GPIO_ResetBits(GPIOC,GPIO_Pin_4); 						 //输出高 
	
	
	
	
}
 
