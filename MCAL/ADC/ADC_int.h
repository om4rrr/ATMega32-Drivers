/*
 * ADC_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/ErrorStates.h"

#define   ADC_DISABLE                   0
#define   ADC_ENABLE                    1

#define   INT_DISABLE                   0
#define   INT_ENABLE                    1

#define   ADC_AREF                      0
#define   ADC_AVCC                      1
#define   ADC_INTERNAL_2_56             3


#define   RIGHT_ADJUSTMENT              0
#define   LEFT_ADJUSTMENT               1

#define   ADC_CHANNEL_0                 0
#define   ADC_CHANNEL_1                 1
#define   ADC_CHANNEL_2                 2
#define   ADC_CHANNEL_3                 3
#define   ADC_CHANNEL_4                 4
#define   ADC_CHANNEL_5                 5
#define   ADC_CHANNEL_6                 6
#define   ADC_CHANNEL_7                 7

#define   ADC_SINGLE_CONVERSION         0
#define   ADC_FREE_RUNNING              1
#define   ADC_ANALOG_COMPARATOR         2
#define   ADC_EXTI0                     3
#define   ADC_TIM0_CTC                  4
#define   ADC_TIM0_OVF                  5
#define   ADC_TIM1_CTC_CHANNEL_B        6
#define   ADC_TIM1_OVF                  7
#define   ADC_TIM1_ICU                  8


#define   ADC_PRE_2                     0
#define   ADC_PRE_4                     2
#define   ADC_PRE_8                     3
#define   ADC_PRE_16                    4
#define   ADC_PRE_32                    5
#define   ADC_PRE_64                    6
#define   ADC_PRE_128                   7


typedef struct
{
	u8*  Channel ;
	u16* Result  ;
	u8   Size    ;
	void (*NotificationFunc)(void);
}Chain_t ;


ES_t ADC_enuInit(void);

ES_t ADC_enuEnable(void);

ES_t ADC_enuDisable(void);

ES_t ADC_enuInterruptEnable(void);

ES_t ADC_enuInterruptDisable(void);

ES_t ADC_enuSetPrescaler (u8 Copy_u8Prescaler);

ES_t ADC_enuGetReadSync(u8 Copy_u8Channel, u16* Copy_pu16ReadingValue);

ES_t ADC_enuStartConversionAsynch(u8 Copy_u8Channel, u16* Copy_pu16ReadingValue , void(*Copy_pvoidNotificationFunc)(void));

ES_t ADC_enuStartConversionChainAsynch (Chain_t * Copy_Chain);

ES_t ADC_enuEnableTriggeringMode(u8 Copy_u8TriggeringSource);

ES_t ADC_enuDisableTriggeringMode(void);

#endif /* MCAL_ADC_ADC_INT_H_ */
