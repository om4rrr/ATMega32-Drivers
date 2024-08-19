/*
 * LED_config.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "LED_config.h"
#include "LED_priv.h"
#include "../../MCAL/DIO/DIO_int.h"

LED_t LED_AstrLedConfig[LED_NUM] = {
		{DIO_u8PORTC, DIO_u8PIN0, LED_SOURCE, LED_OFF},
		{DIO_u8PORTB, DIO_u8PIN6, LED_SOURCE, LED_OFF},
		{DIO_u8PORTB, DIO_u8PIN7, LED_SOURCE, LED_OFF}
};
