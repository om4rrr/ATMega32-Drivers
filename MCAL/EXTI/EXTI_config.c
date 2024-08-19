/*
 * EXIT_config.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#include "EXTI_config.h"
#include "EXTI_priv.h"

EXTI_t EXTI_AstrEXTIConfig[3] = {

		{ENABLED, EXTI_FALLING_EDGE},
		{DISABLED, EXTI_FALLING_EDGE},
		{DISABLED, EXTI_FALLING_EDGE}
};

/*
 Options (SENSE_MODE):-

 	 1-EXTI_FALLING_EDGE
 	 2-EXTI_RISING_EDGE
 	 3-EXTI_LOW_LEVEL
 	 4-EXTI_ON_CHANGE

 */

