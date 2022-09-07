#include <avr/io.h>
#include "uart.h"
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 16000000UL
/*#define BAUD_RATE 9600*/
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)
// #define DOT_LOWER 480000
#define DASH_LOWER 3200000UL
#define DASH_UPPER 6400000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

unsigned long volatile int overflows = 0;
unsigned long volatile int edge = 0;


char str[25]; //String to be printed

ISR(TIMER1_CAPT_vect){
// 	int rising = TCCR1B & (1<<ICES1); //Used to check whether the input capture was a falling or rising edge
	unsigned long int current = ICR1 + (overflows * 65535); //Current time of edge computed using overflow numbers (incremented during overflow ISR)
	unsigned long int duration = current - edge; //Time based subtraction
	
	
//  edge = current; //Updated edge to current time for next calculation
	if(rising) {
		TCCR1B &= ~(1<<ICES1); //Edge triggered event set to falling edge (0)
		if(duration >= DOT_LOWER && duration < DASH_LOWER) { //Dot time
			sprintf(str, "Dot\n");
			UART_putstring(str);
			
		} else if (duration >= DASH_LOWER && duration < DASH_UPPER) { //Dash time
			sprintf(str, "Dash\n");
			UART_putstring(str);
		}
		
		
		
	} else {
		
		TCCR1B |= (1<<ICES1); //Edge triggered event set to rising (1)
		if(duration >= DASH_UPPER) { //Space time
			sprintf(str, "Space\n");
			UART_putstring(str);
			
		}
		
		
		
	}
	
//}


ISR(TIMER1_OVF_vect){
	overflows += 1; //Increment overflows if the overflow ISR is engaged
	
	
}

void Initialize() {
// 	cli(); //Disables all interupt events
	
	TCCR1B = 0; //Set all Clock values to default
	TCCR1B |= (1 << CS11);
	
	TCCR1B &= ~(1<<ICES1); //Edge triggered event set to falling edge (0)
	
	TIFR1 |= (1<<ICF1); //Reset event triggered flag
	TIFR1 |= (1<<TOV1); //Reset timer overflow flag
	
	TCCR1A = 0; //Normalize clock settings
	
	DDRB = 0; //Set all port B pins to input (we only care about DDB5 and DDB0)
	DDRB = (1 << DDB5); //Set PB5 to output, other pins including PB0 are already input
	PORTB = 0; //All voltage at output ports are low. Pull up resistor is disabled at PB0
	
	TIMSK1 |= (1<<ICIE1); //Timer 1 input capture interrupt enabled
	
	TIMSK1 |= (1<<TOIE1); //Timer 1 overflow interrupt enabled.

	sei(); //Re-enables all interrupt events
}


int main(void) {
	UART_init(BAUD_PRESCALER);
	Initialize();
	while(1);
}

