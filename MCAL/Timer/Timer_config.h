#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_

#include "Timer_priv.h"

/*==================================================TIMER0==================================================*/

/*
 Options:
	 1- TIMER_MODE
	 2- COUNTER_MODE
 */

#define    TIMER0_WORKING_MODE                TIMER_MODE

/*
 Options:
     1- TIMER_PRE_1
     2- TIMER_PRE_8
     3- TIMER_PRE_64
     4- TIMER_PRE_256
     5- TIMER_PRE_1024
 */

#define    TIMER0_PRESCALER           TIMER_PRE_64

/*
 Options:
     1- TIMER_PRE_VALUE_1
     2- TIMER_PRE_VALUE_8
     3- TIMER_PRE_VALUE_64
     4- TIMER_PRE_VALUE_256
     5- TIMER_PRE_VALUE_1024
 */

#define    TIMER0_PRESCALER_VALUE      TIMER_PRE_VALUE_64

/*
 Options:
     1- TIMER_FALLING_EDGE
     2- TIMER_RISING_EDGE
 */

#define    COUNTER0_TRIGGER           TIMER_RISING_EDGE

/*
 Options:
     1- TIMER_OVF_MODE
     2- TIMER_CTC_MODE
     3- TIMER_PWM_MODE
	 4- TIMER_FASTPWM_MODE
 */

#define    TIMER0_WAVE_GENER_MODE     TIMER_PWM_MODE

/*
 Options:
     1- ENABLED
     2- DISABLED
 */

#define    TIMER0_OVERFLOW_INTERRUPT      ENABLED
#define    TIMER0_CTC_INTERRUPT           ENABLED

/*
 Compare Output Mode, non-PWM Mode Action.
 
  Options:
     1- OC_DISCONNECTED
     2- TOGGLE_OC
     3- SET_OC
     4- CLEAR_OC
*/

#define    Timer0_CTC_NON_PWM_ACTION        TOGGLE_OC

/*
Compare Output Mode, Phase Correct PWM Mode

  Options:
     1- OC_DISCONNECTED
     2- CLEAR_ON_UP_SET_ON_DOWN (Non-Inverting Mode)
     3- SET_ON_UP_CLEAR_ON_DOWN (Inverting)
*/

#define    Timer0_CTC_PWM_ACTION        CLEAR_ON_UP_SET_ON_DOWN


/*
 Compare Output Mode, Fast PWM Mode.
 
  Options:
     1- OC_DISCONNECTED
     2- CLEAR_ON_COMP_SET_ON_TOP (Non-Inverting Mode)
     3- SET_ON_COMP_CLEAR_ON_TOP (Inverting)
*/

#define    Timer0_CTC_FAST_PWM_ACTION        CLEAR_ON_COMP_SET_ON_TOP


/*==================================================TIMER1==================================================*/

/*
 Options:
	 1- TIMER_MODE
	 2- COUNTER_MODE
 */
#define    TIMER1_WORKING_MODE                TIMER_MODE

/*
 Options:
     1- TIMER_PRE_1
     2- TIMER_PRE_8
     3- TIMER_PRE_64
     4- TIMER_PRE_256
     5- TIMER_PRE_1024
 */

#define    TIMER1_PRESCALER           TIMER_PRE_1024

/*
 Options:
     1- TIMER_PRE_VALUE_1
     2- TIMER_PRE_VALUE_8
     3- TIMER_PRE_VALUE_64
     4- TIMER_PRE_VALUE_256
     5- TIMER_PRE_VALUE_1024
 */

#define    TIMER1_PRESCALER_VALUE      TIMER_PRE_VALUE_1024

/*
 Options:
     1- TIMER_FALLING_EDGE
     2- TIMER_RISING_EDGE
 */

#define    COUNTER1_TRIGGER           TIMER_RISING_EDGE

/*
 Options:
     1-  TIMER_OVF_MODE
     2-  TIMER_CTC_ICR1_TOP_MODE
	 3-  TIMER_CTC_OCR1A_TOP_MODE
     4-  TIMER_PWM_OCR1_TOP_MODE
	 5-  TIMER_PWM_OCR1A_TOP_MODE 
	 6-  TIMER_PWM_FREQ_OCR1_TOP_MODE
	 7-  TIMER_PWM_FREQ_OCR1A_TOP_MODE 
	 8-  TIMER_PWM_8_BIT_MODE       
     9-  TIMER_PWM_9_BIT_MODE       
     10- TIMER_PWM_10_BIT_MODE 	   
     12- TIMER_FAST_PWM_8_BIT_MODE  
     12- TIMER_FAST_PWM_9_BIT_MODE  
     13- TIMER_FAST_PWM_10_BIT_MODE 
     14- TIMER_FASTPWM_ICR1_MODE   
     15- TIMER_FASTPWM_OCRA1_MODE
 */

#define    TIMER1_WAVE_GENER_MODE     TIMER_CTC_OCR1A_TOP_MODE

/*
 Options:
     1- ENABLED
     2- DISABLED
 */
 
 #define   TIMER1_OVERFLOW_INTERRUPT      DISABLED
 #define   TIMER1_CTCA_INTERRUPT          DISABLED
 #define   TIMER1_CTCB_INTERRUPT          ENABLED
 #define   TIMER1_ICR_INTERRUPT           DISABLED
 
 
 /*
 Compare Output Mode, non-PWM Mode Action.
 
  Options:
     1- OC_DISCONNECTED
     2- TOGGLE_OC
     3- SET_OC
     4- CLEAR_OC
*/

#define    Timer1_CTCA_NON_PWM_ACTION        TOGGLE_OC
#define    Timer1_CTCB_NON_PWM_ACTION        TOGGLE_OC

/*
 Compare Output Mode, Fast PWM Mode.
 
  Options:
     1- OC_DISCONNECTED
     2- CLEAR_ON_COMP_SET_ON_TOP (Non-Inverting Mode)
     3- SET_ON_COMP_CLEAR_ON_TOP (Inverting)
*/

#define    Timer1_CTC_PWM_ACTION        OC_DISCONNECTED

/*
Compare Output Mode, Phase Correct PWM Mode

  Options:
     1- OC_DISCONNECTED
     2- CLEAR_ON_UP_SET_ON_DOWN (Non-Inverting Mode)
     3- SET_ON_UP_CLEAR_ON_DOWN (Inverting)
	 4- TOGGLE_OC1A_ON_COMP_MATCH
*/

#define    Timer1_CTC_FAST_PWM_ACTION        OC_DISCONNECTED


/*==================================================TIMER2==================================================*/

/*
 Options:
	 1- TIMER_MODE
	 2- COUNTER_MODE
 */
#define    TIMER2_WORKING_MODE                TIMER_MODE

/*
 Options:
     1- TIMER_PRE_1
     2- TIMER_PRE_8
     3- TIMER_PRE_64
     4- TIMER_PRE_256
     5- TIMER_PRE_1024
 */

#define    TIMER2_PRESCALER           TIMER_PRE_64

/*
 Options:
     1- TIMER_PRE_VALUE_1
     2- TIMER_PRE_VALUE_8
     3- TIMER_PRE_VALUE_64
     4- TIMER_PRE_VALUE_256
     5- TIMER_PRE_VALUE_1024
 */

#define    TIMER2_PRESCALER_VALUE      TIMER_PRE_VALUE_64

/*
 Options:
     1- TIMER_FALLING_EDGE
     2- TIMER_RISING_EDGE
 */

#define    COUNTER2_TRIGGER           TIMER_RISING_EDGE

/*
 Options:
     1- TIMER_OVF_MODE
     2- TIMER_CTC_MODE
     3- TIMER_PWM_MODE
	 4- TIMER_FASTPWM_MODE
 */

#define    TIMER2_WAVE_GENER_MODE     TIMER_FASTPWM_MODE

/*
 Options:
     1- ENABLED
     2- DISABLED
 */

#define    TIMER2_OVERFLOW_INTERRUPT      DISABLED
#define    TIMER2_CTC_INTERRUPT           ENABLED

/*
 Compare Output Mode, non-PWM Mode Action.
 
  Options:
     1- OC_DISCONNECTED
     2- TOGGLE_OC
     3- SET_OC
     4- CLEAR_OC
*/

#define    Timer2_CTC_NON_PWM_ACTION        TOGGLE_OC

/*
Compare Output Mode, Phase Correct PWM Mode

  Options:
     1- OC_DISCONNECTED
     2- CLEAR_ON_UP_SET_ON_DOWN (Non-Inverting Mode)
     3- SET_ON_UP_CLEAR_ON_DOWN (Inverting)
*/

#define    Timer2_CTC_PWM_ACTION        CLEAR_ON_UP_SET_ON_DOWN


/*
 Compare Output Mode, Fast PWM Mode.
 
  Options:
     1- OC_DISCONNECTED
     2- CLEAR_ON_COMP_SET_ON_TOP (Non-Inverting Mode)
     3- SET_ON_COMP_CLEAR_ON_TOP (Inverting)
*/

#define    Timer2_CTC_FAST_PWM_ACTION        CLEAR_ON_COMP_SET_ON_TOP


/*=========================================================================================================*/
/*
Compare Output Mode, Phase Correct PWM Mode

  Options:
     1- 1000UL  KHZ
     2- 2000UL  KHZ
     3- 4000UL  KHZ
     4- 8000UL  KHZ
*/

#define    TIMER_FREQ_CPU                 (8000UL)    // Hint: Set CPU_Freq in KHZ.



#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
