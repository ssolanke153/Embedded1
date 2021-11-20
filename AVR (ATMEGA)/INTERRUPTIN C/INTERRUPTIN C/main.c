/*
 * INTERRUPTIN C.c
 *
 * Created: 27-05-2020 22:19:06
 * Author : Shri
 */ 

#include <avr/io.h>
#include "avr/interrupt.h"


int main(void)
{
    DDRB |= 0x20;
	
	TCNT0 = 00;
	TCCR0 = 0x05;
	
	TIMSK = (1<<TOIE0);
	
	sei();
	
	DDRC = 0x00;
	DDRD = 0xFF;
	
	
	
    while (1) 
    {
		PORTD = PORTC;
		
    }
}

ISR (TIMER0_OVF_vect)
{
	unsigned int z,i;
	TCNT0 = 00;
	PORTB ^= 0x20;
	for(z=0;z<60000;z++)
	{
		for(i=0;i<532;i++)
		{
			
		}
	}
}

