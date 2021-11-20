#include<reg52.h>
//#define LED P2


void delay(unsigned char time);

void main()
{
	unsigned char z,d=200;
	unsigned char count;
	unsigned char value[]={0x0C,0x06,0x03,0x09};
	
//  P1=00;
//	LED=0;
//	for(;;)
//	{
//	  P1++;
//		LED++;
//	}
	
//P1=0x65>>2;
//	P1=0x65<<2;
//	ACC=0x95;
//	ACC=ACC>>4;
//	ACC = ACC|0X50;
//	P1=0x50;
	
//for(z=0;z<8;z++)
//	{
//	  if(P1==0)
//		{
//		  count++;
//		}
//		P1++;
//	
//	}
//	
//	ACC=count;

for(z=0;z<4;z++)
{ 
 P2 = value[z];
	delay(d);
  
  

}
}

void delay(unsigned char time)
{

	unsigned int i,j;
	for(i=0;i<time;i++)
	{
	  for(j=0;j<1275;j++)
		{
		}
	}

}