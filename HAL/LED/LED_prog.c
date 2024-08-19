/*
 * LED_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "LED_priv.h"
#include "LED_config.h"



ES_t LED_enuInit(LED_t * Copy_AstrLeds)
{
	ES_t Local_ErrorState = ES_NOK;

	if(Copy_AstrLeds != NULL)
	{
		u8 Local_u8Iterator;
		for(Local_u8Iterator = 0; Local_u8Iterator < LED_NUM; ++Local_u8Iterator)
		{
			Local_ErrorState = DIO_enuSetPinDirection(Copy_AstrLeds[Local_u8Iterator].LED_u8PortID, Copy_AstrLeds[Local_u8Iterator].LED_u8PinID, DIO_u8OUTPUT);
			if(Copy_AstrLeds[Local_u8Iterator].LED_u8Connection == LED_SOURCE)
			{
				if(Copy_AstrLeds[Local_u8Iterator].LED_Status == LED_ON)
				{
					DIO_enuSetPinValue(Copy_AstrLeds[Local_u8Iterator].LED_u8PortID, Copy_AstrLeds[Local_u8Iterator].LED_u8PinID, DIO_u8HIGH);
				}
				else if(Copy_AstrLeds[Local_u8Iterator].LED_u8Connection == LED_OFF)
				{
					DIO_enuSetPinValue(Copy_AstrLeds[Local_u8Iterator].LED_u8PortID, Copy_AstrLeds[Local_u8Iterator].LED_u8PinID, DIO_u8LOW);
				}
				else
				{
					return ES_OUT_OF_RANGE;
				}
			}
			else if(Copy_AstrLeds[Local_u8Iterator].LED_u8Connection == LED_SINK)
			{
				if(Copy_AstrLeds[Local_u8Iterator].LED_Status == LED_ON)
				{
					DIO_enuSetPinValue(Copy_AstrLeds[Local_u8Iterator].LED_u8PortID, Copy_AstrLeds[Local_u8Iterator].LED_u8PinID, DIO_u8LOW);
				}
				else if(Copy_AstrLeds[Local_u8Iterator].LED_u8Connection == LED_OFF)
				{
					DIO_enuSetPinValue(Copy_AstrLeds[Local_u8Iterator].LED_u8PortID, Copy_AstrLeds[Local_u8Iterator].LED_u8PinID, DIO_u8HIGH);
				}
				else
				{
					return ES_OUT_OF_RANGE;
				}
			}
			else
			{
				return ES_OUT_OF_RANGE;
			}

			if(Local_ErrorState != ES_OK) return Local_ErrorState;
		}
	}
	else
	{
		Local_ErrorState = ES_NULL_POINTER;
	}
	return Local_ErrorState;
}

ES_t LED_enuTrunOn(LED_t * Copy_pstrLedConfig)
{
	ES_t Local_ErrorState = ES_NOK;

	if(Copy_pstrLedConfig != NULL)
	{
		if(Copy_pstrLedConfig->LED_u8Connection == LED_SOURCE)
		{
			DIO_enuSetPinValue(Copy_pstrLedConfig->LED_u8PortID, Copy_pstrLedConfig->LED_u8PinID, DIO_u8HIGH);
		}
		else if(Copy_pstrLedConfig->LED_u8Connection == LED_SINK)
		{
			DIO_enuSetPinValue(Copy_pstrLedConfig->LED_u8PortID, Copy_pstrLedConfig->LED_u8PinID, DIO_u8LOW);
		}
		else
		{
			return ES_OUT_OF_RANGE;
		}
	}

	else
	{
		Local_ErrorState = ES_NULL_POINTER;
	}
	return Local_ErrorState;
}

ES_t LED_enuTrunOff(LED_t * Copy_pstrLedConfig)
{
	ES_t Local_ErrorState = ES_NOK;

	if(Copy_pstrLedConfig != NULL)
	{
		if(Copy_pstrLedConfig->LED_u8Connection == LED_SOURCE)
		{
			DIO_enuSetPinValue(Copy_pstrLedConfig->LED_u8PortID, Copy_pstrLedConfig->LED_u8PinID, DIO_u8LOW);
		}
		else if(Copy_pstrLedConfig->LED_u8Connection == LED_SINK)
		{
			DIO_enuSetPinValue(Copy_pstrLedConfig->LED_u8PortID, Copy_pstrLedConfig->LED_u8PinID, DIO_u8HIGH);
		}
		else
		{
			return ES_OUT_OF_RANGE;
		}
	}

	else
	{
		Local_ErrorState = ES_NULL_POINTER;
	}
	return Local_ErrorState;
}
