/*
 * c0m1.c
 *
 * Created: 28-05-2020 20:45:28
 * Author : Shri
 */ 

#include <avr/io.h>


int main(void)
{
     DDRA = 0xFF;
	 UCSRB = (1<<RXEN);
	 UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);
	 UBRRL = 0x33;
    while (1) 
    {
		while(!(UCSRA & (1<<RXC)));
		PORTC = UDR;
    }
	return 0;
}

