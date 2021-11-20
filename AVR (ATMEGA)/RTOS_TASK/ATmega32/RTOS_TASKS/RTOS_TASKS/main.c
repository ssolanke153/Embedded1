/*
 * RTOS_TASKS.c
 *
 * Created: 21-04-2021 05:13:42 PM
 * Author : Shri
 */ 



// IDLE TASK AND IDLE HOOK APPLICATION

/*
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#define F_CPU 8000000UL
#include "lcd.h" 
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"



void usart_init(void);
void usart_send(char *ch);

void ContinousTask1(void *param);
void ContinousTask2(void *param);


volatile uint32_t ulIdleCycleCount = 0UL;
void vApplicationIdleHook( void )
{
	
	ulIdleCycleCount++;
}
int main(void)
{
	usart_init();
	lcd_init();
	
	xTaskCreate(ContinousTask1, "Task1",100, NULL, 1, NULL);
	xTaskCreate(ContinousTask2, "task2", 100, NULL, 1, NULL);
	
	vTaskStartScheduler();
}


void ContinousTask1(void *param)
{
	char str[30];
	
	
	
	while(1)
	{
		
		sprintf(str, "Tick count ---> %lu\r",ulIdleCycleCount);
		usart_send(str);
		vTaskDelay(1000);
		
	}
}

void ContinousTask2(void *param)
{
	
	
	
	while(1)
	{
		
		
		usart_send((char*)"continous Task2 is running\r\n");
		vTaskDelay(1000);
		
		
	}
}




void usart_init(void)
{
	UCSRB = (1<<TXEN) | (1<<RXEN) | (1<<RXCIE);
	UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);
	UBRRL = 0x33;
}

void usart_send(char *ch)
{
	
	
	
	while(*ch)
	{
		
		while(!(UCSRA & (1<<UDRE)));
		
		
		UDR = *ch;
		
		ch++;
	}
	
	
}

ISR (USART_RXC_vect)
{
	
	display = UDR;
	DISPLAY();
}

*/


// GETTING AND CHANGING THE PRIORITY OF TASKS...


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include "lcd.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"




void usart_init(void);
void usart_send(char *ch);

void ContinousTask1(void *param);
void ContinousTask2(void *param);

TaskHandle_t TaskHandle1;
TaskHandle_t TaskHandle2;


volatile uint32_t ulIdleCycleCount = 0UL;
void vApplicationIdleHook( void )
{
	
	ulIdleCycleCount++;  // increment the varialbe. at each tick of crystal. 
}


int main(void)
{
	usart_init();
	lcd_init();
	
	xTaskCreate(ContinousTask2, "Task2",100, NULL, 1, &TaskHandle2);
	xTaskCreate(ContinousTask1, "task1", 100, NULL, 1, &TaskHandle1);
	
	vTaskStartScheduler();
}


void ContinousTask1(void *param)
{
	char str[30];
	UBaseType_t uxPriority;
	
	
	
	
	while(1)
	{
		if(ulIdleCycleCount > 10)
		{
			uxPriority = uxTaskPriorityGet(NULL);
			vTaskPrioritySet(TaskHandle1, (uxPriority + 2));
			
		    sprintf(str, "Task Priority ---> %d\r",uxPriority);
		    usart_send(str);
		    sprintf(str, "%s\r",__TIME__);
			usart_send(str);

			
			
		
		}
		
		sprintf(str, "Tick count ---> %lu\r",ulIdleCycleCount);
		usart_send(str);
		

		vTaskDelay(1000);
		
	}
}



void ContinousTask2(void *param)
{
	
	
	
	while(1)
	{
		
		
		usart_send((char*)"continous Task2 is running\r\n");
		vTaskDelay(1000);
		
		
	}
}




void usart_init(void)
{
	UCSRB = (1<<TXEN) | (1<<RXEN) | (1<<RXCIE);
	UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);
	UBRRL = 0x33;
}

void usart_send(char *ch)
{
	
	
	
	while(*ch)
	{
		
		while(!(UCSRA & (1<<UDRE)));
		
		
		UDR = *ch;
		
		ch++;
	}
	
	
}

ISR (USART_RXC_vect)
{
	display = UDR;
	DISPLAY();
}

