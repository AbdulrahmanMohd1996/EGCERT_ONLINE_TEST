/*
 * main.c
 *
 *  Created on: Oct 8, 2021
 *      Author: my laptop
 */

#include "spi.h"
#include "std_types.h"
#include "macros.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

#define  TASK1_PRIORITY (0)
void task1_code(void*pvParamter);



int main(void)
{
	xTaskCreate(task1_code,"Task1",50,NULL,TASK1_PRIORITY,NULL);
	vTaskStartScheduler();

	while(1)
	{
	}

	return 0;
}


void task1_code(void*pvParamter)
{
	spiSettings Master_Settings={MSB_FIRST,IDLE_AT_LOW,SAMPLE_AT_LEADING,CPU_F_BY_128};
	SPI_MasterInit(&Master_Settings);

	DDRA=0X0F;
	PORTA=0X00;
	SPI_MasterSendReciveByte('R');
	PORTA=0X0F;

	while(1)
	{
		for(uint8 i=0;i<4;i++)
		{
			CLEAR_BIT(PORTA,i);
			SPI_MasterSendReciveByte('G');
			vTaskDelay(1000);
			SPI_MasterSendReciveByte('Y');
			vTaskDelay(500);
			SPI_MasterSendReciveByte('R');
			SET_BIT(PORTA,i);

		}
	}

}
