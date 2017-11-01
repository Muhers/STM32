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
* Description:128*64�����OLED��ʾ�������ļ����������ڻ����Զ���(heltec.taobao.com)��SD1306����SPIͨ�ŷ�ʽ��ʾ��
*
* Others: none;
*
* Function List:
*
* 1. void OLED_WrDat(unsigned char dat) -- ��OLEDд����
* 2. void OLED_WrCmd(unsigned char cmd) -- ��OLEDд����
* 3. void OLED_SetPos(unsigned char x, unsigned char y) -- ������ʼ������
* 4. void OLED_Fill(unsigned char bmp_dat) -- ȫ�����(0x00��������������0xff��������ȫ������)
* 5. void OLED_CLS(void) -- ����
* 6. void OLED_Init(void) -- OLED��ʾ����ʼ��
* 7. void OLED_6x8Str(unsigned char x, y,unsigned char ch[]) -- ��ʾ6x8��ASCII�ַ�
* 8. void OLED_8x16Str(unsigned char x, y,unsigned char ch[]) -- ��ʾ8x16��ASCII�ַ�
* 9. void OLED_16x16CN(unsigned char x, y, N) -- ��ʾ16x16���ĺ���,����Ҫ����ȡģ�����ȡģ
* 10.void OLED_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[]) -- ȫ����ʾ128*64��BMPͼƬ
*
* History: none;
*
*************************************************************************************/

#ifndef __OLED_H
#define __OLED_H

#include "OS_StartFile.h"
#include "string.h"

#define Max_Column	    128
#define Max_Row			64
#define X_WIDTH 		128
#define Y_WIDTH 		64
#define	Brightness	    0xCF 

//-----------------OLED�˿ڶ���----------------
#define OLED_CS_Clr1() GPIO_ResetBits(GPIOD,GPIO_Pin_1)
#define OLED_CS_Set1() GPIO_SetBits(GPIOD,GPIO_Pin_1)    //��OLEDģ��CS1

#define OLED_DC_Clr1() GPIO_ResetBits(GPIOD,GPIO_Pin_0)
#define OLED_DC_Set1() GPIO_SetBits(GPIOD,GPIO_Pin_0)     //��OLEDģ��D/C

#define OLED_SDA_Clr1() GPIO_ResetBits(GPIOD,GPIO_Pin_15)
#define OLED_SDA_Set1() GPIO_SetBits(GPIOD,GPIO_Pin_15)    //��OLEDģ��SDI

#define OLED_SCL_Clr1() GPIO_ResetBits(GPIOD,GPIO_Pin_14)
#define OLED_SCL_Set1() GPIO_SetBits(GPIOD,GPIO_Pin_14)    //��OLEDģ���CLK




#define OLED_CS_Clr2() GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define OLED_CS_Set2() GPIO_SetBits(GPIOB,GPIO_Pin_12)    //��OLEDģ��CS1

#define OLED_DC_Clr2() GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define OLED_DC_Set2() GPIO_SetBits(GPIOB,GPIO_Pin_13)     //��OLEDģ��D/C

#define OLED_SDA_Clr2() GPIO_ResetBits(GPIOE,GPIO_Pin_10)
#define OLED_SDA_Set2() GPIO_SetBits(GPIOE,GPIO_Pin_10)    //��OLEDģ��SDI

#define OLED_SCL_Clr2() GPIO_ResetBits(GPIOE,GPIO_Pin_9)
#define OLED_SCL_Set2() GPIO_SetBits(GPIOE,GPIO_Pin_9)    //��OLEDģ���CLK

//OLED�����ú���
void OLED_WrDat1(unsigned char dat);//д����
void OLED_WrCmd1(unsigned char cmd);//д����
void OLED_SetPos1(unsigned char x, unsigned char y);//������ʼ������
void OLED_Fill1(unsigned char bmp_dat);//ȫ�����
void OLED_CLS1(void);//����

void OLED_WrDat2(unsigned char dat);//д����
void OLED_WrCmd2(unsigned char cmd);//д����
void OLED_SetPos2(unsigned char x, unsigned char y);//������ʼ������
void OLED_Fill2(unsigned char bmp_dat);//ȫ�����
void OLED_CLS2(void);//����

void OLED_Init(void);//��ʼ��

void LcdDisChar(u8 xPos,u8 yPos,u8 zknum,u8 *zkzip ,u8 NUM);
u8 LcdDisplay_HZ(u8 xPos,u8 yPos,u8 *GBCodeptr,u8 NUM);
void LcdDisplay_Chinese(u8 xPos,u8 yPos,u8 *GBCodeptr,u8 NUM);
void LcdDisplay_char(u8 xPos,u8 yPos,u8 *GBCodeptr,u8 NUM);
void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1,unsigned char BMP[],u8 NUM);
//void OS_Decim_Show(u16 x,u16 y,double num,u8 NumLenth,u8 DecimLenth,u8 NUM);
void OLED_Str_Show(u8 xPos, u8 yPos, char *GBCodeptr, u8 NUM);

#endif
