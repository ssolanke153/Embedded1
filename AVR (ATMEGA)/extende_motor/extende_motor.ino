//#include<avr/io.h>
//#include<util/delay.h>
//#define ena 2
//#define pin1 0
//#define pin2 1
//
//int main()
//  {
//    int a=30;
//    DDRD |= (1<<pin1) | (1<<pin2) | (1<<ena);
//
//    while(1)
//    {
//
//      PORTD |= (1<<ena)| (1<<pin1) & ~(1<<pin2);
//      delay(30);
//      PORTD  = PORTD & ~(1<<ena) | (1<<pin1) & ~(1<<pin2);
//      delay(70); 
//      
//      }
//
//    
//  
//  }


#define ena 8
#define pin1 10
#define pin2 11
int d=30, e=5;
void setup()
{
  pinMode(8, OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  
  }

void loop()
{
  d = e+d;
  if (d<=0 || d>=255)
  {
    e = -e;
    }
    
 digitalWrite(ena, 1);
 digitalWrite(pin1, 0);
 digitalWrite(pin2, 1);
 delay(d);
 digitalWrite(ena, 0);
 digitalWrite(pin1, 0);
 digitalWrite(pin2, 1);
 delay(255-d);

 
  
  
  }
