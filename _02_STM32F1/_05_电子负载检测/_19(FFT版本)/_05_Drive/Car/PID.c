/***************************************************************************************************
  * ��    ����PD.c
  * ��    �ߣ�guojiang 
  * �� �� �壺stm32f103rcʵ���ҿ�����
  * �޸�ʱ�䣺2016.7 
  *-------------------------------------------------------------------------------------------------
  * ��    �飺PID����
  * ��    ��:    
  *************************************************************************************************/  
/* ��ֹ�ݹ�����Ķ���-----------------------------------------------------------------------------*/


/*����--------------------------------------------------------------------------------------------*/
#include "PID.h"
#include "string.h"
/* ˽�ж���ṹ�� --------------------------------------------------------------------------------*/
/* ˽�к�-----------------------------------------------------------------------------------------*/
/* ˽�б��� --------------------------------------------------------------------------------------*/
/* ˽�к���ģ�� ----------------------------------------------------------------------------------*/
struct PID spid; // PID Control Structure
/***************************************************************************************************
  * ����   : PID���ƽṹ�����ݳ�ʼ��
  * ����   : *PP: PID��������ָ��
  * ����   : ��
  * ע��   :
  *************************************************************************************************/
void PID_init(My_PID *pid)
{
	pid->SetValue=1.0;
	pid->ActualValue=0.0;
	pid->err=0.0;
	pid->err_last=0.0;
	pid->err_next=0.0;
	pid->Kp=2;					    //3
	pid->Ki=1;						  //1
	pid->Kd=0;						  //0.5
}


/***************************************************************************************************
  * ����   : PID�����㷨����ʽ
  * ����   : *PP: PID��������ָ�� ActualVaule: ��ǰ����ֵ
  * ����   : 
  * ע��   :
  *************************************************************************************************/

float PID_increa(My_PID *pid)
{
		float incrementValue;
//		pid->SetValue=setValue;
		pid->err=pid->SetValue-pid->ActualValue;
		if(pid->err<0) pid->err=-pid->err;
	
		incrementValue=pid->Kp*(pid->err-pid->err_next)+pid->Ki*pid->err+pid->Kd*(pid->err-2*pid->err_next+pid->err_last);
	  pid->ActualValue+=incrementValue;
		pid->err_last=pid->err_next;
		pid->err_next=pid->err;
		return incrementValue;
}
/////*************************************************�ļ�����*******************************************/

unsigned int PIDCalc( struct PID *pp, unsigned int NextPoint ) 
{
        int dError,Error;
        Error = pp->SetPoint - NextPoint;          // ƫ��  
        if(Error<0)	Error = -Error;
        pp->SumError += Error;                     // ����                                   
        dError = pp->LastError - pp->PrevError;    // ��ǰ΢��  
        pp->PrevError = pp->LastError;                           
        pp->LastError = Error;                                        
        return (pp->Proportion * Error             // ������           
        + pp->Integral * pp->SumError              // ������
        + pp->Derivative * dError);                // ΢����
}
void PIDInit (struct PID *pp)
{
	     pp->SumError= 0; 
       pp->LastError= 0; //Error[-1] 
       pp->PrevError= 0; //Error[-2] 0
       pp->Proportion= 20; //��������Proportional Const 
       pp->Integral= 10; //���ֳ���IntegralConst 
       pp->Derivative= 0; //΢�ֳ���Derivative Const 
       pp->SetPoint= 1; 
}
