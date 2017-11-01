/***************************************************************************************************
  * 文    件：PID.h   
  * 作    者：guojiang 
  * 开 发 板：stm32f103rc实验室开发板
  * 修改时间：2016.7 
  *-------------------------------------------------------------------------------------------------
  * 简    介：PID控制算法
  * 参    考:    
  *************************************************************************************************/  
/* 防止递归包含的定义-----------------------------------------------------------------------------*/
#ifndef __PID_H_
#define __PID_H_

#ifdef __cplusplus
 extern "C" {
#endif 

/* 包含 ------------------------------------------------------------------------------------------*/


/* 出口类型 --------------------------------------------------------------------------------------*/

typedef struct _pid
{
	float SetValue;  				// 设定目标 Desired value
	float ActualValue; 			//实际值
	float err; 							//偏差值
	float err_next; 				//上一个偏差值
	float err_last; 				//最上前的偏差值
	float Kp,Ki,Kd; 				// 比例 Proportional 积分 Integral  微分 Derivative 
}My_PID;


struct PID {
        unsigned int SetPoint; // 设定目标 Desired Value
        unsigned int Proportion; // 比例常数 Proportional Const
        unsigned int Integral; // 积分常数 Integral Const
        unsigned int Derivative; // 微分常数 Derivative Const
        unsigned int LastError; // Error[-1]
        unsigned int PrevError; // Error[-2]
        unsigned int SumError; // Sums of Errors
        };

/* 出口宏-----------------------------------------------------------------------------------------*/


/* 出口变量---------------------------------------------------------------------------------------*/




/*出口函数模型------------------------------------------------------------------------------------*/
float PID_increa(My_PID *pid);
float PID_decrea(My_PID *pid,float angle);
void PID_init(My_PID *pid);
unsigned int PIDCalc( struct PID *pp, unsigned int NextPoint );
void PIDInit (struct PID *pp);
#ifdef __cplusplus
}
#endif

#endif 

/*************************************************文件结束*******************************************/
