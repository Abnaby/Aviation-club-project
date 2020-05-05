#include "UART.h"
unsigned char string[20], x, i = 0;
void UART_init() /* Initialize UART */
{
	UCSRB |= (1 << RXEN) | (1 << TXEN); /* Turn on transmission and reception */
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); /* Use 8-bit character sizes */
	UBRRL = BAUD_PRESCALE; /* Load lower 8-bits of the baud rate value */
	UBRRH = (BAUD_PRESCALE >> 8); /* Load upper 8-bits*/
	/*receive character*/
	LCD4_write_string1("UART initialized correctly");
	_delay_ms(50);
	LCD4_clear1();
}
unsigned char UART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0); /* Wait till data is received */
	return(UDR); /* Return the byte*/
}
void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));
	UDR = ch ;
}
void UART_TxString ( char *str) /*send string*/
{
	unsigned char j=0;
	while (str[j]!=0) /* Send string till null */
	{
		UART_TxChar( str[j]);
		j++;
	}
}

void rw_time_left(void){
	LCD4_gotoxy1(1,11);
	UART_TxString(">> Enter current time left in hours \n");
	//UART_TxChar();
	while(1){
		x = UART_RxChar();
		UART_TxChar(x);
		if (x!= 13 || x!=0x0D){
			string[i] = x ;
			i++ ;
			//LCD4_write(x);
		}
		else{
			string[i] = '\0';
			i=0 ;
			//LCD4_write_string("Done");
			break;
		}
	}
	LCD4_write_string1(string);
}
rw_current_time(){
		LCD4_gotoxy1(2,10);
		UART_TxString(">> Enter current time as XX:XX \n");
		//UART_TxChar();
		while(1){
			x = UART_RxChar();
			UART_TxChar(x);
			if (x!= 13 || x!=0x0D){
				string[i] = x ;
				i++ ;
				//LCD4_write(x);
			}
			else{
				string[i] = '\0';
				i=0 ;
				//LCD4_write_string("Done");
				break;
			}
		}
		LCD4_write_string1(string);

}
void rw_Distance_left(void){	
		LCD4_gotoxy1(2,10);
		UART_TxString(">> Enter Distance left till arrival: \n");
		//UART_TxChar();
		while(1){
			x = UART_RxChar();
			UART_TxChar(x);
			if (x!= 13 || x!=0x0D){
				string[i] = x ;
				i++ ;
				//LCD4_write(x);
			}
			else{
				string[i] = '\0';
				i=0 ;
				//LCD4_write_string("Done");
				break;
			}
		}
		LCD4_write_string1(string);
		
	}