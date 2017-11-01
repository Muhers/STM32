/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/
/**============================================================================
* @FileName    : Drive_OLED.h
* @Description : None
* @Date        : 2016/8/8

*=============================================================================*/
/* ��ֹ�ص��� ----------------------------------------------------------------*/ 
#ifndef __OLED_H
#define __OLED_H
 
/* ͷ�ļ����� ----------------------------------------------------------------*/   
#include "User_Library.h"   

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/  
#define Max_Column	128
#define Max_Row		64
#define X_WIDTH 	128
#define Y_WIDTH 	64
#define	Brightness	0xCF 

//-----------------OLED�˿ڶ���----------------
#define OLED_CS_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_6)
#define OLED_CS_Set() GPIO_SetBits(GPIOC,GPIO_Pin_6)    //��OLEDģ��CS1

#define OLED_DC_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_7)
#define OLED_DC_Set() GPIO_SetBits(GPIOC,GPIO_Pin_7)     //��OLEDģ��D/C

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define OLED_SDA_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)    //��OLEDģ��SDI

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define OLED_SCL_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)    //��OLEDģ���CLK
 
 
/* �ṹ������ ----------------------------------------------------------------*/ 

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ������� --------------------------------------------------------------*/  
//OLED�����ú���
void OLED_WrDat(unsigned char dat);//д����
void OLED_WrCmd(unsigned char cmd);//д����
void OLED_SetPos(unsigned char x, unsigned char y);//������ʼ������
void OLED_Fill(unsigned char bmp_dat);//ȫ�����
void OLED_CLS(void);//����
void OLED_Init(void);//��ʼ��
void LcdDisChar(u8 xPos,u8 yPos,u8 zknum,u8 *zkzip);
u8 LcdDisplay_HZ(u8 xPos,u8 yPos,u8 *GBCodeptr);
void LcdDisplay_Chinese(u8 xPos,u8 yPos,u8 *GBCodeptr);
void LcdDisplay_char(u8 xPos,u8 yPos,u8 *GBCodeptr);
void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_ShowNum(u16 x,u16 y,u32 num);


#endif 
/*******************************(C) COPYRIGHT 2016 Vitamin��������*********************************/












