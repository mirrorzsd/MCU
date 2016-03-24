#include "HB_Filter.h"



float dt=0.01; 						//采样周期
float tau = 0.1;					//时间常数，（自己确定的）
#define a (tau/(tau+dt))	//滤波器系数

float HB_Filter(float gyro, float acc, float angle)
{
	angle = a*(angle+gyro*dt) + (1-a)*acc;
	return angle;
}


