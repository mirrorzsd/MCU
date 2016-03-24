#ifndef __KALMAN_H__
#define __KALMAN_H__



void Kalman_Filter(float Angle_a,float Gyro,float *Angle_out);
float KalmanTest(float new_angle,float new_gyro,float Angle);
#endif