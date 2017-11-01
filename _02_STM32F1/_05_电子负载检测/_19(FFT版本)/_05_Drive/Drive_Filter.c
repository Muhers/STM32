/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_Filter.c
* @Description : None
* @Date        : 2017年7月31日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 各种滤波函数
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Filter.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/

/* 全局变量声明 --------------------------------------------------------------*/

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Filter_Wind()
* @Description   : Wind滤波
* @Data          : 2017年7月31日
* @Explain       : 谢玉伸二号滤波
------------------------------------------------------------------------------*/
int Filter_Wind(Type_Filter *Struct_Filter)
{
    u16 i = 0;
    float temp[FILTER_DEPP_MAX] = {0}; 
    float result = 0;
    int _return = 0;

    /* 限制数据 ------------------------------------*/
//    if(Struct_Filter ->Filter_Depp > FILTER_DEPP_MAX)
//    {
//        Struct_Filter ->Filter_Depp = FILTER_DEPP_MAX;
//        _return = -1;//越界警告
//    }
    if(Struct_Filter ->Filter_Section > 0.4f)
    {
        Struct_Filter ->Filter_Section = 0.4f;
        _return = -2;//越界警告
    } 
	
    /* 更新数据 ------------------------------------*/
    if(fabs(Struct_Filter->Last_Result[Struct_Filter->Filter_Depp - 1] - Struct_Filter->Value) < Struct_Filter->Filter_Mutation)
    {
        Struct_Filter->Last_Result[Struct_Filter->Filter_Depp - 1] = Struct_Filter->Value;
    }
    else //突变
    {
        for(i = 0; i < Struct_Filter->Filter_Depp; i ++)
        {
            Struct_Filter->Last_Result[i] = Struct_Filter->Value;
        }
    }
	
    /* 快速排序 ------------------------------------*/
    for(i = 0; i < Struct_Filter->Filter_Depp; i ++)
    {
        temp[i] = Struct_Filter->Last_Result[i];
    }
    Sort_Quick(temp, 0, Struct_Filter->Filter_Depp - 1);

    /* 平滑滤波 ------------------------------------*/
    for(i = Struct_Filter->Filter_Depp * Struct_Filter->Filter_Section; i < Struct_Filter->Filter_Depp * (1 - Struct_Filter->Filter_Section); i ++)
    {
        result += temp[i];
    }
    result /= (double)(Struct_Filter->Filter_Depp * (1 - Struct_Filter->Filter_Section) - Struct_Filter->Filter_Depp * Struct_Filter->Filter_Section);

    /* 移位 ----------------------------------------*/
    Struct_Filter->Last_Result[Struct_Filter->Filter_Depp - 1] = Struct_Filter->Value;
    for(i = 0; i <  Struct_Filter->Filter_Depp - 1; i ++)
    {
        Struct_Filter->Last_Result[i] = Struct_Filter->Last_Result[i + 1];
    }

    Struct_Filter->Value = result; 
	
    return _return;
}



/**----------------------------------------------------------------------------
* @FunctionName  : Sort_Quick()
* @Description   : 快速排序
* @Data          : 2017年7月31日
* @Explain       : num,数组 	 l,左边起始位置		r,右边起始位置
------------------------------------------------------------------------------*/
void Sort_Quick(float *num, int l, int r)
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
        Sort_Quick(num, l, i - 1); /* 递归调用 */
        Sort_Quick(num, i + 1, r);
    }

}



/**----------------------------------------------------------------------------
* @FunctionName  : Conv()
* @Description   : 卷积
* @Data          : 2017年8月8日
* @Explain       : output 的长度是N1+N2-1;
------------------------------------------------------------------------------*/
void Conv(float *output, float *input1, float *input2, int N1, int N2)
{
    int i = 0, j = 0,k = N1+N2-1;
	
    for(i = 0; i < k; i++)
    { 
        for(j = MAX2(0, i + 1 - N1); j <= MIN2(i, N2 - 1); j++)
        {
            output[i] += input1[j] * input2[i - j];
        } 
		
    }

}



/**----------------------------------------------------------------------------
* @FunctionName  : FIR()
* @Description   : FIR滤波
* @Data          : 2017年8月8日
* @Explain       : output 的长度是N;
------------------------------------------------------------------------------*/
void FIR(float *input)
{
	int i = 0;
	float temp[FIR_LENTH*2] = {0};
//	Conv(temp,input,(float*)FIR_100_LowPass_H,FIR_LENTH,FIR_LENTH);
	
	for(i = 0;i < FIR_LENTH;i ++)
	{
		input[i] = temp[i+FIR_LENTH/2]; 
	}
	
	
}	


/**----------------------------------------------------------------------------
* @FunctionName  : Phase_Limit()
* @Description   : 相位限制
* @Data          : 2017年8月8日
* @Explain       : None
------------------------------------------------------------------------------*/
float Phase_Limit(float _phase)
{ 
	int int_phase = _phase;
	float float_phase = (_phase - int_phase);
	
	while(int_phase < 0)  int_phase += 360; 
	
	int_phase %= 180;
	
	_phase = int_phase + float_phase; 
	
	return _phase;
}	




/*******************************(C) COPYRIGHT 2017 None *********************************/










