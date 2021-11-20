/*
 * MOTOR_SPEED IN C.c
 *
 * Created: 7/1/2020 10:20:19 AM
 * Author : Shri
 */ 
#include<avr/io.h>
//#include <Arduino.h>


int main()
{
	DDRB |= (1<<3) | (1<<0) | (1<<1) ;
	/*DDRB |=(1<<0);
	DDRB |=(1<<1);*/
	//TCNT0 = 0;
	OCR0 = 255;
	TCCR0 = 0x69;
	
	while(1)
	{
		PORTB = PORTB | (1<<1);
		PORTB = PORTB & ~(1<<0);
		
	}
	
}


