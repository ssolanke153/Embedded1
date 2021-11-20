/*
 * 8BIT_TFT.c
 *
 * Created: 07-09-2020 04:27:33 PM
 * Author : Shri
 */ 
  
#define SS 4
 
#define WRX 2
#define DCX 1
#define RDX 3
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#define clearbit(x,y) x &= ~(1<<y)
#define setbit(x,y) x |= (1<<y)
typedef uint8_t byte;                   // I just like byte & sbyte better 
typedef int8_t sbyte;
#define  display PORTD


void writebyte(byte b, byte d)
{
	PORTB |= (1<<SS);
	PORTB &= ~(1<<SS);
	PORTB |= (1<<DCX);
	PORTB |=(1<<RDX);
	PORTB &= ~(1<<WRX);
    display = b;
	PORTB |= (1<<WRX);
	PORTB &=(1<<WRX);
	 
	display = d;
	PORTB |=(1<<WRX);
	PORTB |= (1<<SS);
}

void writecmd(byte cmd)
{
	PORTB &= ~(1<<SS);
	 
	PORTB &= ~(1<<DCX);
	PORTB |=(1<<RDX); 
	PORTB &= ~(1<<WRX);
	
	display = cmd;
	PORTB |=(1<<WRX);
	PORTB |= (1<<DCX);  
	PORTB |= (1<<SS); 
}

void rst()
{
	clearbit(PORTB, 0);
	
	_delay_ms(1);
setbit(PORTB, 0);
	_delay_ms(200);
	
}

void init()

{
	rst();
	writecmd(0x11);
	_delay_ms(15);
	writecmd(0x29);
	 
	 
	 
}
int main(void)
{
	 DDRB=DDRD = 0xFF;
    
	
	init();
 
	writecmd(0x2A); // send Column Address Set command (DC line low)
	writebyte(0x00,0x00 ); // send 1st Parameter, SC[15:8] (DC line high)
	                      // send 2st Parameter, SC[7:0]
	writebyte(0x00, 0xEF); // send 3st Parameter, EC[15:8]
	 
	
	writecmd(0x2B);
	writebyte(0x00,0x00);
	 
	writebyte(0x00, 0x3F);
	 
	
	writecmd(0x2C);
 while(1)
 {
	writebyte(0xF8, 0x00);
	writebyte(0xF9, 0x00); 
	 
	// writecmd(0x21);
	//writebyte(0x00,0x00);
 }
}


