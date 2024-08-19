/*
 * Switch_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/Macro_To_Function.h"


#include "Switch_priv.h"
#include "Switch_config.h"
#include "../../MCAL/DIO/DIO_int.h"

ES_t Switch_enuInit(SW_t * Copy_AstrSwitches)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_AstrSwitches != NULL)
	{
		u8 Local_u8Iterator;
		for(Local_u8Iterator = 0; Local_u8Iterator < SW_NUM; ++Local_u8Iterator)
		{
			Local_enuErrorState = DIO_enuSetPinDirection(Copy_AstrSwitches[Local_u8Iterator].SW_PortID, Copy_AstrSwitches[Local_u8Iterator].SW_PinID, DIO_u8INPUT);
			Local_enuErrorState = DIO_enuSetPinValue(Copy_AstrSwitches[Local_u8Iterator].SW_PortID, Copy_AstrSwitches[Local_u8Iterator].SW_PinID, Copy_AstrSwitches[Local_u8Iterator].SW_Status);
			if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
		}
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}


ES_t Switch_enuGetStatus(SW_t * Copy_AstrSwitch, u8 * Copy_pu8SwitchStatus)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_AstrSwitch != NULL && Copy_pu8SwitchStatus != NULL)
	{
		Local_enuErrorState = DIO_enuGetPinValue(Copy_AstrSwitch->SW_PortID, Copy_AstrSwitch->SW_PinID, Copy_pu8SwitchStatus);
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
	return Local_enuErrorState;
}
