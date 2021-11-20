/*
 * ADC_advance.c
 *
 * Created: 16-07-2020 09:10:52 PM
 * Author : Shri
 */ 
 


#include <avr/io.h>
#include "adc.h"

void adc_init(void)
{
 /*
 ADMUX |= (1<<REFS0);                         // For Aref=AVcc 5v
 ADMUX &= ~(1<<REFS1);                // For Aref=AVcc 5v
 */
 
 ADMUX |= (1<<REFS0);                         // For Aref=AVcc 2.56v
 ADMUX |= (1<<REFS1);                // For Aref=AVcc 2.56v
  
 ADCSRA &= ~(1<<ADPS0); //Rrescalar div factor =64 - 011
 ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1); //Rrescalar div factor =64 - 011
}

uint16_t adc_read(uint8_t ch)
{
 //5 channel selection
 /*
 //channel 0 selection
 ADMUX &= ~(1<<MUX0);
 ADMUX &= ~(1<<MUX1);
 ADMUX &= ~(1<<MUX2);
 ADMUX &= ~(1<<MUX3);
 */
 
 //variable channel selection
 ADMUX = ((1<<REFS0)|(1<<REFS1)|ch); // variable ch and avcc reference 2.56
 
 
 
 ADCSRA |= (1<<ADSC);
 while ((ADCSRA&(1<<ADIF)) == 0);

 
 return ADCW;
}


int main()
{
	adc_init();
	return 0;
}


