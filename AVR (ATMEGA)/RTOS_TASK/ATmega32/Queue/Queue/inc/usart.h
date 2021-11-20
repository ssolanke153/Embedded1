/*
 * usart.h
 *
 * Created: 23-04-2021 04:18:54 PM
 *  Author: Shri
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"

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