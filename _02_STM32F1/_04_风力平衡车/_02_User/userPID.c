#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "userPID.h"

PID Extern_pid_value;
PID my_pid_value;
float  PID_P=80, PID_I=0,PID_D= 0, my_PID_P=70, my_PID_I=0,my_PID_D =0;

void pidInit(void)
{
    Extern_pid_value.export_value = 0;
	Extern_pid_value.incrementspeed = 0.0;
    Extern_pid_value.err = 0.0;
    Extern_pid_value.err_last_0 = 0.0;
    Extern_pid_value.err_last_1 = 0.0;
    Extern_pid_value.integral = 0.0;
    Extern_pid_value.kp = PID_P;
    Extern_pid_value.ki = PID_I;
    Extern_pid_value.kd = PID_D;
	
	my_pid_value.export_value = 0;
	my_pid_value.incrementspeed = 0.0;
    my_pid_value.err = 0.0;
    my_pid_value.err_last_0 = 0.0;
    my_pid_value.err_last_1 = 0.0;
    my_pid_value.integral = 0.0;
    my_pid_value.kp = my_PID_P;
    my_pid_value.ki = my_PID_I;
    my_pid_value.kd = my_PID_D;
}


/*
Return Value:	PID���ں�����ֵ
Parameters:		Set_speed:�趨ֵ;
				Actual_speed:��ǰֵ;
Description:	������PID�����㷨
*/
float pidIncrement(float Set_value, float Actual_value)
{
	float pid_i_state = 1.0;

    Extern_pid_value.err = Set_value - Actual_value;

    /* ʵ�����ֵ����������ʹ�÷�Χ�����ֵ��ֻ�Ӹ���� */
    if((Extern_pid_value.export_value > PID_AMAX) && (Extern_pid_value.err > 0.0))
    {
		pid_i_state = 0.0;
    }
    /* ʵ�����ֵС��������ʹ�÷�Χ����Сֵ��ֻ������� */
    else if((Extern_pid_value.export_value < PID_AMIN) && (Extern_pid_value.err < 0.0))
    {
		pid_i_state = 0.0;
    }

	/* ���ֵ����С��������� */
	if(fabs(Extern_pid_value.err) > PID_EMAX)
		pid_i_state = 0.0;

    Extern_pid_value.incrementspeed = Extern_pid_value.kp * (Extern_pid_value.err - Extern_pid_value.err_last_0)
									+ Extern_pid_value.ki * pid_i_state * Extern_pid_value.err
									+ Extern_pid_value.kd * (Extern_pid_value.err - 2.0 * Extern_pid_value.err_last_0 + Extern_pid_value.err_last_1);

	Extern_pid_value.export_value += Extern_pid_value.incrementspeed;

    Extern_pid_value.err_last_1 = Extern_pid_value.err_last_0;

    Extern_pid_value.err_last_0 = Extern_pid_value.err;

    return Extern_pid_value.export_value;
}

/*
Return Value:	PID���ں�����ֵ
Parameters:		Set_speed:�趨ֵ;
				Actual_speed:��ǰֵ;
Description:	λ����PID�����㷨
*/
float pidLocation(float Set_value, float Actual_value)
{
	float pid_i_state = 1.0;

    Extern_pid_value.err = Set_value - Actual_value;

    /* ʵ�����ֵ����������ʹ�÷�Χ�����ֵ��ֻ�Ӹ���� */
    if((Extern_pid_value.export_value > PID_AMAX) && (Extern_pid_value.err < 0.0))
    {
        Extern_pid_value.integral += Extern_pid_value.err;
    }
    /* ʵ�����ֵС��������ʹ�÷�Χ����Сֵ��ֻ������� */
    else if((Extern_pid_value.export_value < PID_AMIN) && (Extern_pid_value.err > 0.0))
    {
        Extern_pid_value.integral += Extern_pid_value.err;
    }
    else if(fabs(Extern_pid_value.err) < PID_EMAX)
    {
        Extern_pid_value.integral += Extern_pid_value.err;
    }

    /* ���ֵ����С��������� */
    if(fabs(Extern_pid_value.err) > PID_EMAX)
        pid_i_state = 0.0;

    Extern_pid_value.export_value = Extern_pid_value.kp * Extern_pid_value.err
                                   +Extern_pid_value.ki * pid_i_state * Extern_pid_value.integral
                                   +Extern_pid_value.kd * (Extern_pid_value.err - Extern_pid_value.err_last_0);

    Extern_pid_value.err_last_0 = Extern_pid_value.err;

    return Extern_pid_value.export_value;
}



/*
Return Value:	PID���ں�����ֵ
Parameters:		Set_speed:�趨ֵ;
				Actual_speed:��ǰֵ;
Description:	������PID�����㷨
*/
float my_pidIncrement(float Set_value, float Actual_value)
{
	float pid_i_state = 1.0;

    my_pid_value.err = Set_value - Actual_value;

    /* ʵ�����ֵ����������ʹ�÷�Χ�����ֵ��ֻ�Ӹ���� */
    if((my_pid_value.export_value > PID_AMAX) && (my_pid_value.err > 0.0))
    {
		pid_i_state = 0.0;
    }
    /* ʵ�����ֵС��������ʹ�÷�Χ����Сֵ��ֻ������� */
    else if((my_pid_value.export_value < PID_AMIN) && (my_pid_value.err < 0.0))
    {
		pid_i_state = 0.0;
    }

	/* ���ֵ����С��������� */
	if(fabs(my_pid_value.err) > PID_EMAX)
		pid_i_state = 0.0;

    my_pid_value.incrementspeed = my_pid_value.kp * (my_pid_value.err - my_pid_value.err_last_0)
									+ my_pid_value.ki * pid_i_state * my_pid_value.err
									+ my_pid_value.kd * (my_pid_value.err - 2.0 * my_pid_value.err_last_0 + my_pid_value.err_last_1);

	my_pid_value.export_value += my_pid_value.incrementspeed;

    my_pid_value.err_last_1 = my_pid_value.err_last_0;

    my_pid_value.err_last_0 = my_pid_value.err;

    return my_pid_value.export_value;
}

/*
Return Value:	PID���ں�����ֵ
Parameters:		Set_speed:�趨ֵ;
				Actual_speed:��ǰֵ;
Description:	λ����PID�����㷨
*/
float my_pidLocation(float Set_value, float Actual_value)
{
	float pid_i_state = 1.0;

    my_pid_value.err = Set_value - Actual_value;

    /* ʵ�����ֵ����������ʹ�÷�Χ�����ֵ��ֻ�Ӹ���� */
    if((my_pid_value.export_value > PID_AMAX) && (my_pid_value.err < 0.0))
    {
        my_pid_value.integral += my_pid_value.err;
    }
    /* ʵ�����ֵС��������ʹ�÷�Χ����Сֵ��ֻ������� */
    else if((my_pid_value.export_value < PID_AMIN) && (my_pid_value.err > 0.0))
    {
        my_pid_value.integral += my_pid_value.err;
    }
    else if(fabs(my_pid_value.err) < PID_EMAX)
    {
        my_pid_value.integral += my_pid_value.err;
    }

    /* ���ֵ����С��������� */
    if(fabs(my_pid_value.err) > PID_EMAX)
        pid_i_state = 0.0;

    my_pid_value.export_value = my_pid_value.kp * my_pid_value.err
                                   +my_pid_value.ki * pid_i_state * my_pid_value.integral
                                   +my_pid_value.kd * (my_pid_value.err - my_pid_value.err_last_0);

    my_pid_value.err_last_0 = my_pid_value.err;

    return my_pid_value.export_value;
}


