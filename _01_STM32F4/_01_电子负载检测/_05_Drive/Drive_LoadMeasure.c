/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_LoadMeasure.c
* @Description : None
* @Date        : 2017年7月31日
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 负载检测计算
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_LoadMeasure.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
Type_Recognize Recognize_Source[LOAD_MAX] = {0};//记录的
Type_Recognize Recognize_New = {0}; 
	
/* 全局变量声明 --------------------------------------------------------------*/
static float Similarity_Analysis(Type_Recognize Recognize_Source, Type_Recognize Recognize_New);
static Type_Recognize Harmo_Mix(u16 *deep); 

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Load_Recognize(void)
* @Description   : 负载识别
* @Data          : 2017年7月31日
* @Explain       : None
-------------------------------------------------------------------------------
Recognize_New 需要识别的信号
------------------------------------------------------------------------------*/
#define VTP_SIMILARITY		(0.8f) 
Type_Recognize_Result Load_Recognize(Type_Recognize Recognize_Ne)
{
    float similarity = 0.0f;  //相似度
    Type_Recognize Recognize_Temp = {0};
    Type_Recognize_Result Recognize_Result = {0};
    u16 i = 0;
    float TempMax = 0;
    u16 deep[LOAD_MAX] = {0};
    u8 data_save_check = 1;
	
    TempMax = VTP_SIMILARITY;
	
    for(i = 0; i < LOAD_MAX; i ++)
        Recognize_Result.WorkDevice_State[i] = 0xff;
	
    for(deep[0] = 0; deep[0] < WORK_STATE + 1; deep[0] ++)
        for(deep[1] = 0; deep[1] < WORK_STATE + 1; deep[1] ++)
            for(deep[2] = 0; deep[2] < WORK_STATE + 1; deep[2] ++)
                for(deep[3] = 0; deep[3] < WORK_STATE + 1; deep[3] ++)
                    for(deep[4] = 0; deep[4] < WORK_STATE + 1; deep[4] ++)
                        for(deep[5] = 0; deep[5] < WORK_STATE + 1; deep[5] ++)
                            for(deep[6] = 0; deep[6] < WORK_STATE + 1; deep[6] ++)
                            {
                                data_save_check = 1;
                                for(i = 0; i < LOAD_MAX; i ++)
                                {
                                    if(deep[i] != WORK_STATE)
                                        if(!(Recognize_Source[i].Save_State & (0x01 << deep[i])))
                                            data_save_check = 0; //检查是否有数据
                                }

                                if(data_save_check)
                                {
                                    Recognize_Temp = Harmo_Mix(deep);//组合叠加

                                    similarity = Similarity_Analysis(Recognize_Temp, Recognize_Ne); //得到相似值

                                    if(similarity > TempMax) //记录最相似的组合
                                    {
                                        for(i = 0; i < LOAD_MAX; i ++)
                                            Recognize_Result.WorkDevice_State[i] = deep[i];	
										
                                        Recognize_Result.Similarity = similarity;  
										
										ADC_Result.Others[LOAD_MAX-1] = Recognize_Temp.Phase[0];//合成的相位
										
                                        TempMax = similarity;
                                    }
                                }
                            }
	
    return Recognize_Result;
}


static Type_Recognize Harmo_Mix(u16 *deep)//组合叠加
{
    u16 i = 0; 
    Type_Recognize Recognize = {0};  
	
    for(i = 0; i < LOAD_MAX; i ++)	
    {
        Recognize.Py[0] += Recognize_Source[i].Py[deep[i]];  	 
    } 	  
	
	if( Recognize_New.Phase[0] < 20.0f) 
	{
		Recognize.Phase[0] = Recognize_New.Phase[0]; 
	}		
	else 
	{ 
		for(i = 0; i < LOAD_MAX; i ++)	 
		{
			Recognize.Phase[0] += Recognize_Source[i].Phase[deep[i]]*Recognize_Source[i].Py[deep[i]]/Recognize.Py[0];  	
			
		} 
	}
	
    return Recognize;	
}	

 




//2个反馈参数
static float Tick_Paramet[2] = \
{  
    0.70f,	//有功功率	
    0.30f	//相位角	
};
static float Similarity_Analysis(Type_Recognize Recognize_Sou, Type_Recognize Recognize_Ne) //相似度分析
{
    float similarity[2] = {0};
    float Py_error = 0;
    float All_error = 0;
    float Result_similarity = 0;
    u16 i = 0; 
	
	if(Recognize_Mode == 1)
	{
		Py_error = fabsl((Recognize_Sou.Py[0]) - (Recognize_Ne.Py[0]));
		All_error = fabsl(Recognize_Ne.Py[0]);
		similarity[0] = 1.0f - Py_error / All_error;//积分 总 有功功率 相似度
		if(similarity[0] < 0.0f||similarity[0] > 1.0f) similarity[0] = 0.0f;//错误值
		
		Py_error = fabsl((Recognize_Sou.Phase[0]) - (Recognize_Ne.Phase[0]));
		All_error = fabsl(Recognize_Ne.Phase[0]);
		similarity[1] = 1.0f - Py_error / All_error;//积分 相位角 相似度
		if(similarity[1] < 0.0f||similarity[1] > 1.0f) similarity[1] = 0.0f;//错误值
		
		for(i = 0; i < 2; i ++)
			Result_similarity += similarity[i] * Tick_Paramet[i];
	}
	else
	{
		Py_error = fabsl((Recognize_Sou.Py[0]) - (Recognize_Ne.Py[0]));
		All_error = fabsl(Recognize_Ne.Py[0]);
		Result_similarity = 1.0f - Py_error / All_error;//积分 总 有功功率 相似度 
		
	}
	
	if(Result_similarity < 0.0f) Result_similarity = 0.0f;//错误值
	else if(Result_similarity > 1.0f) Result_similarity = 0.0f; //错误值
	
    return Result_similarity;
	
}




/**----------------------------------------------------------------------------
* @FunctionName  : Harmo_Analysis()
* @Description   : 谐波分析
* @Data          : 2017年7月29日
* @Explain       : None
------------------------------------------------------------------------------*/
void Recognize_New_Update(void)
{ 
    Recognize_New.Py[0] = ADC_Result.Py;//积分 总有效功率		
    Recognize_New.Phase[0] = ADC_Result.DiffPhase;//积分相位角	
}









/*******************************(C) COPYRIGHT 2017 None *********************************/












