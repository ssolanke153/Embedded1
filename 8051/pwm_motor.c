#include<reg51.h>


void delay(int a);
sbit  enable = P1^0;
sbit pin1  = P1^1;
sbit pin2 = P1^2;
void main()
{
  int d=80, e=5;
	
	while(1)
	{
		 
		d = d + e;
		if (d<=0 || d >=512)
		{
		e = -e;
		}
		
	    enable = 1;
		pin1 = 1;
		pin2 = 0;
		delay(d);
		enable = 0;
		pin1 = 1;
		pin2 = 0;
		delay(100-d);
		
	}

	
}

void delay(int a)
{
  int x,y;
	
	for(x=0;x<a;x++)
	{
	  
	}
}