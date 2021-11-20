/*
 * task2.c
 *
 * Created: 29-03-2021 09:23:59 PM
 * Author : Shri
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

 


int main(void)
{
	 
	DDRA = 0xFF;      // for monitoring change in bit of port A. making Port A as output port 
	DDRD = 0xFF;	 // making port D as output port.
	
	 
	
   
    while (1) 
    { 
		if(PINA == 1)
		{
			PORTD = 0x01;
			
			_delay_ms(1);
			
		}
		
		else if(PINA == 0x02)
		{
			PORTD = 0x02;
		 
			_delay_ms(1);
			
		}
		
		else if(PINA == 0x03)
		{
		   PORTD = 0x03;
			 
			_delay_ms(1);
		}
		else
	{
	  PORTD = 0x00;	
      _delay_ms(1);
	}
		
		 
		
		
    }
}

