/*
 * Switch_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef SWITCH_INT_H_
#define SWITCH_INT_H_

#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "Switch_priv.h"

#define SW_NUM 1


ES_t Switch_enuInit(SW_t * Copy_AstrSwitches);

ES_t Switch_enuGetStatus(SW_t * Copy_AstrSwitch, u8 * Copy_pu8SwitchStatus);


#endif /* SWITCH_INT_H_ */
