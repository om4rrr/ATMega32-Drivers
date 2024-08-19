/*
 * Switch_config.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#include "../../SERVICE/stdTypes.h"
#include "Switch_priv.h"
#include "Switch_config.h"
#include "../../MCAL/DIO/DIO_int.h"


SW_t Switch_AstrSwitchConfig[SW_NUM] = {
		{DIO_u8PORTD, DIO_u8PIN2, DIO_u8FLOAT}
};
