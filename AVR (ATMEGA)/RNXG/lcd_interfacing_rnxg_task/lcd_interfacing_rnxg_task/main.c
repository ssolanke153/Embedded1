/*
 * lcd_interfacing_rnxg_task.c
 *
 * Created: 19-04-2021 08:55:25 AM
 * Author : Shri
 */ 

 


#include <avr/io.h>
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
	
	display=0x38;  // selecting the 2 line 5x7 matrix
	command();

	display=0x01;  // clear the lcd display. 
	command();

	display=0x0C;  // cursor off display on. 
	command();

	display=0x06;  // increment cursor
	command();

	display=0x80;  // cursor at beginning of first line. 
	command();
}


void DISPLAY(char ch)
{
 
    display = ch;

	PORTB=PORTB | (1<<RS);    // making 1 to send data. 
	
	PORTB=PORTB & ~ (1<<RW);  // set to 0 as we want to write. 
	
	PORTB=PORTB  | (1<<E);    // making LOW to
	PORTB=PORTB & ~(1<<E);    // HIGH
	
	_delay_ms(10);
}


int main()
{
	char z[] = "Hello World!";
	int i  = 0;
	
	lcd_init();
	
	while(z[i])
	{
		DISPLAY(z[i]);
		i++;
	}
	
	
}