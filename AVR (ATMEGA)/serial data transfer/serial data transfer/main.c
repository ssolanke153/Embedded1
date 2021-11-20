/*
 * serial data transfer.c
 *
 * Created: 13-05-2020 09:43:37
 * Author : Shri
 */ 

#include <avr/io.h>


int main(void)
{
  
    while (EECR & (1<<EEWE));
    
		EEARH=0x00;
		EEARL = 0xFF;
		EEDR='D';
		EECR |=(1<<EEMWE);
		EECR |=(1<<EEWE);
		
    
}

