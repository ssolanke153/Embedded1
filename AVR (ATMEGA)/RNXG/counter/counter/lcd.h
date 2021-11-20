/*
 * lcd.h
 *
 * Created: 15-04-2021 05:06:37 PM
 *  Author: Shri
 */ 


/*
 * lcd.h
 *
 * Created: 12-04-2021 04:17:26 PM
 *  Author: Shri
 */ 


 


#define  F_CPU 8000000UL
#include <util/delay.h>
#define display PORTD
#define  RS 0
#define  RW 1
#define  E  2

void command()
{


	PORTC=PORTC & ~ (1<<RS);
	PORTC=PORTC & ~ (1<<RW) ;
	PORTC=PORTC  | (1<<E);
	PORTC=PORTC & ~(1<<E);
	_delay_ms(10);

}

void lcd_init()
{
   DDRD = DDRC = 0xFF;
	
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
 

	PORTC=PORTC | (1<<RS);
	PORTC=PORTC & ~ (1<<RW);
	PORTC=PORTC  | (1<<E);
	PORTC=PORTC & ~(1<<E);
	_delay_ms(10);
}