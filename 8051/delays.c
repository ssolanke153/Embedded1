/* USING TIMER 0,MODE 1 CREATE A DELAY OF 1 SECOND*/

/*#include<reg51.h>
void delay(void);

sbit mybit=P1^0;
void main(void)
{	
	
	mybit=0x00;
	while(1)
	{
		 mybit=~mybit;
		 delay();
		
	} 	
}
void delay()
{
	unsigned  char x,y;
	for(x=0;x<210;x++)
	{
   for(y=0;y<250;y++)
		{
		TMOD= 0x01;
			TH0=0xFF;
	 	  TL0=0xE9;
		TR0=1;
		while(TF0==1)
		{
		  TF0=0;
			TR0=0;
		} 
	}
}
	
*/


/* USING TIMER 0 , MODE 2 CREATE A DELAY OF 1 SECOND*/


#include<reg51.h>
void delay();

void main()
{
  P1=0x00; 
	
	while(1)
	{
		 P1=~P1;
		delay();
		
	}

}

void delay()
{
   
	unsigned char x,y;
	
	for(x=0;x<232;x++)
	{
		for(y=0;y<250;y++)
		{
		TMOD=0x01;
		TH0=-250;
		TR0=1;
		while(TF0==1)
		{
		  TF0=0;
			TR0=0;
		
		}
	}
	}
	

}
