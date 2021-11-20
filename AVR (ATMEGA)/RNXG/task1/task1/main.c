/*
 * task1.c
 *
 * Created: 29-03-2021 02:07:48 PM
 * Author : Shri
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>




int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	
	unsigned char i = 0;
   
    while (1) 
    {
		for(i = 0; i<6; i++)
		{
			PORTD = i;
			_delay_ms(200);
		}
		
		 
    }
}

