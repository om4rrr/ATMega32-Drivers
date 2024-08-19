/*
 * LM35_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef HAL_LM35_LM35_INT_H_
#define HAL_LM35_LM35_INT_H_

#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/stdTypes.h"

typedef struct
{
	u8 Copy_u8LM35Channel ;
	u8 Copy_u8ADCVoltageReference ;       // Vref = 5 , 2.56 , External
	u8 Copy_u8ADCResolution ;
} LM35_CONFIG ;

#define ADC_RESOLUTION_10_BIT 1
#define ADC_RESOLUTION_8_BIT  2

ES_t LM35_u8GetTemp (LM35_CONFIG * lm35, u8 * Copy_u8TempValue);

#endif /* HAL_LM35_LM35_INT_H_ */
