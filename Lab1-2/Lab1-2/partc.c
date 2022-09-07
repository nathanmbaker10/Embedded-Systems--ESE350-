#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


ISR(TIMER1_CAPT_vect){
	int rising = TCCR1B & (1<<ICES1);
	if(rising) {
		TCCR1B &= ~(1<<ICES1); //Edge triggered event set to falling edge (0)
		PORTB |= (1<<PORTB5); //LED turned on
	} else {
		TCCR1B |= (1<<ICES1); //Edge triggered event set to rising
		PORTB &= ~(1<<PORTB5); //LED turned off
	}
	TIFR1 |= (1<<ICF1);
}



void Initialize() {
	cli(); //Disables all interupt events
	
	TCCR1B = 0; //Set all Clock values to default
	TCCR1B |= (1<<CS11); //Divide clock by 28
	TCCR1B &= ~(1<<ICES1); //Edge triggered event set to falling edge (0)
	
	TIFR1 |= (1<<ICF1); //Reset event triggered flag
	
	TCCR1A = 0; //Normalize clock settings
	
	DDRB = 0; //Set all port B pins to input (we only care about DDB5 and DDB0)
	DDRB = (1 << DDB5); //Set PB5 to output, other pins including PB0 are already input
	PORTB = 0; //All voltage at output ports are low. Pull up resistor is disabled at PB0
	
	TIMSK1 |= (1<<ICIE1); //TImer 1 input capture interrupt enabled
	
	
	sei(); //Re-enables all interrupt events
}


int main(void){
	Initialize();
	
	while(1);
	
}