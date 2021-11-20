#include<reg51.h>

#define display P1

sbit En =P2^2;
sbit Rs =P2^0;
sbit Rw =P2^1;


	void delay(unsigned int time)
	{
		unsigned int i,j;
		for(i=0;i<time;i++)
		{
			 for(j=0;j<1275;j++)
			{
				
			}
		}
	}

void command_init()
{

     Rs=0;     // Since we give command we have to make RS=0
     Rw = 0;  // since we write the data on lcd we have to make R/W pin 0
     En = 1; // to take new character
     En = 0;
     delay(10);
}


void lcd_init()
{
	  display = 0x38;
    command_init();

    display = 0x01;
    command_init();
		
     display = 0x0C;
     command_init();
		 
      
     display = 0x06;
     command_init();
		 
 
     display = 0x8F;
     command_init();
	
	   display = 0x07;
     command_init();
}

void send_char(char ch)
{
	 
				 display = ch;
	
	       Rs=1;      // As we send data make RS=1
			   Rw=0;     //  since we write the data on lcd we have to make R/W pin 0
         En = 1;
         En = 0;
			   delay(35);
		 
		
	
}

