/***************************************************************************************************
  * ��    ����PID.h   
  * ��    �ߣ�guojiang 
  * �� �� �壺stm32f103rcʵ���ҿ�����
  * �޸�ʱ�䣺2016.7 
  *-------------------------------------------------------------------------------------------------
  * ��    �飺PID�����㷨
  * ��    ��:    
  *************************************************************************************************/  
/* ��ֹ�ݹ�����Ķ���-----------------------------------------------------------------------------*/
#ifndef __PID_H_
#define __PID_H_

#ifdef __cplusplus
 extern "C" {
#endif 

/* ���� ------------------------------------------------------------------------------------------*/


/* �������� --------------------------------------------------------------------------------------*/

typedef struct _pid
{
	float SetValue;  				// �趨Ŀ�� Desired value
	float ActualValue; 			//ʵ��ֵ
	float err; 							//ƫ��ֵ
	float err_next; 				//��һ��ƫ��ֵ
	float err_last; 				//����ǰ��ƫ��ֵ
	float Kp,Ki,Kd; 				// ���� Proportional ���� Integral  ΢�� Derivative 
}My_PID;


struct PID {
        unsigned int SetPoint; // �趨Ŀ�� Desired Value
        unsigned int Proportion; // �������� Proportional Const
        unsigned int Integral; // ���ֳ��� Integral Const
        unsigned int Derivative; // ΢�ֳ��� Derivative Const
        unsigned int LastError; // Error[-1]
        unsigned int PrevError; // Error[-2]
        unsigned int SumError; // Sums of Errors
        };

/* ���ں�-----------------------------------------------------------------------------------------*/


/* ���ڱ���---------------------------------------------------------------------------------------*/




/*���ں���ģ��------------------------------------------------------------------------------------*/
float PID_increa(My_PID *pid);
float PID_decrea(My_PID *pid,float angle);
void PID_init(My_PID *pid);
unsigned int PIDCalc( struct PID *pp, unsigned int NextPoint );
void PIDInit (struct PID *pp);
#ifdef __cplusplus
}
#endif

#endif 

/*************************************************�ļ�����*******************************************/
