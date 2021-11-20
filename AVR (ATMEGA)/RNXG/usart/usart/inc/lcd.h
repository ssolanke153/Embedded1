/*
 * lcd.h
 *
 * Created: 12-04-2021 03:59:33 AM
 *  Author: Shri
 */ 



#define  F_CPU 8000000UL
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

	display=0x80;
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