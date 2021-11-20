#include<reg51.h>

void main()
{
////   unsigned char mynum[]="ABCDEF";
////		 
////	 unsigned char z;
////	
////	for(z=0;z<=6;z++)
////	{
////	  P1=mynum[z];
////	
////	}
//	
//	
//	unsigned char mydata[100];
//	unsigned char x,z=0;
//	
//	for(x=0;x<100;x++)
//	{
//	  z--;
//		mydata[x]=z;
//		P1=z;
//	}
	
//	P1=0x140;
//	P2=0x0F;

P1=0xF0 | 0X45;
P2=0xF0^0xAA;
ACC=0xF0^0xEE;
	
}