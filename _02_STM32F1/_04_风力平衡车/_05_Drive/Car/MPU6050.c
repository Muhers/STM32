
#include "Drive_MPU6050.h"
#include "MPU6050.h" 

float Roll, Yaw,Angle_Balance,Gyro_Balance,Gyro_Turn,Yaw_Balance;
float Acceleration_Z;                       //Z����ٶȼ�
/**************************************************************************
�������ܣ���ȡ�Ƕ� �����㷨
��ڲ�������ȡ�Ƕȵ��㷨 1��DMP  2�������� 3�������˲�
����  ֵ����
**************************************************************************/
void Get_Angle(u8 Way_Angle)
{ 
	    float Accel_Y,Accel_Angle,Accel_Z,Gyro_X,Gyro_Z;
////			Gyro_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //��ȡY��������
////			Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //��ȡZ��������
////       
////		  if(Gyro_X>32768)  Gyro_X-=65536;                       //��������ת��  Ҳ��ͨ��shortǿ������ת��
////			if(Gyro_Z>32768)  Gyro_Z-=65536;                       //��������ת��
////      Gyro_Balance=Gyro_X;                                  //����ƽ����ٶ�---------------------------
////	   	Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
////		  Angle_Balance=-Roll;             //===����ƽ�����************
////			Yaw_Balance=-Yaw;                                  //****************
////		  Gyro_X=Gyro_X/16.4;     				               //����������ת��	
//// 	  	Kalman_Filter(Angle_Balance,Gyro_X);                   //�������˲�	
//////	    Angle_Balance=angle;                                   //����ƽ�����-----------------
////        Gyro_Turn=Gyro_Z;                                      //����ת����ٶ�------------------
////        Acceleration_Z=Accel_Z;                                //===����Z����ٶȼ�	-----------------

	    if(Way_Angle==1)                           //===DMP�Ķ�ȡ�����ݲɼ��ж϶�ȡ���ϸ���ѭʱ��Ҫ��
			{	
					Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
					Angle_Balance=-Roll;             //===����ƽ�����
					Gyro_Balance=-gyro[0];           //===����ƽ����ٶ�
					Gyro_Turn=gyro[2];               //===����ת����ٶ�
				    Acceleration_Z=accel[2];           //===����Z����ٶȼ�
			}			
      else
      {
	      Gyro_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //��ȡY��������
		  Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //��ȡZ��������
		  Accel_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //��ȡX����ٶȼ�
	  	  Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //��ȡZ����ٶȼ�
		  if(Gyro_X>32768)  Gyro_X-=65536;                       //��������ת��  Ҳ��ͨ��shortǿ������ת��
		  if(Gyro_Z>32768)  Gyro_Z-=65536;                       //��������ת��
	  	  if(Accel_Y>32768) Accel_Y-=65536;                      //��������ת��
		  if(Accel_Z>32768) Accel_Z-=65536;                      //��������ת��
		  Gyro_Balance=Gyro_X;                                  //����ƽ����ٶ�
	   	  Accel_Angle=atan2(Accel_Y,Accel_Z)*180/PI;                 //�������	
		  Gyro_X=Gyro_X/16.4;                                    //����������ת��	
          if(Way_Angle==2)		  	
          Kalman_Filter(Accel_Angle,Gyro_X);//�������˲�	
		  else if(Way_Angle==3)  
          Yijielvbo(Accel_Angle,Gyro_X);    //�����˲�
	      Angle_Balance=angle;                                   //����ƽ�����
		  Gyro_Turn=Gyro_Z;                                      //����ת����ٶ�
		  Acceleration_Z=Accel_Z;                                //===����Z����ٶȼ�	
		}

}
/**********************/

