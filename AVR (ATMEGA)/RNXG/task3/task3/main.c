/*
 * task3.c
 *
 * Created: 30-03-2021 04:05:37 PM
 * Author : Shri
 */ 

/*
#include <avr/io.h>
#define  F_CPU 8000000
#include <util/delay.h>


//  using delay 

int main(void)
{
    DDRB = 0xff;
	DDRD = 0xff;
    while (1) 
    {
		if ((PINB == 0x04) & (PORTB == 0x00))
		{
			PORTD = 0x01;
			_delay_ms(5);
		}
		else if((PINA == 0x04) & (PORTD == 0x01))
		{
			PORTD = 0x00;
		  _delay_ms(5);	
		}
    }
}

*/

// using edge-triggered interrupt


#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
  DDRD = 0xff;
  PORTD = 0x00;
 
  
  MCUCR = (1<<ISC2);
  GICR = (1<<INT2);
  
  sei();
  
  while(1)
  {
	  
  }	
  
}


ISR (INT2_vect)

{
	PORTD ^= (1<<0); 
}