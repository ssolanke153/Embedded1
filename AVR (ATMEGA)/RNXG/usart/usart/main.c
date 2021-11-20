/*
 * usart.c
 *
 * Created: 08-04-2021 04:00:50 PM
 * Author : Shri
 */ 


/* 
#include <avr/io.h>
 
#include <avr/interrupt.h>
#include "lcd.h"
 

 


void usart_init(void);
void usart_send(char *ch);


 

int main(void)
 {
	 
	 lcd_init();
	 
 
 
	 usart_init();
	 sei();
	 
	 usart_send((char*)"are you get data\r");
	 
	 while(1);
 
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

/*

#include <avr/io.h>

#include <avr/interrupt.h>
#include "lcd.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"



void usart_init(void);
void usart_send(char *ch);

void Task1(void *param);
void Task2(void *param);


int main(void)
{
	usart_init();
	
	xTaskCreate(Task1, "Task1",100, NULL, 1, NULL);
	xTaskCreate(Task2, "task2", 100, NULL, 2, NULL);
	
	vTaskStartScheduler();
}



void Task1(void *param)
{
  
 const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
	(void) param;
	while(1)
	{
		
	
	usart_send((char*)"Task1 is running\r");
	vTaskDelay(xDelay250ms);
	}
}

void Task2(void *param)
{
	
	const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
	(void) param;
	while(1)
	{
		
	
	usart_send((char*)"Task2 is running\r");
	vTaskDelay(xDelay250ms);
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



// implementation of vTaskDelayUntil() API funtion. 


/*
#include <avr/io.h>

#include <avr/interrupt.h>
#include "lcd.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"



void usart_init(void);
void usart_send(char *ch);

void Task1(void *param);
void Task2(void *param);


int main(void)
{
	usart_init();
	
	xTaskCreate(Task1, "Task1",100, NULL, 0, NULL);
	xTaskCreate(Task2, "task2", 100, NULL, 0, NULL);
	
	vTaskStartScheduler();
}



void Task1(void *param)
{
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	(void) param;
	
	while(1)
	{
		
		
		usart_send((char*)"Task1 is running\r");
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(250));
		
	}
}

void Task2(void *param)
{
	
	TickType_t xLastWakeTime;
	
	xLastWakeTime = xTaskGetTickCount();
	
	
	(void) param;
	while(1)
	{
		
		usart_send((char*)"Task2 is running\r");
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(250));
		
		
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

// Combining blocking and non-blocking tasks

/*

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include "lcd.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"



void usart_init(void);
void usart_send(char *ch);

void ContinousTask1(void *param);
void ContinousTask2(void *param);
void PeriodicTask3(void *param);

volatile uint32_t ulIdleCycleCount = 0UL;
void vApplicationIdleHook( void )
{
	
	ulIdleCycleCount++;
}
int main(void)
{
	usart_init();
	
	xTaskCreate(ContinousTask1, "Task1",100, NULL, 0, NULL);
	xTaskCreate(ContinousTask2, "task2", 100, NULL, 1, NULL);
	xTaskCreate(PeriodicTask3, "task3", 100, NULL, 2, NULL);
	vTaskStartScheduler();
}


void ContinousTask1(void *param)
{
	 
	
	while(1)
	{
		
		
		usart_send((char*)"continous Task1 is running\r\n");
		 
		
	}
}

void ContinousTask2(void *param)
{
	 
	
	 
	while(1)
	{
	
		
		usart_send((char*)"continous Task2 is running\r\n");
		 
		
		
	}
}


void PeriodicTask3(void *param)
{
	TickType_t xLastWakeTime;
	
	xLastWakeTime = xTaskGetTickCount();
	const TickType_t xDelay3ms = pdMS_TO_TICKS(100);
	
	
	(void) param;
	while(1)
	{
		
		usart_send((char*)"Periodic Task3 is running\r\n");
		vTaskDelayUntil(&xLastWakeTime, xDelay3ms);
		
		
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
*/


// IDLE_TASK AND IDLE HOOK FUNCTION. 



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
	
	xTaskCreate(ContinousTask1, "Task1",100, NULL, 1, NULL);
	xTaskCreate(ContinousTask2, "task2", 100, NULL, 1, NULL);
	 
	vTaskStartScheduler();
}


void ContinousTask1(void *param)
{
	char str[12]; 
	
	 
	
	while(1)
	{
		
		sprintf(str, "%lu",ulIdleCycleCount);
		usart_send(str);
		vTaskDelay(pdMS_TO_TICKS(250));
		
	}
}

void ContinousTask2(void *param)
{
	
	
	
	while(1)
	{
		
		
		usart_send((char*)"continous Task2 is running\r\n");
		vTaskDelay(pdMS_TO_TICKS(250));
		
		
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
