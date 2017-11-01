#ifndef USER_PID_H_INCLUDED
#define USER_PID_H_INCLUDED

#define PID_P       125             //P系数
#define PID_I       1.5            //I系数
#define PID_D       1.0           //D系数
#define PID_EMAX    30.0            //ERROR误差上限
#define PID_AMAX    400.0          //EXPORT输出上限
#define PID_AMIN    -400.0           //EXPORT输出下限

typedef struct{
    float export_value; 	//输出值
	  float incrementspeed;   //增量值
    float integral;     	//积分值
    float err;          	//偏差值
    float err_last_0;   	//上一个偏差值
    float err_last_1;   	//上上个偏差值
    float kp,ki,kd;     	//比例、积分、微分系数
}PID;

void pidInit(void);

float pidIncrement(float Set_value, float Actual_value, float gyro_x);

float pidLocation(float Set_value, float Actual_value);


#endif // PID_H_INCLUDED
