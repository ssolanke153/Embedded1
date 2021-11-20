/*
 * pwm1.c
 *
 * Created: 06-04-2021 11:17:07 PM
 * Author : Shri
 */ 

#include <avr/io.h>


int main(void)
{
     DDRD |= (1<<5);
	 
	 PORTD |= (1<<5);
	  
    while (1) 
    {
    }
}

