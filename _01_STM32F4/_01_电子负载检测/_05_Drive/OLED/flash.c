/************************************************************************************
*  Copyright (c), 2015, HelTec Automation Technology co.,LTD.
*            All rights reserved.
*
* File name: flash.c
* Project  : HelTec
* Processor: STM32F103C8T6
* Compiler : MDK for ARM - 4.72.1.0
* 
* Author : Aaron.Lee
* Version: 1.00
* Date   : 2014.4.20
* Email  : leehunter8801@gmail.com
* Modification: none
* 
* Description: 惠利特自动化自制字库芯片的驱动文件，仅适用于惠利特自动化(Heltec.taobao.com)所售字库版OLED显示屏
*
* Others: none;
*
* Function List:
*
* 1. void FF_Init(void) -- 字库芯片初始化
* 2. u8 Write_FF(u8 value) -- 向字库芯片写一个byte的数据(命令)
* 3. void Read_FLASH(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead) -- 读取字库芯片中的内容
*
* History: none;
*
*************************************************************************************/


#include "flash.h"
#include "delay.h"
#include "OLED.h"

void FF_CS(u8 value)
{
	GPIO_WriteBit(GPIOE, GPIO_Pin_8,(BitAction)value); //CS21

}
void FF_SO(u8 value)
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_15,(BitAction)value); //SDI1

}
void FF_CLK(u8 value)
{ 
	GPIO_WriteBit(GPIOD, GPIO_Pin_14,(BitAction)value); //CLK1
}






void FF_CS2(u8 value)
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_8,(BitAction)value); //CS22

}
void FF_SO2(u8 value)
{
	GPIO_WriteBit(GPIOE, GPIO_Pin_10,(BitAction)value); //SDI2

}
void FF_CLK2(u8 value)
{ 
	GPIO_WriteBit(GPIOE, GPIO_Pin_9,(BitAction)value); //CLK2
}


void FF_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOA,GPIOE时钟
    
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
    GPIO_Init(GPIOE,&GPIO_InitStructure);	
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init(GPIOD,&GPIO_InitStructure);	  

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;        //普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);             
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;        //普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
    
	FF_CS(1);
	FF_CLK(1);
    
	FF_CS2(1);
	FF_CLK2(1);
    
}

u8 Write_FF(u8 value)
{
	u8 i;
	u8 temp=0;
	FF_CLK(1);
	for(i=0;i<8;i++)
	{
	 FF_CLK(0);
	 OSdelay_us(2);
	 if((value&0x80)==0x80)
		 FF_SO(1);
	 else
		 FF_SO(0); 
	 value<<=1;
	 OSdelay_us(2);
	 FF_CLK(1);
	 OSdelay_us(2);
	 temp<<=1;
         if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)) //GPIOB.14 为FSO脚
			temp++;
      
	}
	return(temp);
}

u8 Write_FF2(u8 value)
{
	u8 i;
	u8 temp=0;
	FF_CLK2(1);
	for(i=0;i<8;i++)
	{
	 FF_CLK2(0);
	 OSdelay_us(2);
	 if((value&0x80)==0x80)
		 FF_SO2(1);
	 else
		 FF_SO2(0); 
	 value<<=1;
	 OSdelay_us(2);
	 FF_CLK2(1);
	 OSdelay_us(2);
	 temp<<=1;
         if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)) //GPIOB.14 为FSO脚
			temp++;
      
	}
	return(temp);
}
void Read_FLASH(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead,u8 NUM)
{
    if(NUM==1)
	{
        OLED_CS_Set1();//取消OLED选中	
        FF_CS(0);//选中FLASH芯片    
        Write_FF(0x03);
        Write_FF((ReadAddr & 0xFF0000) >> 16);
        Write_FF((ReadAddr& 0xFF00) >> 8);
        Write_FF(ReadAddr & 0xFF);	
        while(NumByteToRead--)
        {
            *pBuffer = Write_FF(0xA5);
            pBuffer++;
        }
      FF_CS(1);
    }
    else
    { 
        OLED_CS_Set2();//取消OLED选中
        FF_CS2(0);//选中FLASH芯片    
        Write_FF2(0x03);
        Write_FF2((ReadAddr & 0xFF0000) >> 16);
        Write_FF2((ReadAddr& 0xFF00) >> 8);
        Write_FF2(ReadAddr & 0xFF);	
        while(NumByteToRead--)
        {
            *pBuffer = Write_FF2(0xA5);
            pBuffer++;
        }
        FF_CS2(1);
    }

    if(NUM==1)
        OLED_CS_Clr1();
    else
     	OLED_CS_Clr2();   
}





