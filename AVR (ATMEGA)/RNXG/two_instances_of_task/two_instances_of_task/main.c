/*
 * two_instances_of_task.c
 *
 * Created: 02-04-2021 08:15:43 AM
 * Author : Shri
 */ 

#include <avr/io.h>
 
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
 
 
 

void usart_init(void)
{

	UCSRB = (1<<TXEN);
	UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);
	UBRRL = 0x33;
}

void usart_send(void *ch)
{
	char *ch1;
	
	ch1 = (char*) ch;
	
	
	
	while(*ch1)
	{
		
		while(!(UCSRA & (1<<UDRE)));
		
		
		UDR = *ch1;
		
		ch1++;
	}
	
	
	
}



  char *pvParam1 = "task 2 is running\r";
  char *pvParam2 = "task 1 is running\r";

 

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;


portSHORT main(void)
{
	usart_init();
	xTaskCreate(vTask1, "task1", 1000, NULL, 0,&Task_Handle1);
	xTaskCreate(vTask2, "task2", 1000,NULL, 1,&Task_Handle2);

	vTaskStartScheduler();
	
 
}

 
void vTask1(void *pvParameters)
{
	(void) pvParameters;
	while(1)
	{
   	usart_send((char*)"6");
	vTaskDelay(1000);
	}
	
}
 
void vTask2(void *pvParameters)
{
	(void) pvParameters;
        while(1)
		{
		usart_send((char*)"5");
		vTaskDelay(1000);
		}
		
}
