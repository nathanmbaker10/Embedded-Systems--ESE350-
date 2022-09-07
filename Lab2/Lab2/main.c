/*
 * Lab2.c
 *
 * Created: 3/5/2021 2:07:25 PM
 * Author : Nathan Baker
 */ 

#include <avr/io.h>
#include "UART.h"


int main(void)

{
	
	_uartInit(9600);
    /* Replace with your application code */
    while (1) 
    {
		_uartPutString("Testing\n");
    }
}

