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
		PORTB |= (1<<PORTB0);
		
		vTaskDelayUntil(&lastWakeTimeA, a_on);
		PORTB &= ~(1<<PORTB0);
		vTaskDelayUntil(&lastWakeTimeA, a_off);
		
	}
}


void taskBFunction(void *pvParameters) {
	
	const TickType_t b_on = 300 / portTICK_PERIOD_MS;
	const TickType_t b_off = 900 / portTICK_PERIOD_MS;
	
	
	TickType_t lastWakeTimeB = xTaskGetTickCount();
	for ( ;; ) {
		PORTB |= (1<<PORTB1);
		
		vTaskDelayUntil(&lastWakeTimeB, b_on);
		PORTB &= ~(1<<PORTB1);
		vTaskDelayUntil(&lastWakeTimeB, b_off);
		
	}
}



void taskCFunction(void *pvParameters) {
	
	const TickType_t c_on = 1400 / portTICK_PERIOD_MS;
	const TickType_t c_off = 100 / portTICK_PERIOD_MS;
	
	TickType_t lastWakeTimeC = xTaskGetTickCount();
	for ( ;; ) {
		PORTB |= (1<<PORTB2);
		
		vTaskDelayUntil(&lastWakeTimeC, c_on);
		PORTB &= ~(1<<PORTB2);
		vTaskDelayUntil(&lastWakeTimeC, c_off);
		
	}
}

int main(void)
{
	/* Create tasks and make some magic*/
	setup();
	xTaskCreate(taskAFunction, "Task A", 256, NULL, 3, NULL);
	xTaskCreate(taskBFunction, "Task B", 256, NULL, 2, NULL);
	xTaskCreate(taskCFunction, "Task C", 256, NULL, 1, NULL);
	vTaskStartScheduler();
	
	while(1);
	

}
