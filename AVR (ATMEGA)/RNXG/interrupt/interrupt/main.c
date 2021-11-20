/*
 * interrupt.c
 *
 * Created: 11-04-2021 09:27:40 AM
 * Author : Shri
 */ 

#include <avr/io.h>
#define  F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	 DDRB |= (1<<3) | (1<<0) | (1<<1);
	 
	 DDRC = 1<<3;
	 
	 PORTD = 1<<2;
	 
	 MCUCR = 0x02;
	 
	 GICR = (1<<INT0);
	 sei();
	 
	 PORTB = 0x01;	 
	 OCR0 = 100;	
	
	TCCR0 = 0x7A;
	while(1)
	{
		OCR0 = 10;		
	}
     
}
 
 
ISR (INT0_vect)
{
	
	PORTC ^= (1<<3);
	 
}
