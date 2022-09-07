/*
 * Lab3-1.c
 *
 * Created: 3/12/2021 1:38:38 PM
 * Author : Nathan Baker
 */ 

// #include <avr/io.h>
// #include <avr/interrupt.h>
// #define F_CPU 16000000UL
// #include <util/delay.h>
// #include "UART.h"


// ISR(TIMER0_OVF_vect) {
// 	PORTD ^= (1<<PORTD6);
// }
// 
// ISR(TIMER0_COMPA_vect) {
// 	PORTD ^= (1<<PORTD6);
// }

// volatile int output = 1;
// 
// void Initialize() {
// 	cli();
// 	
// 	
// 	//TIMSK0 |= (1<<TOIE0); //Overflow interrupt enabled
// 
// 	
// 	DDRD |= (1<<DDD5); //Pin 5 (Timer 0) configured to output
// 	PORTD &= ~(1<<PORTD5);
// 	OCR0A = 17; //Output compare for A 34 (TOP)
// 	OCR0B = 9; //Toggle OCOB every time TCNT = 17
// 	TCCR0B = 0;
// 	TCCR0B |= (1<<CS00);
// 	TCCR0B |= (1<<CS02); //Clock precaled by 1024. (15,625Hz).
// 	
// 	
// 	
// 	TCCR0B |= (1<<WGM02); //Phase correct mode (WMG0 2:0 = 5)
// 	TCCR0A = 0;
// 	TCCR0A &= ~(1<<WGM01); //Phase correct mode (WMG0 2:0 = 5)
// 	TCCR0A |= (1<<COM0B1); //Clear OC0B on upcount match and clear on downcount match (non-inverted mode).
// 	TCCR0A |= (1<<WGM00); //Phase correct mode (WMG0 2:0 = 5)
// 	//TIFR0 |= (1<<TOV0); 
// 	_uartInit(9600);
// 	sei();
// 	
// }


// int main(void)
// {
//     /* Replace with your application code */
// 	
// 	Initialize();
//     while (1) {
// 		PORTD ^= (1<<PORTD4);
// 		_delay_us(10);
// 		PORTD ^= (1<<PORTD4);
// 		_delay_ms(10000);
// 	}
// }

