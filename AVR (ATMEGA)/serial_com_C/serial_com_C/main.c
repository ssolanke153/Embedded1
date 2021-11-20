/*
 * serial_com_C.c
 *
 * Created: 08-08-2020 11:41:19 AM
 * Author : Shri
 */ 


/*Q. WRITE a C PROGRAM FOR THE AVR TO TRANSFER THE LETTER 'G' SERIALLY AT 9600 baud, 
CONTINOUSLY. USE 8-bit DATA AND 1 STOP BIT. ASSUME XTAL = 8MHz*/ 

#include <avr/io.h>


void usart_init(void)
{
	UCSRB = (1<<TXEN);
	UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);
	UBRRL = 0x33;
}

void usart_send(unsigned char ch)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = ch;
}


int main(void)
{
     usart_init();
    while (1) 
    {
		usart_send('G');
		
    }
	return 0;
}

