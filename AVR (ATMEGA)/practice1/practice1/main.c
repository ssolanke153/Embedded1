/*
 * practice1.c
 *
 * Created: 12-05-2020 12:52:55
 * Author : Shri
 */



/* Q1. WRITE AN AVR PROGRAM TO MONITOR BIT 7 OF PORT B. IF IT IS 1, MAKE BIT 4 OF PORT B INPUT; ELSE, CHANGE PIN 4 OF PORT B TO OUTPUT.*/


//#include <avr/io.h>
//
//
//int main(void)
//{
	//DDRB = DDRB | ~(1<<7);
//
    //while (1)
    //{
		//if (PINB & ~(1<<7))
		//{
			 //DDRB = DDRB & ~(1<<4);
		//}
		//else
		 //{
		   //DDRB = DDRB | (1<<4);
//
		 //}
    //}
//}

/* Q2. WRITE AN AVR C  PROGRAM TO GET THE STATUS OF BIT 5 OF PORT B AND SEND IT TO BIT 7 OF PORT C CONTINUOSLY.*/

//#include <avr/io.h>
//
//int main()
//{
	//DDRB = DDRB & ~(1<<5);
	//DDRC = DDRC | (1<<7);
//
	//while(1)
	//{
//
		//if (PINB & (1<<5) )
		//{
			 //PORTC = PORTC | (1>>7);
		//}
		//else
		      //PORTC = PORTC & ~(1<<7);
//
	//}
	//return 0;
//}



