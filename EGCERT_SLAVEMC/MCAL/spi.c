

#include "spi.h"


volatile void (*g_callBack_Ptr)(void)=NULL_PTR;

uint8 g_lastBufferdInterruptSpiRecivedVal[50]={0};
uint8 g_lastBufferdInterrupSpiCntr=0;


ISR(SPI_STC_vect)
{
	if(g_callBack_Ptr!=NULL_PTR)
	{
		(*g_callBack_Ptr)();
	}

}




#if MASTER_MODE
void SPI_MasterInit(spiSettings* a_setting_Ptr)
{

	SET_BIT(DDRB,PB4);
	SET_BIT(DDRB,PB5);
	SET_BIT(DDRB,PB7);
	CLEAR_BIT(DDRB,PB6);
	SPCR=(1<<SPE)|(1<<MSTR)|(a_setting_Ptr->order<<DORD)|(a_setting_Ptr->plarity<<CPOL)|(a_setting_Ptr->phase<<CPHA)|(a_setting_Ptr->rate&0X03);
	(a_setting_Ptr->rate&0X04)?SPSR=1:0;

}

#elif SLAVE_MODE
void SPI_SlaveInit(void)
{
	CLEAR_BIT(DDRB,PB4);
	CLEAR_BIT(DDRB,PB5);
	CLEAR_BIT(DDRB,PB7);
	SET_BIT(DDRB,PB6);
	SPCR=(1<<SPE);
}
#endif

uint8 SPI_MasterSendReciveByte(uint8 a_data)
{
	SPDR=a_data;
	while(!(READ_BIT(SPSR,SPIF)));
	return SPDR;
}

uint8 SPI_SlavePollngReciveByte(void)
{
	while(!(READ_BIT(SPSR,SPIF)));
	return SPDR;
}


void SPI_SendString(const uint8* a_string_Ptr)
{
	while((*(a_string_Ptr))!='\0')
	{
		SPI_MasterSendReciveByte((*(a_string_Ptr)));
		a_string_Ptr++;
	}
	SPI_MasterSendReciveByte(END_STRING_CHAR);
}

uint8* SPI_ReciveString(uint8* a_emptyString_Ptr)
{
	uint8 i=0;
	while(a_emptyString_Ptr[i-1]!=END_STRING_CHAR)
	{
		a_emptyString_Ptr[i]=SPI_SlavePollngReciveByte();
		i++;
	}
	a_emptyString_Ptr[i-1]='\0';
	return &(a_emptyString_Ptr[0]);
}


void SPI_CallBackFunc(void(*a_func_Ptr)(void))
{
	g_callBack_Ptr=a_func_Ptr;
}

