/*
 * MAHOL.c
 *
 * Created: 14-08-2020 08:24:01 AM
 * Author : Shri
 */ 
  


#define F_CPU 8000000UL
#include <avr/io.h>
#include "util/delay.h"
#define MOSI 5
#define SCK 7
#define SS 4


void execute(unsigned char cmd, unsigned char data)
{
	PORTB &= ~(1<<SS);
	SPDR = cmd;
	while(!(SPSR & (1<<SPIF)));
	
	SPDR = data;
	
	while(!(SPSR & (1<<SPIF)));
	
	PORTB |= (1<<SS);
	
}

void segment_init(void)
{
	 DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS);
	 SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	 execute(0x09, 0xFF);
	 execute(0x0B, 0x03);
	 execute(0x0C, 0x0F);
	 execute(0x0A, 9);
}

void usart_send_packedBCD(unsigned char min)
{
	unsigned char min1, min2;
	/*min1 = 0x;
	min2 = min1>>4;*/
	execute(0x02, 0x05);
	_delay_ms(10);
	execute(0x03, (0x0F&min));
	_delay_ms(1);
	
}

void usart_send_packedBCD1(unsigned char data)
{
	unsigned char data1 = data;
	data = data>>4;
	execute(0x01, data);
	_delay_ms(1);
	execute(0x02, (0x0F&data1));
	_delay_ms(1);
	
	
}

void i2c_init(void)
{
	TWSR = 0x00;
	TWBR = 0x47;
	TWCR = 0x04;	
}

void i2c_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));	
}

void i2c_write(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

unsigned char i2c_read(unsigned char ackval)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (ackval<<TWEA);
	while(!(TWCR &(1<<TWINT)));
	return TWDR;	
}

void i2c_stop()
{
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
  for (int k = 0; k<100; k++)
  {
	  
  }
}

void rtc_init(void)
{
	i2c_init();
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x07);
	i2c_write(0x00);
	i2c_stop();

}

void rtc_setTime(unsigned char h, unsigned char m, unsigned char s)
{
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0x00);
	i2c_write(s);
	i2c_write(m);
	i2c_write(h);
	i2c_stop();
	
}

 


void rtc_getTime(unsigned char *h, unsigned char *m, unsigned char *s)
{
	i2c_start();
	i2c_write(0xD0);
	i2c_write(0);
	i2c_stop();
    
	i2c_start();
    i2c_write(0xD1);
	*s = i2c_read(1);
	*m = i2c_read(1);
	*h = i2c_read(0);
	i2c_stop();	
}

 


int main()
{
	 unsigned char i,j,k;
	 
	 rtc_init();
	 segment_init();
	 rtc_setTime(0x10, 0x18, 0x55);
	  
	   
	 rtc_getTime(&i, &j, &k);
	 //usart_send_packedBCD(i);
	  
	 usart_send_packedBCD(j);
	  
	 segment_init();
	while(1)
	{
		
	do
	 {
		rtc_getTime(&i, &j, &k);
		 usart_send_packedBCD1(k);
		   
	 }while(k != 0x00);
	
	
	 if (k==0x00)
	 {
		 usart_send_packedBCD(j); 
	 }
	 
	
	
	}
     return 0;
}

	