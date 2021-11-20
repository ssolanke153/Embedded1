/*
 * TCP_IP_QUEUE.c
 *
 * Created: 26-04-2021 03:58:00 PM
 * Author : Shri
 */ 

#include <avr/io.h>
#define  F_CPU 8000000UL
#include <stdio.h>
#include "usart.h"



#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


QueueHandle_t xQueuePointer;
TaskHandle_t TaskHandle2;

void vSender(void *param);
void vReceiver(void *param);

void vApplicationIdleHook( void )
{

	
}


int main(void)
{
	
	usart_init();
	
	xQueuePointer = xQueueCreate(5, sizeof(char*));
	
	usart_send((char*)"hello");
	
	if (xQueuePointer !=NULL)
	{
		xTaskCreate(vSender, "Task1", 100, (void*)"This\r", 1, NULL);
		xTaskCreate(vReceiver, "Task2", 100, NULL, 1, NULL);
		
		vTaskStartScheduler();
		
	}
	
	else
	{
		usart_send((char*)"queue is not empty!");
	}
}

void vSender(void *param)
{
	char *StringToSend;
	StringToSend = (char*) param;
	
	
	while(1)
	{
		usart_send((char*)"send to queue\r");

		
		xQueueSendToBack(xQueuePointer, &StringToSend, 0);
		
		vTaskDelay(500);
		

	}
	
	
}

void vReceiver(void *param)
{
	char *ReceivedString;
	
	
	while(1)
	{
		
		xQueueReceive(xQueuePointer, &ReceivedString, 0);
		
		usart_send(ReceivedString);
		usart_send((char*)"Received from Queue\r");

		vTaskDelay(500);
	}
	
}
