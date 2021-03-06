/*
 * clci_new_way.c
 *
 * Created: 04-08-2020 04:30:55 PM
 * Author : Shri
 */ 
 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <string.h>
#include<stdio.h>
#include "util/delay.h"

#define  KEY_PRT PORTC
#define  KEY_DDR DDRC
#define  KEY_PIN PINC
#define  display  PORTD		  
unsigned char z = 0,acc=0;
 
unsigned char keypad[4][4] =  {'7', '8', '9', '/',
	                          '4', '5', '6', '*',
							  '1', '2', '3', '-',
							  'C', '0', '=', '+'};
							  
float a,b,c,d,q,p,r,s;							  
void command()
{


	PORTB=PORTB & ~ (1<<0);
	PORTB=PORTB & ~ (1<<1) ;
	PORTB=PORTB  | (1<<2);
	PORTB=PORTB & ~(1<<2);
	_delay_ms(10);

}

void COMMAND()
{
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

	PORTB=PORTB | (1<<0);
	PORTB=PORTB & ~ (1<<1);
	PORTB=PORTB  | (1<<2);
	PORTB=PORTB & ~(1<<2);
	_delay_ms(1);
}							  
							  
void convert_1();
void convert_2();
void add();
void anti_conv();	
void sub();	
void mul();	
void div();	
void two_digit_1();
void two_digit_2();			  
							  
int main(void)

{
    
	unsigned char colloc, rowloc;
	unsigned char count=0;
	DDRD=DDRB = 0xFF;
	KEY_DDR = 0xF0;
	KEY_PRT = 0xFF;
	
	COMMAND();
	
    while (1) 
    {
		do 
		{
			KEY_PRT &= 0x0F;
			colloc = (KEY_PIN & 0x0F);
		} while (colloc !=0x0F);
		
		do
		{
	      do 
	      {
			  _delay_ms(20);
			  colloc = (KEY_PIN & 0x0F);
	      } while (colloc == 0x0F);
		  
		  _delay_ms(20);
		  colloc = (KEY_PIN & 0x0F);
		}while(colloc == 0x0F);
		
		while(1)
		{
			KEY_PRT = 0xEF;
			colloc = (KEY_PIN & 0x0F);
			
			if (colloc != 0x0F)
			{
				rowloc = 0;
				break;
			}
			
			KEY_PRT = 0xDF;
			colloc = (KEY_PIN & 0x0F);
			
			if (colloc != 0x0F )
			{
				rowloc = 1;
				break;
			}
			KEY_PRT = 0xBF;
			colloc = (KEY_PIN & 0x0F);
			
			if (colloc !=0x0F)
			{
				rowloc = 2;
				break;
			}
			
			KEY_PRT = 0x7F;
			colloc  = (KEY_PIN & 0x0F);
			rowloc = 3;
			break;
		}
		
		if (colloc == 0x0E)
		{
			acc = (keypad[rowloc][0]);
			 
		} 
		else if (colloc == 0x0D)
		{
			acc = (keypad[rowloc][1]);
			 
		}
		else if (colloc == 0x0B)
		{
			acc = (keypad[rowloc][2]);
			 
		}
		else 
		{
			acc = (keypad[rowloc][3]);
			 
		}
		
		display = acc;
		DISPLAY();
		
		if (acc == 'C')
		{   
			count = 0;
			z=0;
			COMMAND();
			continue;
		}
		
		if (acc ==0x3D)
		{
			 
			anti_conv();
			continue;
		}
		
		if (acc == '+' || acc == '-' || acc == '*' || acc == '/')
		{   
			z=1;
			d = acc;
			continue;
		}
		
		
		
		if(acc=='0' || acc == '1' || acc == '2' || acc == '3' || acc == '4'
		|| acc == '5' || acc == '6' || acc == '7' || acc == '8' || acc == '9' )
		{
			count++;
		}
			
		
		if (count == 1 && z==0)
		{
			convert_1(acc);
			
		} 
		else if (count == 2 && z==0)
		{
			p = acc & 0x0F;
			two_digit_1();
		}
		else if((count == 3 && z == 1) || (count == 2 && z == 1))
		{
			convert_2(acc);
			z=2;
		}
		else if ((count == 4 && z==2) || (count == 3 && z == 2))
		{
			r = acc & 0x0F;
			two_digit_2();
			
		}
			
    }
	return 0;
}


// STARTING OF OPERATION



void convert_1()
{
	a = acc & 0x0F;
	 	
}

void two_digit_1()
{
	a = a*10;
	q = a+p;
}

void two_digit_2()
{
	b = b*10;
	s = b+r;
}
void convert_2()
{
	b = acc & 0x0F;
	 
	
	if (d== 0x2B)
	{
		add();
	}
	else if (d == 0x2D)
	{
		sub();
	}
	else if (d == 0x2A)
	{
		mul();
	}
	
	else
	{
		div();
	}
 
	
}

void add()
{
	c = q+s;	 
}

void sub()
{
	c = q-s;
}

void mul()
{
	c = q*s;
}

void div()
{
	c = q/s;
}
void anti_conv()
{
	 char d1[4];
	 c = 2;
	  
	  /*d1 = c/10;
	  d2 = c%10;
	  
	  d1 = 0x30 | d1;
	  d2 = 0x30 | d2;
	 */
	
	sprintf(d1, "%.2f", c);
	
	 for (int i=0; i<2; i++)
	 {
		 display = d1[i];
		 DISPLAY();
		 
	 }
		
	 
	
	
	
	/*display = d2;
	DISPLAY();*/
	
	
	
}
