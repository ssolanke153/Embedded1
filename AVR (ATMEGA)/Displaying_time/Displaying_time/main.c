/*
 * Displaying_time.c
 *
 * Created: 24-07-2020 05:05:08 PM
 * Author : Shri
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include "util/delay.h"

#define display PORTD 

void time_date(void);

void cmd(void)
{
	PORTB &= ~(1<< 0);
	PORTB &= ~(1<<1);
	PORTB |= (1<<2); 
	PORTB &= ~(1<<2);
	_delay_ms(2);
	
}

void send_data(void)
{
	PORTB |= (1<< 0);
	PORTB &= ~(1<<1);
	PORTB |= (1<<2);
	PORTB &= ~(1<<2);
	_delay_ms(2);
}



void lcd_init(void)
{
	DDRD = DDRB = 0xFF;
	
	display = 0x38;
	cmd();
	
	display = 0x80;
	cmd();
	
	display = 0x0C;
	cmd();
	
	display = 0x06;
	cmd();	
}

void lcd_send(unsigned char data)
{
	display = data;
	send_data();
	
}


void lcd_send_packedBCD(unsigned char data)
{
	lcd_send(0x30 | (data>>4));
	lcd_send(0x30 | (data & 0x0F));
	
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

void i2c_write(unsigned char data)  // START OF I2C FOR COMMUNICATION WITH DS1307
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
	i2c_init();      // Initialize I2C module.
	i2c_start();     // Transmit START Condition.
	i2c_write(0xD0); // address DS1307 for write.
	i2c_write(0x07); // Set register pointer to 7.
	i2c_write(0x00); // Set value of location 7 to 0
	i2c_stop();      // STOP I2C module.

}

void rtc_setTime(unsigned char h, unsigned char m, unsigned char s)
{
	i2c_start();     // Transmit START Condition.
	i2c_write(0xD0); // Address DS1307 for write.
	i2c_write(0x00); // Set register pointer to 0.
	i2c_write(s);    // Set seconds.
	i2c_write(m);    // Set minutes.
	i2c_write(h);    // Set hour.
	i2c_stop();      // Transmit STOP Condition.
	
}

void rtc_setDate(unsigned char y,  unsigned char m, unsigned char d)
{
	i2c_start();     // Transmit START Condition.
	i2c_write(0xD0); // Address DS1307 for write.
	i2c_write(0x04); // Set register pointer to 4.
	i2c_write(d);    // Set day.
	i2c_write(m);    // Set month.
	i2c_write(y);    // Set year.
	i2c_stop();      // Transmit STOP Condition.
	
}


void rtc_getTime(unsigned char *h, unsigned char *m, unsigned char *s)
{
	i2c_start();     // Transmit START Condition.
	i2c_write(0xD0); // Address DS1307 for write.
	i2c_write(0);    // Set register pointer to 0.
	i2c_stop();      // Transmit STOP Condition.
    
	i2c_start();      // Transmit START Condition.
    i2c_write(0xD1);  // Address DS1307 for read.
	*s = i2c_read(1); // Read second, return ACKNOWLEDGE
	*m = i2c_read(1); // Read minute, return ACKNOWLEDGE
	*h = i2c_read(0); // Read hour, return ACKNOWLEDGE
	i2c_stop();	       // Transmit STOP Condition.
}

void rtc_getDate(unsigned char *y, unsigned char *m, unsigned char *d)
{
	i2c_start();       // Transmit START Condition.
	i2c_write(0xD0);   // Address DS1307 for read.
	i2c_write(0x04);   // Set register pointer to 4.
	i2c_stop();        // Transmit STOP Condition.
	   
	i2c_start();       // Transmit START Condition.
	i2c_write(0xD1);    // Address DS1307 for read.
	*d = i2c_read(1);   // Read  day, return ACKNOWLEDGE
	*m = i2c_read(1);   // Read month, return ACKNOWLEDGE
	*y = i2c_read(0);   // Read year, return ACKNOWLEDGE
	i2c_stop();         // Transmit STOP Condition.
}


int main()
{
	 unsigned char i,j,k;
	 rtc_init();
	 rtc_setTime(0x10, 0x01, 0x30); // 10:01:30 (HH:MM:SS)
	 rtc_setDate(0x14, 0x08, 0x20); // 09:01:10 (YY:MM:DD)
	 lcd_init();
	 
	time_date();
	 
	 display = 0x87;
	 cmd(); 
		 
	 
	 rtc_getTime(&i, &j, &k);
	 lcd_send_packedBCD(i);
	 lcd_send(':');
	 lcd_send_packedBCD(j);
	 lcd_send(':');
	
	display = 0xC7;
	cmd();
	
	 rtc_getDate(&i, &j, &k);
	 lcd_send_packedBCD(i);
	 lcd_send(':');
	 lcd_send_packedBCD(j);
	 lcd_send(':');
	 lcd_send_packedBCD(k);
	
	while(1)
	{
		
	
	do
	 {
		rtc_getTime(&i, &j, &k);

		display = 0x8D;
		cmd();

		 lcd_send_packedBCD(k);
		   
	 }while(k != 0X00);
	
	 if (k==0x00)
	 {
		 display = 0x8A;
		 cmd(); 
		 lcd_send_packedBCD(j);
		 lcd_send(':');
	 }
	 
	 
	 if (j==0x00)
	 {
		 display = 0x87;
		 cmd();
       lcd_send_packedBCD(i);
	   lcd_send(':');
	 }
	 
	  
	 }
	 
     return 0;
}

void time_date()
{
	unsigned char z[14] = "TIME : DATE : " ;
	
	for (int d=0; d<14; d++)
	{
		if (d==7)
		{
			display = 0xC0;
			cmd();
		}
		 
		lcd_send(z[d]);
		 
	}
}
