/*
 * trial.c
 *
 * Created: 11-05-2020 09:00:45
 *  Author: Shri
 */ 


/*
 * Toggle with delay.c
 *
 * Created: 11-05-2020 8.46.46 AM
 * Author : Shri
 */ 

#include <avr/io.h>
void DELAY(void);



int main(void)
{
	 DDRB=0b00001010;
	  
    while (1) 
    {
		PORTB=0xAA;
		DELAY();
		PORTB=0x55;
		DELAY();
    }
	return 0;
}

void DELAY(void)
{
	unsigned int i,z;
	
	for (i=0;i<=42150;i++)
	{
		for (i=0;i<=4215;i++)
		{
			
		}
	}
}