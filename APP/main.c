
#include "../SERVICE/stdTypes.h"
#include "../SERVICE/ErrorStates.h"


#include "../MCAL/Timer/Timer_int.h"
#include "../MCAL/Timer/Timer_priv.h"

#include "../MCAL/EXTI/interrupt.h"

#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/GIE/GIE_priv.h"


#include "../MCAL/DIO/DIO_int.h"


#include "../MCAL/SPI/SPI_int.h"
#include "../MCAL/SPI/SPI_priv.h"

#include <avr/io.h>
#include <util/delay.h>
	
void SPI_SlaveInit() 
{
    // Set MISO as output
    DDRB |= (1 << 6);

    // Enable SPI, Slave mode
    SPCR = (1 << SPE);
}

u8 SPI_Receive() 
{
	
    // Wait for reception complete
    while (!(SPSR & (1 << SPIF)));

    // Return received data
    return SPDR;
}

int main(void) 
{
    SPI_SlaveInit();

    // Set LED pin as output
    DDRA |= (1 << 0);

    while (1) {
        // Receive data from master
        u8 receivedData = SPI_Receive();

        // Process received data
        if (receivedData == 0x0A) {
            // Turn on the LED
            PORTA |= (1 << 0);
        } else {
            // Turn off the LED
            PORTA &= ~(1 << 0);
        }
    }

    return 0;
}






















































/* 	u8 Local_u8Data;
	while(1){
	
		SPI_enuTransceiveByteSynch(&Local_u8Data, 1);
		_delay_ms(10);
	
	} */
	
		 
/* 	DDRA |= (1<<0);
	
	//SPI_enuTransceiveByteASynch(&Local_u8Data, 10, func);
	
	while(1){

		SPI_enuTransceiveByteSynch(&Local_u8Data, 10);
		_delay_ms(10);
		if(Local_u8Data == 1){
			PORTA |= (1<<0);
		}
	
	} */