/*
 * spi.h
 *
 *  Created on: Jan 28, 2020
 *      Author: my laptop
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "macros.h"
#include "std_types.h"
#include <avr/interrupt.h>


#define MASTER_MODE             ENABLE
#define SLAVE_MODE              DISABLE


#define SPI_INTERRUPT           			ENABLE
#define RX_AL_BY_INT                        DISABLE

#define END_STRING_CHAR            '$'

extern uint8 g_lastBufferdInterruptSpiRecivedVal[50];
extern uint8 g_lastBufferdInterrupSpiCntr;



#if MASTER_MODE

typedef enum
{
	LSB_FIRST=1,
	MSB_FIRST=0,
}dataOrderTx;


typedef enum
{
	IDLE_AT_LOW=0,
	IDLE_AT_HIGH=0,
}clockPolarity;

typedef enum
{
	SAMPLE_AT_LEADING=0,
	SAMPLE_AT_TRAILING=1,
}clockPhase;

typedef enum
{
	CPU_F_BY_4=0,
	CPU_F_BY_16=1,
	CPU_F_BY_64=2,
	CPU_F_BY_128=3,
	CPU_F_BY_2=4,
	CPU_F_BY_8=5,
	CPU_F_BY_32=6,
}clockRate;



typedef struct
{
	dataOrderTx order;
	clockPolarity plarity;
	clockPhase phase;
	clockRate rate;

}spiSettings;


void SPI_MasterInit(spiSettings* a_setting_Ptr);

#elif SLAVE_MODE
void SPI_SlaveInit(void);
#endif

uint8 SPI_MasterSendReciveByte(uint8 a_data);
uint8 SPI_SlavePollngReciveByte(void);
void SPI_SendString(const uint8* a_string_Ptr);
uint8* SPI_ReciveString(uint8* a_emptyString_Ptr);

#endif /* SPI_H_ */
