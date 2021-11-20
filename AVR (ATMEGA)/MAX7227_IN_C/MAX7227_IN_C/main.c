/*
 * MAX7227_IN_C.c
 *
 * Created: 29-07-2020 03:22:40 PM
 * Author : Shri
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "util/delay.h"
#define MOSI 5
#define SCK 7
#define SS 4

void execute(unsigned char cmd, unsigned char data)
{
	PORTB &= ~(1<<SS);
	SPDR = cmd;
	while(!(SPSR & (1<<SPIF)));
	
	SPDR = data;
	
	while(!(SPSR & (1<<SPIF)));
	
	PORTB |= (1<<SS);
	
}


int main(void)
{
   
   DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS);
   SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
   execute(0x09, 0xFF);
   execute(0x0B, 0x02);
   execute(0x0C, 1);
   execute(0x0A, 9);
   
    
   
    while (1) 
    {
	   execute(0x01, 0x09);
	   _delay_ms(1);
	   execute(0x02, 0x07);
	   _delay_ms(1);
	   	
    }
	return 0;
	
}



