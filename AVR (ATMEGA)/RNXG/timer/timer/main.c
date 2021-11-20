/*
 * timer.c
 *
 * Created: 31-03-2021 03:03:35 AM
 * Author : Shri
 */ 

 

#include <avr/io.h>
#define F_CPU 1000000UL

void delay();

int main(void)
{

	DDRB=0xFF;
	
	 

    while (1)
    {
        
		PORTB = ~PORTB;
		delay();
    }
	
	return 0;
}

void delay()
{
   TCNT0 = 0;
   TCCR0 = 0x02;

   while((TIFR &(1<<TOV0))==1)
   {
	   TCCR0 = 0x00;
	   TIFR = 0x01;
   }
}

 

 

