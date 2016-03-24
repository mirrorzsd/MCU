#include <reg52.h>
#include <intrins.h>
#include "IIC.h"
#include "MPU6050_module.h"



void I2C_Start()
{
	SDA = 1;
	SCL = 1;
	Delay5us();
	SDA = 0;
	Delay5us();
	SCL = 0;
}

void I2C_Stop()
{
	SDA = 0;
	SCL = 1;
	Delay5us();
	SDA = 1;
	Delay5us();
}

void Delay5us()
{
	_nop_();
	_nop_();
}

void I2C_SendACK(bit ack)
{
	SDA = ack;
	SCL = 1;
	Delay5us();
	SCL = 0;
	Delay5us();	
}

bit I2C_RecvACK()
{
	SCL = 1;
	Delay5us();
	CY = SDA;
	SCL = 0;
	Delay5us();
	return CY;
}

void I2C_SendByte(unsigned char dat)
{
	unsigned char i;
	for(i=0; i<8; i++)
	{
 		dat <<= 1;
		SDA = CY;
		SCL = 1;
		Delay5us();
		SCL = 0;
		Delay5us();
	}
	I2C_RecvACK();
}
unsigned char I2C_RecvByte()
{
	unsigned char i;
	unsigned char dat = 0;
	SDA = 1;
	for(i=0; i<8; i++)
	{
		dat <<= 1;
		SCL = 1;
		Delay5us();
		dat |= SDA;
		SCL = 0;
		Delay5us();
	}
	return dat;
}

void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
{
    I2C_Start();                  //起始信号
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号
    I2C_SendByte(REG_Address);    //内部寄存器地址，
    I2C_SendByte(REG_data);       //内部寄存器数据，
    I2C_Stop();                   //发送停止信号
}

unsigned char Single_ReadI2C(unsigned char REG_Address)
{
	unsigned char REG_data;
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress);    //发送设备地址+写信号
	I2C_SendByte(REG_Address);     //发送存储单元地址，从0开始
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress+1);  //发送设备地址+读信号
	REG_data=I2C_RecvByte();       //读出寄存器数据
	I2C_SendACK(1);                //接收应答信号
	I2C_Stop();                    //停止信号
	return REG_data;
}