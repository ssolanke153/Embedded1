/*
* Queue.c
*
* Created: 23-04-2021 04:06:52 PM
* Author : Shri
*/

/*
#include <avr/io.h>
#define  F_CPU 8000000UL
#include <stdio.h>
#include "usart.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t xQueue;
char str[30];

void sender(void *param);
void receiver(void *param);


TaskHandle_t TaskHandle1;
TaskHandle_t TaskHandle2;


volatile uint32_t ulIdleCycleCount = 0UL;
void vApplicationIdleHook( void )
{

ulIdleCycleCount++;  // increment the varialbe. at each tick of crystal.
}


int main(void)
{
usart_init();
lcd_init();


xQueue = xQueueCreate( 5, sizeof( int ) );

if(xQueue != NULL)
{




xTaskCreate(sender, "sender", 100, (void*)100, 1, &TaskHandle1);


xTaskCreate(receiver, "Receiver", 1000, NULL, 1, NULL );

vTaskStartScheduler();
}
else
{
usart_send((char*)"not get anything\r");
}
}


void sender(void *param)
{

int ValueToSend;

BaseType_t xStatus;

ValueToSend = (int) param;

while(1)
{
xStatus = xQueueSendToBack(xQueue, &ValueToSend, 0);

if (xStatus == pdPASS)
{
usart_send((char*)"Send to queue\r\r");
}
else
{
usart_send((char*)"not send\r\r");
}

vTaskDelay(500);
}




}



void receiver(void *param)
{
int ReceivedValue;
BaseType_t xStatus;

const TickType_t xTicksToWait = pdMS_TO_TICKS(100);



while(1)
{


if (uxQueueMessagesWaiting(xQueue) != 0)
{
usart_send((char*)"Queue is empty\r\r");
}

xStatus = xQueueReceive(xQueue, &ReceivedValue, xTicksToWait);

if (xStatus == pdPASS)
{
sprintf(str, "Received --->  %d\r\r", ReceivedValue);

usart_send(str);
}
else
{
usart_send((char*)"not received from queue.\r\r");
}
vTaskDelay(500);
}
}

*/


// Blocking when sending to a queue, and sending structures on a
// queue#include <avr/io.h>
#define F_CPU 8000000UL
#include <stdio.h>
#include "usart.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


QueueHandle_t xQueue;
char str[30];

static void sender(void *param);
static void receiver(void *param);

TaskHandle_t TaskHandle1;         // Task handles 
TaskHandle_t TaskHandle2;

volatile uint32_t ulIdleCycleCount = 0UL;

void vApplicationIdleHook(void)
{

	ulIdleCycleCount++; // increment the variable. at each tick of crystal.
}

typedef enum
{
	esender1,
	esender2

} DataSource_t;

typedef struct
{
	int ucValue;
	DataSource_t eDataSource;
	
} Data_t;

Data_t xStructsToSend[2] = {

	{100, esender1},

	{200, esender2}};

	int main(void)
	{
		usart_init();
		

		xQueue = xQueueCreate(5, sizeof(Data_t));

		if (xQueue != NULL)
		{

			xTaskCreate(sender, "sender1", 100, &(xStructsToSend[0]), 2, &TaskHandle1);
			xTaskCreate(sender, "sender2", 100, &(xStructsToSend[1]), 2, &TaskHandle2);

			xTaskCreate(receiver, "Receiver", 100, NULL, 1, NULL);

			vTaskStartScheduler();
		}
		else
		{
			usart_send((char *)"not get anything\r");
		}
	}

	void sender(void *param)
	{

		const TickType_t xTickToWait = pdMS_TO_TICKS(100);
		BaseType_t xStatus;

		//Data_t* ValueToSend;
		//ValueToSend = (Data_t*) param;

		while (1)
		{
			xStatus = xQueueSendToBack(xQueue, param, xTickToWait);  // used to put value at back of queue. and return whether it pass or not. 

			if (xStatus == pdPASS)
			{
				usart_send((char *)"Send to queue\r\r");
			}
			else
			{
				usart_send((char *)"not send\r\r");
			}

			vTaskDelay(500);
		}
	}

	void receiver(void *param)
	{
		Data_t ReceivedValue;
		BaseType_t xStatus;

		while (1)
		{

			if (uxQueueMessagesWaiting(xQueue) != 5)   // How many element hold by queue is returned by this function.
			{
				usart_send((char *)"Queue is full\r\r");
			}

			xStatus = xQueueReceive(xQueue, &ReceivedValue, 0);   // Get value from the queue. and return the whether it get the value or not. 

			if (xStatus == pdPASS)
			{
				if (ReceivedValue.eDataSource == esender1)
				{

					sprintf(str, "Received from sender1 -->  %d\r\r", ReceivedValue.ucValue);

					usart_send(str);
				}

				else
				{
					sprintf(str, "Received from sender2 -->  %d\r\r", ReceivedValue.ucValue);

					usart_send(str);
				}
			}
			else
			{
				usart_send((char *)"not received from queue.\r\r");
			}
			vTaskDelay(500);
		}
	}
