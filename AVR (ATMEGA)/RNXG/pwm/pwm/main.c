/*
 * pwm.c
 *
 * Created: 06-04-2021 09:37:30 PM
 * Author : Shri
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include <util/delay.h>

  
void Task1(void *pvparam);
void Task2(void *pvparam);

#define  ena1 3
#define  ena2 7

#define in1 0
#define in2 1
#define in3 2
#define in4 3


int main(void)
{
	DDRD |= (1<<ena2);
	DDRC |= (1<<in1) | (1<<in2) | (1<<in3) | (1<<in4);
	DDRB |=(1<<ena1);
	
	PORTC = 0x05; 
	  
	
	xTaskCreate(Task1, "task1", 100,NULL, 1,NULL);
	xTaskCreate(Task2, "task2", 100,NULL,1,NULL);
	
	vTaskStartScheduler();
	
	return 0;
      
}


void Task1(void *pvparam)
{
	(void) pvparam;
	int i = 0;
	OCR2 = 0;
	TCCR2 = 0x76;
	
	while(1){
	for(i = 0; i<255; i++)
	{
		OCR2 = i;
 
	 
	}
	 
	}
	
}

void Task2(void *pvparam)
{
	(void) pvparam;
	int j = 0;
	OCR0 = 0;
	
	TCCR0 = 0x74;
	while(1){
	for(j=0; j<255; ++j)
	{
		OCR0 = j;
		 
	}
 
}
}
