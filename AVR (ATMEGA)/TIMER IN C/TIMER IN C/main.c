/*
 * TIMER IN C.c
 *
 * Created: 19-05-2020 09:26:37
 * Author : Shri
 */

#include <avr/io.h>

void delay();

int main(void)
{

	DDRB=0xFF;

    while (1)
    {
        delay();
		PORTB = PORTB ^ 0x01;
    }
	
	return 0;
}

void delay()
{
   TCNT0 = 186;
   TCCR0 = 0x02;

   while(TIFR &(1<<TOV0)==0)
   {
	   TCCR0 = 0x00;
	   TIFR = 0x01;
   }
}

