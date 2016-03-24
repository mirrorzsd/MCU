#ifndef __IIC_H__
#define __IIC_H__

#include "main.h"

sbit    SCL=P1^1;			//IIC时钟引脚定义
sbit    SDA=P1^0;			//IIC数据引脚定义

void Delay5us();
void I2C_Start();						   
void I2C_Stop();
void I2C_SendACK(bit ack);				   
bit I2C_RecvACK();
void I2C_SendByte(unsigned char dat);		//IIC发送1字节
unsigned char I2C_RecvByte();				//IIC接收1字节
void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data);	 //通过IIC向内部地址写入
unsigned char Single_ReadI2C(unsigned char REG_Address);

#endif