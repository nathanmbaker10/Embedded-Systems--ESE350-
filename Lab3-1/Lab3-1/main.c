/*
 * Lab3-1.c
 *
 * Created: 3/12/2021 1:38:38 PM
 * Author : Nathan Baker
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>


ISR(TIMER0_OVF_vect) {
	TCCR0B |= (1<<FOC0A); //Forces the compare match
}

void Initialize() {
	cli();
	
	DDRD |= (1<<DDD6); //Pin 6 configured to output
	PORTD |= (1<<PORTD6); //Sets PD6 to high.
	TIMSK0 |= (1<<TOIE0); //Overflow interrupt enabled
	TCCR0B = 0;
	TCCR0B |= (1<<CS01); //Prescale by 8
	TCCR0A = 0;
	TCCR0A |= (1<<COM0A0); //Toggle OC0A when output compare flag is raised.

	
	TIFR0 |= (1<<TOV0); //Overflow compare flag cleared
	
	
	
	sei();
	
}

int main(void)

{
    /* Replace with your application code */
	Initialize();
    while (1);
}

