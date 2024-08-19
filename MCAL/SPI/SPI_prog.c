/*******************************************************************************************/
/*******************************************************************************************/
/*************************            Author : Omar Ali            *************************/
/*************************            Component : SPI              *************************/
/*************************            Layer : MCAL                 *************************/
/*************************            Version : 1.00               *************************/
/*******************************************************************************************/
/*******************************************************************************************/

#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "../DIO/DIO_int.h"

#include "SPI_int.h"
#include "SPI_priv.h"
#include "SPI_config.h"



static u8 Global_u8SPISentByte;

static u8 *Global_Pu8SPIReceivedByte = NULL;

static void (*Global_PvoidSPINotificationFunctionByte)(void) = NULL;


ES_t SPI_enuInit(void)
{
	ES_t Local_enuErrorState = ES_OK;
	
	
	/*  Enable SPI  */	
#if    SPI_STATE == ENABLE
	
	Set_Bit(SPCR, SPCR_SPE);

#elif SPI_STATE == DISABLE
	
	Clr_Bit(SPCR, SPCR_SPE);
	
#else
#error "Unsupported State"
#endif
	
	
   /*  Initalize Master/Slave select  */	
#if    SPI_MODE == MASTER
	
	Set_Bit(SPCR, SPCR_MSTR);
	
	DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN5, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN6, DIO_u8INPUT);
	DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN7, DIO_u8OUTPUT);
	
	DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN4, DIO_u8INPUT);
	DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN4, DIO_u8PULL_UP);
	
	

#elif SPI_MODE == SLAVE
	
	Clr_Bit(SPCR, SPCR_MSTR);
	
	DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN7, DIO_u8INPUT);
	DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN5, DIO_u8INPUT);
	DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN6, DIO_u8OUTPUT);
	
	DIO_enuSetPinDirection(DIO_u8PORTB, DIO_u8PIN4, DIO_u8INPUT);
	DIO_enuSetPinValue(DIO_u8PORTB, DIO_u8PIN4, DIO_u8FLOAT);
	
#else
#error "Wrong Master/Slave Select"
#endif
	
	
	/*  Set Data Order  */	
#if    SPI_DATA_ORDER == LSB_FIRST
	
	Set_Bit(SPCR, SPCR_DORD);

#elif SPI_DATA_ORDER == MSB_FIRST
	
	Clr_Bit(SPCR, SPCR_DORD);
	
#else
#error "Wrong Data Order"
#endif
	
	  
	/*  Set Clock Polarity  */	
#if    SPI_CLK_POLARITY == HIGH
	
	Set_Bit(SPCR, SPCR_CPOL);

#elif SPI_CLK_POLARITY == LOW
	
	Clr_Bit(SPCR, SPCR_CPOL);
	
#else
#error "Wrong Clock Polarity"
#endif
	
	
	/*  Set Clock Phase  */	
#if    SPI_CLK_PHASE == SAMPLE_FIRST
	
	Set_Bit(SPCR, SPCR_CPHA);

#elif SPI_CLK_PHASE == SETUP_FIRST
	
	Clr_Bit(SPCR, SPCR_CPHA);
	
#else
#error "Wrong Clock Phase"
#endif
	
	
#if (SPI_CLK_RATE == SPI_DIVISION_BY_2)

	Clr_Bit(SPCR, SPCR_SPR0); Clr_Bit(SPCR, SPCR_SPR1); Set_Bit(SPSR, SPSR_SPI2X);

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_4)

	Clr_Bit(SPCR, SPCR_SPR0); Clr_Bit(SPCR, SPCR_SPR1); Clr_Bit(SPSR, SPSR_SPI2X);

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_8)
	
	Set_Bit(SPCR, SPCR_SPR0); Clr_Bit(SPCR, SPCR_SPR1); Set_Bit(SPSR, SPSR_SPI2X);


#elif (SPI_CLK_RATE == SPI_DIVISION_BY_16)
	
	Set_Bit(SPCR, SPCR_SPR0); Clr_Bit(SPCR, SPCR_SPR1); Clr_Bit(SPSR, SPSR_SPI2X);

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_32)

	Clr_Bit(SPCR, SPCR_SPR0); Set_Bit(SPCR, SPCR_SPR1); Set_Bit(SPSR, SPSR_SPI2X);

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_64)
	
	Clr_Bit(SPCR, SPCR_SPR0); Set_Bit(SPCR, SPCR_SPR1); Clr_Bit(SPSR, SPSR_SPI2X);

#elif (SPI_CLK_RATE == SPI_DIVISION_BY_128)

	Set_Bit(SPCR, SPCR_SPR0); Set_Bit(SPCR, SPCR_SPR1); Clr_Bit(SPSR, SPSR_SPI2X);

#else 
#error "Unsupported SPI Clock Rate"	
#endif
	
	return Local_enuErrorState;
}




ES_t SPI_enuTransceiveByteSynch(u8* Copy_pu8ReceivedData, u8 Copy_u8SentData)
{
	ES_t Local_enuErrorState = ES_OK;
	
	SPDR = Copy_u8SentData;
	
	if(Copy_pu8ReceivedData != NULL)
	{
		u64 Local_u8TimeOutCounter = 0;
		
		while(!Get_Bit(SPSR, SPSR_SPIF) && Local_u8TimeOutCounter++ < SPI_TIMEOUT);
		
		if(Local_u8TimeOutCounter >= SPI_TIMEOUT)
		{
			Local_enuErrorState = ES_TIMEOUT_STATE;
		}
		else
		{
			*Copy_pu8ReceivedData = SPDR;
		}
	}
	else 
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


ES_t SPI_enuTransceiveByteASynch(u8* Copy_pu8ReceivedData, u8 Copy_u8SentData, void(*Copy_PvoidNotificationFunction)(void))
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_pu8ReceivedData != NULL && Copy_PvoidNotificationFunction != NULL)
	{
		Global_u8SPISentByte = Copy_u8SentData;
			
		Global_Pu8SPIReceivedByte = Copy_pu8ReceivedData;
			
		Global_PvoidSPINotificationFunctionByte = Copy_PvoidNotificationFunction;
		
		/* Enable the SPI interrupt */
        Set_Bit(SPCR, SPCR_SPIE);
		
	}
	else 
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


ISR(VECT_SPI){
	
	*Global_Pu8SPIReceivedByte = SPDR;
	
	if(Global_PvoidSPINotificationFunctionByte != NULL){
		
		Global_PvoidSPINotificationFunctionByte();
	}
	
}