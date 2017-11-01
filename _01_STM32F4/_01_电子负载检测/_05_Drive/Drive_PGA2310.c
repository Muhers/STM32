/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_PGA2310.c
* @Description : None
* @Date        : 2016/7/29
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_PGA2310.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define PGA2310_MUTE   		GPIOF_OUT(6)
#define PGA2310_CLK    		GPIOF_OUT(8) 
#define PGA2310_SDI   		GPIOF_OUT(10)
#define PGA2310_CS    		GPIOF_OUT(12)   

#define PGA2310_MUTE_1  	GPIOF_OUT(5)
#define PGA2310_CLK_1    	GPIOF_OUT(7) 
#define PGA2310_SDI_1    	GPIOF_OUT(9)
#define PGA2310_CS_1    	GPIOF_OUT(11)   


/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : PGA2310_Init()
* @Description   : PGA2310初始化程序
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void PGA2310_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    PGA2310_CLK = 1;
    PGA2310_SDI = 1;
    PGA2310_CS = 1;
    PGA2310_MUTE = 1;  
	
	PGA2310_CLK_1 = 1;
    PGA2310_SDI_1 = 1;
    PGA2310_CS_1 = 1;
    PGA2310_MUTE_1 = 1; 
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : PGA2310_Mute()
* @Description   : PGA2310静音控制
* @Data          : 2016/7/21
* @Explain
-------------------------------------------------------------------------------
NewState : ENABLE or DISABLE
------------------------------------------------------------------------------*/
void PGA2310_Mute( FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        PGA2310_MUTE = 1;
		PGA2310_MUTE_1 = 1;
    }
    else
    {
        PGA2310_MUTE = 0;
		PGA2310_MUTE_1 = 0;
    }
}

 
/**----------------------------------------------------------------------------
* @FunctionName  : PGA2310_Data_Send()
* @Description   : PGA2310发送数据
* @Data          : 2016/7/29
* @Explain
------------------------------------------------------------------------------- 
Data：右通道在高8位，左通道在低8位
------------------------------------------------------------------------------*/
void PGA2310_Data_Send(u16 Data)
{
    uint8_t i;
    PGA2310_CS = 0; //使能，即片选 
	PGA2310_CS_1 = 0; //使能，即片选 
    OSdelay_ms(1); 
    for(i = 0; i < 16; i++ )
    { 
        if( Data & 0x8000 )
        {
            PGA2310_SDI = 1;
			PGA2310_SDI_1 = 1;
        }		
        else	
        {	
            PGA2310_SDI = 0;
			PGA2310_SDI_1 = 0;
        } 	
		OSdelay_us(100);
        PGA2310_CLK = 1;
        PGA2310_CLK_1 = 1;
		
        OSdelay_us(100);
        PGA2310_CLK = 0; 
		PGA2310_CLK_1 = 0;
		
		Data <<= 1;
    }
    PGA2310_CS = 1; //失能
	PGA2310_CS_1 = 1; //失能
}


/**----------------------------------------------------------------------------
* @FunctionName  : PGA2310_Control()
* @Description   : PGA2310放大控制
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
Right: 右通道放大倍数 Left: 左通道放大倍数
数据格式：右通道在高8位，左通道在低8位
------------------------------------------------------------------------------*/
void PGA2310_Control(u8 Right, u8 Left)
{
    u16 Data;
    Data = Right;
    Data = (Data << 8) + Left;
    PGA2310_Data_Send(Data);
}


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/










