/*
 * counter.c
 *
 * Created: 14-04-2021 06:38:04 PM
 * Author : Shri
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "lcd.h"


void send_char(char *num);


int main(void)
{
	DDRB = 0;  // making DDRB as input port
	
	int i=0, j = 0;
	char value[20];
	lcd_init();
	
	TCCR1A = 0x00;
	TCCR1B = 0x06;
	
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	
	while(1)
	{
		do 
		{
			 i= TCNT1L;
			 j= TCNT1H;
			 
			  
			 sprintf(value, "%d", j*256+i);
			 send_char(value);
			 
			
			 
			 display = 0x01;
			 command();
			 
		} while ((TIFR &(0x1<<TOV1))==1);
		TIFR = 0x1 <<TOV1;
	}
}

void send_char(char *num)
{
	while(*num)
	{
		display = *num;
		DISPLAY();
		num++;
	}
}