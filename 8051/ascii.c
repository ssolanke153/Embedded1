//#include<reg51.h>

//void main(void)
//{
//  unsigned char x,y,z;
//	unsigned char mybyte =0x29;
//	x=mybyte&0x0F;
//	P1=x|0x30;
//	y=mybyte & 0xF0;
//	y=y>>4;
//	P2=y|0x30;
//}


#include<reg51.h>
#define dispaly P1
sbit En =P3^2;
sbit Rs =P3^0;
sbit Rw =P3^1;
char d=10;
void delay(unsigned  int);
void display(unsigned char a);
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
	
//	unsigned char message []="EARTH IS THE BUT ONE COUNTRY;
    unsigned char x,y,s;
	unsigned char z;
	
	s=10+20;
	
	command();
	
    dispaly = 0x38;
    command();

//     dispaly = 0x01;
//    command();
		
     dispaly = 0x0C;
     command();
		 
      
     dispaly = 0x06;
     command();
		 
 
     dispaly = 0x80;
     command();
		 
		 x=s&0xF0;
		 x=x>>4;
		x=x|0x30;
		display(x);
		
		y=s&0x0F;
		x=y|0x30;
		display(x);    
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
	
	void display(unsigned char a)
	{
		
		 
      dispaly = a;
			 
         Rs=1;      // As we send data make RS=1
			   Rw=0;     //  since we write the data on lcd we have to make R/W pin 0
         En = 1;
         En = 0;
			 delay(1);
	
}
