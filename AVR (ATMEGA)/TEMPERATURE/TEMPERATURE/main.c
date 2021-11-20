/*
 * TEMPERATURE.c
 *
 * Created: 7/13/2020 9:42:43 AM
 * Author : Shri
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"
#include "adc.h"
char line[16];
//int adc_value = 0;

float adc_value1 = 0;
float adc_value2 = 0;
float adc_volt1 = 0;
float adc_volt2 = 0;
float mili_volt = 0;
float t1 = 0;
float t2 = 0;
float temp = 0;

int main(void)
{
	LCDInit(); // declare lcd data port and control port
	/* Replace with your application code */
	while (1)
	{
		LCDInit(); //Initialize LCD Display
		adc_init();//Function call
		
		sprintf(line,"ADC:");
		LCDGotoXY(1,1);
		LCDString(line);
		
		sprintf(line,"Temp :");
		LCDGotoXY(1,2);
		LCDString(line);
		
		
		while(1)
		{
			adc_value1 = 10; //adc_read(0); //ADC Read
			adc_value2 = 15; //adc_read(1); //ADC Read
			//adc_volt = ((adc_value*5)/1024.0); ref =5v
			//adc_volt = ((adc_value*2.56)/1024.0); //ref =2.56v
			adc_volt1 = ((adc_value1*2.56)/1024.0); // for all volt measurement. R1= 56K, R2=5K;
			adc_volt2 = ((adc_value2*2.56)/1024.0); // for all volt measurement. R1= 56K, R2=5K;
			//mili_volt = (adc_volt1 - adc_volt2)/1000;
			//temp = mili_volt/10;
			temp = (adc_volt1 - adc_volt2)*100;
			
			sprintf(line,"%.2f,%.2f",adc_value1,adc_value2);
			LCDGotoXY(5,1);
			LCDString(line);
			
			sprintf(line,"%.2f", temp); // 10 mili volt = 1 Centigrade
			LCDGotoXY(10,2);
			LCDString(line);
			
			//_delay_ms(50);
		}
	}
}



