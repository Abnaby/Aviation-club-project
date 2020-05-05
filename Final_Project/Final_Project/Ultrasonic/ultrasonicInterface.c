#include "ultrasonicInterface.h"
void interrupt_init(void){
	//PORTD = 0b11111011 ;
	MCUCR |= (1<<ISC00);	  //Any logical change on INT0 generates an interrupt request
	GICR |= (1<<INT0);
	sei();
	LCD4_gotoxy(1,1);
	LCD4_write_string("Interrupt initialized correctly");
	_delay_ms(200);
	LCD4_clear();
}
void timer0_init(void){
	//Timer 0 will work in normal mode
	/************************************************************************/
	/*                      Timer0 is 8bit timer 0 --> 255 and overflow     */
	/************************************************************************/
	TCCR0 |= (1<<CS00);
	TCNT0 = 0 ;
	TIMSK |=(1<<TOIE0);
	
}
void trigger(void){
		trigDir &= ~(1<<trigPin);
		_delay_us(10);
		trigDir |= (1<<trigPin);
		_delay_us(10);
		trigDir &= ~(1<<trigPin);
				//LCD4_write_string("trig");

}
