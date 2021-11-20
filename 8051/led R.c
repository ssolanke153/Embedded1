#include<reg51.h>

void delay();
 sbit a = P0^0; 
void main()
{
	
	while(1)
	{
    a = 0x55;
		delay();
		a=0xAA;
		delay();
  }
}
void delay()
{
  unsigned int i,j;
	
	for(i=0;i<1475;i++)
	{
	  for(j=0;j<100;j++)
		{
			
		}
	}

}