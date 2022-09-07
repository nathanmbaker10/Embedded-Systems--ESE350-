// /*
//  * CFile1.c
//  *
//  * Created: 3/26/2021 2:33:43 PM
//  *  Author: Nathan Baker
//  */ 
// #include <avr/interrupt.h>
// #define F_CPU 16000000UL
// #include <util/delay.h>
// #include <stdio.h>
// #include "UART.h"
// 
// char toPrint[25];
// 
//  volatile int reading;
//  volatile int read;
// ISR(ADC_vect) {
// 	read = 1;
// 	reading = ADC;
// }
// 
// void Initialize() {
// 	cli();
// 	//Clear power reudction for ADC
// 	PRR &= ~(1<<PRADC);
// 	//Reference to external VCC
// 	ADMUX &= ~(0<<REFS1);
// 	ADMUX &= (1<<REFS0);
// 	//Divides internal clock by 128.  16MHz/128 = 125KHz
// 	ADCSRA |= (1<<ADPS0);
// 	ADCSRA |= (1<<ADPS1);
// 	ADCSRA |= (1<<ADPS2);
// 	//Selects input to be ADC0 (PC0)
// 	ADMUX &= (1<<MUX3);
// 	ADMUX &= (1<<MUX2);
// 	ADMUX &= (1<<MUX1);
// 	ADMUX &= (1<<MUX0);
// 	//Auto trigger
// 	ADCSRA |= (1<<ADATE);
// 	//Set to free running
// 	ADCSRB &= ~(1<<ADTS2);
// 	ADCSRB &= ~(1<<ADTS1);
// 	ADCSRB &= ~(1<<ADTS0);
// 	//Disable digital input buffer for pin 0
// 	DIDR0 |= (1<<ADC0D);
// 	//Enable ADC
// 	ADCSRA |= (1<<ADEN);
// 	//Enable ADC interrupt
// 	ADCSRA |= (1<<ADIE);
// 	//Start conversion
// 	ADCSRA |= (1<<ADSC);
// 	sei();
// }
// 
// int main(void) {
// 	_uartInit(9600);
// 	Initialize();
// 	while(1) {
// 		while(!read);
// 		sprintf(toPrint, "%d\n", reading);
// 		_uartPutString(toPrint);
// 		read = 0;
// 	}
// }
//