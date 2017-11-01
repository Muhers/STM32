/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : OS_UI.c
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
#include "OS_UI.h" 	 


/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 -------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 

/* 全局变量声明 --------------------------------------------------------------*/ 

/* 全局函数编写 --------------------------------------------------------------*/

/*============================================= 底层程序层 =========================================*/
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
* @FunctionName  : OS_LCD_Clear()     
* @Description   : None 
* @Data          : 2016/7/12
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void OS_LCD_Clear(u16 color)
{
	LCD_Clear(color);
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
	LCD_SetCursor(x,y);//设置光标位置 
	LCD_WriteRAM_Prepare(); 
	LCD_WriteRAM(color);
}

/*============================================= 应用程序层 =========================================*/
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
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	u16 temp=TextColor;
	if(x1 == x2&&y1 == y2) x1 = x2 +1; 
	
	TextColor=color; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		OS_Points_Draw(uRow,uCol,color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
    
	TextColor=temp;
} 


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Lines_DrawSize()     
* @Description   : 画线
* @Data          : 2016/7/14
* @Explain        
------------------------------------------------------------------------------- 
* x1,y1:起点坐标
* x2,y2:终点坐标
------------------------------------------------------------------------------*/ 
void OS_Lines_DrawSize(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u8 cnt = 0;
	for(cnt = 0;cnt < size ;cnt ++)
	{ 	
		OS_Lines_Draw(x1,y1+cnt,x2,y2+cnt,color);	
		OS_Lines_Draw(x1,y1-cnt,x2,y2-cnt,color);	
	}  
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
		LCD_DrawCircleS(x,y,size,color);
	}
	else if(mode == 0)
	{
		LCD_DrawCircle(x,y,size);
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
	u16 temp=TextColor;
	TextColor=color;
	if(mode == 1)
	{ 
		LCD_DrawRectS(x1,y1,x2,y2,color);
		
	}
	else if(mode == 0)
	{
		OS_Lines_Draw(x1,y1,x2,y1,color);
		OS_Lines_Draw(x1,y2,x2,y2,color);
		OS_Lines_Draw(x2,y1,x2,y2,color);
		OS_Lines_Draw(x1,y1,x1,y2,color);
	} 
	TextColor=temp;
} 


 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_FFT_Draw1()     
* @Description   : 画FFT图 
* @Data          : 2016/7/12
* @Explain        
-------------------------------------------------------------------------------
density 格子密度     Rate 倍率 
------------------------------------------------------------------------------*/  
void OS_FFT_Draw(u16 x1,u16 y1,u16 x2,u16 y2,u16 *Buff,u16 Lenth,float density)
{
	u16 x=0,y=0,_cnt = 1; 
	u16 TempX1=0,TempY1=0,TempX2 = 0,TempY2 = 0;
	static u16 LastBuff[OS_LCD_WHITH] = {0}; 
	static u16 SourceBuff[OS_LCD_WHITH]	= {0}; 
	u16 Gap = Lenth/(x2 - x1)/2;
	
	Gap = Gap*Struct_OSC.ZoomX/100;
	
	if(Ch1_Switch == 1)	//打开则更新数据
	for(_cnt = 0;_cnt <Lenth;_cnt++)
	{
		SourceBuff[_cnt] = Buff[_cnt]; 
	} 
	
	if(Gap == 0) Gap = 1;
	density=(density+1)/10; 
	
	//画波形		
	for(_cnt = 0;_cnt < x2-x1;_cnt++)
	{    
		TempX1 = _cnt + x1 + 3;		
		TempY1 = y2 - LastBuff[_cnt]-1;		
		TempX2 = TempX1;		
		TempY2 = y2;	
		if(TempY1>y1 && TempY1<y2) 	
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,BLACK);  
		else 
			OS_Lines_Draw(TempX1,y1,TempX2,TempY2,BLACK);  	
		
		
		LastBuff[_cnt] = SourceBuff[_cnt*Gap]*4*Struct_OSC.ZoomY/100;//更新数据且图像偏移 
		TempX1 = _cnt + x1 + 3;		
		TempY1 = y2 - LastBuff[_cnt]-1;		
		TempX2 = TempX1;		
		TempY2 = y2;	
										
		if(TempY1>y1 && TempY1<y2) 				
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,GREEN);  
		else 
			OS_Lines_Draw(TempX1,y1,TempX2,TempY2,RED);  	
	} 
	
	//画左右边框点	
	for(y=y1;y<y2;y+=10*density)							
	{ 
		if(y%5 == 0)
		{ 
			OS_Rect_Draw(x1,y,x1+density*8,y+density,1,WHITE);//左
			OS_Rect_Draw(x2-density*8,y,x2,y+density,1,WHITE);//右
			
		}
		else
		{
			OS_Rect_Draw(x1,y,x1+density*5,y+density,1,WHITE);//左
			OS_Rect_Draw(x2-density*5,y,x2,y+density,1,WHITE);//右 
		}
		
	}
	//画上下边框点
	for(x=x1;x<x2;x+=10*density)							
	{
		if(x%5 == 0)
		{ 
			OS_Rect_Draw(x,y1,x+density,y1+density*8,1,WHITE);//上
			OS_Rect_Draw(x,y2-density*8,x+density,y2,1,WHITE);//下
			
		}
		else
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*5,1,WHITE);//上
			OS_Rect_Draw(x,y2-density*5,x+density,y2,1,WHITE);//下
		}
	} 
	 
	OS_Rect_Draw(x1+1,y1+1,x2-1,y2-1,0,GREEN);  
	OS_Rect_Draw(x1,y1,x2,y2,0,BLACK); 
	OS_Rect_Draw(x1-2,y1-2,x2+2,y2+2,0,BLUE);   
}
 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_FFT_Draw_Double()     
* @Description   : 画FFT图 
* @Data          : 2016/7/12
* @Explain        
-------------------------------------------------------------------------------
density 格子密度     Gap FFT密度
------------------------------------------------------------------------------*/  
void OS_FFT_Draw_Double(u16 x1,u16 y1,u16 x2,u16 y2,double *Buff,double Gap ,float density,float ZoomY)
{
	u16 x=0,y=0,_cnt = 1; 
	u16 TempX1=0,TempY1=0,TempX2 = 0,TempY2 = 0;
	static u16 LastBuff[OS_LCD_WHITH] = {0};   
	  
	if(Gap < 1) Gap = 1;
	density=(density+1)/10; 
	
	//画波形		
	for(_cnt = 0;_cnt < x2-x1-2;_cnt++)
	{    
		TempX1 = _cnt + x1 + 3;		
		TempY1 = y2 - LastBuff[_cnt]-1;		
		TempX2 = TempX1;		
		TempY2 = y2;	
		if(TempY1>y1 && TempY1<y2) 	
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,BLACK);  
		else 
			OS_Lines_Draw(TempX1,y1,TempX2,TempY2,BLACK);  	
		
		
		LastBuff[_cnt] = Buff[(u16)(_cnt*Gap)]*ZoomY;//更新数据且图像偏移 
		TempX1 = _cnt + x1 + 3;		
		TempY1 = y2 - LastBuff[_cnt]-1;		
		TempX2 = TempX1;		
		TempY2 = y2;	
										
		if(TempY1>y1 && TempY1<y2) 				
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,GREEN);  
		else 
			OS_Lines_Draw(TempX1,y1,TempX2,TempY2,RED);  	
	} 
	
	//画左右边框点	
	for(y=y1;y<y2;y+=10*density)							
	{ 
		if(y%5 == 0)
		{ 
			OS_Rect_Draw(x1,y,x1+density*8,y+density,1,WHITE);//左
			OS_Rect_Draw(x2-density*8,y,x2,y+density,1,WHITE);//右
			
		}
		else
		{
			OS_Rect_Draw(x1,y,x1+density*5,y+density,1,WHITE);//左
			OS_Rect_Draw(x2-density*5,y,x2,y+density,1,WHITE);//右 
		}
		
	}
	//画上下边框点
	for(x=x1;x<x2;x+=10*density)							
	{
		if(x%5 == 0)
		{ 
			OS_Rect_Draw(x,y1,x+density,y1+density*8,1,WHITE);//上
			OS_Rect_Draw(x,y2-density*8,x+density,y2,1,WHITE);//下
			
		}
		else
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*5,1,WHITE);//上
			OS_Rect_Draw(x,y2-density*5,x+density,y2,1,WHITE);//下
		}
	} 
	 
	OS_Rect_Draw(x1+1,y1+1,x2-1,y2-1,0,GREEN);  
	OS_Rect_Draw(x1,y1,x2,y2,0,BLACK); 
	OS_Rect_Draw(x1-2,y1-2,x2+2,y2+2,0,BLUE);   
}

/**----------------------------------------------------------------------------
* @FunctionName  : OS_OSC_Draw1()     
* @Description   : 画示波器图 
* @Data          : 2016/5/24
* @Explain        
-------------------------------------------------------------------------------
density 格子密度     Struct_OSC 示波器波形显示参数
------------------------------------------------------------------------------*/ 
void OS_OSC_Draw1(u16 x1,u16 y1,u16 x2,u16 y2,u16 *Buff,u16 Lenth,float density,Type_OSC *Struct_OSC,u16 color)
{
	u16 x=0,y=0,_cnt = 1;
	u16 TempX1=0,TempY1=0,TempX2 = 0,TempY2 = 0;
	u16 sTempX1=0,sTempY1=0,sTempX2 = 0,sTempY2 = 0; 
	u16 MaxX = 0,MinX = 0;
	u16 DutyCnt = 0;
	int UpDateX,UpDateY;
	static u16 LastBuff[OS_LCD_WHITH] = {0};    
	static u16 SourceBuff[OS_LCD_WHITH] = {0}; 
	
	/* 数据限制 ------------------------------------------------*/
	density=(density+1)/10;  
	Struct_OSC ->MaxValue  = 0;
	Struct_OSC ->MinValue  = 0xffff;	
	Struct_OSC ->T = 0;
	Struct_OSC ->Vpp = 0;
	if(Struct_OSC ->ZoomX >300) Struct_OSC ->ZoomX = 300;
	if(Struct_OSC ->ZoomX <2) Struct_OSC ->ZoomX = 2;
	if(Struct_OSC ->ZoomY >300) Struct_OSC ->ZoomY = 300;
	if(Struct_OSC ->ZoomY <2) Struct_OSC ->ZoomY = 2;
	 
	/* 数据转移 ------------------------------------------------*/
	if(Ch1_Switch == 1)//转存数据
	{ 				
		for(_cnt = 0;_cnt < Lenth ;_cnt ++)	
		{	 
			SourceBuff[_cnt] = Buff[_cnt];
		} 
	}
		 
	/* 分析数据 ------------------------------------------------*/	
	for(_cnt = 3;_cnt <Lenth/10;_cnt++)	
	{
		if(SourceBuff[_cnt] > Struct_OSC ->MaxValue) Struct_OSC ->MaxValue = SourceBuff[_cnt],MaxX = _cnt;
		if(SourceBuff[_cnt] < Struct_OSC ->MinValue) Struct_OSC ->MinValue = SourceBuff[_cnt],MinX = _cnt;
		
	}	
	
	for(_cnt = 0;_cnt <Lenth;_cnt++)		
		if(SourceBuff[_cnt] > (Struct_OSC ->MaxValue + Struct_OSC ->MinValue)/2) DutyCnt++; 
	
	Struct_OSC ->Duty = (float)DutyCnt/(float)Lenth*100.0f;
	
	if(MaxX - MinX > 0) Struct_OSC ->T = MaxX - MinX;		
	else Struct_OSC ->T = MinX - MaxX;		
	 
	Struct_OSC ->Vpp = Struct_OSC ->MaxValue - Struct_OSC ->MinValue;		
	if(MaxX > Lenth/2) MaxX = 0;	
	
	
	/* 绘图相关 ------------------------------------------------*/  
	//清除上一次画的		
	for(_cnt = 3;_cnt < x2-x1-3;_cnt++)
	{     
		sTempX1 = x1+_cnt-1;		
		sTempY1 = LastBuff[_cnt-1];		
		sTempX2 = x1+_cnt;		
		sTempY2 = LastBuff[_cnt];
		 
		if(sTempY1>y1 && sTempY1<y2) 		
		if(sTempY2>y1 && sTempY2<y2) 				
//			OS_Lines_DrawSize(TempX1,TempY1,TempX2,TempY2,2,BLACK);   
			OS_Lines_Draw(sTempX1,sTempY1,sTempX2,sTempY2,BLACK); 	 
	}		

	
	//画波形		
	for(_cnt = 3;_cnt < x2-x1-3;_cnt++)
	{     
		
		UpDateX = (int)((_cnt+Struct_OSC ->ShiftX - Struct_OSC ->ZoomX*3)*Struct_OSC ->ZoomX/100.0f+MinX); 
		if(UpDateX > 2000) 
		{
			Struct_OSC ->ShiftX = 900;
			UpDateX = (int)((_cnt+Struct_OSC ->ShiftX - Struct_OSC ->ZoomX*3)*Struct_OSC ->ZoomX/100.0f+MinX); 
		}
		if(UpDateX < 100)
		{
			Struct_OSC ->ShiftX = 1100;
			UpDateX = (int)((_cnt+Struct_OSC ->ShiftX - Struct_OSC ->ZoomX*3)*Struct_OSC ->ZoomX/100.0f+MinX); 
		} 
		 
		UpDateY = y2 - (((SourceBuff[UpDateX]) + Struct_OSC ->ShiftY - Struct_OSC ->ZoomY*0.7)*Struct_OSC ->ZoomY/100.0f)*(y2-y1)/256/4;  
		if(UpDateY > y2) 
		{
			Struct_OSC ->ShiftY += 10;	 
			UpDateY = y2 - (((SourceBuff[UpDateX]) + Struct_OSC ->ShiftY - Struct_OSC ->ZoomY*0.7)*Struct_OSC ->ZoomY/100.0f)*(y2-y1)/256/4; 
		}
		if(UpDateY < y1)
		{
			Struct_OSC ->ShiftY -=10; 
			UpDateY = y2 - (((SourceBuff[UpDateX]) + Struct_OSC ->ShiftY - Struct_OSC ->ZoomY*0.7)*Struct_OSC ->ZoomY/100.0f)*(y2-y1)/256/4;  
		}
		
		 
		LastBuff[_cnt] = UpDateY;
			 
		TempX1 = x1+_cnt-1;		
		TempY1 = LastBuff[_cnt-1];		
		TempX2 = x1+_cnt;		
		TempY2 = LastBuff[_cnt];	 
		if(TempY1>y1 && TempY1<y2) 		
		if(TempY2>y1 && TempY2<y2) 			
//			OS_Lines_DrawSize(TempX1,TempY1,TempX2,TempY2,2,color);  
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,color); 
	} 
	  										
	//画左右边框点	
	for(y=y1;y<y2;y+=10*density)							
	{ 
		if(y%5 == 0)
		{
			OS_Lines_Draw(x1,y,x2,y,GRAY);//横线
			OS_Rect_Draw(x1,y,x1+density*8,y+density,1,WHITE);//左
			OS_Rect_Draw(x2-density*8,y,x2,y+density,1,WHITE);//右
			
		}
		else
		{
			OS_Rect_Draw(x1,y,x1+density*5,y+density,1,WHITE);//左
			OS_Rect_Draw(x2-density*5,y,x2,y+density,1,WHITE);//右 
		}
		
	}
	//画上下边框点
	for(x=x1;x<x2;x+=10*density)							
	{
		if(x%5 == 0)
		{
			OS_Lines_Draw(x,y1,x,y2,GRAY);//竖线
			OS_Rect_Draw(x,y1,x+density,y1+density*8,1,WHITE);//上
			OS_Rect_Draw(x,y2-density*8,x+density,y2,1,WHITE);//下
			
		}
		else
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*5,1,WHITE);//上
			OS_Rect_Draw(x,y2-density*5,x+density,y2,1,WHITE);//下
		}
	} 
	 
	OS_Rect_Draw(x1+1,y1+1,x2-1,y2-1,0,GREEN);  
	OS_Rect_Draw(x1,y1,x2,y2,0,BLACK); 
	OS_Rect_Draw(x1-2,y1-2,x2+2,y2+2,0,BLUE);  
	 	 

}
 

/**----------------------------------------------------------------------------
* @FunctionName  : OS_OSC_Draw2()     
* @Description   : 画示波器图 
* @Data          : 2016/5/24
* @Explain        
-------------------------------------------------------------------------------
density 格子密度     Struct_OSC 示波器波形显示参数
------------------------------------------------------------------------------*/ 
void OS_OSC_Draw2(u16 x1,u16 y1,u16 x2,u16 y2,u16 *Buff,u16 Lenth,float density,Type_OSC *Struct_OSC,u16 color)
{
	u16 x=0,y=0,_cnt = 1;
	u16 TempX1=0,TempY1=0,TempX2 = 0,TempY2 = 0;
	u16 sTempX1=0,sTempY1=0,sTempX2 = 0,sTempY2 = 0; 
	u16 MaxX = 0,MinX = 0;
	int UpDateX,UpDateY;
	static u16 LastBuff[OS_LCD_WHITH] = {0};    
	static u16 SourceBuff[OS_LCD_WHITH] = {0}; 
	
	/* 数据限制 ------------------------------------------------*/
	density=(density+1)/10;  
	Struct_OSC ->MaxValue  = 0;
	Struct_OSC ->MinValue  = 0xffff;	
	Struct_OSC ->T = 0;
	Struct_OSC ->Vpp = 0;
	if(Struct_OSC ->ZoomX >300) Struct_OSC ->ZoomX = 300;
	if(Struct_OSC ->ZoomX <2) Struct_OSC ->ZoomX = 2;
	if(Struct_OSC ->ZoomY >300) Struct_OSC ->ZoomY = 300;
	if(Struct_OSC ->ZoomY <2) Struct_OSC ->ZoomY = 2;
	 
	/* 数据转移 ------------------------------------------------*/
	if(Ch2_Switch == 1)//转存数据
	{ 				
		for(_cnt = 0;_cnt < Lenth ;_cnt ++)	
		{	
			if(Buff[_cnt] < 100)	
				SourceBuff[_cnt] = (u8)((Buff[_cnt]*0.0294f - 2.441f)*255/3.3f);//矫正AD	
			else if(Buff[_cnt] < 130)	
				SourceBuff[_cnt] = (u8)((Buff[_cnt]/29.0f - 2.7931f)*255/3.3f);//矫正AD
			else if(Buff[_cnt] < 150)	
				SourceBuff[_cnt] = (u8)((Buff[_cnt]/38.0f - 1.89474f)*255/3.3f);//矫正AD
			else
			{
				if(((Buff[_cnt] + 2)/75.2f)*255/3.3f > 255) SourceBuff[_cnt] = 255;
				else SourceBuff[_cnt] = (u8)(((Buff[_cnt] + 2)/75.2f)*255/3.3f);//矫正AD
			}
		}
		  
	}
		 
	/* 分析数据 ------------------------------------------------*/	
	for(_cnt = 3;_cnt <Lenth/10;_cnt++)	
	{
		if(SourceBuff[_cnt] > Struct_OSC ->MaxValue) Struct_OSC ->MaxValue = SourceBuff[_cnt],MaxX = _cnt;
		if(SourceBuff[_cnt] < Struct_OSC ->MinValue) Struct_OSC ->MinValue = SourceBuff[_cnt],MinX = _cnt;
	}		
	 
	if(MaxX - MinX > 0) Struct_OSC ->T = MaxX - MinX;		
	else Struct_OSC ->T = MinX - MaxX;		
	 
	Struct_OSC ->Vpp = Struct_OSC ->MaxValue - Struct_OSC ->MinValue;		
	if(MaxX > Lenth/2) MaxX = 0;	
	
	
	/* 绘图相关 ------------------------------------------------*/  
	//清除上一次画的		
	for(_cnt = 3;_cnt < x2-x1-3;_cnt++)
	{     
		sTempX1 = x1+_cnt-1;		
		sTempY1 = LastBuff[_cnt-1];		
		sTempX2 = x1+_cnt;		
		sTempY2 = LastBuff[_cnt];
		 
		if(sTempY1>y1 && sTempY1<y2) 		
		if(sTempY2>y1 && sTempY2<y2) 				
//			OS_Lines_DrawSize(TempX1,TempY1,TempX2,TempY2,2,BLACK);   
			OS_Lines_Draw(sTempX1,sTempY1,sTempX2,sTempY2,BLACK); 	 
	}		 

	
	//画波形		
	for(_cnt = 3;_cnt < x2-x1-3;_cnt++)
	{     
		
		UpDateX = (int)((_cnt+Struct_OSC ->ShiftX - Struct_OSC ->ZoomX*3)*Struct_OSC ->ZoomX/100.0f+MinX); 
		if(UpDateX > 2000) 
		{
			Struct_OSC ->ShiftX = 900;
			UpDateX = (int)((_cnt+Struct_OSC ->ShiftX - Struct_OSC ->ZoomX*3)*Struct_OSC ->ZoomX/100.0f+MinX); 
		}
		if(UpDateX < 100)
		{
			Struct_OSC ->ShiftX = 1100;
			UpDateX = (int)((_cnt+Struct_OSC ->ShiftX - Struct_OSC ->ZoomX*3)*Struct_OSC ->ZoomX/100.0f+MinX); 
		} 
		 
		UpDateY =  (((SourceBuff[UpDateX]) + Struct_OSC ->ShiftY - Struct_OSC ->ZoomY*0.7)*Struct_OSC ->ZoomY/100.0f)*(y2-y1)/256/4;  
		if(UpDateY > y2) 
		{
			Struct_OSC ->ShiftY += 10;	 
			UpDateY =(((SourceBuff[UpDateX]) + Struct_OSC ->ShiftY - Struct_OSC ->ZoomY*0.7)*Struct_OSC ->ZoomY/100.0f)*(y2-y1)/256/4; 
		}
		if(UpDateY < y1)
		{
			Struct_OSC ->ShiftY -=10; 
			UpDateY = (((SourceBuff[UpDateX]) + Struct_OSC ->ShiftY - Struct_OSC ->ZoomY*0.7)*Struct_OSC ->ZoomY/100.0f)*(y2-y1)/256/4; 
			
		}
		
		 
		LastBuff[_cnt] = UpDateY;
			 
		TempX1 = x1+_cnt-1;		
		TempY1 = LastBuff[_cnt-1];		
		TempX2 = x1+_cnt;		
		TempY2 = LastBuff[_cnt];	 
		if(TempY1>y1 && TempY1<y2) 		
		if(TempY2>y1 && TempY2<y2) 			
//			OS_Lines_DrawSize(TempX1,TempY1,TempX2,TempY2,2,color);  
			OS_Lines_Draw(TempX1,TempY1,TempX2,TempY2,color); 
	} 
	  										
	//画左右边框点	
	for(y=y1;y<y2;y+=10*density)							
	{ 
		if(y%5 == 0)
		{
			OS_Lines_Draw(x1,y,x2,y,GRAY);//横线
			OS_Rect_Draw(x1,y,x1+density*8,y+density,1,WHITE);//左
			OS_Rect_Draw(x2-density*8,y,x2,y+density,1,WHITE);//右
			
		}
		else
		{
			OS_Rect_Draw(x1,y,x1+density*5,y+density,1,WHITE);//左
			OS_Rect_Draw(x2-density*5,y,x2,y+density,1,WHITE);//右 
		}
		
	}
	//画上下边框点
	for(x=x1;x<x2;x+=10*density)							
	{
		if(x%5 == 0)
		{
			OS_Lines_Draw(x,y1,x,y2,GRAY);//竖线
			OS_Rect_Draw(x,y1,x+density,y1+density*8,1,WHITE);//上
			OS_Rect_Draw(x,y2-density*8,x+density,y2,1,WHITE);//下
			
		}
		else
		{
			OS_Rect_Draw(x,y1,x+density,y1+density*5,1,WHITE);//上
			OS_Rect_Draw(x,y2-density*5,x+density,y2,1,WHITE);//下
		}
	} 
	 
	OS_Rect_Draw(x1+1,y1+1,x2-1,y2-1,0,GREEN);  
	OS_Rect_Draw(x1,y1,x2,y2,0,BLACK); 
	OS_Rect_Draw(x1-2,y1-2,x2+2,y2+2,0,BLUE);  
	 	 
	 	
}

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Picture_Draw()     
* @Description   : 显示图片
* @Data          : 2016/3/22
* @Explain        
------------------------------------------------------------------------------- 
* RGB565  16位真彩显示
* mode :  0 不可放缩      1 可缩放       2 可缩放，不显示白色
		  3 可缩放，不显示白色,且变灰 
* 带头数据 
------------------------------------------------------------------------------*/ 
void OS_Picture_Draw(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic,u8 mode)
{	
	u16 temp=TextColor;  
	
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
		
		for(y=0;y<len_y;y++) 
		for(x=0;x<len_x*2;x+=2) 
		{  
			if((u16)((x/2)*density_x+x1) <= x2)
			if((u16)(y*density_y+y1) <= y2)		
			{
				p_color=pic[x+6+y*len_x*2]<<8|pic[(x+7)+y*len_x*2];
				if(p_color > 1) //不显示白色背景
				{ 
					LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//设置光标位置 
					LCD_WriteRAM_Prepare(); 
					LCD_WriteRAM(p_color);
				}
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
				p_color=pic[x+6+y*len_x*2]<<8|pic[(x+7)+y*len_x*2];
				if(p_color > 1) //不显示黑色背景
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
	
	}
	TextColor = temp;
} 


/**----------------------------------------------------------------------------
* @FunctionName  : OS_String_Show()     
* @Description   : 打印句子 
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* x,y 坐标    *str 语句指针   size 字体大小   
------------------------------------------------------------------------------*/ 
void OS_HzMat_Get(uint8_t *code,uint8_t *mat,u8 size)
{		    
	uint8_t qh,ql;
	uint8_t i;					  
	uint32_t foffset; 
	u8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数	 
	qh=*code;
	ql=*(++code);
	if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//非常用汉字
	{   		    
	    for(i=0;i<csize;i++)*mat++=0x00;//填充满格
	    return; //结束访问
	}          
	if(ql<0x7f)ql-=0x40;//注意!
	else ql-=0x41;
	qh-=0x81;   
	foffset=((uint32_t)190*qh+ql)*csize;	//得到字库中的字节偏移量  		  
	switch(size)
	{
		case 32:
			W25Q64_Read(mat,foffset+ftinfo.f12addr,csize);
			break;
		case 16:
			W25Q64_Read(mat,foffset+ftinfo.f16addr,csize);
			break;
		case 24:
			W25Q64_Read(mat,foffset+ftinfo.f24addr,csize);
			break;
			
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
void OS_Font_Show(u16 x,u16 y,u8 *font,u8 size,u8 mode)
{
	u8 temp,t,t1;
	u16 y0=y;
	u8 dzk[144];   
	u8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数	 
	if(size!=32&&size!=16&&size!=24) return;	//不支持的size
	OS_HzMat_Get(font,dzk,size);	//得到相应大小的点阵数据 
	for(t=0;t<csize;t++)
	{   												   
		temp=dzk[t];			//得到点阵数据                          
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80) OS_Points_Draw(x,y,TextColor); 			
			else if(mode==1) OS_Points_Draw(x,y,BackColor); 		
			temp<<=1;		
			y++;		
			if((y-y0)==size)		
			{
				y=y0;
				x++;
				break;
			}
		}  	 
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
void  OS_String_Show(u16 x, u16 y, u8 *str, u8 size, u8 mode)
{ 
    uint16_t x0 = x;
    uint8_t bHz = 0;   //字符或者中文  
	u16 error = 0;
	static u8 UeseState = 0;
	
	if(UeseState) return;
	UeseState = 1;
	
    while(*str != 0)		//数据未结束
    {
 
        if(!bHz)
        {
            if(*str > 0x80)bHz = 1; //中文
            else              //字符
            {
                if(*str == 13) //换行符号
                {
                    y += size;
                    x = x0;
                    str++;
                } 
                OS_Char_Show(x, y,*str,size,mode); 
                str++;
                x += size / 2; //字符,为全字的一半 
            } 
        }
        else //中文
        {	
            bHz = 0; //有汉字库	
            OS_Font_Show(x,y, str, size,mode);	
            str += 2;
            x += size; //下一个汉字偏移	
        }
    } 
	UeseState = 0;
}

 
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Char_Show()     
* @Description   : 打印字符
* @Data          : 2016/7/14
* @Explain        
-------------------------------------------------------------------------------
在指定位置显示一个字符
x,y:起始坐标
num:要显示的字符:" "--->"~"
size:字体大小 16/24/32
mode:叠加方式(1)还是非叠加方式(0)
------------------------------------------------------------------------------*/  
void OS_Char_Show(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
	//设置窗口		   
	num=num-' ';//得到偏移后的值 
	for(t=0;t<csize;t++)
	{    
		if(size==16)temp=asc2_1608[num][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[num][t];//调用2412字体
		else if(size==32)temp = asc2_3216[num][t];//调用3216字体
		else return;//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)OS_Points_Draw(x,y,TextColor);
			else if(mode==1)OS_Points_Draw(x,y,BackColor);
			temp<<=1;
			y++;
			if(y>=480)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=800)return;	//超区域了
				break;
			}
		}  	 
	}   
} 

/**----------------------------------------------------------------------------
* @FunctionName  : OS_0Num_Show()     
* @Description   : 高位置0显示
* @Data          : 2016/7/18
* @Explain        
------------------------------------------------------------------------------- 
x,y 坐标    num 数值   size 字体大小   
digit 保留有效数字     len 数值总长度 
------------------------------------------------------------------------------*/ 
void OS_0Num_Show(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{         	
	u8 t,temp,tem[10] ={0};
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/(u32)pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				
				OS_String_Show(x+(size/2)*t,y,(u8*)"0",size,mode);
				continue;
			}else enshow=1;  
		}
		if(temp <= 9) tem[0]=temp+'0';  
	 	OS_String_Show(x+(size/2)*t,y,tem,size,mode); 
	}
} 

/**----------------------------------------------------------------------------
* @FunctionName  : OS_Decim_Show()     
* @Description   : 打印小数 
* @Data          : 2016/7/12
* @Explain        
------------------------------------------------------------------------------- 
x,y 坐标    num 数值   size 字体大小   
DecimLenth 小数长度     NumLenth 整数长度 
------------------------------------------------------------------------------*/ 
void OS_Decim_Show(u16 x,u16 y,double num,u8 NumLenth,u8 DecimLenth,u8 size,u8 mode)
{ 	                         
	unsigned long int sNum,sDecim;                  
	unsigned long int temp;  
	unsigned char ch[32] = {0},flag = 0;	
	unsigned int cnt = 0,i = 0;
	
	ch[0] = ' ';	
	if(num < 0.0f)	
	{	
		num = -num;		
		ch[0] = '-';	
	} 	
	
	sNum = (unsigned long int)num;		
	sDecim = (num - sNum + 0.0000000000001f)*pow(10,DecimLenth);//保留digit位小数，弥补double型正负的误差	
 
	while(NumLenth--) //显示整数
	{ 
		temp = pow(10,NumLenth); 
		ch[++cnt] = '0' + sNum/temp;
		
		if(flag == 0)
		{
			if(ch[cnt] == '0') ch[cnt] = ' '; 
			else flag = 1;
		} 
		sNum -= (sNum/temp)*temp; 
	} 
	if(ch[cnt] == ' ') ch[cnt] = '0';
		
	if(DecimLenth != 0)//显示小数部分
	{
		ch[++cnt] = '.';
		  
		while(DecimLenth--) 
		{ 
			temp = pow(10,DecimLenth); 
			ch[++cnt] = '0' + sDecim/temp;
			sDecim -= (sDecim/temp)*temp; 
		}  
	}
	 
	for(i = cnt+1;i<32;i++) ch[i] = 0;
	 
	OS_String_Show(x,y,ch,size,mode); 
	
} 


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Num_Show()     
* @Description   : 打印整数	
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------  
x,y 坐标    num 数值   size 字体大小   
NumLenth 整数长度
------------------------------------------------------------------------------*/   
void OS_Num_Show(u16 x,u16 y,long long int num,u8 NumLenth,u8 size,u8 mode)
{    
	 OS_Decim_Show(x,y,num,NumLenth,0,size,mode); 
}


/**----------------------------------------------------------------------------
* @FunctionName  : OS_Point_Read()     
* @Description   : 读取点颜色
* @Data          : 2016/3/22
* @Explain        
-------------------------------------------------------------------------------
* x,y 坐标    num 数值   size 字体大小   
* len 数值总长度
------------------------------------------------------------------------------*/ 
u16 OS_Point_Read(u16 x,u16 y) 
{  
//	return LCD_ReadPoint(x,y); 
	return BackColor;
} 

void OS_LCD_Init(void) 
{   
	TFT_LCD_Init();	
	OSdelay_ms(100);
	LCD_Clear(BLACK);//清屏	
	if(font_init()) OS_String_Show(400,200,(u8*)"Font Error!!!",32,1);;  //检查字库  
	TextColor = WHITE;
	BackColor = BLACK;
	
}	

 
						
			

		
	
		
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
		
		
		
	
	
	

