/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_Key.h
* @Description : None
* @Date        : 2016/7/19
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __APP_KEY_H
#define __APP_KEY_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 
#define KEY_NUM_MAX			10

#define KEY_MODE_SHORT		(0x0001<<0)	
#define KEY_MODE_LONG		(0x0001<<1)	
  
#define KEY_COUNT_SHORT		10
#define KEY_COUNT_LONG		50
#define KEY_COUNT_LIMIT		200


#define GPIO_UP			PBin(8)	
#define GPIO_DOWN		PBin(5)	
#define GPIO_LEFT		PBin(7)	
#define GPIO_RIGHT  	PBin(0)	
#define GPIO_LEARN 		PGin(15)	
#define GPIO_FUNC1  	PGin(13)	
#define GPIO_FUNC2  	PGin(12)	
#define GPIO_FSAVE  	PBin(6)	
#define GPIO_FREAD 		PBin(1)	
#define GPIO_FERASE 	PGin(14)	 


#define KEY_PRESS 	\
( \
	GPIO_UP		 == 0|| \
	GPIO_DOWN	 == 0|| \
	GPIO_LEFT	 == 0|| \
	GPIO_RIGHT   == 0|| \
	GPIO_LEARN   == 0|| \
	GPIO_FUNC1   == 0|| \
	GPIO_FUNC2   == 0|| \
	GPIO_FSAVE   == 0|| \
	GPIO_FREAD   == 0|| \
	GPIO_FERASE  == 0	\
) \

#define UP			(0x0001<<0)	
#define DOWN		(0x0001<<1)													
#define LEFT		(0x0001<<2)	
#define RIGHT		(0x0001<<3)	 
#define LEARN		(0x0001<<4)	
#define FUNC1		(0x0001<<5)													
#define FUNC2		(0x0001<<6)	
#define FSAVE		(0x0001<<7)	
#define FREAD		(0x0001<<8)
#define FERASE		(0x0001<<9)

#define KEY_ALL		 0xffff


/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct
{ 
	u16	CountNow[KEY_NUM_MAX];//����
	u16	CountLast[KEY_NUM_MAX];//��һ�η��ټ���ͣ��
	u16 ResultShort;//�̰�������Ͻ��
	u16 ResultLong;//����������Ͻ��
	
}Type_Key;

/* ȫ�ֱ������� --------------------------------------------------------------*/  
extern Type_Key Key;

/* ȫ�ֺ������� --------------------------------------------------------------*/  				
extern Type_AppList App_Key;
u16 Key_Now_Get(u16 KeyNum,u16 Mode);
u16 Key_Get(u16 KeyNum,u16 Mode);
void Key_Clear(u16 Mode);
 
 
 
 
 
#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



