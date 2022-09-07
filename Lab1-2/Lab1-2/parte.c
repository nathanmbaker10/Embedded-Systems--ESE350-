#include <avr/io.h>
#include "uart.h"
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)
#define DOT_LOWER 480000
#define DASH_LOWER 1600000
#define DASH_UPPER 3200000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

unsigned long volatile int overflows = 0;
unsigned long volatile int edge = 0;

char currentLetter = ' ';

char str[25]; //String to be printed



void handleMorse(int dot) {
	if (dot) {
		if(currentLetter == 'e'){
			currentLetter = 'i';
		} else if (currentLetter == 'i') {
			currentLetter = 's';
		} else if (currentLetter == 's'){
			currentLetter = 'h';
		} else if (currentLetter == 'u'){
			currentLetter = 'f';
		} else if (currentLetter == 'a'){
			currentLetter = 'r';
		} else if (currentLetter == 'r'){
			currentLetter = 'l';
		} else if (currentLetter == 'w'){
			currentLetter = 'p';
		} else if (currentLetter == 't'){
			currentLetter = 'n';
		} else if (currentLetter == 'm'){
			currentLetter = 'g';
		} else if (currentLetter == 'n'){
			currentLetter = 'd';
		} else if (currentLetter == 'd'){
			currentLetter = 'b';
		} else if (currentLetter == 'k'){
			currentLetter = 'c';
		} else if (currentLetter == 'g'){
			currentLetter = 'z';
		} else if (currentLetter == 'h'){
			currentLetter = '5';
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';
		} else if (currentLetter == 'b'){
			currentLetter = '6';
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';
		} else if (currentLetter == 'o'){
			currentLetter = '8';
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';
		} else if (currentLetter == '9'){
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';
		} else if (currentLetter == 'z'){
			currentLetter = '7';
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';
		} else {
			currentLetter = 'e';
		}
		
	} else {
		
		if(currentLetter == 'e'){
			currentLetter = 'a';
		} else if (currentLetter == 'i') {
			currentLetter = 'u';
		} else if (currentLetter == 's'){
			currentLetter = 'v';
		} else if (currentLetter == 'w'){
			currentLetter = 'j';
		} else if (currentLetter == 'a'){
			currentLetter = 'w';
		} else if (currentLetter == 't'){
			currentLetter = 'm';
		} else if (currentLetter == 'm'){
			currentLetter = 'o';
		} else if (currentLetter == 'n'){
			currentLetter = 'k';
		} else if (currentLetter == 'd'){
			currentLetter = 'x';
		} else if (currentLetter == 'k'){
			currentLetter = 'y';
		} else if (currentLetter == 'g'){
			currentLetter = 'q';
		} else if (currentLetter == 'j'){
			currentLetter = '1';
		} else if (currentLetter == 'u'){
			currentLetter = '2';
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';
		} else if (currentLetter == 'v'){
			currentLetter = '3';
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';
		} else if (currentLetter == 'h'){
			currentLetter = '4';
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';
		} else if (currentLetter == 'o'){
			currentLetter = '9';
		} else if (currentLetter == '9') {
			currentLetter = '0';
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';
		 } else {
			currentLetter = 't';
		}
		
		
		
		
	}
}

ISR(TIMER1_CAPT_vect){
	int rising = TCCR1B & (1<<ICES1); //Used to check whether the input capture was a falling or rising edge
	unsigned long int current = ICR1 + (overflows * 65535); //Current time of edge computed using overflow numbers (incremented during overflow ISR)
	unsigned long int duration = current - edge; //Time based subtraction
	
	
	edge = current; //Updated edge to current time for next calculation
	if(rising) {
		TCCR1B &= ~(1<<ICES1); //Edge triggered event set to falling edge (0)
		if(duration >= 100 && duration < DASH_LOWER) { //Dot time
			PORTB |= (1<<PORTB1); //Toggle LED On
			_delay_ms(50); 
			handleMorse(1);
			PORTB &= ~(1<<PORTB1); //Toggle LED Off
		} else if (duration >= DASH_LOWER && duration < DASH_UPPER) { //Dash time
			PORTB |= (1<<PORTB2); //Toggle LED On
			_delay_ms(50); 
			handleMorse(0);
			PORTB &= ~(1<<PORTB2); //Toggle LED Off
		}
		
		} else {
		
		TCCR1B |= (1<<ICES1); //Edge triggered event set to rising (1)
		if(duration >= DASH_UPPER) { //Space time
			strcat(str, &currentLetter);
			UART_putstring(str);
			currentLetter = ' ';			
		}
		
		
		
	}
	
}


ISR(TIMER1_OVF_vect){
	overflows += 1; //Increment overflows if the overflow ISR is engaged
	
	
}

void Initialize() {
	cli(); //Disables all interrupt events
	
	TCCR1B = 0; //Set all Clock values to default
	TCCR1B |= (1 << CS11);
	
	TCCR1B &= ~(1<<ICES1); //Edge triggered event set to falling edge (0)
	
	TIFR1 |= (1<<ICF1); //Reset event triggered flag
	TIFR1 |= (1<<TOV1); //Reset timer overflow flag
	
	TCCR1A = 0; //Normalize clock settings
	
	DDRB = 0; //Set all port B pins to input (we only care about DDB5 and DDB0)
	DDRB |= (1 << DDB5); //Set PB5 to output, other pins including PB0 are already input
	DDRB |= (1 << DDB1); //Sets PB1 to output
	DDRB |= (1 << DDB2); //Sets PB2 to output
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

