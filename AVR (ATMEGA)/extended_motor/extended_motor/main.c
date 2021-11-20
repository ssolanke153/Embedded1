/*
 * extended_motor.c
 *
 * Created: 7/3/2020 8:44:03 AM
 * Author : Shri
 */ 

#include<avr/io.h>
#include<util/delay.h>
#define ena 2
#define pin1 0
#define pin2 1

int main()
{
	int a=150;
	DDRD |= (1<<pin1) | (1<<pin2) | (1<<ena);

	while(1)
	{

		PORTD |= ((1<<ena)| (1<<pin1) & ~(1<<pin2));
		_delay_ms(a);
		PORTD  = PORTD & ~(1<<ena) | (1<<pin1) & ~(1<<pin2);
		_delay_ms(150-a);
		
	}

	
	
}

