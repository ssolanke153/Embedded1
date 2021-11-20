/*
 * lcd.h
 *
 * Created: 21-04-2021 05:43:29 PM
 *  Author: Shri
 */ 

 
#include <util/delay.h>
#define display PORTA
#define  RS 0
#define  RW 1
#define  E  2

void command()
{


	PORTB=PORTB & ~ (1<<RS);
	PORTB=PORTB & ~ (1<<RW) ;
	PORTB=PORTB  | (1<<E);
	PORTB=PORTB & ~(1<<E);
	_delay_ms(10);

}

void lcd_init()
{
	DDRA = DDRB = 0xFF;
	
	display=0x38;
	command();

	display=0x01;
	command();

	display=0x0C;
	command();

	display=0x06;
	command();

	display=0x8F;
	command();
	
	display = 0x07;
	command();
}


void DISPLAY()
{
	

	PORTB=PORTB | (1<<RS);
	PORTB=PORTB & ~ (1<<RW);
	PORTB=PORTB  | (1<<E);
	PORTB=PORTB & ~(1<<E);
	_delay_ms(10);
}