/*
 * Toggle with delay.c
 *
 * Created: 11-05-2020 8.46.46 AM
 * Author : Shri
 */ 

#include <avr/io.h>
//#include <util/delay.h>
void DELAY(void);



int main(void)
{
	 DDRD=0xFF;
	  
    while (1) 
    {
		PORTD=0xAA;
		_delay_ms(1000);
		PORTD=0x55;
		_delay_ms(1000);
    }
	
	return 0;
}

void DELAY(void)
{
	unsigned int i,z;
	
	for (i=0;i<=42150;i++)
	{
	
	}
}