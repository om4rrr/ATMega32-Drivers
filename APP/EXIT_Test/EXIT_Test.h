#ifndef APP_EXIT_TEST_EXIT_TEST_H_
#define APP_EXIT_TEST_EXIT_TEST_H_

#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/GIE/GIE_int.h"
#include "../../MCAL/EXTI/EXTI_int.h"
#include "../../MCAL/EXTI/EXTI_config.h"

#include "../../HAL/LED/LED_int.h"
#include "../../HAL/Switch/Switch_int.h"
#include "../../HAL/SevenSegment/SevenSegment_PreCompile/Seven_Segment_int.h"



#define     RED_LED                0
#define     YALLOW_LED             1
#define     GREEN_LED              2

#define     NORMAL_MODE            5
#define     PEDESTRIANS_MODE       6

void APP_voidInit(void);

void APP_voidProgram(void);

void INT0_ISR(void);

void APP_voidNormalMode(void);

void APP_voidPedestriansMODE(void);

void APP_voidYellowLed(void);

void APP_voidGreenLed(void);

void APP_voidRedLed(void);



#endif /* APP_EXIT_TEST_EXIT_TEST_H_ */
