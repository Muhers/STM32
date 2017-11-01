/***************************************************************************************************
  * 文    件：PD.c
  * 作    者：guojiang 
  * 开 发 板：stm32f103rc实验室开发板
  * 修改时间：2016.7 
  *-------------------------------------------------------------------------------------------------
  * 简    介：PID计算
  * 参    考:    
  *************************************************************************************************/  
/* 防止递归包含的定义-----------------------------------------------------------------------------*/


/*包含--------------------------------------------------------------------------------------------*/
#include "PID.h"
#include "string.h"
/* 私有定义结构体 --------------------------------------------------------------------------------*/
/* 私有宏-----------------------------------------------------------------------------------------*/
/* 私有变量 --------------------------------------------------------------------------------------*/
/* 私有函数模型 ----------------------------------------------------------------------------------*/
struct PID spid; // PID Control Structure
/***************************************************************************************************
  * 描述   : PID控制结构体数据初始化
  * 参数   : *PP: PID控制数据指针
  * 返回   : 无
  * 注意   :
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
  * 描述   : PID控制算法增量式
  * 参数   : *PP: PID控制数据指针 ActualVaule: 当前测量值
  * 返回   : 
  * 注意   :
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
/////*************************************************文件结束*******************************************/

unsigned int PIDCalc( struct PID *pp, unsigned int NextPoint ) 
{
        int dError,Error;
        Error = pp->SetPoint - NextPoint;          // 偏差  
        if(Error<0)	Error = -Error;
        pp->SumError += Error;                     // 积分                                   
        dError = pp->LastError - pp->PrevError;    // 当前微分  
        pp->PrevError = pp->LastError;                           
        pp->LastError = Error;                                        
        return (pp->Proportion * Error             // 比例项           
        + pp->Integral * pp->SumError              // 积分项
        + pp->Derivative * dError);                // 微分项
}
void PIDInit (struct PID *pp)
{
	     pp->SumError= 0; 
       pp->LastError= 0; //Error[-1] 
       pp->PrevError= 0; //Error[-2] 0
       pp->Proportion= 20; //比例常数Proportional Const 
       pp->Integral= 10; //积分常数IntegralConst 
       pp->Derivative= 0; //微分常数Derivative Const 
       pp->SetPoint= 1; 
}
