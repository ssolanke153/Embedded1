/*
 * TFT_DISPLAY.c
 *
 * Created: 16-08-2020 09:42:17 AM
 * Author : Shri
 */ 

#define SS 4
#define MOSI 5
#define SCL 7
#define DCX 1
#define F_CPU 8000000UL

#define SWRESET 0x01                   // software reset 
#define SLPOUT  0x11                   // sleep out 
#define DISPOFF 0x28                   // display off 
#define DISPON  0x29                   // display on 
#define CASET   0x2A                   // column address set 
#define RASET   0x2B                   // row address set 
#define RAMWR   0x2C                   // RAM write
#define MADCTL  0x36                   // axis control 
#define COLMOD  0x3A                   // color mode

#define XSIZE   128 
#define YSIZE   160 
#define XMAX    XSIZE-1 
#define YMAX    YSIZE-1

// Color constants 
#define BLACK   0x0000 
#define BLUE    0x001F 
#define RED     0xF800 
#define GREEN   0x0400 
#define LIME    0x07E0 
#define CYAN    0x07FF 
#define MAGENTA 0xF81F 
#define YELLOW  0xFFE0 
#define WHITE   0xFFFF


#include <avr/io.h>                     // deal with port registers 
#include <avr/interrupt.h>              // deal with interrupt calls 
#include <avr/pgmspace.h>               // put character data into progmem 
#include <util/delay.h>                 // used for _delay_ms function 
#include <string.h>                     // string manipulation routines 
#include <avr/sleep.h>                  // used for sleep functions 
#include <stdlib.h>


typedef uint8_t byte;
typedef int8_t sbyte;


const byte FONT_CHARS[96][5]  = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // (space)
	{ 0x00, 0x00, 0x5F, 0x00, 0x00 }, // !
	{ 0x00, 0x07, 0x00, 0x07, 0x00 }, // "
	{ 0x14, 0x7F, 0x14, 0x7F, 0x14 }, // #
	{ 0x24, 0x2A, 0x7F, 0x2A, 0x12 }, // $
	{ 0x23, 0x13, 0x08, 0x64, 0x62 }, // %
	{ 0x36, 0x49, 0x55, 0x22, 0x50 }, // &
	{ 0x00, 0x05, 0x03, 0x00, 0x00 }, // '
	{ 0x00, 0x1C, 0x22, 0x41, 0x00 }, // (
	{ 0x00, 0x41, 0x22, 0x1C, 0x00 }, // )
	{ 0x08, 0x2A, 0x1C, 0x2A, 0x08 }, // *
	{ 0x08, 0x08, 0x3E, 0x08, 0x08 }, // +
	{ 0x00, 0x50, 0x30, 0x00, 0x00 }, // ,
	{ 0x08, 0x08, 0x08, 0x08, 0x08 }, // -
	{ 0x00, 0x60, 0x60, 0x00, 0x00 }, // .
	{ 0x20, 0x10, 0x08, 0x04, 0x02 }, // /
	{ 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 0
	{ 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 1
	{ 0x42, 0x61, 0x51, 0x49, 0x46 }, // 2
	{ 0x21, 0x41, 0x45, 0x4B, 0x31 }, // 3
	{ 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 4
	{ 0x27, 0x45, 0x45, 0x45, 0x39 }, // 5
	{ 0x3C, 0x4A, 0x49, 0x49, 0x30 }, // 6
	{ 0x01, 0x71, 0x09, 0x05, 0x03 }, // 7
	{ 0x36, 0x49, 0x49, 0x49, 0x36 }, // 8
	{ 0x06, 0x49, 0x49, 0x29, 0x1E }, // 9
	{ 0x00, 0x36, 0x36, 0x00, 0x00 }, // :
	{ 0x00, 0x56, 0x36, 0x00, 0x00 }, // ;
	{ 0x00, 0x08, 0x14, 0x22, 0x41 }, // <
	{ 0x14, 0x14, 0x14, 0x14, 0x14 }, // =
	{ 0x41, 0x22, 0x14, 0x08, 0x00 }, // >
	{ 0x02, 0x01, 0x51, 0x09, 0x06 }, // ?
	{ 0x32, 0x49, 0x79, 0x41, 0x3E }, // @
	{ 0x7E, 0x11, 0x11, 0x11, 0x7E }, // A
	{ 0x7F, 0x49, 0x49, 0x49, 0x36 }, // B
	{ 0x3E, 0x41, 0x41, 0x41, 0x22 }, // C
	{ 0x7F, 0x41, 0x41, 0x22, 0x1C }, // D
	{ 0x7F, 0x49, 0x49, 0x49, 0x41 }, // E
	{ 0x7F, 0x09, 0x09, 0x01, 0x01 }, // F
	{ 0x3E, 0x41, 0x41, 0x51, 0x32 }, // G
	{ 0x7F, 0x08, 0x08, 0x08, 0x7F }, // H
	{ 0x00, 0x41, 0x7F, 0x41, 0x00 }, // I
	{ 0x20, 0x40, 0x41, 0x3F, 0x01 }, // J
	{ 0x7F, 0x08, 0x14, 0x22, 0x41 }, // K
	{ 0x7F, 0x40, 0x40, 0x40, 0x40 }, // L
	{ 0x7F, 0x02, 0x04, 0x02, 0x7F }, // M
	{ 0x7F, 0x04, 0x08, 0x10, 0x7F }, // N
	{ 0x3E, 0x41, 0x41, 0x41, 0x3E }, // O
	{ 0x7F, 0x09, 0x09, 0x09, 0x06 }, // P
	{ 0x3E, 0x41, 0x51, 0x21, 0x5E }, // Q
	{ 0x7F, 0x09, 0x19, 0x29, 0x46 }, // R
	{ 0x46, 0x49, 0x49, 0x49, 0x31 }, // S
	{ 0x01, 0x01, 0x7F, 0x01, 0x01 }, // T
	{ 0x3F, 0x40, 0x40, 0x40, 0x3F }, // U
	{ 0x1F, 0x20, 0x40, 0x20, 0x1F }, // V
	{ 0x7F, 0x20, 0x18, 0x20, 0x7F }, // W
	{ 0x63, 0x14, 0x08, 0x14, 0x63 }, // X
	{ 0x03, 0x04, 0x78, 0x04, 0x03 }, // Y
	{ 0x61, 0x51, 0x49, 0x45, 0x43 }, // Z
	{ 0x00, 0x00, 0x7F, 0x41, 0x41 }, // [
	{ 0x02, 0x04, 0x08, 0x10, 0x20 }, // "\"
	{ 0x41, 0x41, 0x7F, 0x00, 0x00 }, // ]
	{ 0x04, 0x02, 0x01, 0x02, 0x04 }, // ^
	{ 0x40, 0x40, 0x40, 0x40, 0x40 }, // _
	{ 0x00, 0x01, 0x02, 0x04, 0x00 }, // `
	{ 0x20, 0x54, 0x54, 0x54, 0x78 }, // a
	{ 0x7F, 0x48, 0x44, 0x44, 0x38 }, // b
	{ 0x38, 0x44, 0x44, 0x44, 0x20 }, // c
	{ 0x38, 0x44, 0x44, 0x48, 0x7F }, // d
	{ 0x38, 0x54, 0x54, 0x54, 0x18 }, // e
	{ 0x08, 0x7E, 0x09, 0x01, 0x02 }, // f
	{ 0x08, 0x14, 0x54, 0x54, 0x3C }, // g
	{ 0x7F, 0x08, 0x04, 0x04, 0x78 }, // h
	{ 0x00, 0x44, 0x7D, 0x40, 0x00 }, // i
	{ 0x20, 0x40, 0x44, 0x3D, 0x00 }, // j
	{ 0x00, 0x7F, 0x10, 0x28, 0x44 }, // k
	{ 0x00, 0x41, 0x7F, 0x40, 0x00 }, // l
	{ 0x7C, 0x04, 0x18, 0x04, 0x78 }, // m
	{ 0x7C, 0x08, 0x04, 0x04, 0x78 }, // n
	{ 0x38, 0x44, 0x44, 0x44, 0x38 }, // o
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 }, // p
	{ 0x08, 0x14, 0x14, 0x18, 0x7C }, // q
	{ 0x7C, 0x08, 0x04, 0x04, 0x08 }, // r
	{ 0x48, 0x54, 0x54, 0x54, 0x20 }, // s
	{ 0x04, 0x3F, 0x44, 0x40, 0x20 }, // t
	{ 0x3C, 0x40, 0x40, 0x20, 0x7C }, // u
	{ 0x1C, 0x20, 0x40, 0x20, 0x1C }, // v
	{ 0x3C, 0x40, 0x30, 0x40, 0x3C }, // w
	{ 0x44, 0x28, 0x10, 0x28, 0x44 }, // x
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C }, // y
	{ 0x44, 0x64, 0x54, 0x4C, 0x44 }, // z
	{ 0x00, 0x08, 0x36, 0x41, 0x00 }, // {
	{ 0x00, 0x00, 0x7F, 0x00, 0x00 }, // |
	{ 0x00, 0x41, 0x36, 0x08, 0x00 }, // }
	{ 0x08, 0x08, 0x2A, 0x1C, 0x08 }, // ->
	{ 0x08, 0x1C, 0x2A, 0x08, 0x08 } // <-
};




void sendcmd(unsigned char cmd)
{
	PORTB &= ~(1<<SS);
	PORTD &= ~(1<<DCX);
	SPDR = cmd;
	while(!(SPSR & (1<<SPIF)));
	PORTB |= (1<<SS);
	
}

void sendata(unsigned char data)
{
	PORTB &= ~(1<<SS);
	PORTB |= (1<<DCX);
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	PORTB |= (1<<SS);
}

void rst()
{
	PORTB &= ~(1<<0);
	_delay_ms(1);
	
	PORTB |= (1<<0);
	_delay_ms(250);
}

void writeword(int w)
{
	sendata(w>>8);
	sendata(w & 0xFF);
}

void SetAddrwindow(byte x0, byte y0, byte x1, byte y1)
{
	sendcmd(CASET);
	writeword(x0);
	writeword(x1);
	sendcmd(RASET);
	writeword(y0);
	writeword(y1);
}



void write565(int data, unsigned int count)
{
	sendcmd(RAMWR);
	
	for (;count>0;count--)
	{
		sendata(data>>8);
		sendata(data&0xFF);
	}
}


void DrawPixel(byte x, byte y, int color)
{
	SetAddrwindow(x,y,x,y);
	write565(color, 1);
}

void Line (int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;     
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;     
	int err = (dx>dy ? dx : -dy)/2, e2;         
	for(;;)
	
	   {         
		   DrawPixel(x0,y0,color);         
		   if (x0==x1 && y0==y1) 
		   {
			   break;
			}         
			e2 = err;         
			if (e2 >-dx) { 
				err -= dy; x0 += sx; 
				}   
			if (e2 < dy) 
			{ 
				err += dx; y0 += sy; 
				}    
			} 
				 
	
}

void ClearScreen()
{
	SetAddrwindow(0,0,XMAX, YMAX);
	sendcmd(RAMWR);
	
	for (unsigned int i = 40960; i>0; --i)
	{
		SPDR = 0;
		while(!(SPSR & 0x80));
	}
}


void LineTest()
{
	ClearScreen();
	int x,y, x0=64, y0=80;
	
	for (x=0;x<XMAX;x+=2)
	{
		 Line(x0,y0,x,0,YELLOW);
	}
	
	 for (y=0;y<YMAX;y+=2) 
	 {
		 Line(x0,y0,XMAX,y,CYAN);
		 }     
	for (x=XMAX;x>0;x-=2)
	 {
		Line(x0,y0,x,YMAX,YELLOW);  
	  }   
	for (y=YMAX;y>0;y-=2) 
	{
		Line(x0,y0,0,y,CYAN);
	}     
	_delay_ms(2000); 
	
	
}

void Putch(char ch, byte x, byte y, int color)
{
	int pixel;
	byte row, col, bit, data, mask = 0x01;
	SetAddrwindow(x,y,x+4,y+6);
	sendcmd(RAMWR);
	
	for (row =0;row<7;row++)
	{
		for (col=0; col<5;col++)
		{
			data = pgm_read_byte(&(FONT_CHARS[ch-32][col]));
			bit = data & mask;
			
			if (bit==0)
			{
				pixel = BLACK;
				
			}
			else{
				pixel=color;
			}
			writeword(pixel);
		}
		mask <<=1;
	}
}






void PortraitChars()
{
  ClearScreen();
  
  for (int i=420;i>0;i--)
  {
	  byte x = i % 21;
	  byte y = i/21;
	  char ascii = (i % 96) +32;
	  Putch(ascii, x*6, y*8, CYAN);
  }
  _delay_ms(2000);
}

int main(void)
{
	DDRB |= (1<<SS) | (1<<MOSI) | (1<<SCL) | (1<<DCX);;
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	
	rst();
	sendcmd(0x11); //sleep out
	_delay_ms(150);
	sendcmd(0x29); //display on
	sendcmd(0x2D); //color mode on 
	sendata(0x05); // mode = 5
	PortraitChars();
	LineTest();
   
}

