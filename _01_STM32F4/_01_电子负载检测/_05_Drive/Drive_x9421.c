/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_x9421.c
* @Description : x9421数字电位器测试
* @Date        : 2016/7/29
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_x9421.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define  X9421_Address  0x5a  //高4位地址为0101（器件类型辨识符），低4位地址由A3~A0输入端状态决定

//寄存器0~3
#define  X9421_REG   (0x03)
#define  X9421_REG0  (0x00)
#define  X9421_REG1  (0x01)
#define  X9421_REG2  (0x02)
#define  X9421_REG3  (0x03)

//数字电位器0~3（Digital Potentiometer）
#define  X9421_DP   (0x03<<2)
#define  X9421_DP0  (0x00<<2)
#define  X9421_DP1  (0x01<<2)
#define  X9421_DP2  (0x02<<2)
#define  X9421_DP3  (0x03<<2)

//指令 
#define  ReadWCR       (0x09<<4)
#define  WriteWCR      (0x0a<<4)
#define  ReadREG       (0x0b<<4)
#define  WriteREG      (0x0c<<4)
#define  REGtoWCR_one  (0x0d<<4)
#define  WCRtoREG_one  (0x0e<<4)
#define  REGtoWCR_all  (0x01<<4)
#define  WCRtoREG_all  (0x08<<4)
#define  Inc_Dec_WCR   (0x02<<4)

#define  CM  (0x01<<7)  //串联方式，其为0时电位器正常工作；其为1时，电位器与它相邻的高序号的电位器串联连接
#define  DW  (0x01<<6)  //禁止滑动端，其为0时滑动端使能；为1时滑动端被禁止，此时滑动端是电气上隔离的并且是浮空的



/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : x9421_Init()
* @Description   : x9421初始化程序
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void x9421_Init(void)
{
    /* 配置继电器IO口 --------------------------------------*/
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* 配置IIC --------------------------------------------*/
    IIC_Init();	
	
}



/**----------------------------------------------------------------------------
* @FunctionName  : x9421_Control()
* @Description   : x9421控制程序
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void x9421_Control(u8 num)  
{
    u8 DP = 0, byte[4] = {0, 0, 0, 0};
    if(num > 252) //超过最大值
        return;

    if(num >= 189)
    {
        byte[3] = num - 189;
        byte[2] = 63;
        byte[1] = 63;
        byte[0] = 63;

    }
    else if(num >= 126)
    {
        byte[3] = 0;
        byte[2] = num - 126;
        byte[1] = 63;
        byte[0] = 63;
    }
    else if(num >= 63)
    {
        byte[3] = 0;
        byte[2] = 0;
        byte[1] = num - 63;
        byte[0] = 63;
    }
    else
    {
        byte[3] = 0;
        byte[2] = 0;
        byte[1] = 0;
        byte[0] = num;
    }
    for(DP = 0; DP < 4; DP++)
    {
        IIC_Start();
        IIC_Send_Byte(X9421_Address);
        IIC_Wait_Ack();
        IIC_Send_Byte(WriteWCR | (DP << 2));
        IIC_Wait_Ack();
        IIC_Send_Byte( (63 - byte[DP]) & 0x3f); //若是滑片接高端，则用(63- byte[DP])，否则直接用(byte[DP])
        IIC_Wait_Ack();
        IIC_Stop();
    }

}

/**----------------------------------------------------------------------------
* @FunctionName  : x9421_Send()
* @Description   : x9421发送程序
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void x9421_Send(u8 DP, u8 num) //写指定WCR值
{
    //  	num = 63-num;
    if(num > 63) //超过最大值
        return;
	
    IIC_Start();
    IIC_Send_Byte(X9421_Address);
    IIC_Wait_Ack();
    IIC_Send_Byte(WriteWCR | (DP << 2));
    IIC_Wait_Ack();
    IIC_Send_Byte((num) & 0x3f); //发送数据
    IIC_Wait_Ack();
    IIC_Stop();
}


/**----------------------------------------------------------------------------
* @FunctionName  : x9421_Init()
* @Description   : x9421读取程序
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
u8 x9421_Read(u8 DP, u8 num) //读指定WCR值
{
    u8 byte = 0;
    IIC_Start();
    IIC_Send_Byte(X9421_Address);
    IIC_Wait_Ack();
    IIC_Send_Byte(WriteWCR | (DP << 2));
    IIC_Wait_Ack();
    byte = IIC_Read_Byte(1); //IIC_Send_Byte((num) & 0x3f); //发送数据
    IIC_Wait_Ack();
    IIC_Stop();
    return (byte);
}


/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/










