////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////    main.c
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

#define F_CPU 16000000UL

/*--------------------Libraries---------------------------*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/sleep.h>

/* Scheduler include files. */
#include "AVR_FreeRTOS/FreeRTOS.h"
#include "AVR_FreeRTOS/task.h"
#include "AVR_FreeRTOS/queue.h"
#include "AVR_FreeRTOS/semphr.h"

/* system time include file. */
#include "time.h"

/*-----------------------------------------------------*/

void setup() {
	DDRB |= (1<<DDB0);
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
}

void taskAFunction(void *pvParameters) {
	
	const TickType_t a_on = 150 / portTICK_PERIOD_MS;
	const TickType_t a_off = 600 / portTICK_PERIOD_MS;
	
	TickType_t lastWakeTimeA = xTaskGetTickCount();
	for ( ;; ) {
		taskENTER_CRITICAL();
		PORTB |= (1<<PORTB0);
		int i = 0;
		int j = 0;
		for (i = 0; i < 150; i++) {
			for (j = 0;j < 4000; j++){}
		}
		
		PORTB &= ~(1<<PORTB0);
		taskEXIT_CRITICAL();
		for (i = 0; i < 600; i++) {
			for (j = 0;j < 4000; j++){}
		}
	}
}


void taskBFunction(void *pvParameters) {
	
	const TickType_t b_on = 300 / portTICK_PERIOD_MS;
	const TickType_t b_off = 900 / portTICK_PERIOD_MS;
	
	
	TickType_t lastWakeTimeB = xTaskGetTickCount();
	for ( ;; ) {
		taskENTER_CRITICAL();
		PORTB |= (1<<PORTB1);
		int u;
		int v;
		for (u = 0; u < 300; u++) {
			for (v = 0; v < 4000; v++){}
		}
		PORTB &= ~(1<<PORTB1);
		
		taskEXIT_CRITICAL();
		for (u = 0; u < 300; u++) {
			for (v = 0; v < 4000; v++){}
		}
	}
}



void taskCFunction(void *pvParameters) {
	
	const TickType_t c_on = 1400 / portTICK_PERIOD_MS;
	const TickType_t c_off = 100 / portTICK_PERIOD_MS;
	
	TickType_t lastWakeTimeC = xTaskGetTickCount();
	for ( ;; ) {
		taskENTER_CRITICAL();
		PORTB |= (1<<PORTB2);
		int x;
		int y;
		for (x = 0; x < 450; x++) {
			for (y = 0; y < 4000; y++){}
		}
		PORTB &= ~(1<<PORTB2);
		
		taskEXIT_CRITICAL();
		for (x = 0; x < 1050; x++) {
			for (y = 0; y < 4000; y++){}
		}
	}
}

int main(void)
{
	/* Create tasks and make some magic*/
	setup();
	xTaskCreate(taskAFunction, "Task A", 256, NULL, 1, NULL);
	xTaskCreate(taskBFunction, "Task B", 256, NULL, 1, NULL);
	xTaskCreate(taskCFunction, "Task C", 256, NULL, 1, NULL);
	vTaskStartScheduler();
	while(1);

}
