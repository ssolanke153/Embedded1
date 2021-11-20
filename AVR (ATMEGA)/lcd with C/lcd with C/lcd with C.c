/*
 * lcd_with_C.c
 *
 * Created: 11-05-2020 15:27:37
 *  Author: Shri
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "lcd.h"


void LCDInit()
{

	LCD_CONTROL_DIRECTION |= (1<<LCD_RS);  
	LCD_CONTROL_DIRECTION |= (1<<LCD_RW);  
	LCD_CONTROL_DIRECTION |= (1<<LCD_E); 

	LCD_DATA_DIRECTION |= (1<<LCD_D4);  
	LCD_DATA_DIRECTION |= (1<<LCD_D5);  
	LCD_DATA_DIRECTION |= (1<<LCD_D6);  
	LCD_DATA_DIRECTION |= (1<<LCD_D7);  


	LCD_CONTROL_PORT &= ~(1<<LCD_RS);  
	LCD_CONTROL_PORT &= ~(1<<LCD_E);  
	_delay_ms(150);

	LCDSendCmd4BIT(0x03);  
	_delay_ms(150);
	LCDSendCmd4BIT(0x03);  
	_delay_ms(150);
	LCDSendCmd4BIT(0x03);  
	_delay_ms(150);

	LCDSendCmd4BIT(0x02);   
	LCDSendCmd(0x28);   
	      
	LCDOn();     
	LCDSendCmd(0x06);  
}



void LCDSendCmd(unsigned char ucCmd)
{
	 
	LCD_CONTROL_PORT &= ~(1<<LCD_RS);
	 
	LCDSendCmd4BIT(ucCmd>>4);
 
	
	LCDSendCmd4BIT(ucCmd);
}


void LCDSendData (unsigned char ucData)
{
	 
	LCD_CONTROL_PORT |= (1<<LCD_RS);
	 
	LCDSendCmd4BIT(ucData>>4);
	 
	
	LCDSendCmd4BIT(ucData);
}


void LCDSendCmd4BIT(unsigned char ucCmd)
{
	
	if(ucCmd&0x01) LCD_DATA_PORT |= (1<<LCD_D4);
	else LCD_DATA_PORT &= ~(1<<LCD_D4);

	if(ucCmd&0x02) LCD_DATA_PORT |= (1<<LCD_D5);
	else LCD_DATA_PORT &= ~(1<<LCD_D5);

	if(ucCmd&0x04) LCD_DATA_PORT |= (1<<LCD_D6);
	else LCD_DATA_PORT &= ~(1<<LCD_D6);

	if(ucCmd&0x08) LCD_DATA_PORT |= (1<<LCD_D7);
	else LCD_DATA_PORT &= ~(1<<LCD_D7);

	LCD_CONTROL_PORT |= (1<<LCD_E);
	LCD_CONTROL_PORT &= ~(1<<LCD_E);

	_delay_ms(2);
}

void LCDPutchar(char c)
{
	LCDSendData(c);
}

void LCDString(char *msg)
{
	uint8_t len = 0;

	while(*msg)
	{
		LCDPutchar(*msg);
		msg++;
		len++;
	}
	
}

int main(void)
{
   LCDInit();
  
  
  
//char name[]= "EARTH IS BUT ONE COUNTRY";
char line[50];
  

//unsigned char z=0, d=0, l=0;
float a = 0.5;
float b = 0.2, sum=0;
sum = a+b;

sprintf(line, "%f", sum);


 LCDString(line);



 
/*l = strlen(name);

 
	 for (z=0; z<l; z++)
	 {   
		 if (z==16)
		 {
			 LCDSendCmd(0xC0);  
			_delay_ms(10);
		 }
		 
		 d = name[z];
		 LCDSendData(d);
		 _delay_ms(10);
	 }
*/

return 0;
}