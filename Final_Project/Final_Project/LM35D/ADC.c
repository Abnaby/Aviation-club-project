#include "ADC.h"
void init_ADC(void){
	ADMUX  |=(1<<REFS0); //AVCC with external capacitor at AREF pin
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2) ; //128 prescaler
	ADCSRA |= (1<<ADEN); //ADC Enable
	LCD4_gotoxy(1,1);
	LCD4_write_string("ADC initialized correctly");
	_delay_ms(50);
	LCD4_clear();

}
int ADC_read(){
	ADCSRA |= (1<< ADSC); // Start conversion if 1 conversion still running
	// wait for conversion to complete
	// ADSC becomes '0' again
	while(ADCSRA & (1<<ADSC));
	return ADC ;
}



