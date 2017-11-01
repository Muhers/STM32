/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/
/**============================================================================
* @FileName    : Drive_OLED.c
* @Description : None

-------------------------------------------------------------------------------
* 1. void OLED_WrDat(unsigned char dat) -- 向OLED写数据
* 2. void OLED_WrCmd(unsigned char cmd) -- 向OLED写命令
* 3. void OLED_SetPos(unsigned char x, unsigned char y) -- 设置起始点坐标
* 4. void OLED_Fill(unsigned char bmp_dat) -- 全屏填充(0x00可以用于清屏，0xff可以用于全屏点亮)
* 5. void OLED_CLS(void) -- 清屏
* 6. void OLED_Init(void) -- OLED显示屏初始化
* 7. void OLED_6x8Str(unsigned char x, y,unsigned char ch[]) -- 显示6x8的ASCII字符
* 8. void OLED_8x16Str(unsigned char x, y,unsigned char ch[]) -- 显示8x16的ASCII字符
* 9. void OLED_16x16CN(unsigned char x, y, N) -- 显示16x16中文汉字,汉字要先在取模软件中取模
* 10.void OLED_BMP(unsigned char x0, y0,x1, y1,unsigned char _BMP[]) -- 全屏显示128*64的BMP图片
*
* 接线方式:
* VCC -- +3.3V~5V
* GND -- GND
* CLK -- PB13
* SDI -- PB15
* D/C -- PC7
* CS1 -- PC6
* FSO -- PB14
* CS2 -- PB12
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_OLED.h"  

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OLED_Flash 
* @Description   : OLED_Flash相关函数
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
static void FF_CS(u8 value)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_12,(BitAction)value); //CS2
}
static void FF_SO(u8 value)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_15,(BitAction)value); //SDI
}
static void FF_CLK(u8 value)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_13,(BitAction)value); //CLK
}

static void FF_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //PB14 -- FSO(读取Flash芯片的状态)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	FF_CS(1);
	FF_CLK(1);
}

static u8 Write_FF(u8 value)
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
	 if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)) //GPIOB.14 为FSO脚
			temp++;
	}
	return(temp);
}

static void Read_FLASH(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
	OLED_CS_Set();//取消OLED选中
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
	OLED_CS_Clr();
}


/**----------------------------------------------------------------------------
* @FunctionName  : OLED_WrDat()
* @Description   : 写数据
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void OLED_WrDat(unsigned char dat)
{
	unsigned char i;
	OLED_DC_Set();
	for(i=0;i<8;i++)
	{
		if((dat << i) & 0x80)
		{
			OLED_SDA_Set();
		}
		else
			OLED_SDA_Clr();
		OLED_SCL_Clr();
		OLED_SCL_Set();
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : OLED_WrCmd()
* @Description   : 写命令
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void OLED_WrCmd(unsigned char cmd)
{
	unsigned char i;
	OLED_DC_Clr();
	for(i=0;i<8;i++) //发送一个八位数据
	{
		if((cmd << i) & 0x80)
		{
			OLED_SDA_Set();
		}
		else
		{
			OLED_SDA_Clr();
		}
		OLED_SCL_Clr();
		OLED_SCL_Set();
	}
}




/**----------------------------------------------------------------------------
* @FunctionName  : OLED_Init()
* @Description   : 初始化
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
 void OLED_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能 PB 端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;	  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_15);	//PB13,PB15 输出高

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能 PC 端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7);
	 
	OSdelay_ms(100);
	
 	OLED_CS_Clr();
	OLED_WrCmd(0xae);
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00);
	OLED_SetPos(0,0);
	OLED_CS_Set();
	FF_Init();//OLED_Flash 初始化
}



/**----------------------------------------------------------------------------
* @FunctionName  : OLED_SetPos()
* @Description   : 设置起始点坐标
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void OLED_SetPos(unsigned char x, unsigned char y) 
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
}

/**----------------------------------------------------------------------------
* @FunctionName  : OLED_Fill()
* @Description   : 全屏填充
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	
	OLED_CS_Clr();
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		{
			OLED_WrDat(bmp_dat);
		}
	}
	OLED_CS_Set();
}


/**----------------------------------------------------------------------------
* @FunctionName  : OLED_CLS()
* @Description   : 清屏 
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void OLED_CLS(void) 
{
	OLED_Fill(0x00);
}



/**----------------------------------------------------------------------------
* @FunctionName  : LcdDisChar()
* @Description   : 显示一个字符
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void LcdDisChar(u8 xPos,u8 yPos,u8 zknum,u8 *zkzip)
{
	u8 i;
	OLED_SetPos(xPos,yPos);
	for(i=0; i<zknum;i++)
	{
		OLED_WrDat(zkzip[i]); 
	}
	OLED_SetPos(xPos,yPos+1);
	for(i=zknum; i<zknum*2;i++)
	{
		OLED_WrDat(zkzip[i]);
	}
}


/**----------------------------------------------------------------------------
* @FunctionName  : LcdDisplay_HZ()
* @Description   : 显示一个中文字符
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
u8 LcdDisplay_HZ(u8 xPos,u8 yPos,u8 *GBCodeptr)
{
	u8 msb,lsb,zknum;
	u8 zkzip[32];  //读取字库数据的缓存区	
	u32 offset;	   //字库地址索引
	
	OLED_CS_Clr();
	if(xPos>=Max_Column || yPos>=Max_Row) return 0 ;  //超范围退出
	msb= *GBCodeptr;     //汉字或ASCII的机器码的低8位。
	lsb= *(GBCodeptr+1); //汉字或ASCII的机器码的高8位。
	if (msb>128 && lsb>128)	//表明为汉字
	{
		if(xPos+16>Max_Column || yPos+16>Max_Row)return 0; //超范围退出
		offset =0x00000+((msb-0xA1)*94+(lsb-0xa1))*32;//具体算法详细查看字库原理
		zknum =16;	//汉字为16*16的字库
	}
	else	               //否则为ASCII码
	{
		if(xPos+8>Max_Column || yPos+16>Max_Row)return 0;	//超范围退出
		offset =0x8100+(msb-32)*16;  //查看提供的2012_KZ.txt文档中的“!”的首地址
		zknum =8;   // ASCII码位8*16的字库
	}
	Read_FLASH(zkzip,offset,zknum*2);	 //从FLASH中读取字库数据。
	LcdDisChar(xPos,yPos,zknum,zkzip);
	OLED_CS_Set();

	return 1;
}

/**----------------------------------------------------------------------------
* @FunctionName  : LcdDisplay_HZ()
* @Description   : 显示中文字符串
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void LcdDisplay_Chinese(u8 xPos,u8 yPos,u8 *GBCodeptr)
{
	u8 i,len;
	xPos*=8;
	yPos*=2;
	len =  strlen((const char*)GBCodeptr);
	for(i=0;i<len;i++)	
	{
	   	LcdDisplay_HZ(xPos+i*8,yPos,GBCodeptr+i);
		i++;
	}
}


/**----------------------------------------------------------------------------
* @FunctionName  : LcdDisplay_HZ()
* @Description   : 显示字符串
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void LcdDisplay_char(u8 xPos,u8 yPos,u8 *GBCodeptr)
{
  u8 i, len;
	xPos*=8;
	yPos*=2;
	len =  strlen((const char*)GBCodeptr);
  for(i=0;i<len;i++)	
	{
		LcdDisplay_HZ(xPos+i*8,yPos,GBCodeptr+i);
	}
}


 
/**----------------------------------------------------------------------------
* @FunctionName  : OLED_BMP()
* @Description   : 显示图片
* @Data          : 2016/8/8
* @Explain       : 
------------------------------------------------------------------------------- 
在指定区域显示BMP图片 
x0(0~127),yo(0~7) -- 图片起始坐标，x1(1~128),y1(1~8)图片结束点坐标
将BMP图片导入取模软件生成字模,再将字模放到本工程的codetab.h中
------------------------------------------------------------------------------*/
void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;
  
	OLED_CS_Clr();
	if(y1%8==0) y=y1/8;
	else y=y1/8+1;
	
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
		
		for(x=x0;x<x1;x++) 
			OLED_WrDat(BMP[j++]); 
		
	}
	OLED_CS_Set();
}	

 












/*******************************(C) COPYRIGHT 2016 Vitamin（郭郭）*********************************/








