#include <stdio.h>
#include "UART.h"
#include "Kalman.h"

unsigned char xdata log[10];

float xdata ts = 0.015;         //滤波器采样频率(ms)
float xdata q_acc = 0.01;       //加速度计协方差->信任程度
float xdata q_gyro = 0.005;      //陀螺仪协方差->信任程度
int uk = 0;          //U(k)为现在状态的控制量，如果没有控制量，它可以为0。
int zk;          //Z(k)为k时刻的测量值，即new_angle
float xdata r_acc = 0.056;       //测量误差的协方差矩阵
float temp;

float idata a[2][2]; //因为只有一个输入量，所以a取a[0][0],b取b[0]
float xdata b[2];
float xdata q[2][2];
float xdata h[2] = {0,1};
float xdata k[2] = {0,0};     //卡尔曼增益 
float xdata p[2][2] = {{0,0},{0,0}};

float KalmanTest(float new_angle,float new_gyro,float Angle)
{
	//初始化
	a[0][0] = 1; //因为只有一个输入量，所以a取a[0][0],b取b[0]
	b[0] = ts;
	p[0][0] = q_acc;
	p[0][1] = 0;
	p[1][0] = 0;
	p[1][1] = q_gyro;

	//先验估计
	Angle = Angle + ts * new_gyro;

	//先验估计的协方差
	p[0][0] -= ts * (p[1][0] + p[0][1]); 
	p[0][1] -= ts * p[1][1];
	p[1][0] -= ts * p[1][1];
	p[1][1] = p[1][1];

	//卡尔曼增益
	temp = p[0][0] + r_acc;
	k[0] = p[0][0] / temp;
	k[1] = p[1][0] / temp;

	//k时刻的最优值
	Angle += k[0] * (new_angle - Angle);
	//Gyro = Gyro + k[1] * (new_angle - Angle);

	//更新k状态下的协方差
	p[0][0] -= k[0] * p[0][0];
	p[0][1] -= k[0] * p[0][1];
	p[1][0] -= k[1] * p[0][0];
	p[1][1] -= k[1] * p[0][1];
	return Angle;
} 

/*
float code Q_angle=0.01;//0.001;  
float code Q_gyro=0.005;
float code R_angle=0.056;//0.5;
float code ts=0.02;	                  //dt为kalman滤波器采样时间;
char  code C_0 = 1;
float xdata Q_bias=0;
float xdata Angle_err;
float xdata PCt_0, PCt_1, E;
float xdata K_0, K_1, t_0, t_1;
float xdata Pdot[4] ={0,0,0,0};
float xdata PP[2][2] = { { 1, 0 },{ 0, 1 } };
//*********************************************************
// 卡尔曼滤波
//*********************************************************
//Q:过程噪声，Q增大，动态响应变快，收敛稳定性变坏
//R:测量噪声，R增大，动态响应变慢，收敛稳定性变好
void Kalman_Filter(float Angle_a,float Gyro,float *Angle_out)		
{	
	
	*Angle_out+=(Gyro - Q_bias) * ts; //先验估计

	sprintf(log,"a1=%.2f\n",*Angle_out);
	Send_Str(log);

	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
	Pdot[1]=- PP[1][1];
	Pdot[2]=- PP[1][1];
	Pdot[3]=Q_gyro;
	PP[0][0] += Pdot[0] * ts;   // Pk-先验估计误差协方差微分的积分
	PP[0][1] += Pdot[1] * ts;   // =先验估计误差协方差
	PP[1][0] += Pdot[2] * ts;
	PP[1][1] += Pdot[3] * ts;

	sprintf(log,"p%.4f,%.4f,%.4f,%.4f\n",PP[0][0],PP[0][1],PP[1][0],PP[1][1]);
	Send_Str(log);

	Angle_err = Angle_a - *Angle_out;	//zk-先验估计
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	E = R_angle + C_0 * PCt_0;
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	sprintf(log,"%.2f,%.2f\n",K_0,K_1);
	Send_Str(log);
		
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];
	PP[0][0] -= K_0 * t_0;		 //后验估计误差协方差
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;		
	*Angle_out += K_0 * Angle_err;	 //后验估计

	sprintf(log,"%.2f\n",*Angle_out);
	Send_Str(log);

	Q_bias += K_1 * Angle_err;	 //后验估计
	//Gyro_y   = Gyro - Q_bias;	 //输出值(后验估计)的微分=角速度
}
*/
