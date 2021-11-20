/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include<avr/io.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void command();
void com_com();
void com_data();
int main();
//End of Auto generated function prototypes by Atmel Studio



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
  PORTB = PORTB | (1<<0);
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
