/*

 * Seven_Segment_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef SEVEN_SEGMENT_INT_H_
#define SEVEN_SEGMENT_INT_H_

#include "../../../SERVICE/stdTypes.h"
#include "../../../SERVICE/ErrorStates.h"
#include "../../../SERVICE/Macro_To_Function.h"


ES_t Seven_Segment_enuInit(void);

ES_t Seven_Segment_enuDisplayNum(u8 Copy_u8DisplyedNum);

ES_t Seven_Segment_enuEnableCommon(void);

ES_t Seven_Segment_enuDisableCommon(void);

ES_t Seven_Segment_enuEnableDot(void);

ES_t Seven_Segment_enuDisableDot(void);

ES_t Seven_Segment_enuClear(void);

#endif /* SEVEN_SEGMENT_INT_H_ */
