/*
 * ADC.c
 *
 * Created: 7/12/2020 1:02:30 PM
 * Author : Shri
 */ 

/*
#include <avr/io.h>


int main(void)
{
	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRA = 0;
	ADCSRA = 0x87;
	ADMUX = 0xC0; 
    
    while (1) 
    {
		ADCSRA |=(1<<ADSC);
		while((ADCSRA & (1<<ADIF))==0)
		{
			PORTD = ADCL;
			PORTB = ADCH;
		}
    }
    
	return 0;
}

*/

#include <avr/io.h>
#include <avr/interrupt.h>


ISR(ADC_vect)
{
	PORTD = ADCL;
	PORTB = ADCH;
	
	ADCSRA |= (1<<ADSC);
	
}


int main(void)
{
	
	DDRB = 0xFF;
	DDRD = 0xFF;
	
	DDRA =  0;
	
	sei();
	
	ADCSRA = 0x8F;
	ADMUX = 0xC0;
	
	ADCSRA |= (1<<ADSC);
	while(1);
	
	return 0;
}