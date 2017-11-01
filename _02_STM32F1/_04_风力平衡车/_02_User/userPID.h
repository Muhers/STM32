#ifndef USER_PID_H_INCLUDED
#define USER_PID_H_INCLUDED
#include "User_Library.h"  
extern float  PID_P,PID_I ,PID_D, my_PID_P, my_PID_I,my_PID_D;
 

#define PID_EMAX    30.0            //ERROR�������
#define PID_AMAX    400.0          //EXPORT�������
#define PID_AMIN   -400.0         //EXPORT�������


#define my_PID_EMAX    30.0         //ERROR�������
#define my_PID_AMAX    400.0       //EXPORT�������
#define my_PID_AMIN    -400.0     //EXPORT�������

typedef struct{
    float export_value; 	    //���ֵ
	  float incrementspeed;    //����ֵ
    float integral;     	  //����ֵ
    float err;          	 //ƫ��ֵ
    float err_last_0;   	//��һ��ƫ��ֵ
    float err_last_1;    //���ϸ�ƫ��ֵ
    float kp,ki,kd;     //���������֡�΢��ϵ��
}PID;

extern PID Extern_pid_value; 
void pidInit(void);

float pidIncrement(float Set_value, float Actual_value);
float pidLocation(float Set_value, float Actual_value);

float my_pidIncrement(float Set_value, float Actual_value);
float my_pidLocation(float Set_value, float Actual_value);

#endif // PID_H_INCLUDED
