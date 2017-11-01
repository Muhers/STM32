/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_UI.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain        
* -------------------------------------------- 
*  若要使用OS_UI 则要求完善该文件下的底层驱动
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_UI.h" 			  

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OSTextColor_Set()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
unsigned int OS_TextColor_Set(u16 _color)
{
	uint16_t temp = TextColor;
	TextColor = _color;
	return temp;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_BackColor_Set()     
* @Description   : None 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
unsigned int OS_BackColor_Set(u16 _color)
{
	uint16_t temp = BackColor;
	BackColor = _color;
	return temp;
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Points_Draw()     
* @Description   : 画点 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* x,y:坐标
* POINT_COLOR:此点的颜色
------------------------------------------------------------------------------*/
void OS_Points_Draw(u16 x,u16 y,u16 color)
{
	u16 temp=TextColor;
	TextColor=color;
	LCD_Fast_DrawPoint(x,y,TextColor);
	TextColor=temp;
}

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Lines_Draw()     
* @Description   : 画线
* @Data          : 2016/3/22
* @Explain        
------------------------------------------------------------------------------- 
* x1,y1:起点坐标
* x2,y2:终点坐标
------------------------------------------------------------------------------*/ 
void OS_Lines_Draw(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{ 
	u16 temp=TextColor;
	TextColor=color;
	LCD_DrawLine(x1, y1,x2,y2);
	TextColor=temp;
} 



/**----------------------------------------------------------------------------
* @FunctionName  : OS_Circle_Draw()     
* @Description   : 画圆 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* (x,y):中心点
* size:圆点的的大小
* mode: 0 空心   1 实心
------------------------------------------------------------------------------*/  
void OS_Circle_Draw(u16 x,u16 y,u8 size,u8 mode,u16 color)
{
	u16 temp=TextColor;
	TextColor=color;
	if(mode == 1)
	{
		if(x<=size) x=size+1;
		for(;size>0;size--)
		LCD_Draw_Circle(x,y,size);
	}
	else if(mode == 0)
	{
		LCD_Draw_Circle(x,y,size);
	}
	TextColor=temp;
} 
	
 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Rect_Draw()     
* @Description   : 画矩形
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* x1,y1,x2,y2 ：矩形两对角坐标  
* mode： 0 空心   1实心
------------------------------------------------------------------------------*/  
void OS_Rect_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode,u16 color)
{	
  
	if(mode == 1)
	{ 
		LCD_Fill(x1,y1,x2,y2,color);
		
	}
	else if(mode == 0)
	{
		OS_Lines_Draw(x1,y1,x2,y1,color);
		OS_Lines_Draw(x1,y2,x2,y2,color);
		OS_Lines_Draw(x2,y1,x2,y2,color);
		OS_Lines_Draw(x1,y1,x1,y2,color);
	} 
} 

/**----------------------------------------------------------------------------
* @FunctionName  : OS_String_Show()     
* @Description   : 打印句子 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* x,y 坐标    *str 语句指针   size 字体大小   
------------------------------------------------------------------------------*/ 
u8  OS_String_Show(u16 x,u16 y,char*str,u8 size,u8 mode)
{ 
	static u8 used = 0;//用于独占资源
	if(used == 1) return 1;
	
	used = 1; 
//	Show_Str(x,y,strlen((const char*)str)*size,size,(u8*)str,size,mode); 
	used = 0;	
	 
	return 0;
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Decim_Show()     
* @Description   : 打印小数 
* @Data          : 2016/3/22
* @Explain        
------------------------------------------------------------------------------- 
x,y 坐标    num 数值   size 字体大小   
digit 保留有效数字     len 数值总长度
------------------------------------------------------------------------------*/ 
void OS_Decim_Show(u16 x,u16 y,double num,u8 digit,u8 size,u8 mode)//长度 包括.在内
{ 	 
	char str[100] = {0}; 
	char str_digit[8] = {0};
	str_digit[0] = '%';
	str_digit[1] = '.';
	str_digit[2] = '0' + digit/10;
	str_digit[3] = '0' + digit%10;
	str_digit[4] = 'f';
	sprintf(str,str_digit,num);	
	OS_String_Show(x,y,str,size,mode);	 
} 


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Num_Show()     
* @Description   : 打印整数	
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------  
x,y 坐标    num 数值   size 字体大小   
len 数值总长度
------------------------------------------------------------------------------*/ 
void OS_Num_Show(u16 x,u16 y,u32 num,u8 size,u8 mode) 
{  
	char str[100] = {0};
	sprintf(str,"%d",num);
	OS_String_Show(x,y,str,size,mode); 
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Point_Read()     
* @Description   : 读取点颜色
* @Data          : 2016/3/22
* @Explain        
* --------------------------------------------  
* x,y 坐标    num 数值   size 字体大小   
* len 数值总长度
------------------------------------------------------------------------------*/ 
u16 OS_Point_Read(u16 x,u16 y) 
{  
	return LCD_ReadPoint(x,y); 
}
	
	
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Picture_Draw()     
* @Description   : 显示图片
* @Data          : 2016/3/22
* @Explain        
------------------------------------------------------------------------------- 
* RGB565  16位真彩显示
* mode :  0 不可放缩      1 可缩放       2 固定图片位置（不可放缩）
		  3 图片变灰（不可放缩）
* 带头数据 
------------------------------------------------------------------------------*/ 
void OS_Picture_Draw(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic,u8 mode)
{	
	if(mode == 0)
	{
		u16 x,y,p_color;
		u16 len_x=(pic[2]<<8)|pic[3];
		u16 len_y=(pic[4]<<8)|pic[5];
		
		for(y=0;y<len_y;y++)
		for(x=0;x<len_x*2;x+=2)
		{
			if((u16)(x/2+x1) <= x2)
			if((u16)(y+y1) <= y2)		
			{
				p_color=pic[x+6+y*len_x*2]<<8|pic[(x+7)+y*len_x*2];
				
				LCD_SetCursor(x/2+x1,y+y1);//设置光标位置 
				LCD_WriteRAM_Prepare(); 
				LCD_WriteRAM(p_color);
			}
		}
	}
	
	else if(mode == 1)
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
			if((u16)((x/2)*density_x+x1) <= x2)
			if((u16)(y*density_y+y1) <= y2)		
			{
				p_color=pic[x+6+y*len_x*2]<<8|pic[(x+7)+y*len_x*2];
				LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//设置光标位置 
				LCD_WriteRAM_Prepare(); 
				LCD_WriteRAM(p_color);
			}				
			 
		}
	
	}
	
	else if(mode == 2)
	{
		u16 x,y,p_color;
		float density_x,density_y;
		u16 len_x=(pic[2]<<8)|pic[3];
		u16 len_y=(pic[4]<<8)|pic[5];
		
		density_x=(float)(x2-x1)/len_x; 
		density_y=(float)(y2-y1)/len_y; 
		
		for(y=y1;y<y2;y++) 
		for(x=x1;x<x2*2;x+=2) 
		{ 
			if((u16)((x/2)*density_x+x1) <= x2)
			if((u16)(y*density_y+y1) <= y2)	
			{
				p_color=pic[x+6+y*len_x*2]<<8|+pic[(x+7)+y*len_x*2]; 
				LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//设置光标位置 
				LCD_WriteRAM_Prepare(); 
				LCD_WriteRAM(p_color); 
			}
			 
		}
	}
	
	else if(mode == 3)
	{
		u16 x,y,p_color,BitRed,BitGreen,BitBlue;
		float density_x,density_y;
		u16 len_x=(pic[2]<<8)|pic[3];
		u16 len_y=(pic[4]<<8)|pic[5];
		
		density_x=(float)(x2-x1)/len_x; 
		density_y=(float)(y2-y1)/len_y; 
		
		for(y=0;y<len_y;y++) 
		for(x=0;x<len_x*2;x+=2) 
		{ 
			
			
			if((u16)((x/2)*density_x+x1) <= x2)
			if((u16)(y*density_y+y1) <= y2)		
			{ 
				p_color = pic[x+6+y*len_x*2]<<8|pic[(x+7)+y*len_x*2];
				BitRed   = (p_color & (0x1f << 11))>>11; 
				BitGreen = (p_color & (0x3f << 5 ))>>5;
				BitBlue = p_color & 0x1f;
				p_color = ((BitRed/3)<<11)|((BitGreen/3)<<5)|(BitBlue/3);
				
				LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//设置光标位置 
				LCD_WriteRAM_Prepare(); 
				LCD_WriteRAM(p_color);
			}				
			 
		}
	
	}
	else OS_String_Show(x1,y1,"No this model,please checking it！！！",FONT_3,0);
	
} 

 

 				 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_FFT_Draw()     
* @Description   : 画FFT图 
* @Data          : 2016/5/24
* @Explain        
-------------------------------------------------------------------------------
density 格子密度     Rate 倍率 
------------------------------------------------------------------------------*/  
void OS_FFT_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u16 *Buff,u16 Lenth,float Rate,float density)
{
	u16 x=0,y=0,_cnt = 1;   
	density=(density+1)/10;
 
	//画FFT图 
	for(_cnt = 0;_cnt < x2-x1-2;_cnt++)
	{
		if(Buff[_cnt*Lenth/(x2-x1-2)]*Rate < y2-y1-2)
		{
			OS_Lines_Draw(x1+_cnt,y1+2,x1+_cnt,y2- Buff[_cnt*Lenth/(x2-x1-2)]*Rate,WHITE);
			OS_Lines_Draw(x1+_cnt,y2 - Buff[_cnt*Lenth/(x2-x1-2)]*Rate,x1+_cnt,y2 - 2,BLUE);
		}
		else OS_Lines_Draw(x1+_cnt,y1 + 2,x1+_cnt,y2,RED);
	}
	  
	OS_Rect_Draw(x1,y1,x2,y2,0,BLACK);
	OS_Rect_Draw(x1+1,y1+1,x2-1,y2-1,0,BLACK);  
	OS_Rect_Draw(x1-2,y1-2,x2+2,y2+2,0,BLACK);  
	
	//画左右边框点
	for(y=y1;y<y2;y+=10*density)							
	{
		if(y%((u16)(50*density)) == y1)
		{
			OS_Rect_Draw(x1,y,x1+density*8,y+density,1,BLACK);//左
			OS_Rect_Draw(x2-density*8,y,x2,y+density,1,BLACK);//右
		}
		else
		{
			OS_Rect_Draw(x1,y,x1+density*5,y+density,1,BLACK);//左
			OS_Rect_Draw(x2-density*5,y,x2,y+density,1,BLACK);//右 
		}
	}
	//画上下边框点
	for(x=x1;x<x2;x+=10*density)							
	{
		if(x%((u16)(50*density)) == x1)
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*8,1,BLACK);//上
			OS_Rect_Draw(x,y2-density*8,x+density,y2,1,BLACK);//下
		}
		else
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*5,1,BLACK);//上
			OS_Rect_Draw(x,y2-density*5,x+density,y2,1,BLACK);//下
		}
	}  
	 
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : OS_OSC_Draw()     
* @Description   : 画示波器图 
* @Data          : 2016/5/24
* @Explain        
-------------------------------------------------------------------------------
density 格子密度     Struct_OSC 示波器波形显示参数
------------------------------------------------------------------------------*/ 
void OS_OSC_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u16 *Buff,u16 Lenth,float density,Type_OSC *Struct_OSC)
{
	u16 x=0,y=0,_cnt = 1;
	u16 TempX1=0,TempY1=0,TempX2 = 0,TempY2 = 0;
	u16 MaxX = 0,MinX = 0;
	static u16 LastBuff[OS_LCD_WHITH] = {0}; 
	density=(density+1)/10; 
	 
	//画小点
	for(x=x1;x<x2-2;x+=10*density)													
	for(y=y1;y<y2-2;y+=10*density)							
	{
		OS_Circle_Draw(x+2,y+2,1,1,GRAY);  
	}		
																			
	//画大点
	for(x=x1;x<x2-2;x+=50*density)													
	for(y=y1;y<y2-2;y+=50*density)							
	{
		OS_Circle_Draw(x+2,y+2,1,1,BLACK);
	}
	
	//清除上次画的点
	for(_cnt = 3;_cnt < x2-x1-3;_cnt++)
	{  
		TempX1 = x1+_cnt-1;
		TempY1 = LastBuff[_cnt-1];
		TempX2 = x1+_cnt;
		TempY2 = LastBuff[_cnt];
		 
		if(TempY1>y1 && TempY1<y2) 
		if(TempY2>y1 && TempY2<y2) 	
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,WHITE);    
	}
	
	Struct_OSC ->MaxValue  = 0;
	Struct_OSC ->MinValue  = 0xffff;	
	Struct_OSC ->T = 0;
	Struct_OSC ->Vpp = 0;
	
	//分析数据 
	for(_cnt = 3;_cnt <Lenth/10;_cnt++)
	{
		if(Buff[_cnt] > Struct_OSC ->MaxValue) Struct_OSC ->MaxValue = Buff[_cnt],MaxX = _cnt;
		if(Buff[_cnt] < Struct_OSC ->MinValue) Struct_OSC ->MinValue = Buff[_cnt],MinX = _cnt;
	}		
				
	if(MaxX - MinX) Struct_OSC ->T = MaxX - MinX;	
	else Struct_OSC ->T = MinX - MaxX;	
	
	Struct_OSC ->Vpp = Struct_OSC ->MaxValue - Struct_OSC ->MinValue;	
											
	//画点		
	for(_cnt = 3;_cnt < x2-x1-3;_cnt++)
	{     
		LastBuff[_cnt] = ((u16)(Buff[(u16)((_cnt+Struct_OSC ->ShiftX)/Struct_OSC ->ZoomX)+MaxX])*Struct_OSC ->ZoomY) + Struct_OSC ->ShiftY - 100;//更新数据且图像偏移 
		TempX1 = x1+_cnt-1;		
		TempY1 = LastBuff[_cnt-1];		
		TempX2 = x1+_cnt;		
		TempY2 = LastBuff[_cnt];	
										
		if(TempY1>y1 && TempY1<y2) 		
		if(TempY2>y1 && TempY2<y2) 			
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,BLUE);  		
	} 
	OS_Num_Show(0,FONT_2*1,Struct_OSC ->T,FONT_2,1);		 OS_Num_Show(FONT_2*4,FONT_2*1,Struct_OSC ->Vpp,FONT_2,1); 
	OS_Num_Show(0,FONT_2*2,Struct_OSC ->MinValue,FONT_2,1);OS_Num_Show(FONT_2*4,FONT_2*2,Struct_OSC ->MaxValue,FONT_2,1);
	 
	OS_Rect_Draw(x1,y1,x2,y2,0,BLACK);
	OS_Rect_Draw(x1+1,y1+1,x2-1,y2-1,0,BLACK);  
	OS_Rect_Draw(x1-2,y1-2,x2+2,y2+2,0,BLACK);  
												
	//画左右边框点	
	for(y=y1;y<y2;y+=10*density)							
	{
		if(y%((u16)(50*density)) == y1)
		{
			OS_Rect_Draw(x1,y,x1+density*8,y+density,1,BLACK);//左
			OS_Rect_Draw(x2-density*8,y,x2,y+density,1,BLACK);//右
		}
		else
		{
			OS_Rect_Draw(x1,y,x1+density*5,y+density,1,BLACK);//左
			OS_Rect_Draw(x2-density*5,y,x2,y+density,1,BLACK);//右 
		}
	}
	//画上下边框点
	for(x=x1;x<x2;x+=10*density)							
	{
		if(x%((u16)(50*density)) == x1)
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*8,1,BLACK);//上
			OS_Rect_Draw(x,y2-density*8,x+density,y2,1,BLACK);//下
		}
		else
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*5,1,BLACK);//上
			OS_Rect_Draw(x,y2-density*5,x+density,y2,1,BLACK);//下
		}
	}  
	 
}
 


			

		
	
		
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
		
		
		
	
	
	

