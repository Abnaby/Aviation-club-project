/*
 * Final_Project.c
 *
 * Created: 4/28/2020 3:19:00 PM
 * Author : Mohamed Abd El-Naby
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "LCD/lcd.h"
#include "LCD/lcd_lib.h"
#include "LM35D/ADC.h"
#include "Ultrasonic/ultrasonicInterface.h"
#include "UART/UART.h"
char c[100] ;
uint8_t logichange =0 ;
uint16_t tcnt =0 ;
uint8_t digit_no(uint8_t num);
void print_checker(uint8_t value);
int main(void)
{
	/************************************************************************/
	/* FOR LCD :
				DDRC = 0xFF;         LCD 0                                               
				DDRD = (1<<PD7)|(1<<PD6)|(1<<PD5)|(1<<PD4) LCD1                  
				DDRB = 0xFF;         LCD 0 LCD 1 (RS ,RW,EN) 
				LCD4_init()-LCD4_init1() : 4 Bit mode                       */
	/************************************************************************/
	DDRC = 0xFF;
	DDRB = 0xFF;
	DDRD = (1<<PD7)|(1<<PD6)|(1<<PD5)|(1<<PD4) ;
	LCD4_init();
	LCD4_init1();
	/************************************************************************/
	/* FOR LM35D :
			initialize ADC0.
			Read from ADC
			Make array of character (c) for LCD
			itoa int to string                                               */
	/************************************************************************/
	init_ADC();
	/************************************************************************/
	/* FOR UART                                                            */
	/************************************************************************/
	UART_init();
	/************************************************************************/
	/* FOR ultrasonic :
			initialize INT0.
			initialize TIMER0.
			TIMER1 will be enabled in ISR
			Read from TCNT1.                                                */
	/************************************************************************/
	//DDRD = 0b11111011;
	DDRD &=~(1<<PD2);
	DDRA |= (1<<PA3);
	// Labels :
	interrupt_init();
	LCD4_gotoxy(1,1);
	LCD4_write_string("Ultrasonic:");
	LCD4_gotoxy(2, 1);
	LCD4_write_string("Temp in celi:");
	LCD4_gotoxy1(1,1);
	LCD4_write_string1("Time left: ");
	LCD4_gotoxy1(2, 1);
	LCD4_write_string1("time now:");
	//TIME LEFT
	rw_time_left();
	//CURRENT TIME
	rw_current_time();
	while (1) 
    {
	/************************************************************************/
						//for 10 us 
	//					________
	//	     10 us     |		|
	/*    Low	   ____|        |____________                               */
	/************************************************************************/
		//ultrasonic
		trigger();
		_delay_us(10);
		LCD4_gotoxy(1,12);
		print_checker ((uint8_t)(tcnt/466.47));
		//ADC
		LCD4_gotoxy(2,14);
		print_checker (ADC_read()/2);
	
	}
}
uint8_t digit_no(uint8_t num){
   uint8_t count = 0;
   /* Run loop till num is greater than 0 */
   do
   {
	   // Increment digit count 
	   count++;
	   // Remove last digit of 'num'
	   num /= 10;
   } while(num != 0);
   return count ;
}
void print_checker(uint8_t value){
		if (digit_no(value) >=3)
		LCD4_write_string(itoa(value,c,10));
		else{
			LCD4_write_string(itoa(value,c,10));
			LCD4_write_string(" ");
			LCD4_write_string(" ");
		}
}
/************************************************************************/
/* Ultrasonic logic change interrupt
	enable timer 0 to start counting                                    */
/************************************************************************/
ISR(INT0_vect)
{
	/************************************************************************/
	/* 0 to 1  from low to high
	   1 to 0  from high to low                                             */
	/************************************************************************/
	DDRB |= (1<<PB0);
	PORTB ^= (1<<PB0);
	if(logichange == 1) //1 mean rising edge
	{
		
		TCCR1B = 0;
		tcnt = TCNT1; 
		TCNT1 = 0;
		logichange = 0;
	}
	else if(logichange==0) //0 mean falling edge
	{
		TCCR1B |= 1<<CS10; // Start counting in timer1
		logichange = 1;
	}
}