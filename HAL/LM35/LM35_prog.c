/*
 * LM35_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "../../MCAL/ADC/ADC_int.h"

#include "../LCD/LCD_int.h"
#include "../LCD/LCD_config.h"

#include "LM35_int.h"


ES_t LM35_u8GetTemp (LM35_CONFIG * lm35, u8 * Copy_u8TempValue) {

	ES_t Local_enuErrorState = ES_OK;

	u16 Local_u16ADCResult, Local_u16AnalogValue;

	u16 Local_u8ADCReference = ( lm35->Copy_u8ADCVoltageReference ) * 1000 ;  // To Convert from ( V --> mV )

	// ADC Digital Reading
	ADC_enuGetReadSync( lm35->Copy_u8LM35Channel , &Local_u16ADCResult) ;

	// Check for ADC Resolution
	if ( lm35->Copy_u8ADCResolution == ADC_RESOLUTION_10_BIT ) {

		Local_u16AnalogValue = (u16) ( ((u32)Local_u16ADCResult * (u32)Local_u8ADCReference ) / 1024UL) ;

	}
	else if ( lm35->Copy_u8ADCResolution == ADC_RESOLUTION_8_BIT ) {

		Local_u16AnalogValue = (u16) ( ((u32)Local_u16ADCResult * (u32)Local_u8ADCReference ) / 256UL) ;
	}
	else {

		Local_enuErrorState = ES_OUT_OF_RANGE;
	}


	// Convert ( mV --> Temp )
	* Copy_u8TempValue = Local_u16AnalogValue / 10 ;

	return Local_enuErrorState;
}
