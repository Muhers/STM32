#ifndef USER_PID_H_INCLUDED
#define USER_PID_H_INCLUDED

#define PID_P       125             //Pϵ��
#define PID_I       1.5            //Iϵ��
#define PID_D       1.0           //Dϵ��
#define PID_EMAX    30.0            //ERROR�������
#define PID_AMAX    400.0          //EXPORT�������
#define PID_AMIN    -400.0           //EXPORT�������

typedef struct{
    float export_value; 	//���ֵ
	  float incrementspeed;   //����ֵ
    float integral;     	//����ֵ
    float err;          	//ƫ��ֵ
    float err_last_0;   	//��һ��ƫ��ֵ
    float err_last_1;   	//���ϸ�ƫ��ֵ
    float kp,ki,kd;     	//���������֡�΢��ϵ��
}PID;

void pidInit(void);

float pidIncrement(float Set_value, float Actual_value, float gyro_x);

float pidLocation(float Set_value, float Actual_value);


#endif // PID_H_INCLUDED
