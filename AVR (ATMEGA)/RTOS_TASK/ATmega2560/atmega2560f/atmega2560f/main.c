/*
 * atmega2560f.c
 *
 * Created: 19-05-2021 12:26:03 PM
 * Author : Shri
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#define Baud 9600
#define Myubrr 103

void Usart_init();
void USART_Transmit(char *data );


char *z = "Hello World!\r\n";

void vTask1(void *pvparm);
void vTask2(void *pvparam);

void vApplicationIdleHook( void )
{
}

int main(void)
{
	DDRB = 0xff;
	
	
	Usart_init();
	
	PORTB = 0x80;
	
	
    xTaskCreate(vTask1, "task1", 100, NULL,0, NULL);
	xTaskCreate(vTask2, "task1", 100, NULL,0, NULL);
	vTaskStartScheduler();
	
	for(;;);
   
}



void Usart_init()
{
	
	UBRR0 = 0x67;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	 
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(char *data )
{
	  
	  while(*data)
	  {  
		while ( !( UCSR0A & (1<<UDRE0)) );
	  
		UDR0 = *data;
		data++;
	  }
	
	
}

void vTask1(void *pvparam)
{
	while(1)
	{
		
		USART_Transmit(z);
		vTaskDelay(100);
	}
	
}

void vTask2(void *pvparam)
{
	 while (1)
	 {
		 PORTB = ~PORTB;
		 if(PORTB == 0x80)
		 {
			 USART_Transmit((char*)"Led On\r\n");	 
		 }
		 else
		 {
			 USART_Transmit((char*)"Led Off\r\n");	 
		 }
		 
		 
		 vTaskDelay(100);
	 }
}



