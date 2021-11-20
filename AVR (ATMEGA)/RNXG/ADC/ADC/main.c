/*
 * ADC.c
 *
 * Created: 11-04-2021 06:36:30 AM
 * Author : Shri
 */ 

#include <avr/io.h>
 
#include <avr/interrupt.h>
#include "lcd.h"
#include <stdio.h> 
 
int value = 0, i =0;

void sendchar(char* sval )
{
	
	while(*sval)
	{
		display = *sval;
		DISPLAY();
		sval++;
	}
}

ISR(ADC_vect)
{
	
	char sval[20];
    
	value   = ADCL>>2;
	PORTC = ADCH>>2;
	
	 
	if(i != value )
	{
		i = value;	
		display = 0x01;
		command();
		
		sprintf(sval, "%d", value);
		
		sendchar(sval);	
	}
	 

	ADCSRA |= (1<<ADSC);
	
}


int main(void)
{
    
	 DDRA = 0;
     DDRC = 0xFF;
     lcd_init();
    
  
	 ADCSRA = 0x8F;   
	 ADMUX = 0xC0;
	 sei();
	 
	 ADCSRA |= (1<<ADSC);
	 
	 while(1);

	 
	 return 0;
	 
	 
}

 

 