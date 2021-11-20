/*
 * usart.h
 *
 * Created: 25-05-2021 04:37:27 AM
 *  Author: Shri
 */ 



#include <avr/io.h>
 

#define Baud 9600
#define Myubrr 103


void usart_init()
{
	
	UBRR0 = 0x67;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void usart_send(char *data )
{
	
	while(*data)
	{
		while ( !( UCSR0A & (1<<UDRE0)) );
		
		UDR0 = *data;
		data++;
	}
	
	
}

