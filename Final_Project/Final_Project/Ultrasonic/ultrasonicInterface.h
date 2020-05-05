#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#define F_CPU 1000000UL
#define trigDir DDRA
#define trigPin PA3
#define EchoDir DDRD
#define EchoPin PIND2
void trigger(void);
void interrupt_init(void);
