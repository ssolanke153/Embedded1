/*
 * analog_clock.c
 *
 * Created: 05-09-2020 09:03:20 AM
 * Author : Shri
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <gfx.h>

//include our already created header file for user level simplicity
#include "clock.h"

int main(void)
{


	//initialize the graphical lcd
	GFXInit();

	//write the function for drawing the clock
	Draw_clock(20,10,15);

	//update the graphical lcd
	GFXUpdate();

	//wait forever
	while(1)
	{

	}

}

