#define LCD_DATA1 PORTD
#define ctrl1 PORTB
#define rs1 PINB4
#define rw1 PINB3
#define en1 PINB2
//#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void LCD_cmd1(unsigned char);
void LCD4_cmd1(unsigned char);
void LCD_init1();
void LCD4_init1();
void LCD_write1(unsigned char);
void LCD4_write1(unsigned char);
void LCD_write_string1(unsigned char*);
void LCD4_write_string1(unsigned char*);
void LCD_gotoxy1(int, int);
void LCD4_gotoxy1(int, int);
void LCD_clear1();
void LCD4_clear1();