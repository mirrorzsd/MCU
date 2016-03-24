//#include <string.h>
#include <reg52.h>
#include "UART.h"

void Init_UART()
{
	SCON = 0x50;	//MODE1,接收使能
	TMOD = 0x20;    //Timer1,MODE2
	PCON = 0x00;	//单倍波特率
	IE = 0x00;		//关闭所有中断
	TH1 = (unsigned char)(256 - (XTAL / (32L * 12L * baudrate)));	
	TL1 = (unsigned char)(256 - (XTAL / (32L * 12L * baudrate)));
	TR1 = 1;
}

void Send_Str(unsigned char *str)
{	
	while(*str != '\0')
	{
		Send_Byte(*str);
		str++;	
	}
	
}

void Send_Byte(unsigned char dat)
{
	SBUF = dat;
	while(!TI);
	TI = 0;
}

unsigned char Recv_Byte()
{	
	SBUF = 0;
	while(!RI);
	RI = 0;
	return SBUF;	
}
/*从串口接收pc发送的位数随机的数据
//数据遗漏现象=>缓冲池？
//随机位数无法确定=>某种协议？
void Recv_Str(unsigned char *StrArray)
{
	unsigned char temp;
	Send_Str("waiting...");
	temp = Recv_Byte();
	while(temp)
	{		
		strcat(StrArray,&temp);
		Send_Str(StrArray);
		Send_Str("\n");
		temp = Recv_Byte();	
	}
	Send_Str("Got it！");
}
*/

//16字节缓冲池
/*
	unsigned char UARTRbuff[16] = {0};
	unsigned char *UARTRbuffp = UARTRbuff;
	if (RI)
    {
        RI = 0;
        *UARTRbuffp++ = SBUF;
        *UARTRbuffp = 0x00;
    }
*/

