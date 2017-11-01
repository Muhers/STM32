//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//

//TFT显示屏文件
#include "my_TFT.h"
#include "text.h"	

/* 私有定义结构体 --------------------------------------------------------------------------------*/
typedef struct
{
  __IO uint16_t LCD_REG;
  __IO uint16_t LCD_RAM;
} LCD_TypeDef;
/* Note: LCD /CS is NE3 - Bank 3 of NOR/SRAM Bank 1~4 */
#define LCD_BASE           ((uint32_t)(0x60000000))
#define LCD                ((LCD_TypeDef *) LCD_BASE)





void TFT_Init(void)
{  
	TFT_LCD_Init();	
	font_init();  //检查字库
	LCD_Clear(BLACK);//清屏	
	TextColor = WHITE;
	BackColor = BLACK;
		
}




//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
//=========================================================================
void LCD_DrawPoints(u16 x,u16 y)
{
PutPixel(x,y);
}
//=========================================================================



//画线
//x1,y1:起点坐标
//x2,y2:终点坐标
//=========================================================================
void LCD_DrawLines(u16 x1, u16 y1, u16 x2, u16 y2)
{
	
LCD_DrawuniLine(x1, y1,x2,y2);
}
//=========================================================================


//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
//=========================================================================
void LCD_Fill(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{	
	uint32_t x,y;
	u16 temp=TextColor;
	TextColor=color;
	for(y=y1;y<y2;y++)
	{
		LCD_SetCursor(x1,y);			
		LCD_WriteRAM_Prepare();
		
		for(x=x1;x<x2;x++)
		LCD->LCD_RAM =color;
	}
	TextColor=temp;
}
//=========================================================================


//显示字符串
//x y 起始坐标
//*p:字符串起始地址	
//=========================================================================
void LCD_ShowString(u16 x,u16 y,u8 *p)
{
LCD_DisplayStringLine(y,x,p);
}
//=========================================================================



//x,y:起点坐标
//digit:保留位数
//num:数值(0~4294967295).
//size:字体大小  12/16/24/90(预留位，暂时不能实现)
//=========================================================================
void LCD_ShowNum(u16 x,u16 y,double num,u8 digit,u8 size)
{
	u8 ch_inte[50]={0};
	int i=0,_0=0;
	u32 integer=(u32)num,temp=integer,len_inte=0,temp0=temp,digit0=digit;
	double temp01=num;
	digit++;
	temp01*=10;
	temp0*=10;
	while((--digit0)&&(u32)(temp01-temp0)==0)
	{	
		_0++;
		temp01*=10;
		temp0*=10; 
	}
	
	while(digit--)
	num*=10,temp*=10;
	temp=integer*10;
	while(temp/=10) len_inte++;
	
	if(len_inte==0){Show_String(x,y,"0",size);x=x+size/2;}
	
	len_inte--;
	  
	temp=len_inte;
	for(i=len_inte;i>=0;i--) ch_inte[i]='0'+integer%10,integer/=10;
	 
	len_inte=temp+1;
	Show_String(x,y,ch_inte,size);
	
	
	
}
//=========================================================================



//画实心圆点
//(x,y):中心点
//size:圆点的的大小
//=========================================================================
void LCD_Big_Point(u16 x,u16 y,u16 size,u16 color)
{
	u16 temp=TextColor;
	TextColor=color;
	if (x<=size) x=size+1;
	for(;size>0;size--)
	LCD_DrawCircle(x,y,size);
	TextColor=temp;
}
//=========================================================================




//画实心矩形
//x,y,xi,yi 矩形四个角
//=========================================================================
void LCD_Big_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{	
	u16 temp=TextColor;
	TextColor=color;
	for(;x2>=x1;x2--)
	LCD_DrawLines(x2,y1,x2,y2);
	TextColor=temp;
}
//=========================================================================


//画空心矩形
//x,y,xi,yi 矩形四个角
//=========================================================================
void Draw_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 tc=TextColor;
	TextColor=color;
	LCD_DrawLines(x1,y1,x2,y1);
	LCD_DrawLines(x1,y2,x2,y2);
	LCD_DrawLines(x2,y1,x2,y2);
	LCD_DrawLines(x1,y1,x1,y2);
	TextColor=tc;
}
//=========================================================================




//创建坐标
//mode 是否重写边框 1写   0不写
//=========================================================================
void Creat_Coord(u16 x1,u16 y1,u16 x2,u16 y2,float density,u8 mode)
{
	u16 x=0,y=0;					
	density=(density+1)/10;
	if(mode==1)	      			
	{LCD_Fill(x1,y1,x2,y2,BLACK);}	//写边框		
												
	LCD_Fill(x1+density*5,y1+density*5,x2-density*5,y2-density*5,WHITE); //写背景						
	
	//画小点
	for(x=x1;x<x2;x+=10*density)													
	for(y=y1;y<y2;y+=10*density)							
	{LCD_Big_Point(x,y,1,GRAY);}		
																			
	//画大点
	for(x=x1;x<x2;x+=50*density)													
	for(y=y1;y<y2;y+=50*density)							
	{LCD_Big_Point(x,y,2,BLACK);}		
		
	//画左右边框点
	for(y=y1+10*density;y<y2;y+=10*density)							
	{
	LCD_Big_Rect(x1+density*5,y,x1+density*8,y+density,BLACK);//左
	LCD_Big_Rect(x2-density*8,y,x2-density*5,y+density,BLACK);//右
	}
	//画上下边框点
	for(x=x1+10*density;x<x2;x+=10*density)							
	{
	LCD_Big_Rect(x,y1+density*5,x+density,y1+density*8,BLACK);//上
	LCD_Big_Rect(x,y2-density*5,x+density,y2-density*8,BLACK);//下
	}
	
	
	
	
}
//=========================================================================



//显示图片
//RGB565  16位真彩显示
//不可放缩
//带头数据
//=========================================================================
void Show_Picture0(u16 x1,u16 y1,const u8 *pic)
{	
	u16 x,y,p_color;
	u16 len_x=(pic[2]<<8)|pic[3];
	u16 len_y=(pic[4]<<8)|pic[5];
	
	for(y=0;y<len_y;y++)
	for(x=0;x<len_x*2;x+=2)
	{
	p_color=pic[x+y*len_x*2]*16*16+pic[(x+1)+y*len_x*2];
	LCD_SetCursor(x/2+x1,y+y1);//设置光标位置 
    LCD_WriteRAM_Prepare(); 
    LCD_WriteRAM(p_color);
	
	}
	
}
//=========================================================================



//显示图片
//RGB565  16位真彩显示
//可放缩
//带头数据
//=========================================================================
void Show_Picture1(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic)
{	
	u16 x,y,p_color;
	float density_x,density_y;
	u16 len_x=(pic[2]<<8)|pic[3];
	u16 len_y=(pic[4]<<8)|pic[5];
	
	density_x=(float)(x2-x1)/len_x; 
	density_y=(float)(y2-y1)/len_y; 
	
	for(y=0;y<len_y;y++) 
	for(x=0;x<len_x*2;x+=2) 
	{ 
	p_color=pic[x+y*len_x*2]*16*16+pic[(x+1)+y*len_x*2]; 
	LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//设置光标位置 
    LCD_WriteRAM_Prepare(); 
    LCD_WriteRAM(p_color); 
	
		
		
	}
	
}

//=========================================================================



//=========================================================================
void  Show_String(uint16_t x,uint16_t y,u8*str,u8 size)
{

// Show_Str(y,x,str,size);
	
	
}

 

//=========================================================================
//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}		

void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp,tem[10];
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				tem[0]='0';
				if(mode&0X80)Show_String(x+(size/2)*t,y,tem,size);  
				else Show_String(x+(size/2)*t,y," ",size);  
 				continue;
			}else enshow=1; 
		 	 
		}
		tem[0]=temp+'0';
	 	Show_String(x+(size/2)*t,y,tem,size); 
	}
} 
//显示数字,高位为0
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小 12/16/24
//color:颜色 
//num:数值(0~4294967295);	 
void LCD_Show0Num(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp,tem[10];
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				
				Show_String(x+(size/2)*t,y,"0",size);
				continue;
			}else enshow=1; 
		 	 
		}
		if(temp <= 9) tem[0]=temp+'0'; 
	 	Show_String(x+(size/2)*t,y,tem,size); 
	}
} 



//显示小数
//x,y:起点坐标
//digit:保留位数
//size:字体大小  12/16/24
void LCD_ShowDecim(u16 x,u16 y,double num,u8 digit,u8 len,u8 size)//长度 包括.在内
{ 
	
	volatile unsigned long int digitnum=LCD_Pow(10,digit);                              
	volatile unsigned long int numd=(u32)(num*digitnum);     	                   
	volatile unsigned long int temp;                                               
	len=len-digit-1;
	temp=numd/digitnum;
	LCD_ShowxNum(x,y,temp,len,size,1);//显示整数部分
	temp=(unsigned long int)(numd-((double)(numd/digitnum)*digitnum));
	Show_String(x+len*(size/2),y,".",size);
	LCD_Show0Num(x+(len+1)*(size/2),y,temp,digit,size);//显示小数部分
	

} 





//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//
