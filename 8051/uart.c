#include<reg51.h>
#include "lcd.h"



 
char b;
void uart_init();
void delay(unsigned  int);
void uart_send(char);
 

 

void serialinterrupt () interrupt 4
{
		if (TI ==1)
		{
			TI=0;
		}
		
		else 
		{
			b = SBUF;
			RI =0;
			send_char(b);
		}
}



// STARTING OF MAIN FUNCTION 

	void main(void)
	{
	
		char *z  = "Are you get data\r";
		unsigned int a=0;
		
		
			
		uart_init();
			
		lcd_init();
	  
	  uart_send(*z);
		
		while(1)
		{}
	 
	} 


void uart_init()
{
	  TMOD=0x20;
			
		TH1=0xFD;
			
		SCON=0x50;
			
		IE=0x92;    //ENABLE SERIAL INTERRUPT
			
		TR1=1;
	
}
	
	
	void uart_send(char *ch)
	{
		
		while(*ch)
		{
			SBUF = *ch;
			
			while(TI==0);
			ch++;
		}
		
	}


	
	 