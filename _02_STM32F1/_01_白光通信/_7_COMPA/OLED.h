/************************************************************************************
*  Copyright (c), 2015, HelTec Automation Technology co.,LTD.
*            All rights reserved.
*
* File name: OLED.h
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
* History: none;
*
*************************************************************************************/

#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"
#include "string.h"

#define Max_Column	128
#define Max_Row			64
#define X_WIDTH 		128
#define Y_WIDTH 		64
#define	Brightness	0xCF 

//-----------------OLED端口定义----------------
#define OLED_CS_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_6)
#define OLED_CS_Set() GPIO_SetBits(GPIOC,GPIO_Pin_6)    //接OLED模块CS1

#define OLED_DC_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_7)
#define OLED_DC_Set() GPIO_SetBits(GPIOC,GPIO_Pin_7)     //接OLED模块D/C

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)    //接OLED模块SDI

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)    //接OLED模块的CLK

//OLED控制用函数
void OLED_WrDat(unsigned char dat);//写数据
void OLED_WrCmd(unsigned char cmd);//写命令
void OLED_SetPos(unsigned char x, unsigned char y);//设置起始点坐标
void OLED_Fill(unsigned char bmp_dat);//全屏填充
void OLED_CLS(void);//清屏
void OLED_Init(void);//初始化

void LcdDisChar(u8 xPos,u8 yPos,u8 zknum,u8 *zkzip);
u8 LcdDisplay_HZ(u8 xPos,u8 yPos,u8 *GBCodeptr);
void LcdDisplay_Chinese(u8 xPos,u8 yPos,u8 *GBCodeptr);
void LcdDisplay_char(u8 xPos,u8 yPos,u8 *GBCodeptr);
void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_ShowNum(u16 x,u16 y,u32 num);
#endif
