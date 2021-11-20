/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */
/*#include<avr/io.h>
#include<util/delay.h>

#define LED 5
int main()
{
  DDRB = DDRB | (1<<LED);
  PORTB = PORTB & ~(1<<LED);
   
  
  while(1)
  {
    
    PORTB = ~PORTB;
    
    _delay_ms(200);
      
   
  }
}
*/



/*#include<avr/io.h>
#include <Arduino.h>
//Beginning of Auto generated function prototypes by Atmel Studio
int main();
//End of Auto generated function prototypes by Atmel Studio



void command();
void com_com();
void com_data();

void command()
{
  
  PORTD = 0x38;
  com_com();
  
  PORTD = 0x01;
  com_com();
  
  PORTD = 0x06;
  com_com();
  
  PORTD = 0x0C;
  com_com();
  

}

void com_com()
{
  PORTB = PORTB & ~(1<<0);
  PORTB = PORTB & ~(1<<1);
  PORTB = PORTB | (1<<2);
  PORTB = PORTB & ~(1<<2);
  
}

void com_data()
{
  PORTB = PORTB & ~(1<<0);
  PORTB = PORTB & ~(1<<1);
  PORTB = PORTB | (1<<2);
  PORTB = PORTB & ~(1<<2);
  
}

int main()
 {
  
   DDRD = 0xFF;
   DDRB = 0xFF;
   DDRC = 0x00;
  
   command();
   ADCSRA = 0x87;
   ADMUX = 0xE0;
  
  while(1)
  {
    ADCSRA |=(1<<ADSC);
    while((ADCSRA & (1<<ADIF))==0)
    {
     PORTD = ADCH;
      com_data();
    }
  
  }
 return 0;
}
*/


#include<avr/io.h>
#include <util/delay.h>
//#include <Arduino.h>


int main()
{
	
	int i=255;
  DDRD |= (1<<5) | (1<<4) | (1<<7);
  
  
  TCCR0A = 0x23;
  TCCR0B = 0x01;
  
  while(1)
  {
	  if (i == 0)
	  {
		  i=255;
	  }
	  OCR0B = i;
    PORTD = PORTD | (1<<4);
    PORTD = PORTD & ~(1<<7);
	i--;
	_delay_ms(100);
  
  }
  
}


