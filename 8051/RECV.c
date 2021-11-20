#	include<reg51.h>
void delay(void);
void main()
{

		TMOD=0X20;
	  TH1=-3;
	  SCON=0X50;
	  TR1=1;
	  RI=0;
	while(1)
	{
		while(RI==1)
		{
	 ACC=SBUF;
		P2=ACC;
		RI=0;
			delay();
		
		}
		  
		
	}

}


void delay()
{
	  unsigned char x,y;
	
	for(x=0;x<250;x++)
	
	{
		for(y=0;y<100;y++)
		{
	  TMOD = 0x10;
		TH1=0XFF;
		TL1=0XE9;
		TR1=1;	
			
			while(TF1==1)
		{
		  TF1=0;
			TR1=0;
			
		}
		
		}
		
	}
}