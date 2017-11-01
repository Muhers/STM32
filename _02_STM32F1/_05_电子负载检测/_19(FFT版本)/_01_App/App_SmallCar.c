/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_SmallCar.c
* @Description : 小车
* @Date        : 2016/8/20
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_SmallCar.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/ 
 
/* 全局变量定义 --------------------------------------------------------------*/
static Type_AppList App_SmallCar_ChannelScan; 	
static void EasyPID(int State);	

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar()
* @Description   : 小车主程序
* @Data          : 2016/8/8
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int SmallCar_Main(void)
{
    static u16 cnt = 0; 
	u8 i = 0;
	 
    cnt += 50;
    cnt %= 2400;
    OS_Num_Show(0, 0, SmallCar.LeftSpeed, 5);
    OS_Num_Show(5, 0, SmallCar.RightSpeed, 5);
	 
	for(i = 0;i < 7;i ++)
	{
		if(SmallCar.LastChannelEvent[SmallCar.Cnt] & 0x01 << i) OS_Num_Show(i, 1, 1, 1); 
		else OS_Num_Show(i, 1, 0, 1); 
		 
	} 
	 
	
    return 0;
}

unsigned int SmallCar_Start(void)
{
    SmallCar_Init();
	OSTask_Creat(&App_SmallCar_ChannelScan);  
	
    return 0;
}


Type_AppList App_SmallCar = {SmallCar_Main, NULL, SmallCar_Start, NULL, \
                             OS_STATE_ACTIVE, OS_THREAD_PRIMARY, \
                             (u8 *)"SmallCar", 100
                            };


							
//快速排序算法
static void quick_sort(u16 num[], int l, int r)  
{  
    int i, j, x;  
    if (l < r)  
    {  
        i = l;  
        j = r;  
        x = num[i];  
        while (i < j)  
        {  
            while(i < j && num[j] > x)   
                j--; /* 从右向左找第一个小于x的数 */  
            if(i < j)   
                num[i++] = num[j];  
      
  
            while(i < j && num[i] < x)   
                i++; /* 从左向右找第一个大于x的数 */  
            if(i < j)   
                num[j--] = num[i];  
  
        }  
        num[i] = x;  
        quick_sort(num, l, i-1); /* 递归调用 */  
        quick_sort(num, i+1, r);  
    }  
}  

 
/**----------------------------------------------------------------------------
* @FunctionName  : SmallCar()
* @Description   : 通道扫描
* @Data          : 2016/8/8
* @Explain       : None
------------------------------------------------------------------------------*/							
unsigned int SmallCar_ChannelScan_Main(void)
{
	u16 i = 0; 						
	u8 BitNum[7] = {0};			
	
	
	if(SmallCar.Channel_Flag)//数据更新
	{
		for(i = 0;i<CHANNEL_NUM;i++) //快速排序
		{ 
			quick_sort(SmallCar.Channel[i],0,CHANNEL_LENTH - 1);	  
			if(SmallCar.Channel[i][CHANNEL_LENTH/2] > 500)   SmallCar.LastChannelEvent[SmallCar.Cnt] |= (0x01 << i),BitNum[i] = 1;		
			else SmallCar.LastChannelEvent[SmallCar.Cnt] &= ~(0x01 << i),BitNum[i] = 0; 
			 
		}	
		 
		
		
		if(BitNum[0] == 0 && BitNum[1] == 0 && BitNum[2] == 0 && BitNum[3] == 0 && BitNum[4] == 0 && BitNum[5] == 0 && BitNum[6] == 0)//空白
		{
			OS_String_Show(0,2,(u8*)"全空  ");   
			EasyPID(0xffff); 
		}
		else if(BitNum[0] == 1 && BitNum[6] == 1) //交叉路口
		{
			EasyPID(0);
			OS_String_Show(0,2,(u8*)"交叉路");   
		}
		else if(BitNum[0]) //偏离中线，左大转 
		{ 
			EasyPID(-90);
			OS_String_Show(0,2,(u8*)"左大转");  
		}
		else if(BitNum[6])//偏离中线，右大转
		{	
			EasyPID(90);
			OS_String_Show(0,2,(u8*)"右大转"); 
		}
		else if(BitNum[3]) //直线
		{ 
			EasyPID(0);
			OS_String_Show(0,2,(u8*)"直线  "); 
			
		}
		else if(BitNum[2])//左中转
		{
			EasyPID(-5);
			OS_String_Show(0,2,(u8*)"左中转"); 
		}
		else if(BitNum[4])//右中转
		{
			EasyPID(5);
			OS_String_Show(0,2,(u8*)"右中转"); 	
		}
		else if(BitNum[1])//左转
		{
			EasyPID(-10);
			OS_String_Show(0,2,(u8*)"左转  "); 
		}
		else if(BitNum[5])//右转
		{
			EasyPID(10);
			OS_String_Show(0,2,(u8*)"右转  "); 
			
			
		}
		 
		SmallCar.Cnt ++;
		SmallCar.Cnt %= 100;
		SmallCar.Channel_Flag = 0;	
	}
	 
    return 0;
}
static Type_AppList App_SmallCar_ChannelScan = {SmallCar_ChannelScan_Main, NULL, NULL, NULL, \
												OS_STATE_ACTIVE, OS_THREAD_SYSTEM, \
												(u8 *)"SmallCar_ChannelScan", 1
												};
	
												
static void EasyPID(int State)
{
	u16 BasisValue = 2200;
	
	static int LastState = 0xfffe,Integral = 0;  
	
	if(State == 0xffff) State = LastState;
	
	if(LastState == State)
	{
		Integral +=10;
		if(Integral > 200) Integral = 200;
	}
	else 
	{
		Integral --;
	}
	LastState = State;
	
	if(State > 100) State = 100;		
	else if(State < -100) State = -100;		
 
	if(State > 0)//往右偏
	{ 
		SmallCar_Right_Control(BasisValue - State*BasisValue*2/100 - Integral);			
		SmallCar_Left_Control(BasisValue + Integral); 	
	}
	else if(State < 0)//往左偏 
	{
		State = -State;
		 
		SmallCar_Right_Control(BasisValue + Integral);			
		SmallCar_Left_Control(BasisValue - State*BasisValue*2/100 - Integral); 	
	}
	else//直线
	{
		SmallCar_Right_Control(BasisValue);			
		SmallCar_Left_Control(BasisValue); 	 
	}
	
}	

 

/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/



							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							
							

