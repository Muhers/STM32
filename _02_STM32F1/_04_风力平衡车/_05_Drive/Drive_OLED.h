/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/
/**============================================================================
* @FileName    : Drive_OLED.h
* @Description : None
* @Date        : 2016/8/8

*=============================================================================*/
/* 防止重调用 ----------------------------------------------------------------*/ 
#ifndef __OLED_H
#define __OLED_H
 
/* 头文件包含 ----------------------------------------------------------------*/   
#include "User_Library.h"   

/* 全局宏定义 ----------------------------------------------------------------*/  
#define Max_Column	128
#define Max_Row		64
#define X_WIDTH 	128
#define Y_WIDTH 	64
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
 
 
/* 结构体声明 ----------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数声明 --------------------------------------------------------------*/  
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
/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/












