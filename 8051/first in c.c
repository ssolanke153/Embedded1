#include<reg51.h>
#define dispaly P1
sbit En =P3^2;
sbit Rs =P3^0;
sbit Rw =P3^1;
char d=10;
void delay(unsigned  int);
void command()
{

     Rs=0;     // Since we give command we have to make RS=0
     Rw = 0;  // since we write the data on lcd we have to make R/W pin 0
     En = 1; // to take new character
     En = 0;
delay(d);
}

void main(void)
{
	


/*unsigned char z;
for(z=0;z<=255;z++)
{
	if(z%5==0)
		continue;
else
	P1=z;
}

*/
	/*unsigned char mynum[]="0123456789ABCD";
	unsigned char z;
	
	for(z=0;z<=10;z++)
	{
	  P1=mynum[z];
	}
	*/
	
	unsigned char message []="EARTH IS THE BUT ONE COUNTRY";
	unsigned char z;
	
	command();
	
    dispaly = 0x38;
    command();

     dispaly = 0x01;
    command();
		
     dispaly = 0x0C;
     command();
		 
      
     dispaly = 0x06;
     command();
		 
 
     dispaly = 0x80;
     command();
		 
		 ACC=0xF0^0xAA;
 

     for (z = 0; z <= 28; z++)
     {
			 if(z==16)
			 {
				 dispaly = 0xC0;
     Rs=0;
     Rw = 0;
     En = 1;
     En = 0;
				 delay(d);
				 
			 }
			 else{
         dispaly = message[z];
			 
         Rs=1;      // As we send data make RS=1
			   Rw=0;     //  since we write the data on lcd we have to make R/W pin 0
         En = 1;
         En = 0;
			 delay(d);
			 }
	
	}	
}

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
