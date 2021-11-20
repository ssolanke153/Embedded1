/*
 * 4BIT_LCD(Atmega328p).c
 *
 * Created: 05-08-2020 07:06:52 AM
 * Author : Shri
 */ 
# define F_CPU 8000000UL
 #include<avr/io.h>
 #include <util/delay.h>
 
 void lcd_init(void);
 void lcd_data(unsigned char data);
 void lcd_cmd(unsigned char data);
 void lcd_sendata(unsigned char data);
 
unsigned char data;
 int main()
 {

	 lcd_init();
	 lcd_data('S');
	 
	 return 0;
 }

 void lcd_init()
 {
	 DDRC = DDRB = 0xFF;

	 PORTC &= ~(1<<0);
	 PORTC &= ~(1<<1);
	 PORTC |= (1<<2);
	 PORTC &=(1<<2);
	 _delay_ms(10);
	 lcd_cmd(0x04);
	 _delay_ms(10);
	 lcd_cmd(0x028);
	 _delay_ms(10);
	 lcd_cmd(0x38);
	 _delay_ms(10);
	 lcd_cmd(0x01);
	 _delay_ms(10);
	 lcd_cmd(0x80);
	 _delay_ms(10);
	 lcd_cmd(0x0C);
	 _delay_ms(10);
	 lcd_cmd(0x06);
	 _delay_ms(10);
	 	 
 }


void lcd_data(unsigned char data)
{
  PORTC |= (1<<0);
  lcd_sendata(data>>4);
  lcd_sendata(data);
  
}

void lcd_cmd(unsigned char data)
{
	PORTC &= ~(1<<0);
	lcd_sendata(data<<4);
	lcd_sendata(data);
}


void lcd_sendata(unsigned char data)
{
	
	PORTB= data;
	PORTC |=(1<<2);
	PORTC &= ~(1<<2);
	
}