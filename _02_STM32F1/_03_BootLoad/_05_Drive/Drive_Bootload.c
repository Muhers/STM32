/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Bootload.c
* @Description : �����ļ�
* @Date        : 2016/10/9
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : 
-------------------------------------------------------------------------------
10k(0x8000000 ~ 0x8002800)��������ļ�
1K(0x8002800~0x8003000)�����������
*=============================================================================*/
/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Bootload.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/
static void Bootload_Init(void);
static void Bootload_Update(void);

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_Bootload Bootload = {0};

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Bootload_Init()
* @Description   : ����������ʼ��
* @Data          : 2016/10/9
* @Explain       : 
-------------------------------------------------------------------------------
����ֻ��ģ�⣬�Ժ�����ʵ�ʵõ������ݳ�ʼ������
------------------------------------------------------------------------------*/ 
static void Bootload_Init(void)
{
	Bootload.Flag_Update = 0;//û�и��±�־(ʵ�ʲ���ʱӦ����ȡFlash��ֵ)
	Bootload.New_Addr = (Type_Void *)(0x8003000|0x01);
	Bootload.Old_Addr = NULL;//Ҫ����ĳ���ĵ�ַ
	
}

/**----------------------------------------------------------------------------
* @FunctionName  : Bootload_Update()
* @Description   : ��������
* @Data          : 2016/10/10 
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
static void Bootload_Update(void)
{
	if(Bootload.Flag_Update)
	{
		Bootload.Flag_Update = 0;//(ʵ�ʲ���ʱӦ��д��Flash)
		Bootload.Old_Addr = Bootload.New_Addr;//ת��ԭ������ĵ�ַ(ʵ�ʲ���ʱӦ��д��Flash)
		Bootload.New_Addr = (Type_Void *)(0x8003000|0x01);//(ʵ�ʲ���ʱӦ����ȡFlash��ֵ) 
		
		NVIC_SystemReset();//���� 
		
	}
}

 
/**----------------------------------------------------------------------------
* @FunctionName  : Bootload_Run()
* @Description   : ������������
* @Data          : 2016/10/9
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void Bootload_Run(void)
{ 
	while(1)
	{
		Bootload_Init(); 							
		Bootload_Update();							
		Bootload.New_Addr();//��ת�����еĳ���		
		
	}
	
}
 




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/











