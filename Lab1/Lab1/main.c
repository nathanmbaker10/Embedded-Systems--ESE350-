/*
 * Lab1.c
 *
 * Created: 2/26/2021 2:22:48 PM
 * Author : Nathan Baker
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>



void Initialize() {
	DDRB |= 0x1E;
	DDRD = 0;
	PORTD = 0f;
}

void toggleLEDs(int toggles) {
	if (toggles % 4 == 0){
		PORTB = 0b00000010;
	} else if (toggles % 4 == 1) {
		PORTB = 0b00000100;
	} else if (toggles %4 == 2) {
		PORTB = 0b00001000;
	} else {
		PORTB = 0b00010000;
	}
} 

int main(void)
{
    /* Replace with your application code */
	Initialize();
	int toggles = -1;
    while(1) {
		if(PIND & (1<<PIND7)){
			toggles++;
			toggleLEDs(toggles);
		}
		_delay_ms(250);
	}
	
	
	
	
	
}

