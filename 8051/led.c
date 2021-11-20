#include<reg51.h>
void MSDelay(unsigned int);

void main(void)
{
  while(1)
	{
	  P0=0x55;
		MSDelay(10);
		P0=0xAA;
		MSDelay(100);
	}


}

void MSDelay(unsigned int itime)
{
 unsigned int i,j;
	for(i=0;i<itime;i++)
	{
	  for(j=0;j<2000;j++)
		{
		}
	}
	
	
}
	