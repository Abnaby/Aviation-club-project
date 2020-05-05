/*******************************
******* Mohammad Khaled ********
**** AVR LCD 8-bit & 4-bit *****
*******************************/
#include "lcd.h"

void LCD_cmd1(unsigned char cmd)
{
	LCD_DATA1 = cmd;
	_delay_ms(1);
	ctrl1 = (0<<rs1)|(0<<rw1)|(1<<en1);
	_delay_ms(1);
	ctrl1 = (0<<rs1)|(0<<rw1)|(0<<en1);
	_delay_ms(10);
}

void LCD4_cmd1(unsigned char cmd)
{
	unsigned char value;
	value = (cmd & 0xf0);
	LCD_cmd1(value);
	_delay_ms(1);
	value = ((cmd<<4) & 0xf0);
	LCD_cmd1(value);
	_delay_ms(1);
}

void LCD_init1()
{
	LCD_cmd1(0x38);
	_delay_ms(1);
	LCD_cmd1(0x01);
	_delay_ms(1);
	LCD_cmd1(0x0E);
	_delay_ms(1);
	LCD_cmd1(0x80);
	_delay_ms(1);
}

void LCD4_init1()
{
	LCD4_cmd1(0x02);
	_delay_ms(1);
	LCD4_cmd1(0x28);
	_delay_ms(1);
	LCD4_cmd1(0x0c);
	_delay_ms(1);
	LCD4_cmd1(0x06);
	_delay_ms(1);
	LCD4_cmd1(0x80);
	_delay_ms(1);
	LCD4_write_string1("LCD1 initialized correctly");
	_delay_ms(50);
	LCD4_clear1();
}

void LCD_write1(unsigned char data)
{
	LCD_DATA1 = data;
	ctrl1 = (1<<rs1)|(0<<rw1)|(1<<en1);
	_delay_ms(1);
	ctrl1 = (1<<rs1)|(0<<rw1)|(0<<en1);
	_delay_ms(10);
}

void LCD4_write1(unsigned char data)
{
	unsigned char value;
	value = (data & 0xf0);
	LCD_write1(value);
	_delay_ms(1);
	value = ((data<<4) & 0xf0);
	LCD_write1(value);
	_delay_ms(1);
}

void LCD_write_string1(unsigned char *data)
{
	int n=0;
	while(data[n])
	{
		LCD_write1(data[n]);
		n++;
		if (n==16)
		{
			LCD_cmd1(0xC0);
		}
	}
}

void LCD4_write_string1(unsigned char *data)
{
	int n=0;
	while(data[n])
	{
		LCD4_write1(data[n]);
		n++;
		if (n==16)
		{
			LCD4_cmd1(0xC0);
		}
	}
}

void LCD_gotoxy1(int x, int y)
{
	if (x==1)
	{
		LCD_cmd1(0x80);
		for (int i=1;i<y;i++)
		{
			LCD_cmd1(0x06);
		}
	}
	if (x==2)
	{
		LCD_cmd1(0xC0);
		for (int i=1;i<y;i++)
		{
			LCD_cmd1(0x06);
		}
	}
}

void LCD4_gotoxy1(int x, int y)
{
	y--;
	if (x==1)
	{
		LCD4_cmd1(0x80+y);
	}
	if (x==2)
	{
		LCD4_cmd1(0xC0+y);
	}
}

void LCD_clear1()
{
	LCD_cmd1(0x01);
}

void LCD4_clear1()
{
	LCD4_cmd1(0x01);
}