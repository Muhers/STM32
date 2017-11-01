/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_DAC.c
* @Description : DAC��������	
* @Date        : 2016/8/8
* @By          : Wind��л���죩
* @Email       : 1659567673@qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F103RCT6)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_DAC.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : DAC1_Init()
* @Description   : DACͨ��1�����ʼ��
* @Data          : 2016/8/8
* @Explain       : 
-------------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/ 
void DAC1_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��PORTAͨ��ʱ��
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //ģ������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 �����
					
	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1
    DAC_Init(DAC_Channel_1,&DAC_InitType);	 //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
  
    DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ

}


/**----------------------------------------------------------------------------
* @FunctionName  : DAC1_Set()
* @Description   : ����ͨ��1�����ѹ
* @Data          : 2016/8/8
* @Explain       : 
------------------------------------------------------------------------------- 
vol:��ѹ 0~4096
------------------------------------------------------------------------------*/ 
void DAC1_Set(u16 vol)
{  
	if(vol > 4096) vol = 4096; 
	DAC_SetChannel1Data(DAC_Align_12b_R,vol);//12λ�Ҷ������ݸ�ʽ����DACֵ
}















/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





