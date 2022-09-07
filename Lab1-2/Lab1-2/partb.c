#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>



void Initialize() {
	cli(); //Disables all interupt events
	
	TCCR1B = 0; //Set all Clock values to default
	TCCR1B |= (1<<CS11); //Divide clock by 8
	TCCR1B &= ~(1<<ICES1); //Edge triggered event set to falling edge (0)
	
	TIFR1 |= (1<<ICF1); //Reset event triggered flag
	
	TCCR1A = 0; //Normalize clock settings
	
	DDRB = 0; //Set all port B pins to input (we only care about DDB5 and DDB0)
	DDRB = (1 << DDB5); //Set PB5 to output, other pins including PB0 are already input
	PORTB = 0; //All voltage at output ports are low. Pull up resistor is disabled at PB0
	
	sei(); //Re-enables all interrupt events
}

int main(void)
{
	/* Replace with your application code */
	Initialize(); //Calls initialization function
	while(1) {
		while(!(TIFR1 & (1 <<ICF1))); //Continuous while loop that runs until falling edge flag is triggered at ICF1
		PORTB |= (1<<PORTB5); //Sets output voltage to high at PB5
		TIFR1 |= (1<<ICF1); //Resets event flag
		while(!(TIFR1 & (1 <<ICF1)));
		PORTB = 0;
		TIFR1 |= (1<<ICF1);
	}
	
}

