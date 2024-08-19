/*
 * EXIT_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef EXIT_INT_H_
#define EXIT_INT_H_

#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "EXTI_config.h"


ES_t EXTI_enuInit(EXTI_t *Copy_pstrEXTILINE);

ES_t EXTI_enuSetSignalLatch(u8 Copy_u8SenseMode, u8 Copy_u8Line);

ES_t EXTI_enuDisableInterrupt(u8 Copy_u8Line);

ES_t EXTI_enuEnableInterrupt(u8 Copy_u8Line);

ES_t EXTI_enuClearFlag(u8 Copy_u8Line);

ES_t EXTI_u8GetFlag(u8 Copy_u8Line, u8 * Copy_pu8IntFlag);

ES_t EXTI_enuSetCallBack(void (*Copy_pvoidCallBack)(void) , u8 Copy_u8EXTILine );

#endif /* EXIT_INT_H_ */
