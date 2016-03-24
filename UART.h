#ifndef __UART_H__
#define __UART_H__

#define XTAL 11059200
#define baudrate 9600

void Init_UART();						   //波特率9600
void Send_Byte(unsigned char dat);		   //串口发送一字节
void Send_Str(unsigned char *str);
unsigned char Recv_Byte();
//void Recv_Str(unsigned char *StrArray);  //【未完成】串口接收随机位数字符串
#endif