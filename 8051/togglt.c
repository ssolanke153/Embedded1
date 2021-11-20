/*#include<reg51.h>

void tmdelay(void);

void main()
{
  unsigned char x;
	P1=0x55;
	while(1)
	{
	  P1=~P1;
		for(x=0;x<20;x++)
		{
		  tmdelay();
		}
	}
}

void tmdelay(void)
{
  TMOD =0x10;
	TL1=0xFE;
	TH1=0xA5;
	TR1=1;
	while(TF1==0)
	{
	  TR1=0;
		TF1=0;
	}
}*/

/* GENERATE THE DELAY OF THE 250MS AND TOGGLE THE BIT P1.5*/

#include<reg51.h>
//sbit  port= P1^5;
void delay(void);

void main(void)
{
	
	unsigned char z,x;
//	port=0;
	P1=0x55;
	
	while(1)
	{
//		port=~port;
		P1=~P1;
		for(z=0;z<10;z++)
		{
			for(x=0;x=36;x++)
			{
			delay();
			}
		}
		
	}
	
}
	void delay()
	{
		TMOD =0x02;
		TH0=233;
		TR0=1;
		while(TF0==0)
		{
			TR0=0;
			TF0=0;	
		}
	             
	}
	
	

	
/*CLOCK USING 60HZ EXTERNAL CLOCK*/

//#include<reg51.h>

//void time(unsigned char value);
//unsigned char sec,min;
//void main()
//{
//  unsigned char val;
//	T0=1;
//	TMOD = 0x06;
//	TH0=60;
//	while(1)
//	{
//	  do
//		{
//		  TR0=1;
//			sec=TL0;
//			time(val);
//		}
//		
//		while(TF0=0);
//		{
//		   TR0=0;
//			 TF0=0;
//		}
//	}

//}


//void time(unsigned char value)
//{
//  
//	
//	min=value/60;
//	sec=value%60;
//	
//	P1=sec;
//	P2=min;
//}