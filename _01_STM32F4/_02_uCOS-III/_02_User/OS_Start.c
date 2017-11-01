/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : OS_Start.c
* @Description : None
* @Date        : 2017/2/16
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "OS_Start.h"  
#include "App_Include.h"  

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/  

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : OS_Start()     
* @Description   : ϵͳ��������
* @Data          : 2017/2/16
* @Explain       : None
------------------------------------------------------------------------------*/
void OS_Start(void)		
{
	OS_ERR err;
	 
	CPU_Init(); 
	OSInit(&err);			//��ʼ��UCOSIII  
	GUI_Init();  			//STemWin��ʼ�� 
	
	OS_TaskCreate(&App_LED);
	OS_TaskCreate(&App_Test);
	OS_TaskCreate(&App_emWinTest);
	
	OSStart(&err);  //����UCOSIII					
}	


/**----------------------------------------------------------------------------
* @FunctionName  : OS_TaskCreate()     
* @Description   : ���״�������
* @Data          : 2017/2/20
* @Explain       : ���أ�err
------------------------------------------------------------------------------*/
OS_ERR OS_TaskCreate(OS_Struct *os_struct)
{ 
	OS_ERR err;
	CPU_SR_ALLOC(); 
	OS_CRITICAL_ENTER();//�����ٽ���
	OSTaskCreate(//�������� 
					 (OS_TCB 	* )os_struct->app_tcb,			//������ƿ� 
					 (CPU_CHAR	* )os_struct->app_name, 		//��������
					 (OS_TASK_PTR )os_struct->app_fun, 			//������
					 (void		* )os_struct->p_arg,			//���ݸ��������Ĳ���
					 (OS_PRIO	  )os_struct->app_prio,   		//�������ȼ�
					 (CPU_STK   * )os_struct->app_STK,			//�����ջ����ַ
					 (CPU_STK_SIZE)os_struct->app_limit,		//�����ջ�����λ
					 (CPU_STK_SIZE)os_struct->app_size,			//�����ջ��С
					 (OS_MSG_QTY  )os_struct->q_size,							//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
					 (OS_TICK	  )os_struct->time_quanta,							//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
					 (void   	* )os_struct->p_ext,							//�û�����Ĵ洢��
					 (OS_OPT      )os_struct->opt, //����ѡ��
					 (OS_ERR 	* )&err							//��Ÿú�������ʱ�ķ���ֵ
			   );	
	
	OS_CRITICAL_EXIT();	//�˳��ٽ���	  
	
	return err;			 
}	



/**----------------------------------------------------------------------------
* @FunctionName  : Num_LenthGet()     
* @Description   : ��ȡ��ֵ�ĳ���
* @Data          : 2017/2/20
* @Explain       : ���أ���ֵ�ĳ���
------------------------------------------------------------------------------*/
u16 Num_LenthGet(u32 num)
{
	u16 cnt = 1;
	while(1)
	{
		num /= 10;
		if(num == 0) break;
		else cnt ++;
	}
	return cnt;
}

																				
/*******************************(C) COPYRIGHT 2017 Wind��л���죩*********************************/





