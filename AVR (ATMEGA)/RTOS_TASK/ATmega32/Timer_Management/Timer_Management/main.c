/*
* Timer_Management.c
*
* Created: 01-05-2021 08:14:32 AM
* Author : Shri
*/

/* #include <avr/io.h>
#include <stdio.h>
#define  F_CPU 8000000UL
#include "usart.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include "FreeRTOSConfig.h"

#define mainONE_SHOT_TIMER_PERIOD	    pdMS_TO_TICKS(3333)  // Coverting ms to Ticks
#define mainAUTO_RELOAD_TIMER_PERIOD	pdMS_TO_TICKS(500)

void AutoReloadTimerCallback(TimerHandle_t xTimer);
void AOneShotTimerCallback( TimerHandle_t xTimer );

void vApplicationIdleHook( void )
{
}

int main(void)
{
usart_init();
TimerHandle_t xAutoReloadTimer, xOneShotTimer;       // Timer Handles
BaseType_t    xTimer1Started, xTimer2Started;


xOneShotTimer = xTimerCreate("OneShot", mainONE_SHOT_TIMER_PERIOD, pdFALSE, 0, AOneShotTimerCallback);   // Creating the timers.

xAutoReloadTimer = xTimerCreate("AutoReload", mainAUTO_RELOAD_TIMER_PERIOD, pdTRUE, 0, AutoReloadTimerCallback);  // Creating the timers.

if ((xOneShotTimer != NULL)  &&  (xAutoReloadTimer != NULL))
{
xTimer1Started = xTimerStart(xOneShotTimer, 0);        //  Starting the Timers (This will send commands to 'command Queue')
xTimer2Started = xTimerStart(xAutoReloadTimer, 0);

if( (xTimer1Started == pdPASS) && (xTimer2Started == pdPASS))

{
vTaskStartScheduler();			// Starting the Scheduler...
}
}

for(;;);
}

void AOneShotTimerCallback( TimerHandle_t xTimer )
{
TickType_t xTimeNow;
char ticks[10];

xTimeNow = xTaskGetTickCount();          // Getting Tick Count

usart_send((char*)"One Shot is executing ---> ");
sprintf(ticks, "%d\r",xTimeNow);
usart_send(ticks);

}

void AutoReloadTimerCallback(TimerHandle_t xTimer)
{
TickType_t xTimerNow;
char ticks1[10];

int ulExecutionCount;

ulExecutionCount = ( int ) pvTimerGetTimerID( xTimer );   // Getting the Timer Id
ulExecutionCount++;
vTimerSetTimerID( xTimer, ( void * ) ulExecutionCount );  // Setting the timer ID


xTimerNow = xTaskGetTickCount();                   // Getting Tick counts.

usart_send((char*)"Auto reload is executing ---> ");
sprintf(ticks1, "%d,  %d\r",xTimerNow, ulExecutionCount);
usart_send(ticks1);

}
*/


// Doing job only with one Callback funtion.


#include <avr/io.h>
#include <stdio.h>
#define  F_CPU 8000000UL
#include "usart.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include "FreeRTOSConfig.h"

TimerHandle_t xAutoReloadTimer, xOneShotTimer;       // Timer Handles
 

#define mainONE_SHOT_TIMER_PERIOD	    pdMS_TO_TICKS(3333)  // Coverting ms to Ticks
#define mainAUTO_RELOAD_TIMER_PERIOD	pdMS_TO_TICKS(500)

void ACommonTimerCallback(TimerHandle_t xTimer);


void vApplicationIdleHook( void )
{
}

int main(void)
{
	usart_init();
	
	BaseType_t    xTimer1Started, xTimer2Started;
	
	
	xOneShotTimer = xTimerCreate("OneShot", mainONE_SHOT_TIMER_PERIOD, pdFALSE, 0, ACommonTimerCallback);   // Creating the timers.
	
	xAutoReloadTimer = xTimerCreate("AutoReload", mainAUTO_RELOAD_TIMER_PERIOD, pdTRUE, 0, ACommonTimerCallback);  // Creating the timers.
	
	if ((xOneShotTimer != NULL)  &&  (xAutoReloadTimer != NULL))
	{
		xTimer1Started = xTimerStart(xOneShotTimer, 0);        //  Starting the Timers (This will send commands to 'command Queue')
		xTimer2Started = xTimerStart(xAutoReloadTimer, 0);
		
		if( (xTimer1Started == pdPASS) && (xTimer2Started == pdPASS))
		
		{
			vTaskStartScheduler();			// Starting the Scheduler...
		}
	}
	
	for(;;);
}

 
void ACommonTimerCallback(TimerHandle_t xTimer)
{
	TickType_t xTimerNow;
	char ticks[10];
	
	xTimerNow = xTaskGetTickCount();                   // Getting Tick counts.
	
	/* The if condition below check which Timer is executing. if it xOneShotTimer then if is true and it executes code in it. otherwise else get executed.*/
	
	if(xTimer == xOneShotTimer)
	{
		usart_send((char*)"One Shot is executing ---> ");
		sprintf(ticks, "%d\r",xTimerNow);
		usart_send(ticks);
	}
	
	else
	{
		
		usart_send((char*)"Auto reload is executing ---> ");
		sprintf(ticks, "%d\r",xTimerNow);
		usart_send(ticks);
		 
	}

}

 