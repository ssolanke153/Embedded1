/*
 * usart.h
 *
 * Created: 11-04-2021 05:03:54 PM
 *  Author: Shri
 */ 


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


int  usart_recv(void)
{
	
	while(! (UCSRA & (1<<RXC)));
	return UDR;
}