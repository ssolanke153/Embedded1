/*
 * lcd.h
 *
 * Created: 25-04-2021 02:14:51 PM
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