#ifndef __1602_H__
#define __1602_H__
#include <reg52.h>
#define DataPin P0

sbit LCDEn = P2^7;
sbit LCDRs = P2^6;
sbit LCDRw = P2^5;

void LCD_write_com(unsigned char com);
void LCD_write_data(unsigned char dat);
void Init_LCD();
void LCD_Delay1ms(unsigned int time);

#endif