/*******************************(C) COPYRIGHT 2017 None *********************************/
/**============================================================================
* @FileName    : Drive_LoadMeasure.c
* @Description : None
* @Date        : 2017��7��31��
* @By          : None
* @Email       : None
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : ���ؼ�����
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_LoadMeasure.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_Recognize Recognize_Source[LOAD_MAX] = {0};//��¼��
Type_Recognize Recognize_New = {0}; 
	
/* ȫ�ֱ������� --------------------------------------------------------------*/
static float Similarity_Analysis(Type_Recognize Recognize_Source, Type_Recognize Recognize_New);
static Type_Recognize Harmo_Mix(u16 *deep); 

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Load_Recognize(void)
* @Description   : ����ʶ��
* @Data          : 2017��7��31��
* @Explain       : None
-------------------------------------------------------------------------------
Recognize_New ��Ҫʶ����ź�
------------------------------------------------------------------------------*/
#define VTP_SIMILARITY		(0.8f) 
Type_Recognize_Result Load_Recognize(Type_Recognize Recognize_Ne)
{
    float similarity = 0.0f;  //���ƶ�
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
                                            data_save_check = 0; //����Ƿ�������
                                }

                                if(data_save_check)
                                {
                                    Recognize_Temp = Harmo_Mix(deep);//��ϵ���

                                    similarity = Similarity_Analysis(Recognize_Temp, Recognize_Ne); //�õ�����ֵ

                                    if(similarity > TempMax) //��¼�����Ƶ����
                                    {
                                        for(i = 0; i < LOAD_MAX; i ++)
                                            Recognize_Result.WorkDevice_State[i] = deep[i];	
										
                                        Recognize_Result.Similarity = similarity;  
										
										ADC_Result.Others[LOAD_MAX-1] = Recognize_Temp.Phase[0];//�ϳɵ���λ
										
                                        TempMax = similarity;
                                    }
                                }
                            }
	
    return Recognize_Result;
}


static Type_Recognize Harmo_Mix(u16 *deep)//��ϵ���
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

 




//2����������
static float Tick_Paramet[2] = \
{  
    0.70f,	//�й�����	
    0.30f	//��λ��	
};
static float Similarity_Analysis(Type_Recognize Recognize_Sou, Type_Recognize Recognize_Ne) //���ƶȷ���
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
		similarity[0] = 1.0f - Py_error / All_error;//���� �� �й����� ���ƶ�
		if(similarity[0] < 0.0f||similarity[0] > 1.0f) similarity[0] = 0.0f;//����ֵ
		
		Py_error = fabsl((Recognize_Sou.Phase[0]) - (Recognize_Ne.Phase[0]));
		All_error = fabsl(Recognize_Ne.Phase[0]);
		similarity[1] = 1.0f - Py_error / All_error;//���� ��λ�� ���ƶ�
		if(similarity[1] < 0.0f||similarity[1] > 1.0f) similarity[1] = 0.0f;//����ֵ
		
		for(i = 0; i < 2; i ++)
			Result_similarity += similarity[i] * Tick_Paramet[i];
	}
	else
	{
		Py_error = fabsl((Recognize_Sou.Py[0]) - (Recognize_Ne.Py[0]));
		All_error = fabsl(Recognize_Ne.Py[0]);
		Result_similarity = 1.0f - Py_error / All_error;//���� �� �й����� ���ƶ� 
		
	}
	
	if(Result_similarity < 0.0f) Result_similarity = 0.0f;//����ֵ
	else if(Result_similarity > 1.0f) Result_similarity = 0.0f; //����ֵ
	
    return Result_similarity;
	
}




/**----------------------------------------------------------------------------
* @FunctionName  : Harmo_Analysis()
* @Description   : г������
* @Data          : 2017��7��29��
* @Explain       : None
------------------------------------------------------------------------------*/
void Recognize_New_Update(void)
{ 
    Recognize_New.Py[0] = ADC_Result.Py;//���� ����Ч����		
    Recognize_New.Phase[0] = ADC_Result.DiffPhase;//������λ��	
}









/*******************************(C) COPYRIGHT 2017 None *********************************/












