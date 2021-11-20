/*
 * ISR_TASK.c
 *
 * Created: 08-05-2021 04:25:42 PM
 * Author : Shri
 */ 

#include <avr/io.h>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "semphr.h"



#define mainINTERRUPT_NUMBER 3
static void vHandlerTask(void *pvParam);
static uint32_t ulExampleInterruptHandler(void);
SemaphoreHandle_t xBinarySemaphore;

int main(void)
{
	xBinarySemaphore = xSemaphoreCreateBinary();
	
	if (xBinarySemaphore != NULL)
	{
		xTaskCreate(vHandlerTask, "Handler", 1000, NULL, 3, NULL);
		
		xTaskCreate(ulExampleInterruptHandler, "Periodic", 1000, NULL, 1, NULL);
		
		
		vTaskStartScheduler();
	}
		   
		   for (;;)
		   {
		   }
		     

}



static void vHandlerTask(void *pvParam)
{
	for (;;)
	{
		xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
		usart_send("Handler task - Processing event.\r\n");
	}
	
}

static uint32_t ulExampleInterruptHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken;
	
	xHigherPriorityTaskWoken = pdFALSE;
	
	
	xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
	
	vPortYield();
}


