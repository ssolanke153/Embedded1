#include<reg51.h>

void Tdeley(void);

void main(void)
{
	
	while(1)
	{
		P1=0x55;
		t0deley();
		P1=0xAA;
		Tdeley();
	}
	}

	void Tdelay()
	{
	  TMOD = 0x01;
		TL0 = 0x00;
		TH0 = 0x35;
		TR0 = 1;
		while(TCON.5==0)
		{
		TCON.5 = 0;
		TCON.4 = 0;
		}
	
	}