#define FCPU 16000000UL
#include <avr/io.h>
#include <stdio.h>

#include "UART.h"

char toPrint[25];

void _uartInit(int baudrate) {
	unsigned long baud_prescale = (((FCPU)/(16UL*baudrate)) - 1);
	UBRR0H = (unsigned char)(baud_prescale >> 8);
	UBRR0L = (unsigned char)baud_prescale;
	
	UCSR0C &= ~(1<<UMSEL01);
	UCSR0C &= ~(1<<UMSEL00);
	
	
	UCSR0C |= (1<<USBS0);
	UCSR0C &= ~(1<<UCSZ02);
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

void _uartSendData(unsigned char data) {
	while(!(UCSR0A & (1<<UDRE0)));
	
	UDR0 = data;
}


void _uartPutString(char* stringPtr) {
	while(*stringPtr != 0x00){
		_uartSendData(*stringPtr);
		stringPtr++;
	}
}
