/*
 * toggle.c
 *
 * Created: 10-05-2020 4.02.48 PM
 * Author : Shri
 */ 

#include <avr/io.h>
#include "util/delay.h"

int main(void)
{
    unsigned char mylist[]={-4,-3,-2,-1,0,1,2,3,4};
	unsigned char z;

	DDRB =0xFF;
   
	for (z=0;z<=8;z++)
	{
		PORTB=mylist[z];
	}
     
	return 0;
}

