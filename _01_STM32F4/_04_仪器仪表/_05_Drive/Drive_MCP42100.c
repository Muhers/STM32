/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_MCP42100.c
* @Description : None
* @Date        : 2016/7/21
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_MCP42100.h"							

/* 私有宏定义 ----------------------------------------------------------------*/ 
 
/* 私有（静态）函数声明 ------------------------------------------------------*/  
//static void SendByte(u8 Data);

/* 全局变量定义 --------------------------------------------------------------*/ 
 
/* 全局函数编写 --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : MCP42100_Init()     
* @Description   : MCP42100初始化程序 
* @Data          : 2016/7/21
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void MCP42100_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure; 

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIO时钟 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	/* 使能端配置 ---------------------------------------*/ 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;	
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;	
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6; 	
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10 | GPIO_Pin_11;		
	GPIO_Init(GPIOC,&GPIO_InitStructure);	  
	MCP42100_DISABLE();		
}



/**----------------------------------------------------------------------------
* @FunctionName  : MCP42100_Control()     
* @Description   : MCP42100控制程序 
* @Data          : 2016/7/21
* @Explain        
------------------------------------------------------------------------------- 
_ch 	通道
_value 	值（0~255）
------------------------------------------------------------------------------*/
void MCP42100_Control(u8 _ch,u8 _value)
{	 
	u8 i = 0;
	MCP42100_ENABLE();	   
	for(i = 0;i<8;i++)
	{
		MCP42100_SCK_L(); 
		if(_ch & (0x80>>i)) MCP42100_SI_H();
		else MCP42100_SI_L();
		OSdelay_us(1);
		MCP42100_SCK_H();
		OSdelay_us(1);
	}
	for(i = 0;i<8;i++)
	{
		MCP42100_SCK_L();
		if(_value & (0x80>>i)) MCP42100_SI_H();
		else MCP42100_SI_L();
		OSdelay_us(1);
		MCP42100_SCK_H();
		OSdelay_us(1);
	}
	MCP42100_SCK_L();	 			
	MCP42100_DISABLE();						
}
 


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





















