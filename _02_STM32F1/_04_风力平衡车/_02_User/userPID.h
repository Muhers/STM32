#ifndef USER_PID_H_INCLUDED
#define USER_PID_H_INCLUDED
#include "User_Library.h"  
extern float  PID_P,PID_I ,PID_D, my_PID_P, my_PID_I,my_PID_D;
 

#define PID_EMAX    30.0            //ERROR误差上限
#define PID_AMAX    400.0          //EXPORT输出上限
#define PID_AMIN   -400.0         //EXPORT输出下限


#define my_PID_EMAX    30.0         //ERROR误差上限
#define my_PID_AMAX    400.0       //EXPORT输出上限
#define my_PID_AMIN    -400.0     //EXPORT输出下限

typedef struct{
    float export_value; 	    //输出值
	  float incrementspeed;    //增量值
    float integral;     	  //积分值
    float err;          	 //偏差值
    float err_last_0;   	//上一个偏差值
    float err_last_1;    //上上个偏差值
    float kp,ki,kd;     //比例、积分、微分系数
}PID;

extern PID Extern_pid_value; 
void pidInit(void);

float pidIncrement(float Set_value, float Actual_value);
float pidLocation(float Set_value, float Actual_value);

float my_pidIncrement(float Set_value, float Actual_value);
float my_pidLocation(float Set_value, float Actual_value);

#endif // PID_H_INCLUDED
