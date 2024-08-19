/*
 * EXIT_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/Macro_To_Function.h"


#include "EXTI_config.h"
#include "EXTI_int.h"
#include "EXTI_priv.h"

/*
	Global Pointer to Function => Carry The Adress of ISR func in the main
	Hint : I Made an array of pointers to carry EXTI 0, 1, 2 according to its index

 */
void (*EXTI_CallBack[3]) (void) = { NULL } ;


ES_t EXTI_enuInit(EXTI_t *Copy_pstrEXTILINE) {

	ES_t Local_enuErrorState = ES_OK;

	if(Copy_pstrEXTILINE != NULL) {

		if(Copy_pstrEXTILINE[EXTI_INT1].EXTI_u8State == ENABLED) {

			switch(Copy_pstrEXTILINE[EXTI_INT1].EXTI_u8Sense) {

			case EXTI_FALLING_EDGE : Clr_Bit(MCUCR_REG, MCUCR_ISC10); Set_Bit(MCUCR_REG, MCUCR_ISC11); break;
			case EXTI_RISING_EDGE  : Set_Bit(MCUCR_REG, MCUCR_ISC10); Set_Bit(MCUCR_REG, MCUCR_ISC11); break;
			case EXTI_LOW_LEVEL    : Clr_Bit(MCUCR_REG, MCUCR_ISC10); Clr_Bit(MCUCR_REG, MCUCR_ISC11); break;
			case EXTI_ON_CHANGE    : Set_Bit(MCUCR_REG, MCUCR_ISC10); Clr_Bit(MCUCR_REG, MCUCR_ISC11); break;
			default : Local_enuErrorState = ES_UNSUPPORTED_SENSE_Config;

			}
		}

		if(Copy_pstrEXTILINE[EXTI_INT0].EXTI_u8State == ENABLED) {

			switch(Copy_pstrEXTILINE[EXTI_INT0].EXTI_u8Sense) {

			case EXTI_FALLING_EDGE : Clr_Bit(MCUCR_REG, MCUCR_ISC00); Set_Bit(MCUCR_REG, MCUCR_ISC01); break;
			case EXTI_RISING_EDGE  : Set_Bit(MCUCR_REG, MCUCR_ISC00); Set_Bit(MCUCR_REG, MCUCR_ISC01); break;
			case EXTI_LOW_LEVEL    : Clr_Bit(MCUCR_REG, MCUCR_ISC00); Clr_Bit(MCUCR_REG, MCUCR_ISC01); break;
			case EXTI_ON_CHANGE    : Set_Bit(MCUCR_REG, MCUCR_ISC00); Clr_Bit(MCUCR_REG, MCUCR_ISC01); break;
			default : Local_enuErrorState = ES_UNSUPPORTED_SENSE_Config;

			}
		}

		if(Copy_pstrEXTILINE[EXTI_INT2].EXTI_u8State == ENABLED) {

			switch(Copy_pstrEXTILINE[EXTI_INT2].EXTI_u8Sense) {

			case EXTI_FALLING_EDGE : Clr_Bit(MCUCSR_REG, MCUCSR_ISC2); break;
			case EXTI_RISING_EDGE  : Set_Bit(MCUCSR_REG, MCUCSR_ISC2); break;
			default : Local_enuErrorState = ES_UNSUPPORTED_SENSE_Config;

			}
		}
	}
	else {
		return ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}



ES_t EXTI_enuSetSignalLatch(u8 Copy_u8SenseMode, u8 Copy_u8ExtiLine) {

	ES_t Local_enuErrorState = ES_OK;

	/*  For EXTI0 & EXTI1  */
	if( Copy_u8ExtiLine >= EXTI_INT0 && Copy_u8ExtiLine <= EXTI_INT1 ){

		switch(Copy_u8SenseMode){

		/*   INT Sense Control (Trigger) For EXTI0 & EXTI1   */
		case EXTI_LOW_LEVEL    : Clr_Bit( MCUCR_REG , Copy_u8ExtiLine ); Clr_Bit( MCUCR_REG , Copy_u8ExtiLine + 1 ); break;
		case EXTI_ON_CHANGE    : Set_Bit( MCUCR_REG , Copy_u8ExtiLine ); Clr_Bit( MCUCR_REG , Copy_u8ExtiLine + 1 ); break;
		case EXTI_FALLING_EDGE : Clr_Bit( MCUCR_REG , Copy_u8ExtiLine ); Set_Bit( MCUCR_REG , Copy_u8ExtiLine + 1 ); break;
		case EXTI_RISING_EDGE  : Set_Bit( MCUCR_REG , Copy_u8ExtiLine ); Set_Bit( MCUCR_REG , Copy_u8ExtiLine + 1 ); break;
		default : Local_enuErrorState = ES_UNSUPPORTED_SENSE_Config;

		}
	}

	/*  For EXTI2  */
	else if (Copy_u8ExtiLine == EXTI_INT2) {

		switch(Copy_u8SenseMode) {

		/*    INT Sense Control (Trigger) For EXTI2   */
		case EXTI_FALLING_EDGE : Clr_Bit( MCUCSR_REG , MCUCSR_ISC2);  break;
		case EXTI_RISING_EDGE  : Set_Bit( MCUCSR_REG , MCUCSR_ISC2);  break;
		default : Local_enuErrorState = ES_UNSUPPORTED_SENSE_Config;

		}
	}
	else {

		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}


ES_t   EXTI_enuEnableInterrupt(u8 Copy_u8ExtiLine) {

	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_u8ExtiLine) {
	case EXTI_INT0 : Set_Bit(GICR_REG ,GICR_INT0); break;
	case EXTI_INT1 : Set_Bit(GICR_REG ,GICR_INT1); break;
	case EXTI_INT2 : Set_Bit(GICR_REG ,GICR_INT2); break;
	default : Local_enuErrorState = ES_OUT_OF_RANGE;

	}

	return Local_enuErrorState;
}


ES_t   EXTI_enuDisableInterrupt(u8 Copy_u8ExtiLine) {

	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_u8ExtiLine) {

	case EXTI_INT0 : Clr_Bit(GICR_REG ,GICR_INT0); break;
	case EXTI_INT1 : Clr_Bit(GICR_REG ,GICR_INT1); break;
	case EXTI_INT2 : Clr_Bit(GICR_REG ,GICR_INT2); break;
	default : Local_enuErrorState = ES_OUT_OF_RANGE;

	}

	return Local_enuErrorState;
}




ES_t EXTI_enuClearFlag(u8 Copy_u8ExtiLine) {

	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_u8ExtiLine) {
	case EXTI_INT0 : Set_Bit(GIFR_REG ,GICR_INT0); break;
	case EXTI_INT1 : Set_Bit(GIFR_REG ,GICR_INT1); break;
	case EXTI_INT2 : Set_Bit(GIFR_REG ,GICR_INT2); break;
	default : Local_enuErrorState = ES_OUT_OF_RANGE;

	}

	return Local_enuErrorState;
}




ES_t EXTI_u8GetFlag(u8 Copy_u8ExtiLine, u8 * Copy_pu8IntFlag){

	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_u8ExtiLine) {

	case EXTI_INT0 : *Copy_pu8IntFlag = Get_Bit(GICR_REG ,GICR_INT0); break;
	case EXTI_INT1 : *Copy_pu8IntFlag = Get_Bit(GICR_REG ,GICR_INT1); break;
	case EXTI_INT2 : *Copy_pu8IntFlag = Get_Bit(GICR_REG ,GICR_INT2); break;
	default : Local_enuErrorState = ES_OUT_OF_RANGE;

	}

	return Local_enuErrorState;
}





ES_t EXTI_enuSetCallBack(void (*Copy_pvoidCallBack)(void) , u8 Copy_u8ExtiLine ) {

	ES_t Local_enuErrorState = ES_OK;


	if(Copy_pvoidCallBack != NULL) {

		if(Copy_u8ExtiLine >= EXTI_INT0 && Copy_u8ExtiLine <= EXTI_INT2) {

			EXTI_CallBack[Copy_u8ExtiLine] = Copy_pvoidCallBack;
		}
		else {

			return ES_OUT_OF_RANGE;
		}
	}
	else {

		return ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if( EXTI_CallBack[0] != NULL ){

		EXTI_CallBack[0]();
		EXTI_enuClearFlag( EXTI_INT0 );

	}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if( EXTI_CallBack[1] != NULL ){

		EXTI_CallBack[1]();
		EXTI_enuClearFlag( EXTI_INT1 );

	}
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if( EXTI_CallBack[2] != NULL ){

		EXTI_CallBack[2]();
		EXTI_enuClearFlag( EXTI_INT2 );

	}
}




