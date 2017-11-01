/************************************************************************************
*  Copyright (c), 2015, HelTec Automation Technology co.,LTD.
*            All rights reserved.
*
* File name: OLED.c
* Project  : HelTec
* Processor: STM32F103C8T6
* Compiler : MDK for ARM - 4.72.1.0
*
* Author : Aaron.Lee
* Version: 1.01
* Date   : 2014.5.10
* Email  : leehunter8801@gmail.com
* Modification: none
*
* Description:128*64点阵的OLED显示屏驱动文件，仅适用于惠特自动化(heltec.taobao.com)的SD1306驱动SPI通信方式显示屏
*
* Others: none;
*
* Function List:
*
* 1. void OLED_WrDat(unsigned char dat) -- 向OLED写数据
* 2. void OLED_WrCmd(unsigned char cmd) -- 向OLED写命令
* 3. void OLED_SetPos(unsigned char x, unsigned char y) -- 设置起始点坐标
* 4. void OLED_Fill(unsigned char bmp_dat) -- 全屏填充(0x00可以用于清屏，0xff可以用于全屏点亮)
* 5. void OLED_CLS(void) -- 清屏
* 6. void OLED_Init(void) -- OLED显示屏初始化
* 7. void OLED_6x8Str(unsigned char x, y,unsigned char ch[]) -- 显示6x8的ASCII字符
* 8. void OLED_8x16Str(unsigned char x, y,unsigned char ch[]) -- 显示8x16的ASCII字符
* 9. void OLED_16x16CN(unsigned char x, y, N) -- 显示16x16中文汉字,汉字要先在取模软件中取模
* 10.void OLED_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- 全屏显示128*64的BMP图片
*
* History:
*
* Description: 接线方式
* 					VCC -- +3.3V~5V
* 					GND -- GND
*						CLK -- PB13
*						SDI -- PB15
*						D/C -- PC7
*						CS1 -- PC6
*						FSO -- PB14
*						CS2 -- PB12
*
*
*						CLK2 -- PD8
*						SDI2 -- PE14
*						D/C2 -- PE12
*						CS12 -- PE10
、
*	OQC:	Xia Dao
*************************************************************************************/

#include "OLED.h"
#include "delay.h"
#include <math.h>
#include "flash.h"

void OLED_WrDat1(unsigned char dat)//写数据
{
    unsigned char i;
    OLED_DC_Set1();
    for(i = 0; i < 8; i++)
    {
        if((dat << i) & 0x80)
        {
            OLED_SDA_Set1();
        }
        else
            OLED_SDA_Clr1();
        OLED_SCL_Clr1();
        OLED_SCL_Set1();
    }
}


void OLED_WrCmd1(unsigned char cmd)//写命令
{
    unsigned char i;
    OLED_DC_Clr1();
    for(i = 0; i < 8; i++) //发送一个八位数据
    {
        if((cmd << i) & 0x80)
        {
            OLED_SDA_Set1();
        }
        else
        {
            OLED_SDA_Clr1();
        }
        OLED_SCL_Clr1();
        OLED_SCL_Set1();
    }
}

void OLED_SetPos1(unsigned char x, unsigned char y)//设置起始点坐标
{
    OLED_WrCmd1(0xb0 + y);
    OLED_WrCmd1(((x & 0xf0) >> 4) | 0x10);
    OLED_WrCmd1((x & 0x0f) | 0x01);
}

void OLED_Fill1(unsigned char bmp_dat)//全屏填充
{
    unsigned char y, x;

    OLED_CS_Clr1();
    for(y = 0; y < 8; y++)
    {
        OLED_WrCmd1(0xb0 + y);
        OLED_WrCmd1(0x01);
        OLED_WrCmd1(0x10);
        for(x = 0; x < X_WIDTH; x++)
        {
            OLED_WrDat1(bmp_dat);
        }
    }
    OLED_CS_Set1();
}

void OLED_CLS1(void)//清屏
{
    OLED_Fill1(0x00);
}










void OLED_WrDat2(unsigned char dat)//写数据
{
    unsigned char i;
    OLED_DC_Set2();
    for(i = 0; i < 8; i++)
    {
        if((dat << i) & 0x80)
        {
            OLED_SDA_Set2();
        }
        else
            OLED_SDA_Clr2();
        OLED_SCL_Clr2();
        OLED_SCL_Set2();
    }
}


void OLED_WrCmd2(unsigned char cmd)//写命令
{
    unsigned char i;
    OLED_DC_Clr2();
    for(i = 0; i < 8; i++) //发送一个八位数据
    {
        if((cmd << i) & 0x80)
        {
            OLED_SDA_Set2();
        }
        else
        {
            OLED_SDA_Clr2();
        }
        OLED_SCL_Clr2();
        OLED_SCL_Set2();
    }
}

void OLED_SetPos2(unsigned char x, unsigned char y)//设置起始点坐标
{
    OLED_WrCmd2(0xb0 + y);
    OLED_WrCmd2(((x & 0xf0) >> 4) | 0x10);
    OLED_WrCmd2((x & 0x0f) | 0x01);
}

void OLED_Fill2(unsigned char bmp_dat)//全屏填充
{
    unsigned char y, x;

    OLED_CS_Clr2();
    for(y = 0; y < 8; y++)
    {
        OLED_WrCmd2(0xb0 + y);
        OLED_WrCmd2(0x01);
        OLED_WrCmd2(0x10);
        for(x = 0; x < X_WIDTH; x++)
        {
            OLED_WrDat2(bmp_dat);
        }
    }
    OLED_CS_Set2();
}

void OLED_CLS2(void)//清屏
{
    OLED_Fill2(0x00);
}




void OLED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOB, ENABLE); //使能GPIOA,GPIOE时钟

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_14 | GPIO_Pin_15;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    OSdelay_ms(500);

    OLED_CS_Clr1();/*****************************************************************************************************/
    OLED_WrCmd1(0xae);
    OLED_WrCmd1(0xae);//--turn off oled panel
    OLED_WrCmd1(0x00);//---set low column address
    OLED_WrCmd1(0x10);//---set high column address
    OLED_WrCmd1(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrCmd1(0x81);//--set contrast control register
    OLED_WrCmd1(Brightness); // Set SEG Output Current Brightness
    OLED_WrCmd1(0xa1);//--Set SEG/Column Mapping
    OLED_WrCmd1(0xc8);//Set COM/Row Scan Direction
    OLED_WrCmd1(0xa6);//--set normal display
    OLED_WrCmd1(0xa8);//--set multiplex ratio(1 to 64)
    OLED_WrCmd1(0x3f);//--1/64 duty
    OLED_WrCmd1(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WrCmd1(0x00);//-not offset
    OLED_WrCmd1(0xd5);//--set display clock divide ratio/oscillator frequency
    OLED_WrCmd1(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WrCmd1(0xd9);//--set pre-charge period
    OLED_WrCmd1(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WrCmd1(0xda);//--set com pins hardware configuration
    OLED_WrCmd1(0x12);
    OLED_WrCmd1(0xdb);//--set vcomh
    OLED_WrCmd1(0x40);//Set VCOM Deselect Level
    OLED_WrCmd1(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrCmd1(0x02);//
    OLED_WrCmd1(0x8d);//--set Charge Pump enable/disable
    OLED_WrCmd1(0x14);//--set(0x10) disable
    OLED_WrCmd1(0xa4);// Disable Entire Display On (0xa4/0xa5)
    OLED_WrCmd1(0xa6);// Disable Inverse Display On (0xa6/a7)
    OLED_WrCmd1(0xaf);//--turn on oled panel
    OLED_Fill1(0x00);
    OLED_SetPos1(0, 0);
    OLED_CS_Set1();/*****************************************************************************************************/



    OLED_CS_Clr2();/*****************************************************************************************************/
    OLED_WrCmd2(0xae);
    OLED_WrCmd2(0xae);//--turn off oled panel
    OLED_WrCmd2(0x00);//---set low column address
    OLED_WrCmd2(0x10);//---set high column address
    OLED_WrCmd2(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrCmd2(0x81);//--set contrast control register
    OLED_WrCmd2(Brightness); // Set SEG Output Current Brightness
    OLED_WrCmd2(0xa1);//--Set SEG/Column Mapping
    OLED_WrCmd2(0xc8);//Set COM/Row Scan Direction
    OLED_WrCmd2(0xa6);//--set normal display
    OLED_WrCmd2(0xa8);//--set multiplex ratio(1 to 64)
    OLED_WrCmd2(0x3f);//--1/64 duty
    OLED_WrCmd2(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WrCmd2(0x00);//-not offset
    OLED_WrCmd2(0xd5);//--set display clock divide ratio/oscillator frequency
    OLED_WrCmd2(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WrCmd2(0xd9);//--set pre-charge period
    OLED_WrCmd2(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WrCmd2(0xda);//--set com pins hardware configuration
    OLED_WrCmd2(0x12);
    OLED_WrCmd2(0xdb);//--set vcomh
    OLED_WrCmd2(0x40);//Set VCOM Deselect Level
    OLED_WrCmd2(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrCmd2(0x02);//
    OLED_WrCmd2(0x8d);//--set Charge Pump enable/disable
    OLED_WrCmd2(0x14);//--set(0x10) disable
    OLED_WrCmd2(0xa4);// Disable Entire Display On (0xa4/0xa5)
    OLED_WrCmd2(0xa6);// Disable Inverse Display On (0xa6/a7)
    OLED_WrCmd2(0xaf);//--turn on oled panel
    OLED_Fill2(0x00);
    OLED_SetPos2(0, 0);
    OLED_CS_Set2();/*****************************************************************************************************/


    FF_Init();
}


void LcdDisChar(u8 xPos, u8 yPos, u8 zknum, u8 *zkzip, u8 NUM)
{
    u8 i;
    if(NUM == 1)
        OLED_SetPos1(xPos, yPos);
    else
        OLED_SetPos2(xPos, yPos);
    for(i = 0; i < zknum; i++)
    {
        if(NUM == 1)
            OLED_WrDat1(zkzip[i]);
        else
            OLED_WrDat2(zkzip[i]);
    }
    if(NUM == 1)
        OLED_SetPos1(xPos, yPos + 1);
    else
        OLED_SetPos2(xPos, yPos + 1);

    for(i = zknum; i < zknum * 2; i++)
    {
        if(NUM == 1)
            OLED_WrDat1(zkzip[i]);
        else
            OLED_WrDat2(zkzip[i]);
    }
}

u8 LcdDisplay_HZ(u8 xPos, u8 yPos, u8 *GBCodeptr, u8 NUM)
{
    u8 msb, lsb, zknum;
    u8 zkzip[32];  //读取字库数据的缓存区
    u32 offset;	   //字库地址索引
    if(NUM == 1)
        OLED_CS_Clr1();/*****************************************************************************************************/
    else
        OLED_CS_Clr2();

    if(xPos >= Max_Column || yPos >= Max_Row) return 0 ; //超范围退出
    msb = *GBCodeptr;    //汉字或ASCII的机器码的低8位。
    lsb = *(GBCodeptr + 1); //汉字或ASCII的机器码的高8位。
    if (msb > 128 && lsb > 128)	//表明为汉字
    {
        if(xPos + 16 > Max_Column || yPos + 16 > Max_Row)return 0; //超范围退出
        offset = 0x00000 + ((msb - 0xA1) * 94 + (lsb - 0xa1)) * 32; //具体算法详细查看字库原理
        zknum = 16;	//汉字为16*16的字库
    }
    else	               //否则为ASCII码
    {
        if(xPos + 8 > Max_Column || yPos + 16 > Max_Row)return 0;	//超范围退出
        offset = 0x8100 + (msb - 32) * 16; //查看提供的2012_KZ.txt文档中的“!”的首地址
        zknum = 8;  // ASCII码位8*16的字库
    }
    Read_FLASH(zkzip, offset, zknum * 2, 1);	 //从FLASH中读取字库数据。
    LcdDisChar(xPos, yPos, zknum, zkzip, NUM);
    if(NUM == 1)
        OLED_CS_Set1();/*****************************************************************************************************/
    else
        OLED_CS_Set2();
    return 1;
}

void LcdDisplay_Chinese(u8 xPos, u8 yPos, u8 *GBCodeptr, u8 NUM)
{
    u8 i, len;
    len =  strlen((const char *)GBCodeptr);
    for(i = 0; i < len; i++)
    {
        LcdDisplay_HZ(xPos + i * 8, yPos, GBCodeptr + i, NUM);
        i++;
    }
}

void LcdDisplay_char(u8 xPos, u8 yPos, u8 *GBCodeptr, u8 NUM)
{
    u8 i, len;
    len =  strlen((const char *)GBCodeptr);
    for(i = 0; i < len; i++)
    {
        LcdDisplay_HZ(xPos + i * 8, yPos, GBCodeptr + i, NUM);
    }
}

void OLED_Str_Show(u8 xPos, u8 yPos, char *GBCodeptr, u8 NUM)
{ 
	yPos *= 2;
	xPos *= 8;
    LcdDisplay_char( xPos,  yPos,(u8*)GBCodeptr,  NUM);
}

















