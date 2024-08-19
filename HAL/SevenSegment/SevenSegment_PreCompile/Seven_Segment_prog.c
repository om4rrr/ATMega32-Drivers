/*

 * Seven_Segment_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#include "../../../SERVICE/stdTypes.h"
#include "../../../SERVICE/ErrorStates.h"
#include "../../../SERVICE/Macro_To_Function.h"

#include "Seven_Segment_priv.h"
#include "Seven_Segment_config.h"

#include "../../../MCAL/DIO/DIO_int.h"

ES_t Seven_Segment_enuInit(void)
{
	ES_t Local_ErrorState = ES_NOK;

	u32 Local_u32Check = 0;

		Local_u32Check |= (DIO_enuSetPinDirection(SEG_APORT, SEG_APIN, DIO_u8OUTPUT) << 0);
		Local_u32Check |= (DIO_enuSetPinDirection(SEG_BPORT, SEG_BPIN, DIO_u8OUTPUT) << 3);
		Local_u32Check |= (DIO_enuSetPinDirection(SEG_CPORT, SEG_CPIN, DIO_u8OUTPUT) << 6);
		Local_u32Check |= ((u32)DIO_enuSetPinDirection(SEG_DPORT, SEG_DPIN, DIO_u8OUTPUT) << 9);
		Local_u32Check |= ((u32)DIO_enuSetPinDirection(SEG_EPORT, SEG_EPIN, DIO_u8OUTPUT) << 12);
		Local_u32Check |= ((u32)DIO_enuSetPinDirection(SEG_FPORT, SEG_FPIN, DIO_u8OUTPUT) << 15);
		Local_u32Check |= ((u32)DIO_enuSetPinDirection(SEG_GPORT, SEG_GPIN, DIO_u8OUTPUT) << 18);

#if SEG_CMN_PIN <= DIO_u8PIN7 && SEG_CMN_PORT <= DIO_u8PORTD
	DIO_enuSetPinDirection(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8OUTPUT);
#elif 	SEG_CMN_PIN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

#else
#error "Your Common Pin has a wrong Selection"
#endif

#if SEG_DOT_PIN <= DIO_u8PIN7 && SEG_DOT_PORT <= DIO_u8PORTD
	DIO_enuSetPinDirection(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8OUTPUT);
#elif 	SEG_DOT_PIN == NOT_CONNECTED || SEG_DOT_PORT == NOT_CONNECTED

#else
#error "Your Dot Pin has a wrong Selection"
#endif


	u8 Local_u8Iterator;
	for(Local_u8Iterator = 0; Local_u8Iterator < BITS_NUM * SEG_PINS_NUM ; Local_u8Iterator += BITS_NUM)
	{
		if(((Local_u32Check >> Local_u8Iterator) & 0x00000007) != ES_OK)
		{
			return ES_NOK;
		}
	}

	Local_ErrorState = ES_OK;
	return Local_ErrorState;
}

ES_t Seven_Segment_enuDisplayNum(u8 Copy_u8DisplyedNum)
{
	ES_t Local_ErrorState = ES_NOK;

	if(Copy_u8DisplyedNum < 10)
	{
		u32 Local_u32Check = 0;

#if SEG_TYPE == COMMON_CTHODE
		Local_u32Check |= (DIO_enuSetPinValue(SEG_APORT, SEG_APIN, (Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_A_PIN)&1)<<0);
		Local_u32Check |= (DIO_enuSetPinValue(SEG_BPORT, SEG_BPIN, (Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_B_PIN)&1)<<3);
		Local_u32Check |= (DIO_enuSetPinValue(SEG_CPORT, SEG_CPIN, (Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_C_PIN)&1)<<6);
		Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_DPORT, SEG_DPIN, (Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_D_PIN)&1)<<9);
		Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_EPORT, SEG_EPIN, (Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_E_PIN)&1)<<12);
		Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_FPORT, SEG_FPIN, (Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_F_PIN)&1)<<15);
		Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_GPORT, SEG_GPIN, (Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_G_PIN)&1)<<18);
#elif SEG_TYPE == COMMON_ANODE
		Local_u32Check |= (DIO_enuSetPinValue(SEG_APORT, SEG_APIN, !((Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_A_PIN)&1))<<0);
		Local_u32Check |= (DIO_enuSetPinValue(SEG_BPORT, SEG_BPIN, !((Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_B_PIN)&1))<<3);
		Local_u32Check |= (DIO_enuSetPinValue(SEG_CPORT, SEG_CPIN, !((Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_C_PIN)&1))<<6);
		Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_DPORT, SEG_DPIN, !((Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_D_PIN)&1))<<9);
		Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_EPORT, SEG_EPIN, !((Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_E_PIN)&1))<<12);
		Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_FPORT, SEG_FPIN, !((Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_F_PIN)&1))<<15);
		Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_GPORT, SEG_GPIN, !((Seven_Segment_Au8DisplayedNumbers[Copy_u8DisplyedNum]>>SEG_G_PIN)&1))<<18);
#else
#error "Your Seven_Segment Type has wrong Selection"
#endif

		u8 Local_u8Iterator;
		for(Local_u8Iterator = 0; Local_u8Iterator < BITS_NUM * SEG_PINS_NUM ; Local_u8Iterator += BITS_NUM)
		{
			if(((Local_u32Check >> Local_u8Iterator) & 7) != ES_OK)
			{
				return ES_NOK;
			}
		}
	}
	else
	{
		Local_ErrorState = ES_OUT_OF_RANGE;
	}
	Local_ErrorState = ES_OK;
	return Local_ErrorState;
}

ES_t Seven_Segment_enuEnableCommon(void)
{
	ES_t Local_ErrorState = ES_NOK;

#if SEG_CMN_PIN <= DIO_u8PIN7 && SEG_CMN_PORT <= DIO_u8PORTD
#if SEG_TYPE == COMMON_CTHODE
	DIO_enuSetPinValue(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8LOW);
#elif SEG_TYPE == COMMON_ANODE
	DIO_enuSetPinValue(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8HIGH);
#else
#error "Your Seven_Segment Type has wrong Selection"
#endif
#elif 	SEG_CMN_PIN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

#else
#error "Your Common Pin has a wrong Selection"
#endif

	Local_ErrorState = ES_OK;
	return Local_ErrorState;
}

ES_t Seven_Segment_enuDisableCommon(void)
{
	ES_t Local_ErrorState = ES_NOK;

#if SEG_CMN_PIN <= DIO_u8PIN7 && SEG_CMN_PORT <= DIO_u8PORTD
#if SEG_TYPE == COMMON_CTHODE
	DIO_enuSetPinValue(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8HIGH);
#elif SEG_TYPE == COMMON_ANODE
	DIO_enuSetPinValue(SEG_CMN_PORT, SEG_CMN_PIN, DIO_u8LOW);
#else
#error "Your Seven_Segment Type has wrong Selection"
#endif
#elif 	SEG_CMN_PIN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

#else
#error "Your Common Pin has a wrong Selection"
#endif

	Local_ErrorState = ES_OK;
	return Local_ErrorState;
}

ES_t Seven_Segment_enuEnableDot(void)
{
	ES_t Local_ErrorState = ES_NOK;

#if SEG_DOT_PIN <= DIO_u8PIN7 && SEG_DOT_PORT <= DIO_u8PORTD
#if SEG_TYPE == COMMON_CTHODE
	DIO_enuSetPinValue(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8LOW);
#elif SEG_TYPE == COMMON_ANODE
	DIO_enuSetPinValue(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8HIGH);
#else
#error "Your Seven_Segment Type has wrong Selection"
#endif
#elif 	SEG_DOT_PIN == NOT_CONNECTED || SEG_DOT_PORT == NOT_CONNECTED

#else
#error "Your Dot Pin has a wrong Selection"
#endif

	Local_ErrorState = ES_OK;
	return Local_ErrorState;
}

ES_t Seven_Segment_enuDisableDot(void)
{
	ES_t Local_ErrorState = ES_NOK;

#if SEG_DOT_PIN <= DIO_u8PIN7 && SEG_DOT_PORT <= DIO_u8PORTD
#if SEG_TYPE == COMMON_CTHODE
	DIO_enuSetPinValue(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8HIGH);
#elif SEG_TYPE == COMMON_ANODE
	DIO_enuSetPinValue(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8LOW);
#else
#error "Your Seven_Segment Type has wrong Selection"
#endif
#elif 	SEG_DOT_PIN == NOT_CONNECTED || SEG_DOT_PORT == NOT_CONNECTED

#else
#error "Your Dot Pin has a wrong Selection"
#endif

	Local_ErrorState = ES_OK;
	return Local_ErrorState;
}

ES_t Seven_Segment_enuClear(void)
{
	ES_t Local_ErrorState = ES_NOK;

	u32 Local_u32Check = 0;

#if SEG_TYPE == COMMON_CTHODE
	Local_u32Check |= (DIO_enuSetPinValue(SEG_APORT, SEG_APIN, DIO_u8LOW)<<0);
	Local_u32Check |= (DIO_enuSetPinValue(SEG_BPORT, SEG_BPIN, DIO_u8LOW)<<3);
	Local_u32Check |= (DIO_enuSetPinValue(SEG_CPORT, SEG_CPIN, DIO_u8LOW)<<6);
	Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_DPORT, SEG_DPIN, DIO_u8LOW)<<9);
	Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_EPORT, SEG_EPIN, DIO_u8LOW)<<12);
	Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_FPORT, SEG_FPIN, DIO_u8LOW)<<15);
	Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_GPORT, SEG_GPIN, DIO_u8LOW)<<18);
#elif SEG_TYPE == COMMON_ANODE
	Local_u32Check |= (DIO_enuSetPinValue(SEG_APORT, SEG_APIN, DIO_u8HIGH)<<0);
	Local_u32Check |= (DIO_enuSetPinValue(SEG_BPORT, SEG_BPIN, DIO_u8HIGH)<<3);
	Local_u32Check |= (DIO_enuSetPinValue(SEG_CPORT, SEG_CPIN, DIO_u8HIGH)<<6);
	Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_DPORT, SEG_DPIN, DIO_u8HIGH)<<9);
	Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_EPORT, SEG_EPIN, DIO_u8HIGH)<<12);
	Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_FPORT, SEG_FPIN, DIO_u8HIGH)<<15);
	Local_u32Check |= ((u32)DIO_enuSetPinValue(SEG_GPORT, SEG_GPIN, DIO_u8HIGH)<<18);
#else
#error "Your Seven_Segment Type has wrong Selection"
#endif

	u8 Local_u8Iterator;
	for(Local_u8Iterator = 0; Local_u8Iterator < BITS_NUM * SEG_PINS_NUM ; Local_u8Iterator += BITS_NUM)
	{
		if(((Local_u32Check >> Local_u8Iterator) & 7) != ES_OK)
		{
			return ES_NOK;
		}
	}

#if SEG_DOT_PIN <= DIO_u8PIN7 && SEG_DOT_PORT <= DIO_u8PORTD
#if SEG_TYPE == COMMON_CTHODE
	DIO_enuSetPinValue(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8LOW);
#elif SEG_TYPE == COMMON_ANODE
	DIO_enuSetPinValue(SEG_DOT_PORT, SEG_DOT_PIN, DIO_u8HIGH);
#else
#error "Your Seven_Segment Type has wrong Selection"
#endif
#elif 	SEG_DOT_PIN == NOT_CONNECTED || SEG_DOT_PORT == NOT_CONNECTED

#else
#error "Your Dot Pin has a wrong Selection"
#endif

	Local_ErrorState = ES_OK;
	return Local_ErrorState;
}


