
#include "Drive_MPU6050.h"
#include "MPU6050.h" 

float Roll, Yaw,Angle_Balance,Gyro_Balance,Gyro_Turn,Yaw_Balance;
float Acceleration_Z;                       //Z轴加速度计
/**************************************************************************
函数功能：获取角度 三种算法
入口参数：获取角度的算法 1：DMP  2：卡尔曼 3：互补滤波
返回  值：无
**************************************************************************/
void Get_Angle(u8 Way_Angle)
{ 
	    float Accel_Y,Accel_Angle,Accel_Z,Gyro_X,Gyro_Z;
////			Gyro_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //读取Y轴陀螺仪
////			Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //读取Z轴陀螺仪
////       
////		  if(Gyro_X>32768)  Gyro_X-=65536;                       //数据类型转换  也可通过short强制类型转换
////			if(Gyro_Z>32768)  Gyro_Z-=65536;                       //数据类型转换
////      Gyro_Balance=Gyro_X;                                  //更新平衡角速度---------------------------
////	   	Read_DMP();                      //===读取加速度、角速度、倾角
////		  Angle_Balance=-Roll;             //===更新平衡倾角************
////			Yaw_Balance=-Yaw;                                  //****************
////		  Gyro_X=Gyro_X/16.4;     				               //陀螺仪量程转换	
//// 	  	Kalman_Filter(Angle_Balance,Gyro_X);                   //卡尔曼滤波	
//////	    Angle_Balance=angle;                                   //更新平衡倾角-----------------
////        Gyro_Turn=Gyro_Z;                                      //更新转向角速度------------------
////        Acceleration_Z=Accel_Z;                                //===更新Z轴加速度计	-----------------

	    if(Way_Angle==1)                           //===DMP的读取在数据采集中断读取，严格遵循时序要求
			{	
					Read_DMP();                      //===读取加速度、角速度、倾角
					Angle_Balance=-Roll;             //===更新平衡倾角
					Gyro_Balance=-gyro[0];           //===更新平衡角速度
					Gyro_Turn=gyro[2];               //===更新转向角速度
				    Acceleration_Z=accel[2];           //===更新Z轴加速度计
			}			
      else
      {
	      Gyro_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //读取Y轴陀螺仪
		  Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //读取Z轴陀螺仪
		  Accel_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //读取X轴加速度计
	  	  Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //读取Z轴加速度计
		  if(Gyro_X>32768)  Gyro_X-=65536;                       //数据类型转换  也可通过short强制类型转换
		  if(Gyro_Z>32768)  Gyro_Z-=65536;                       //数据类型转换
	  	  if(Accel_Y>32768) Accel_Y-=65536;                      //数据类型转换
		  if(Accel_Z>32768) Accel_Z-=65536;                      //数据类型转换
		  Gyro_Balance=Gyro_X;                                  //更新平衡角速度
	   	  Accel_Angle=atan2(Accel_Y,Accel_Z)*180/PI;                 //计算倾角	
		  Gyro_X=Gyro_X/16.4;                                    //陀螺仪量程转换	
          if(Way_Angle==2)		  	
          Kalman_Filter(Accel_Angle,Gyro_X);//卡尔曼滤波	
		  else if(Way_Angle==3)  
          Yijielvbo(Accel_Angle,Gyro_X);    //互补滤波
	      Angle_Balance=angle;                                   //更新平衡倾角
		  Gyro_Turn=Gyro_Z;                                      //更新转向角速度
		  Acceleration_Z=Accel_Z;                                //===更新Z轴加速度计	
		}

}
/**********************/

