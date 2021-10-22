/*
 * main.c
 *
 *  Created on: Oct 8, 2021
 *      Author: my laptop
 */


#include "spi.h"
#include "std_types.h"
#include "macros.h"
#include <util/delay.h>

int main(void)
{
	SPI_SlaveInit();
	SET_BIT(DDRD,0);
	SET_BIT(DDRD,1);
	SET_BIT(DDRD,2);

	while(1)
	{

		unsigned int x=SPI_SlavePollngReciveByte();

		if (x=='R')
		{
			SET_BIT(PORTD,0);
			CLEAR_BIT(PORTD,1);
			CLEAR_BIT(PORTD,2);
		}
		if (x=='G')
		{
			SET_BIT(PORTD,2);
			CLEAR_BIT(PORTD,0);
			CLEAR_BIT(PORTD,1);
		}
		if (x=='Y')
		{
			SET_BIT(PORTD,1);
			CLEAR_BIT(PORTD,0);
			CLEAR_BIT(PORTD,2);
		}


	}

	return 0;
}
