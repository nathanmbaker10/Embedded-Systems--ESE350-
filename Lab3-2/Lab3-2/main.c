//  #include <avr/io.h>
// #include <avr/interrupt.h>
// #define F_CPU 16000000UL
// #include <util/delay.h>
// #include <stdio.h>
// #include "UART.h"
// 
// volatile int captured = 0;
// volatile int down = 1;
// volatile int discreteMode = 1;
// volatile int reading;
// volatile int read;
// volatile unsigned long int risingEdge;
// volatile unsigned long int duration = 20;
// volatile unsigned long int distance;
// char toPrint[25];
// 
// ISR(TIMER1_CAPT_vect){
// 	int rising = TCCR1B & (1<<ICES1);
// 	if(rising) {
// 		risingEdge = ICR1;
// 	} else {
// 		duration = ICR1 - risingEdge;
// 		captured = 1;
// 	}
// 	TCCR1B ^= (1<<ICES1);
// }
// 
// 
// ISR(ADC_vect) {
// 	read = 1;
// 	reading = ADC;
// }
// 
// 
// ISR(PCINT0_vect){
// 	if(down) {
// 		_delay_us(10);
// 		down = 0;
// 	} else {
// 		down = 1;
// 		if(discreteMode) {
// 			discreteMode = 0;
// 			
// 			PORTB &= ~(1<<PORTB2);
// 			} else {
// 			discreteMode = 1;
// 			PORTB |= (1<<PORTB2);
// 		}
// 	}
// }
// 
// 
// 
// void Initialize() {
// 
// 	cli();
// 	//Code for discrete mode circuit
// 	//Pin change for D9 enabled
//   	PCMSK0 |= (1<<PCINT1);
//   	PCICR |= (1<<PCIE0);
//   	
//  	DDRB &= ~(1<<DDB1);
// 	DDRB |= (1<<DDB2);
// 	
// 	
// 	//Code to setup sensor and speaker circuit
//  	DDRD |= (1<<DDD5);
//  	TCCR0B &= ~(1<<CS02);
//  	TCCR0B |= (1<<CS01);
//  	TCCR0B |= (1<<CS00); //Prescale clock by 64. Running at 250Khz.
// 	OCR0A = 238;
// 	OCR0B = 119;
// 	TCCR0A |= (1<<COM0B1); 
// 	TCCR0A &= ~(1<<COM0B0); //Toggle OC0B on compare match
//  	TCCR0B |= (1<<WGM02);
//  	TCCR0A |= (1<<WGM01);
//  	TCCR0A |= (1<<WGM00);//Fast PWM mode with OCR0A as TOP
// 	TCCR1B = 0;
// 	TCCR1B |= (1<<CS12);
// 	TCCR1B &= ~(1<<CS11);
// 	TCCR1B |= (1<<CS10);
// 	//Clock prescaler number 5 (divide by 1024; clock running at 15,625Hz)
// 	TCCR1B |= (1<<ICES1); //Initialized to rising edge
// 	TIMSK1 &= ~(1<<ICIE1); //Overflow interrupt initially not enabled
// 	TIFR1 |= (1<<ICF1); //Interrupt flag cleared for sanity check
// 	
// 	
// 	//Code to configure the ADC:
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
// 	//Set to convert on Timer1 capture event
// 	ADCSRB |= (1<<ADTS2);
// 	ADCSRB |= (1<<ADTS1);
// 	ADCSRB |= (1<<ADTS0);
// 	//Disable digital input buffer for pin 0
// 	DIDR0 |= (1<<ADC0D);
// 	//Enable ADC
// 	ADCSRA |= (1<<ADEN);
// 	//Enable ADC interrupt
// 	ADCSRA |= (1<<ADIE);
// 	//Start conversion
// 	
// 	
// 	//UART Initialization
// 	_uartInit(9600);
// 	sei();
// 
// }
// 
// unsigned long discreteFrequency(unsigned long frequency) {
// 	if(frequency <= 1046 + 64) {
// 		return 1046;
// 	} else if (frequency > 1046 + 64 && frequency <= 1174 + 72) {
// 		return 1174;
// 	} else if (frequency > 1174 + 72 && frequency <= 1318 + 39) {
// 		return 1318;
// 	} else if (frequency > 1318 + 39 && frequency <= 1397 + 95) {
// 		return 1397;
// 	} else if (frequency > 1397 + 95 && frequency <= 1568 + 96) {
// 		return 1568;
// 	} else if (frequency > 1568 + 96 && frequency <= 1760 + 107) {
// 		return 1760;
// 	} else if (frequency > 1760 + 107 && frequency <= 1975 + 59) {
// 		return 1975;
// 	} else {
// 		return 2093;
// 	}
// 
// }
// 
// int dutyCylceFromADC(int TOP) {
// 	if(reading <= 140) {
// 		return TOP / 20;
// 	} else if (reading > 140 && reading <= 230) {
// 		return TOP / 10;
// 	} else if (reading > 230 && reading <= 320) {
// 		return (TOP * 15)/100;
// 	} else if (reading > 320 && reading <= 410) {
// 		return TOP/5;
// 	} else if (reading > 410 && reading <= 500) {
// 		return TOP/4;
// 	} else if (reading > 500 && reading <= 590) {
// 		return (TOP * 30)/100;
// 	} else if (reading > 590 && reading <= 680) {
// 		return (TOP * 35)/100;
// 	} else if (reading > 680 && reading <= 770) {
// 		return (TOP * 40)/100;
// 	} else if (reading > 770 && reading <= 860) {
// 		return (TOP * 45)/100;
// 	} else {
// 		return TOP/2;
// 	}
// }
// 
// 
// 
// unsigned int distanceToOCR0A(unsigned long distance) {
// 	unsigned long frequency = -1046/60 * distance + 2790;
// 	if (discreteMode) {
// 		frequency = discreteFrequency(frequency);
// 	}
// 	return (unsigned int) (250000UL / frequency);
// }
// 
// 
// int main(void) {
// 	Initialize();
// 	while(1){
// 		DDRB |= (1<<DDB0);
// 		_delay_us(2);
// 		PORTB |= (1<<PORTB0);
// 		_delay_us(10);
// 		PORTB &= ~(1<<PORTB0);
// 		DDRB &= ~(1<<DDB0);
// 		TIMSK1 |= (1<<ICIE1);
// 		while(!captured);
// 		
// 		distance = duration * 1000000;
// 		distance /= 2;
// 		distance /= 15625;
// 		distance /= 29;
// 		
// 		
// 		OCR0A = distanceToOCR0A(distance);
// 		
// 		OCR0B = dutyCylceFromADC(OCR0A);
// 
// 		captured = 0;
// 		read = 0;
// 		TIMSK1 &= ~(1<<ICIE1);
// 	
// 
// 			
// 
// 	}
// 
// }
// 
// 
