#include <reg52.h>
#include "mpu6050_module.h"
#include "IIC.h"
#include "Kalman.h"
#include "UART.h"
 

/*
//float xdata Angle_x;
//float xdata Angle_y;
//float xdata Angle_z;
float xdata Angle_ax;
float xdata Angle_ay;
float xdata Angle_az;
float xdata Angle_outx = 0;
float xdata Angle_outy = 0;
float xdata Angle_outz = 0;
float xdata Angle_gx;
float xdata Angle_gy;
float xdata Angle_gz;
float xdata Qgx = 0;
float xdata Qgy = 0;
float xdata Qgz = 0;
float xdata Qax = 0;
float xdata Qay = 0;
float xdata Qaz = 0;
*/



void Init_mpu6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);	
}

float Get_Data(unsigned char REG_Address)  //输入IIC地址，输出数据（加速度，角速度）
{
	unsigned int H;
	unsigned char L;
	H = Single_ReadI2C(REG_Address);
	L = Single_ReadI2C(REG_Address+1);
	return (H<<8)+L;
}

float Accel_To_Angle(unsigned char REG_Address,float Q)   //输入IIC地址和零点误差，输出计算后的角度值
{
	float Angle,Accel;
	Accel = Get_Data(REG_Address);
	Angle = (Accel - Q) /16384;   //计算角度（弧度）
	Angle = Angle*1.54*180/3.14;  //换算成角度
	if(Angle > 100)
	{
		Angle -= 360;
	}
	return Angle;
}

float Gyro_To_Angle(unsigned char REG_Address,float Q)
{
	float Gyro;
	Gyro = Get_Data(REG_Address);	     
	Gyro = -(Gyro-Q)/16.4*0.01;         //去除零点偏移，积分计算角速度值,负号为方向处理
	//Angle_g = Angle_a + Gyro*0.01 - Q;
	return Gyro;
}

/*
void Angle_Calcu(float Angles[]) //输入数组，输出Angles[0]，Angles[1]，Angles[2]对应Ax,Ay,Az	 
{
	Angle_ax = Accel_To_Angle(ACCEL_XOUT_H,Qax);	 //弧度转换为角度，1.2为适当放大
	Angle_ay = Accel_To_Angle(ACCEL_YOUT_H,Qay);
	Angle_az = Accel_To_Angle(ACCEL_ZOUT_H,Qaz);
	Angle_gx = Gyro_To_Angle(GYRO_XOUT_H,Qgx);
	Angle_gy = Gyro_To_Angle(GYRO_YOUT_H,Qgy);
	Angle_gz = Gyro_To_Angle(GYRO_ZOUT_H,Qgz);
	Kalman_Filter(Angle_ax,Angle_gy,&Angle_outx);
	Kalman_Filter(Angle_ay,Angle_gz,&Angle_outy);
	Kalman_Filter(Angle_az,Angle_gx,&Angle_outz);
	Angles[0] = Angle_outx;
	Angles[1] = Angle_outy;
	Angles[2] = Angle_outz;
} */



