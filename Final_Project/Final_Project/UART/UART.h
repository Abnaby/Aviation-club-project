
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL /* Define frequency here its 8MHz */
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void UART_init();
unsigned char UART_RxChar();
void UART_TxChar(char ch);
void UART_TxString( char *str) ;
void rw_time_left(void);
void rw_current_time(void);
void rw_Distance_left(void);