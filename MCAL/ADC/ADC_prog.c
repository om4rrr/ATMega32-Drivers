/*
 * ADC_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "../EXTI/Interrupt.h"

#include "ADC_int.h"
#include "ADC_config.h"
#include "ADC_priv.h"


// Global pointer to carry the conversion result in the Asynchronous execution
static u16 * ADC_pu16AsynchConversionResult = NULL;

// Global pointer to function to carry the notification function called by ISR
static void (* ADC_pvidNotificationFunc)(void)= NULL;

// Global flag for the ADC ISR State
static u8 Global_u8ADCISRSource;

// Global flag for the ADC Busy State
static u8 Global_u8ADCState= IDLE;

// Global pointer to carry the chain Channel
static u8 * Global_pu8ADCChainChannel;

// Global variable to carry the chain size
static u8 Global_u8ADCChainSize;

// Global variable to indicate for the current ADC Chain
static u8 Global_u8ADCIndex;



ES_t ADC_enuInit(void) {
	ES_t Local_enuErrorState = ES_OK;

	/*   Select The Voltage Reference    */

#if   ADC_VREF == ADC_AREF

	Clr_Bit(ADMUX, ADMUX_REFS0); Clr_Bit(ADMUX, ADMUX_REFS1);

#elif ADC_VREF == ADC_AVCC

	Set_Bit(ADMUX, ADMUX_REFS0); Clr_Bit(ADMUX, ADMUX_REFS1);

#elif ADC_VREF == ADC_INTERNAL_2_56

	Set_Bit(ADMUX, REFS0); Set_Bit(ADMUX, REFS1);

#else
#error "Wrong ADC Voltage Reference Configuration"
#endif


	//  Select The Adjustment

#if   ADC_ADJUSTMENT == RIGHT_ADJUSTMENT

	Clr_Bit(ADMUX, ADMUX_ADLAR);

#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT

	Set_Bit(ADMUX, ADMUX_ADLAR);

#else
#error "Wrong ADC ADJUSTMENT Configuration"
#endif


	// Set Prescaler Value

	if(ADC_PRESCALER >= ADC_PRE_2 && ADC_PRESCALER <= ADC_PRE_128) {

		ADCSRA &= ADC_PRESCALER_MASK ;
		ADCSRA |= ADC_PRESCALER ;
	}
	else {

		Local_enuErrorState = ES_UNSUPPORTED_prescaller_Config;
	}


	//  ENABLE The Peripheral and Interrupt

#if ADC_STATUS == ADC_DISABLE

	Clr_Bit(ADCSRA , ADCSRA_ADEN) ;

#elif ADC_STATUS == ADC_ENABLE

	Set_Bit(ADCSRA , ADCSRA_ADEN) ;

#else
#error "Wrong ADC STATUS Configuration"
#endif


#if INT_STATUS == INT_DISABLE

	Clr_Bit(ADCSRA , ADCSRA_ADIE) ;

#elif INT_STATUS == INT_ENABLE

	Set_Bit(ADCSRA , ADCSRA_ADIE) ;

#else
#error "Wrong ADC INT_STATUS Configuration"
#endif

	return Local_enuErrorState;
}


ES_t ADC_enuEnable(void) {
	ES_t Local_enuErrorState = ES_OK;

	Set_Bit(ADCSRA , ADCSRA_ADEN) ;

	return Local_enuErrorState;
}


ES_t ADC_enuDisable(void) {
	ES_t Local_enuErrorState = ES_OK;

	Clr_Bit(ADCSRA , ADCSRA_ADEN) ;

	return Local_enuErrorState;
}



ES_t ADC_enuInterruptEnable(void) {
	ES_t Local_enuErrorState = ES_OK;

	Set_Bit(ADCSRA , ADCSRA_ADIE) ;

	return Local_enuErrorState;
}


ES_t ADC_enuInterruptDisable(void) {
	ES_t Local_enuErrorState = ES_OK;

	Clr_Bit(ADCSRA , ADCSRA_ADIE) ;

	return Local_enuErrorState;
}




ES_t ADC_enuEnableTriggeringMode(u8 Copy_u8TriggeringSource) {
	ES_t Local_enuErrorState = ES_OK;

	Clr_Bit(ADCSRA, ADCSRA_ADATE);

	switch(Copy_u8TriggeringSource) {

	case ADC_FREE_RUNNING       : Clr_Bit(SFIOR, SFIOR_ADTS0); Clr_Bit(SFIOR, SFIOR_ADTS1); Clr_Bit(SFIOR, SFIOR_ADTS2); break;
	case ADC_ANALOG_COMPARATOR  : Set_Bit(SFIOR, SFIOR_ADTS0); Clr_Bit(SFIOR, SFIOR_ADTS1); Clr_Bit(SFIOR, SFIOR_ADTS2); break;
	case ADC_EXTI0              : Clr_Bit(SFIOR, SFIOR_ADTS0); Set_Bit(SFIOR, SFIOR_ADTS1); Clr_Bit(SFIOR, SFIOR_ADTS2); break;
	case ADC_TIM0_CTC           : Set_Bit(SFIOR, SFIOR_ADTS0); Set_Bit(SFIOR, SFIOR_ADTS1); Clr_Bit(SFIOR, SFIOR_ADTS2); break;
	case ADC_TIM0_OVF           : Clr_Bit(SFIOR, SFIOR_ADTS0); Clr_Bit(SFIOR, SFIOR_ADTS1); Set_Bit(SFIOR, SFIOR_ADTS2); break;
	case ADC_TIM1_CTC_CHANNEL_B : Set_Bit(SFIOR, SFIOR_ADTS0); Clr_Bit(SFIOR, SFIOR_ADTS1); Set_Bit(SFIOR, SFIOR_ADTS2); break;
	case ADC_TIM1_OVF           : Clr_Bit(SFIOR, SFIOR_ADTS0); Set_Bit(SFIOR, SFIOR_ADTS1); Set_Bit(SFIOR, SFIOR_ADTS2); break;
	case ADC_TIM1_ICU           : Set_Bit(SFIOR, SFIOR_ADTS0); Set_Bit(SFIOR, SFIOR_ADTS1); Set_Bit(SFIOR, SFIOR_ADTS2); break;
	default : Local_enuErrorState = ES_UNSUPPORTED_trigger_source_Config;

	}

	Set_Bit(ADCSRA, ADCSRA_ADATE);

	return Local_enuErrorState;
}

ES_t ADC_enuDisableTriggeringMode(void) {
	ES_t Local_enuErrorState = ES_OK;

	Clr_Bit(ADCSRA, ADCSRA_ADATE);

	return Local_enuErrorState;
}




ES_t ADC_enuSetPrescaler (u8 Copy_u8Prescaler) {
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_u8Prescaler >= ADC_PRE_2 && Copy_u8Prescaler <= ADC_PRE_128) {

		// Set Prescaler Value
		ADCSRA &= ADC_PRESCALER_MASK ;
		ADCSRA |= Copy_u8Prescaler ;

	}
	else {

		Local_enuErrorState = ES_UNSUPPORTED_prescaller_Config;
	}

	return Local_enuErrorState;
}




ES_t   ADC_enuGetReadSync(u8 Copy_u8Channel, u16* Copy_pu16ReadingValue) {
	ES_t Local_enuErrorState = ES_OK;

	u32 Local_u32TimeOutCounter = 0;

	if(Copy_pu16ReadingValue != NULL) {

		if(Global_u8ADCState == IDLE) {

			// ADC is now Busy
			Global_u8ADCState = BUSY;

			// Set required channel
			ADMUX &= ADC_CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			// Start Conversion
			Set_Bit(ADCSRA, ADCSRA_ADSC);


			while(!Get_Bit(ADCSRA, ADCSRA_ADIF) && Local_u32TimeOutCounter < ADC_TIMEOUT) {

				Local_u32TimeOutCounter++;
			}

			if(Local_u32TimeOutCounter == ADC_TIMEOUT) {

				Local_enuErrorState = ES_TIMEOUT_STATE;
			}
			else {

				// Clear the interrupt flag
				Set_Bit(ADCSRA, ADCSRA_ADIF);

				// Return Conversion Result
#if   ADC_ADJUSTMENT == RIGHT_ADJUSTMENT

				*Copy_pu16ReadingValue  = (ADCL | ((u16)ADCH << 8));

#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT

				*Copy_pu16ReadingValue  = ADCH;

#else
#error "Wrong ADC ADJUSTMENT Configuration"
#endif

			}

			// ADC is now IDLE
			Global_u8ADCState = IDLE;
		}
		else {

			Local_enuErrorState = ES_BUSY_STATE;
		}
	}
	else {

		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}




ES_t   ADC_enuStartConversionAsynch(u8 Copy_u8Channel, u16* Copy_pu16ReadingValue , void(*Copy_pvoidNotificationFunc)(void)) {
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_pu16ReadingValue != NULL && Copy_pvoidNotificationFunc != NULL) {

		if(Global_u8ADCState == IDLE) {

			// ADC is now Busy
			Global_u8ADCState = BUSY;

			// set ISR state
			Global_u8ADCISRSource = SINGLE_CHANNEL_ASYNCH;

			// Initialize the global result pointer
			ADC_pu16AsynchConversionResult = Copy_pu16ReadingValue;

			// Set Callback Funcation
			ADC_pvidNotificationFunc = Copy_pvoidNotificationFunc;

			// Set required channel
			ADMUX &= ADC_CHANNEL_MASK;
			ADMUX |= Copy_u8Channel;

			// Start Conversion
			Set_Bit(ADCSRA, ADCSRA_ADSC);

			// ADC Conversion Complete Interrupt Enable
			Set_Bit(ADCSRA , ADCSRA_ADIE) ;
		}
		else {

			Local_enuErrorState = ES_BUSY_STATE;
		}
	}
	else {

		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}




ES_t ADC_enuStartConversionChainAsynch (Chain_t * Copy_Chain) {
	ES_t Local_enuErrorState = ES_OK;

	if(Copy_Chain != NULL && Copy_Chain->Channel != NULL && Copy_Chain->Result != NULL && Copy_Chain->NotificationFunc) {

		if(Global_u8ADCState == IDLE) {

			// ADC is now Busy
			Global_u8ADCState = BUSY;

			// Initialize the global result pointer
			ADC_pu16AsynchConversionResult = Copy_Chain->Result ;

			// Initialize the global Chain Channel pointer
			Global_pu8ADCChainChannel = Copy_Chain->Channel ;

			// Set ChainSize to global Chain Size Var.
			Global_u8ADCChainSize = Copy_Chain->Size ;

			// Set Callback Funcation
			ADC_pvidNotificationFunc = Copy_Chain->NotificationFunc;

			// Set Index to first element
			Global_u8ADCIndex = 0;

			// Set required channel
			ADMUX &= ADC_CHANNEL_MASK;
			ADMUX |= Global_pu8ADCChainChannel[Global_u8ADCIndex];

			// Start Conversion
			Set_Bit(ADCSRA, ADCSRA_ADSC);

			// ADC Conversion Complete Interrupt Enable
			Set_Bit(ADCSRA , ADCSRA_ADIE) ;
		}
		else {

			Local_enuErrorState = ES_BUSY_STATE;
		}
	}
	else {

		Local_enuErrorState = ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


ISR(VECT_ADC)
{
	if(Global_u8ADCISRSource == SINGLE_CHANNEL_ASYNCH) {

		// Get Conversion Result
#if   ADC_ADJUSTMENT == RIGHT_ADJUSTMENT

		*ADC_pu16AsynchConversionResult  = (ADCL | ((u16)ADCH << 8));

#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT

		*ADC_pu16AsynchConversionResult  = ADCH;

#else
#error "Wrong ADC ADJUSTMENT Configuration"
#endif

		// ADC is now IDLE
		Global_u8ADCState = IDLE;

		// Call Notification Function
		ADC_pvidNotificationFunc() ;

		// Disable the Conversion Complete Interrupt
		Clr_Bit(ADCSRA , ADCSRA_ADIE);

	}
	else {

		// Get Conversion Result
#if   ADC_ADJUSTMENT == RIGHT_ADJUSTMENT

		*ADC_pu16AsynchConversionResult  = (ADCL | ((u16)ADCH << 8));

#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT

		*ADC_pu16AsynchConversionResult  = ADCH;

#else
#error "Wrong ADC ADJUSTMENT Configuration"
#endif

		Global_u8ADCIndex++;

		if(Global_u8ADCIndex == Global_u8ADCChainSize) {

			// ADC is now IDLE
			Global_u8ADCState = IDLE;

			// Call Notification Function
			ADC_pvidNotificationFunc() ;

			// Disable the Conversion Complete Interrupt
			Clr_Bit(ADCSRA , ADCSRA_ADIE);

		}
		else {

			// Set required channel
			ADMUX &= ADC_CHANNEL_MASK;
			ADMUX |= Global_pu8ADCChainChannel[Global_u8ADCIndex];

			// Start Conversion
			Set_Bit(ADCSRA, ADCSRA_ADSC);
		}
	}
}







