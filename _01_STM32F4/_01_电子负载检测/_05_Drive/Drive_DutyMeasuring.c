/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸) *********************************/
/**============================================================================
* @FileName    : Drive_DutyMeasuring.c
* @Description : None
* @Date        : 2017年7月17日
* @By          : Wind(谢玉伸)
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 测占空比
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_DutyMeasuring.h"

/* 私有宏定义 ----------------------------------------------------------------*/
#define DUTY_PIN(X) PEin(X)

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
static u32 Duty_Time[DUTY_NUM][2] = {0};
u32 Duty_TimeOver[DUTY_NUM] = {0};
u8 Duty_H_Cnt[DUTY_NUM] = {0};

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : DutyMeasuring_Init(void)
* @Description   : 测占空比
* @Data          : 2017年7月17日
* @Explain       : None
------------------------------------------------------------------------------*/
int DutyMeasuring_Init(void)
{  
	Exti0_Init();//PE0 
	TIM5_Init();
	
    return 0;
}	


/**----------------------------------------------------------------------------
* @FunctionName  : DutyMeasuring_IRQHandler(void)
* @Description   : 测占空比中断服务函数
* @Data          : 2017年7月17日
* @Explain       : None
------------------------------------------------------------------------------*/
int DutyMeasuring_IRQHandler(u8 ch)
{   
	static u32 _TimeLast[DUTY_NUM] = {0},_TimeOverLast[DUTY_NUM] = {0};   
	static u8 cnt[DUTY_NUM] = {0};
	
//	static u16 j = 0;
	
	Duty_Time[ch][cnt[ch]] = TIM_GetCounter(TIM5) + (Duty_TimeOver[ch] - _TimeOverLast[ch])*0xffffffff - _TimeLast[ch];
	if(DUTY_PIN(ch))Duty_H_Cnt[ch] = cnt[ch];
	
	cnt[ch] = (cnt[ch]+ 1)%2; 
	_TimeLast[ch] = TIM_GetCounter(TIM5);
	_TimeOverLast[ch] = Duty_TimeOver[ch];
	
//	Duty_Time[ch][cnt[ch]] = Duty_Time[ch][cnt[ch]] + sin(2*3.14*j/64)*500;//加入噪声模拟
//	j++;
	
    return 0;
}	



/**----------------------------------------------------------------------------
* @FunctionName  : Duty_Read(void)
* @Description   : 读取占空比
* @Data          : 2017年7月17日
* @Explain       : None
------------------------------------------------------------------------------*/
#define DUTY_FILTER_DEPP			(60)	//滤波深度
#define DUTY_FILTER_MUTATION		(4.0f)	//突变阈值
#define DUTY_FILTER_SECTION			(0.3f)	//滤波区间
static void quick_sort(float num[], int l, int r);
static float modified(float Duty);

float Duty_Read(u8 ch)
{   
	double Duty = 0.0f;
	static float LastDuty[DUTY_NUM][DUTY_FILTER_DEPP] = {0}; 
	float temp[DUTY_FILTER_DEPP] = {0};
	u16 i = 0; 

	
	if((Duty_Time[ch][0] + Duty_Time[ch][1]) > 0)
		Duty = (float)Duty_Time[ch][Duty_H_Cnt[ch]]/(float)(Duty_Time[ch][0] + Duty_Time[ch][1]); 
	Duty = 100.0f - Duty*100.0f;
	 
	/* 更新数据 ------------------------------------*/
	for(i = 0;i < DUTY_FILTER_DEPP - 1;i ++)
	{
		LastDuty[ch][i] = LastDuty[ch][i+1]; 
	} 
	if(fabs(LastDuty[ch][DUTY_FILTER_DEPP - 1] - Duty) < DUTY_FILTER_MUTATION) 
	{
		LastDuty[ch][DUTY_FILTER_DEPP - 1] = Duty;
	}
	else 
	{
		for(i = 0;i < DUTY_FILTER_DEPP;i ++)
		{
			LastDuty[ch][i] = Duty;
		} 
	}
		
	/* 快速排序 ------------------------------------*/
	for(i = 0;i < DUTY_FILTER_DEPP;i ++)
	{
		temp[i] = LastDuty[ch][i];
	} 
	quick_sort(temp,0,DUTY_FILTER_DEPP-1);
	
	/* 平滑滤波 ------------------------------------*/
	for(i = DUTY_FILTER_DEPP*DUTY_FILTER_SECTION;i < DUTY_FILTER_DEPP*(1-DUTY_FILTER_SECTION);i ++)
	{
		Duty += temp[i];   
	} 
	
	Duty /= (float)(DUTY_FILTER_DEPP*(1-DUTY_FILTER_SECTION) - DUTY_FILTER_DEPP*DUTY_FILTER_SECTION + 1); 
	
	return modified(Duty);
}	
 
static float modified(float x)
{ 
   double a = -1.15160937207356E-09;
   double b = 2.72134408900977E-07;
   double c = -2.45683941548218E-05;
   double d = 1.05839139411745E-03;
   double e = 0.970262530662193;
   double f = 0.590575727408956;
   double result;

   result = ((((((a * (pow(x , 5))) + (b * (pow(x , 4)))) + (c * (pow(x , 3)))) + (d * (pow(x , 2)))) + (e * x)) + f);
	
	return result;
}

static void quick_sort(float num[], int l, int r)  
{  
    int i, j;
	float x;  
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




/*******************************(C) COPYRIGHT 2017 Wind(谢玉伸) *********************************/







