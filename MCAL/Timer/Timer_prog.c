#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "../EXTI/Interrupt.h"
#include "../DIO/DIO_priv.h"

#include "Timer_int.h"
#include "Timer_priv.h"
#include "Timer_config.h"

/*===================Static Global Variable needed in the ISR of each OVF timer interrupt===================*/
static u32 Global_u32Timer0Counter = 0;
static u32 Global_u32Timer1Counter = 0;
static u32 Global_u32Timer2Counter = 0;

/*===========================Static Global Variable to hold timers preload value===========================*/
static u32 Global_u32Timer0PreloadValue = 0;
static u32 Global_u32Timer1PreloadValue = 0;
static u32 Global_u32Timer2PreloadValue = 0;

/*========================Static Global Variable to hold timers required time counts=======================*/
static u32 Global_u32Timer0ReqTimeCounts;
static u32 Global_u32Timer1ReqTimeCounts;
static u32 Global_u32Timer2ReqTimeCounts;

/*==========================================Static Global Falgs ==========================================*/
static u8 Global_u8Timer0CTCFlag = 0;
static u8 Global_u8Timer1CTCFlag = 0;
static u8 Global_u8Timer2CTCFlag = 0;

/*=============================Static Global Variable to hold timers CTC Valus============================*/
static u8  Global_u8Timer0CTCValue;
static u32 Global_u32Timer1CTCValue;
static u8  Global_u8Timer2CTCValue;




/*===========Global Pointer to array of Function to Hold the Call Back Function Address for Timer==========*/
static void (*TIMERS_pvCallBackFunc[8])(void) = {NULL} ;  /*===we have 8 interrupt sources in timer===*/


/*=================================================TIMER 0=================================================*/

ES_t TIMER0_enuInit(void)
{
	ES_t Local_enuErrorState = ES_OK;

/*       Set Timer0 Working Mode       */	
#if    TIMER0_WORKING_MODE == TIMER_MODE

	/*   Set Timer0 Prescaler   */
	TCCR0 &= TIMER_PRESCALER_MASk;
	TCCR0 |= TIMER0_PRESCALER;

#elif  TIMER0_WORKING_MODE == COUNTER_MODE

	/*   Set Counter0 Trigger  */
	TCCR0 &= TIMER_COUNTER_MASk;
	TCCR0 |= COUNTER0_TRIGGER;

#else
#error "Timer Working Mode is Wrong"
#endif


/*       Set Timer0 WaveForm Generation Mode       */
#if   TIMER0_WAVE_GENER_MODE == TIMER_OVF_MODE

	Clr_Bit(TCCR0, TCCR0_WGM00); Clr_Bit(TCCR0, TCCR0_WGM01);
	
      /*   Timer0 Overflow Interrupt Enable   */
#if   TIMER0_OVERFLOW_INTERRUPT == DISABLED

	Clr_Bit(TIMSK, TIMSK_TOIE0) ;

#elif TIMER0_OVERFLOW_INTERRUPT == ENABLED

	Set_Bit(TIMSK, TIMSK_TOIE0);

#else
#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
#endif
	

#elif  TIMER0_WAVE_GENER_MODE == TIMER_CTC_MODE

     Clr_Bit(TCCR0, TCCR0_WGM00); Set_Bit(TCCR0, TCCR0_WGM01);
	 
       /*      Set Compare Match Output Mode      */
#if    Timer0_CTC_NON_PWM_ACTION == OC_DISCONNECTED	 

	 Clr_Bit(TCCR0, TCCR0_COM00); Clr_Bit(TCCR0, TCCR0_COM01);
	
#elif  Timer0_CTC_NON_PWM_ACTION == TOGGLE_OC

     Set_Bit(TCCR0, TCCR0_COM00); Clr_Bit(TCCR0, TCCR0_COM01);

#elif  Timer0_CTC_NON_PWM_ACTION == SET_OC

     Set_Bit(TCCR0, TCCR0_COM00); Set_Bit(TCCR0, TCCR0_COM01);

#elif  Timer0_CTC_NON_PWM_ACTION == CLEAR_OC

     Clr_Bit(TCCR0, TCCR0_COM00); Set_Bit(TCCR0, TCCR0_COM01);
	 
#else
#error "UNSupported CTC Mode"
#endif
	 
	 
/*     Timer0 Compare Match Interrupt Enable    */
#if   TIMER0_CTC_INTERRUPT == DISABLED

	Clr_Bit(TIMSK, TIMSK_OCIE0) ;

#elif TIMER0_CTC_INTERRUPT == ENABLED

	Set_Bit(TIMSK, TIMSK_OCIE0);

#else
#error "Wrong TIMER0_CTC_INTERRUPT Config"
#endif
	 
	 
	 
#elif  TIMER0_WAVE_GENER_MODE == TIMER_PWM_MODE

       Set_Bit(TCCR0, TCCR0_WGM00); Clr_Bit(TCCR0, TCCR0_WGM01);
	   
/*      Set Compare Match Output Mode         */
#if    Timer0_CTC_PWM_ACTION == OC_DISCONNECTED	 

	 Clr_Bit(TCCR0, TCCR0_COM00); Clr_Bit(TCCR0, TCCR0_COM01);
	
#elif  Timer0_CTC_PWM_ACTION == CLEAR_ON_UP_SET_ON_DOWN

     Clr_Bit(TCCR0, TCCR0_COM00); Set_Bit(TCCR0, TCCR0_COM01);

#elif  Timer0_CTC_PWM_ACTION == SET_ON_UP_CLEAR_ON_DOWN

     Set_Bit(TCCR0, TCCR0_COM00); Set_Bit(TCCR0, TCCR0_COM01);
	 
#else
#error "UNSupported CTC Mode"
#endif


#elif  TIMER0_WAVE_GENER_MODE == TIMER_FASTPWM_MODE

       Set_Bit(TCCR0, TCCR0_WGM00); Set_Bit(TCCR0, TCCR0_WGM01);
	   
/*          Set Compare Match Output Mode          */
#if    Timer0_CTC_FAST_PWM_ACTION == OC_DISCONNECTED	 

	 Clr_Bit(TCCR0, TCCR0_COM00); Clr_Bit(TCCR0, TCCR0_COM01);
	
#elif  Timer0_CTC_FAST_PWM_ACTION == CLEAR_ON_COMP_SET_ON_TOP

     Clr_Bit(TCCR0, TCCR0_COM00); Set_Bit(TCCR0, TCCR0_COM01);

#elif  Timer0_CTC_FAST_PWM_ACTION == SET_ON_COMP_CLEAR_ON_TOP

     Set_Bit(TCCR0, TCCR0_COM00); Set_Bit(TCCR0, TCCR0_COM01);
	 
#else
#error "UNSupported CTC Mode"
#endif	 
	 
#else
#error "Unsupported Timer WaveForm Generation Mode"
#endif
	
	return Local_enuErrorState;
}



ES_t Timer0_enuSetPreLoadValue(u8 Copy_u8PreLoadValue) 
{
	ES_t Local_enuErrorState = ES_OK;

    if(Copy_u8PreLoadValue <= TIMER0_MAX)
	{
		// Set the Required Preload Value
	    TCNT0 = Copy_u8PreLoadValue ;
	}
	else 
	{
		return ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}




ES_t TIMER0_voidSetCTCValue(u8 Copy_u8CTCValue) 
{
	
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_u8CTCValue <= TIMER0_MAX)
	{
		OCR0 = Copy_u8CTCValue;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}





ES_t TIMER0_enuGetTimerCounterValue(u8* Copy_Pu8TimerCounterValue)
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_Pu8TimerCounterValue != NULL)
	{
		*Copy_Pu8TimerCounterValue = TCNT0;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
		
	return Local_enuErrorState;
}



ES_t TIMER0_enuSetDesiredTime_ms(f32 Copy_u32Time_ms)
{
	
	ES_t Local_enuErrorState = ES_OK;
	
	// Calculate OverFlow Time
	f32 Local_f32OverFlowTime = TIMER0_NUM_TICKS * ((f32)TIMER0_PRESCALER_VALUE / TIMER_FREQ_CPU);

	// Calculate Number of OverFlow
	f32 Local_f32NumberOfOverFlow = Copy_u32Time_ms / Local_f32OverFlowTime;
	
	if(TIMER0_WAVE_GENER_MODE == TIMER_OVF_MODE)
	{
		// (T_req > T_ovf) or (T_req < T_ovf)
		if(Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow != 0.0) {

			// Rounding The Number To The Nearest Integer Number
			Global_u32Timer0ReqTimeCounts = (u32)Local_f32NumberOfOverFlow + 1;

			// Calculate preLoad Value
			Global_u32Timer0PreloadValue = ((u32)Local_f32NumberOfOverFlow + 1 - Local_f32NumberOfOverFlow ) * TIMER0_NUM_TICKS;

			// Set the Required Preload Value
			TCNT0 = Global_u32Timer0PreloadValue ;
		}
		else 
		{
			Global_u32Timer0ReqTimeCounts = (u32)Local_f32NumberOfOverFlow;
		}
			// Enable OverFlow Interrupt
			Set_Bit(TIMSK, TIMSK_TOIE0);
	}
	else if(TIMER0_WAVE_GENER_MODE == TIMER_CTC_MODE)
	{
		if(Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow < 1){
			// Clear Timer0 CTC Flag 
			Global_u8Timer0CTCFlag = 0;
			
			Global_u32Timer0ReqTimeCounts = 1;
			
			// Calculate Timer0CTCValue Value
			Global_u8Timer0CTCValue = (Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow) * TIMER0_NUM_TICKS;
			
			// Set OCR0 Value
			OCR0 = 	Global_u8Timer0CTCValue;
		}
		else if(Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow > 1) {
			// Set Timer0 CTC Flag
			Global_u8Timer0CTCFlag = 1;
			
			// Rounding The Number To The Nearest Integer Number
			Global_u32Timer0ReqTimeCounts = (u32)Local_f32NumberOfOverFlow + 2;
			
			// Calculate Timer0CTCValue Value
			Global_u8Timer0CTCValue = (Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow) * TIMER0_NUM_TICKS;
			
		    // Set OCR0 Value
            OCR0 = Global_u8Timer0CTCValue; 
		}
		else 
		{
			// Clear Timer0 CTC Flag
			Global_u8Timer0CTCFlag = 0;
			
			Global_u32Timer0ReqTimeCounts = 1;
			Global_u8Timer0CTCValue = 0xff;
			
			// Set OCR0 Value
			OCR0 = Global_u8Timer0CTCValue;
		}
		// Enable Compare Match Interrupt
		Set_Bit(TIMSK, TIMSK_OCIE0);
			
	}
	else
	{
		Local_enuErrorState = ES_NOK;
	}

	return Local_enuErrorState;
}



ES_t TIMER0_enuPWMSetDutyCycle(f32 Copy_f32DutyCycle)
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_f32DutyCycle >= 0.0 && Copy_f32DutyCycle <= 100.0)
	{
		u8 Local_u8TimerTicks = TIMER0_NUM_TICKS;
		if(Copy_f32DutyCycle == 100.0) 
		{
			Local_u8TimerTicks--;
		}
		
#if  TIMER0_WAVE_GENER_MODE == TIMER_PWM_MODE
	
	   /*    Non_Inverted Mode     */
#if    Timer0_CTC_PWM_ACTION == CLEAR_ON_UP_SET_ON_DOWN

     OCR0 = Local_u8TimerTicks - (u8)((Copy_f32DutyCycle / 100.0)   * Local_u8TimerTicks);

	   /*       Inverted Mode     */
#elif  Timer0_CTC_PWM_ACTION == SET_ON_UP_CLEAR_ON_DOWN

     OCR0 = (u8)((Copy_f32DutyCycle / 100.0)   * Local_u8TimerTicks);
	 
#else
#error "UNSupported CTC Mode"
#endif


#elif  TIMER0_WAVE_GENER_MODE == TIMER_FASTPWM_MODE
	
	   /*    Non-Inverted Mode    */
#if    Timer0_CTC_FAST_PWM_ACTION == CLEAR_ON_COMP_SET_ON_TOP

     OCR0 = (u8)((Copy_f32DutyCycle / 100.0)   * Local_u8TimerTicks);

	   /*      Inverted Mode     */
#elif  Timer0_CTC_FAST_PWM_ACTION == SET_ON_COMP_CLEAR_ON_TOP

     OCR0 = Local_u8TimerTicks - (u8)((Copy_f32DutyCycle / 100.0)   * Local_u8TimerTicks);
	 
#else
#error "UNSupported CTC Mode"
#endif	 
	 
#else
#error "Unsupported Timer WaveForm Generation Mode"
#endif
		
	}
	else
	{
		return ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}




/*=================================================TIMER 1=================================================*/

ES_t TIMER1_enuInit(void)
{
	ES_t Local_enuErrorState = ES_OK;
	
/*      Set Timer1 Working Mode        */	

#if    TIMER0_WORKING_MODE == TIMER_MODE

	/*   Set Timer1 Prescaler    */
	TCCR1B &= TIMER_PRESCALER_MASk;
	TCCR1B |= TIMER1_PRESCALER;

#elif  TIMER0_WORKING_MODE == COUNTER_MODE

	/*    Set Counter1 Trigger    */
	TCCR1B &= TIMER_COUNTER_MASk;
	TCCR1B |= COUNTER1_TRIGGER;

#else
#error "Timer Working Mode is Wrong"
#endif
	
	
	
/*     Set Timer1 WaveForm Generation Mode      */

#if    TIMER1_WAVE_GENER_MODE == TIMER_OVF_MODE

	Clr_Bit(TCCR1A, TCCR1A_WGM10); Clr_Bit(TCCR1A, TCCR1A_WGM11);
	Clr_Bit(TCCR1B, TCCR1B_WGM12); Clr_Bit(TCCR1B, TCCR1B_WGM13);

#elif  TIMER1_WAVE_GENER_MODE == TIMER_CTC_ICR1_TOP_MODE

	Clr_Bit(TCCR1A, TCCR1A_WGM10); Clr_Bit(TCCR1A, TCCR1A_WGM11);
	Set_Bit(TCCR1B, TCCR1B_WGM12); Set_Bit(TCCR1B, TCCR1B_WGM13);
	
#elif  TIMER1_WAVE_GENER_MODE == TIMER_CTC_OCR1A_TOP_MODE

	Clr_Bit(TCCR1A, TCCR1A_WGM10); Clr_Bit(TCCR1A, TCCR1A_WGM11);
	Set_Bit(TCCR1B, TCCR1B_WGM12); Clr_Bit(TCCR1B, TCCR1B_WGM13);
	
/*                  Set OCR1A mode                 */
#if     Timer1_CTCA_NON_PWM_ACTION == OC_DISCONNECTED

	Clr_Bit(TCCR1A, TCCR1A_COM1A0); Clr_Bit(TCCR1A, TCCR1A_COM1A1);
	
#elif   Timer1_CTCA_NON_PWM_ACTION == TOGGLE_OC
	
	Set_Bit(TCCR1A, TCCR1A_COM1A0); Clr_Bit(TCCR1A, TCCR1A_COM1A1);
	
#elif   Timer1_CTCA_NON_PWM_ACTION == SET_OC
	
	Set_Bit(TCCR1A, TCCR1A_COM1A0); Set_Bit(TCCR1A, TCCR1A_COM1A1);
	
#elif   Timer1_CTCA_NON_PWM_ACTION == CLEAR_OC
	
	Clr_Bit(TCCR1A, TCCR1A_COM1A0); Set_Bit(TCCR1A, TCCR1A_COM1A1);
	
#else
#error "Wrong TIMER1_OCR1A_MODE Config"
#endif
		
/*                  Set OCR1B mode                 */
#if     Timer1_CTCB_NON_PWM_ACTION == OC_DISCONNECTED
	
	Clr_Bit(TCCR1A, TCCR1A_COM1B0); Clr_Bit(TCCR1A, TCCR1A_COM1B1);

#elif   Timer1_CTCB_NON_PWM_ACTION == TOGGLE_OC
	
    Set_Bit(TCCR1A, TCCR1A_COM1B0); Clr_Bit(TCCR1A, TCCR1A_COM1B1);
	
#elif   Timer1_CTCB_NON_PWM_ACTION == SET_OC
	
	Set_Bit(TCCR1A, TCCR1A_COM1B0); Set_Bit(TCCR1A, TCCR1A_COM1B1);
	
#elif   Timer1_CTCB_NON_PWM_ACTION == CLEAR_OC
	
	Clr_Bit(TCCR1A, TCCR1A_COM1B0); Set_Bit(TCCR1A, TCCR1A_COM1B1);
	
#else
#error "Wrong TIMER1_OCR1B_MODE Config"
#endif
	 
#elif  TIMER1_WAVE_GENER_MODE == TIMER_PWM_OCR1_TOP_MODE

    Clr_Bit(TCCR1A, TCCR1A_WGM10); Set_Bit(TCCR1A, TCCR1A_WGM11);
	Clr_Bit(TCCR1B, TCCR1B_WGM12); Set_Bit(TCCR1B, TCCR1B_WGM13);
	
#elif  TIMER1_WAVE_GENER_MODE == TIMER_PWM_OCR1A_TOP_MODE

    Set_Bit(TCCR1A, TCCR1A_WGM10); Set_Bit(TCCR1A, TCCR1A_WGM11);
	Clr_Bit(TCCR1B, TCCR1B_WGM12); Set_Bit(TCCR1B, TCCR1B_WGM13);

#elif  TIMER1_WAVE_GENER_MODE == TIMER_PWM_FREQ_OCR1_TOP_MODE

    Clr_Bit(TCCR1A, TCCR1A_WGM10); Clr_Bit(TCCR1A, TCCR1A_WGM11);
	Clr_Bit(TCCR1B, TCCR1B_WGM12); Set_Bit(TCCR1B, TCCR1B_WGM13);
	
#elif  TIMER1_WAVE_GENER_MODE == TIMER_PWM_FREQ_OCR1A_TOP_MODE

    Set_Bit(TCCR1A, TCCR1A_WGM10); Clr_Bit(TCCR1A, TCCR1A_WGM11);
	Clr_Bit(TCCR1B, TCCR1B_WGM12); Set_Bit(TCCR1B, TCCR1B_WGM13);	

#elif  TIMER1_WAVE_GENER_MODE == TIMER_PWM_8_BIT_MODE

    Set_Bit(TCCR1A, TCCR1A_WGM10); Clr_Bit(TCCR1A, TCCR1A_WGM11);
	Clr_Bit(TCCR1B, TCCR1B_WGM12); Clr_Bit(TCCR1B, TCCR1B_WGM13);
	 
#elif  TIMER1_WAVE_GENER_MODE == TIMER_PWM_9_BIT_MODE

    Clr_Bit(TCCR1A, TCCR1A_WGM10); Set_Bit(TCCR1A, TCCR1A_WGM11);
	Clr_Bit(TCCR1B, TCCR1B_WGM12); Clr_Bit(TCCR1B, TCCR1B_WGM13);

#elif  TIMER1_WAVE_GENER_MODE == TIMER_PWM_10_BIT_MODE

    Set_Bit(TCCR1A, TCCR1A_WGM10); Set_Bit(TCCR1A, TCCR1A_WGM11);
	Clr_Bit(TCCR1B, TCCR1B_WGM12); Clr_Bit(TCCR1B, TCCR1B_WGM13);

#elif  TIMER1_WAVE_GENER_MODE == TIMER_FAST_PWM_8_BIT_MODE

    Set_Bit(TCCR1A, TCCR1A_WGM10); Clr_Bit(TCCR1A, TCCR1A_WGM11);
	Set_Bit(TCCR1B, TCCR1B_WGM12); Clr_Bit(TCCR1B, TCCR1B_WGM13);
	 
#elif  TIMER1_WAVE_GENER_MODE == TIMER_FAST_PWM_9_BIT_MODE

    Clr_Bit(TCCR1A, TCCR1A_WGM10); Set_Bit(TCCR1A, TCCR1A_WGM11);
	Set_Bit(TCCR1B, TCCR1B_WGM12); Clr_Bit(TCCR1B, TCCR1B_WGM13);

#elif  TIMER1_WAVE_GENER_MODE == TIMER_FAST_PWM_10_BIT_MODE

    Set_Bit(TCCR1A, TCCR1A_WGM10); Set_Bit(TCCR1A, TCCR1A_WGM11);
	Set_Bit(TCCR1B, TCCR1B_WGM12); Clr_Bit(TCCR1B, TCCR1B_WGM13);

#elif  TIMER1_WAVE_GENER_MODE == TIMER_FASTPWM_ICR1_MODE

    Clr_Bit(TCCR1A, TCCR1A_WGM10); Set_Bit(TCCR1A, TCCR1A_WGM11);
	Set_Bit(TCCR1B, TCCR1B_WGM12); Set_Bit(TCCR1B, TCCR1B_WGM13);
	 
#elif  TIMER1_WAVE_GENER_MODE == TIMER_FASTPWM_OCRA1_MODE

    Set_Bit(TCCR1A, TCCR1A_WGM10); Set_Bit(TCCR1A, TCCR1A_WGM11);
	Set_Bit(TCCR1B, TCCR1B_WGM12); Set_Bit(TCCR1B, TCCR1B_WGM13);

#else
#error "Unsupported Timer WaveForm Generation Mode"
#endif


	/*==========Timer1 Overflow Interrupt Enable==========*/
#if   TIMER1_OVERFLOW_INTERRUPT == DISABLED

	Clr_Bit(TIMSK, TIMSK_TOIE1) ;

#elif TIMER1_OVERFLOW_INTERRUPT == ENABLED

	Set_Bit(TIMSK, TIMSK_TOIE1);

#else
#error "Wrong TIMER1_OVERFLOW_INTERRUPT Config"
#endif


/*=======Timer1A Compare Match Interrupt Enable=======*/
#if   TIMER1_CTCA_INTERRUPT == DISABLED

	Clr_Bit(TIMSK, TIMSK_OCIE1A) ;

#elif TIMER1_CTCA_INTERRUPT == ENABLED

	Set_Bit(TIMSK, TIMSK_OCIE1A);

#else
#error "Wrong TIMER1A_CTC_INTERRUPT Config"
#endif

/*=======Timer1B Compare Match Interrupt Enable=======*/
#if   TIMER1_CTCB_INTERRUPT == DISABLED

	Clr_Bit(TIMSK, TIMSK_OCIE1B) ;

#elif TIMER1_CTCB_INTERRUPT == ENABLED

	Set_Bit(TIMSK, TIMSK_OCIE1B);

#else
#error "Wrong TIMER1B_CTC_INTERRUPT Config"
#endif
	
	
	return Local_enuErrorState;
}


//---------------------------------------------------------------------------------------------------


ES_t Timer1_enuSetPreLoadValue(u16 Copy_u16PreLoadValue) {
	ES_t Local_enuErrorState = ES_OK;

    if(Copy_u16PreLoadValue <= TIMER1_MAX){
		/*--Set the Required Preload Value--*/
	    TCNT1 = Copy_u16PreLoadValue ;
	}
	else {
		return ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}


//---------------------------------------------------------------------------------------------------


ES_t TIMER1_voidSetCTCAValue(u16 Copy_u16CTCAValue){
	
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_u16CTCAValue <= ((TIMER1_MAX + 1) >> 1))
	{
		OCR1A = Copy_u16CTCAValue;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}


//----------------------------------------------------------------------------------------------------

ES_t TIMER1_voidSetCTCBValue(u16 Copy_u16CTCBValue){
	
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_u16CTCBValue <= ((TIMER1_MAX + 1) >> 1))
	{
		OCR1A = Copy_u16CTCBValue;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}


//----------------------------------------------------------------------------------------------------

ES_t TIMER1_enuGetTimerCounterValue(u16* Copy_Pu16TimerCounterValue) {
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_Pu16TimerCounterValue != NULL)
	{
		*Copy_Pu16TimerCounterValue = TCNT1;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
		
	return Local_enuErrorState;
}


//----------------------------------------------------------------------------------------------------

ES_t TIMER1_enuSetDesiredTime_ms(f32 Copy_u32Time_ms){
	
	ES_t Local_enuErrorState = ES_OK;
	
	// Calculate OverFlow Time
	f32 Local_f32OverFlowTime = TIMER1_NUM_TICKS * ((f32)TIMER1_PRESCALER_VALUE / TIMER_FREQ_CPU);

	// Calculate Number of OverFlow
	f32 Local_f32NumberOfOverFlow = Copy_u32Time_ms / Local_f32OverFlowTime;
	
	
#if    TIMER1_WAVE_GENER_MODE == TIMER_OVF_MODE
	
	// (T_req > T_ovf) or (T_req < T_ovf)
	if(Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow != 0.0) {

		// Rounding The Number To The Nearest Integer Number
		Global_u32Timer1ReqTimeCounts = (u32)Local_f32NumberOfOverFlow + 1;

		// Calculate preLoad Value
		Global_u32Timer1PreloadValue = ((u32)Local_f32NumberOfOverFlow + 1 - Local_f32NumberOfOverFlow ) * TIMER1_NUM_TICKS;

		// Set the Required Preload Value
		TCNT1 = Global_u32Timer1PreloadValue ;
	}
	else 
	{
		Global_u32Timer1ReqTimeCounts = (u32)Local_f32NumberOfOverFlow;
	}
		// Enable OverFlow Interrupt
		Set_Bit(TIMSK, TIMSK_TOIE1);

	
#elif  TIMER1_WAVE_GENER_MODE == TIMER_CTC_OCR1A_TOP_MODE
	
		////////////////////////////////////////////////
	
#else
#error "Unsupported Timer WaveForm Generation Mode"
#endif
	
	return Local_enuErrorState;
	
}

/*=================================================TIMER 2=================================================*/

ES_t TIMER2_enuInit(void) {
	ES_t Local_enuErrorState = ES_OK;
	

/*     Set Timer2 Working Mode          */	
#if    TIMER2_WORKING_MODE == TIMER_MODE

	/*   Set Timer2 Prescaler   */
	TCCR2 &= TIMER_PRESCALER_MASk;
	TCCR2 |= TIMER2_PRESCALER;

#elif  TIMER0_WORKING_MODE == COUNTER_MODE

	/*   Set Counter2 Trigger   */
	TCCR2 &= TIMER_COUNTER_MASk;
	TCCR2 |= COUNTER2_TRIGGER;

#else
#error "Timer Working Mode is Wrong"
#endif


/*     Set Timer2 WaveForm Generation Mode     */
#if   TIMER2_WAVE_GENER_MODE == TIMER_OVF_MODE

	Clr_Bit(TCCR2, TCCR2_WGM20); Clr_Bit(TCCR2, TCCR2_WGM21);
	
/*    Timer2 Overflow Interrupt Enable      */
#if   TIMER2_OVERFLOW_INTERRUPT == DISABLED

	Clr_Bit(TIMSK, TIMSK_TOIE2) ;

#elif TIMER2_OVERFLOW_INTERRUPT == ENABLED

	Set_Bit(TIMSK, TIMSK_TOIE2);

#else
#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
#endif
	

#elif  TIMER2_WAVE_GENER_MODE == TIMER_CTC_MODE

     Clr_Bit(TCCR2, TCCR2_WGM20); Set_Bit(TCCR2, TCCR2_WGM21);
	 
/*        Set Compare Match Output Mode          */
#if    Timer2_CTC_NON_PWM_ACTION == OC_DISCONNECTED	 

	 Clr_Bit(TCCR2, TCCR2_COM20); Clr_Bit(TCCR2, TCCR2_COM21);
	
#elif  Timer2_CTC_NON_PWM_ACTION == TOGGLE_OC

     Set_Bit(TCCR2, TCCR2_COM20); Clr_Bit(TCCR2, TCCR2_COM21);

#elif  Timer2_CTC_NON_PWM_ACTION == SET_OC

     Set_Bit(TCCR2, TCCR2_COM20); Set_Bit(TCCR2, TCCR2_COM21);

#elif  Timer2_CTC_NON_PWM_ACTION == CLEAR_OC

     Clr_Bit(TCCR2, TCCR2_COM20); Set_Bit(TCCR2, TCCR2_COM21);
	 
#else
#error "UNSupported CTC Mode"
#endif
	 
	 
/*    Timer2 Compare Match Interrupt Enable     */
#if   TIMER2_CTC_INTERRUPT == DISABLED

	Clr_Bit(TIMSK, TIMSK_OCIE2) ;

#elif TIMER0_CTC_INTERRUPT == ENABLED

	Set_Bit(TIMSK, TIMSK_OCIE2);

#else
#error "Wrong TIMER2_CTC_INTERRUPT Config"
#endif
	 
	 
	 
#elif  TIMER2_WAVE_GENER_MODE == TIMER_PWM_MODE

       Set_Bit(TCCR2, TCCR2_WGM20); Clr_Bit(TCCR2, TCCR2_WGM21);
	   
/*       Set Compare Match Output Mode        */
#if    Timer2_CTC_PWM_ACTION == OC_DISCONNECTED	 

	 Clr_Bit(TCCR2, TCCR2_COM20); Clr_Bit(TCCR2, TCCR2_COM21);
	
#elif  Timer2_CTC_PWM_ACTION == CLEAR_ON_UP_SET_ON_DOWN

     Clr_Bit(TCCR2, TCCR2_COM20); Set_Bit(TCCR2, TCCR2_COM21);

#elif  Timer2_CTC_PWM_ACTION == SET_ON_UP_CLEAR_ON_DOWN

     Set_Bit(TCCR2, TCCR2_COM20); Set_Bit(TCCR2, TCCR2_COM21);
	 
#else
#error "UNSupported CTC Mode"
#endif


#elif  TIMER2_WAVE_GENER_MODE == TIMER_FASTPWM_MODE

       Set_Bit(TCCR2, TCCR2_WGM20); Set_Bit(TCCR2, TCCR2_WGM21);
	   
/*         Set Compare Match Output Mode          */
#if    Timer2_CTC_FAST_PWM_ACTION == OC_DISCONNECTED	 

	 Clr_Bit(TCCR2, TCCR2_COM20); Clr_Bit(TCCR2, TCCR2_COM21);
	
#elif  Timer2_CTC_FAST_PWM_ACTION == CLEAR_ON_COMP_SET_ON_TOP

     Clr_Bit(TCCR2, TCCR2_COM20); Set_Bit(TCCR2, TCCR2_COM21);

#elif  Timer2_CTC_FAST_PWM_ACTION == SET_ON_COMP_CLEAR_ON_TOP

     Set_Bit(TCCR2, TCCR2_COM20); Set_Bit(TCCR2, TCCR2_COM21);
	 
#else
#error "UNSupported CTC Mode"
#endif	 
	 
#else
#error "Unsupported Timer WaveForm Generation Mode"
#endif
	
	
	return Local_enuErrorState;
}




ES_t Timer2_enuSetPreLoadValue(u8 Copy_u8PreLoadValue) {
	ES_t Local_enuErrorState = ES_OK;

    if(Copy_u8PreLoadValue <= TIMER2_MAX){
		//Set the Required Preload Value
	    TCNT2 = Copy_u8PreLoadValue ;
	}
	else {
		return ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}




ES_t TIMER2_enuGetTimerCounterValue(u8* Copy_Pu8TimerCounterValue) {
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_Pu8TimerCounterValue != NULL)
	{
		*Copy_Pu8TimerCounterValue = TCNT2;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER;
	}
		
	return Local_enuErrorState;
}





ES_t TIMER2_voidSetCTCValue(u8 Copy_u8CTCValue) {
	
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_u8CTCValue <= TIMER0_MAX)
	{
		OCR2 = Copy_u8CTCValue;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}





ES_t TIMER2_enuSetDesiredTime_ms(f32 Copy_u32Time_ms){
	
	ES_t Local_enuErrorState = ES_OK;
	
	// Calculate OverFlow Time
	f32 Local_f32OverFlowTime = TIMER2_NUM_TICKS * ((f32)TIMER2_PRESCALER_VALUE / TIMER_FREQ_CPU);

	// Calculate Number of OverFlow
	f32 Local_f32NumberOfOverFlow = Copy_u32Time_ms / Local_f32OverFlowTime;
	
	if(TIMER2_WAVE_GENER_MODE == TIMER_OVF_MODE)
	{
		// (T_req > T_ovf) or (T_req < T_ovf)
	if(Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow != 0.0) {

		// Rounding The Number To The Nearest Integer Number
		Global_u32Timer2ReqTimeCounts = (u32)Local_f32NumberOfOverFlow + 1;

		// Calculate preLoad Value
		Global_u32Timer2PreloadValue = ((u32)Local_f32NumberOfOverFlow + 1 - Local_f32NumberOfOverFlow ) * TIMER2_NUM_TICKS;

		// Set the Required Preload Value
		TCNT2 = Global_u32Timer2PreloadValue ;
	}
	else 
	{
		Global_u32Timer2ReqTimeCounts = (u32)Local_f32NumberOfOverFlow;
	}
	    // Enable OverFlow Interrupt
        Set_Bit(TIMSK, TIMSK_TOIE2);
	}
	else if(TIMER2_WAVE_GENER_MODE == TIMER_CTC_MODE)
	{
		
		if(Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow < 1){
			// Clear Timer0 CTC Flag 
			Global_u8Timer2CTCFlag = 0;
			
			Global_u32Timer2ReqTimeCounts = 1;
			
			// Calculate Timer0CTCValue Value
			Global_u8Timer2CTCValue = (Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow) * TIMER2_NUM_TICKS;
			
			// Set OCR2 Value
			OCR2 = 	Global_u8Timer2CTCValue;
		}
		else if(Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow > 1) {
			// Set Timer2 CTC Flag
			Global_u8Timer2CTCFlag = 1;
			
			// Rounding The Number To The Nearest Integer Number
			Global_u32Timer2ReqTimeCounts = (u32)Local_f32NumberOfOverFlow + 2;
			
			// Calculate Timer2CTCValue Value
			Global_u8Timer2CTCValue = (Local_f32NumberOfOverFlow - (u32)Local_f32NumberOfOverFlow) * TIMER2_NUM_TICKS;
			
		    // Set OCR2 Value
            OCR2 = Global_u8Timer2CTCValue; 
		}
		else 
		{
			// Clear Timer2 CTC Flag
			Global_u8Timer2CTCFlag = 0;
			
			Global_u32Timer2ReqTimeCounts = 1;
			Global_u8Timer2CTCValue = 0xff;
			
			// Set OCR2 Value
			OCR2 = Global_u8Timer2CTCValue;
		}
		// Enable Compare Match Interrupt
		Set_Bit(TIMSK, TIMSK_OCIE2);
	}
	else
	{
		Local_enuErrorState = ES_NOK;
	}
	
	return Local_enuErrorState;
}



ES_t TIMER2_enuPWMSetDutyCycle(f32 Copy_f32DutyCycle)
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_f32DutyCycle >= 0.0 && Copy_f32DutyCycle <= 100.0)
	{
		u8 Local_u8TimerTicks = TIMER0_NUM_TICKS;
		if(Copy_f32DutyCycle == 100.0) 
		{
			Local_u8TimerTicks--;
		}
		
#if  TIMER2_WAVE_GENER_MODE == TIMER_PWM_MODE
	
	   /*    Non_Inverted Mode     */
#if    Timer2_CTC_PWM_ACTION == CLEAR_ON_UP_SET_ON_DOWN

     OCR2 = Local_u8TimerTicks - (u8)((Copy_f32DutyCycle / 100.0)   * Local_u8TimerTicks);

	   /*       Inverted Mode     */
#elif  Timer2_CTC_PWM_ACTION == SET_ON_UP_CLEAR_ON_DOWN

     OCR2 = (u8)((Copy_f32DutyCycle / 100.0)   * Local_u8TimerTicks);
	 
#else
#error "UNSupported CTC Mode"
#endif


#elif  TIMER2_WAVE_GENER_MODE == TIMER_FASTPWM_MODE
	
	   /*    Non-Inverted Mode    */
#if    Timer2_CTC_FAST_PWM_ACTION == CLEAR_ON_COMP_SET_ON_TOP

     OCR2 = (u8)((Copy_f32DutyCycle / 100.0)   * Local_u8TimerTicks);

	   /*      Inverted Mode     */
#elif  Timer2_CTC_FAST_PWM_ACTION == SET_ON_COMP_CLEAR_ON_TOP

     OCR2 = Local_u8TimerTicks - (u8)((Copy_f32DutyCycle / 100.0)   * Local_u8TimerTicks);
	 
#else
#error "UNSupported CTC Mode"
#endif	 
	 
#else
#error "Unsupported Timer WaveForm Generation Mode"
#endif
		
	}
	else
	{
		return ES_OUT_OF_RANGE;
	}
	
	return Local_enuErrorState;
}




/*=================================================TIMERS=================================================*/



ES_t TIMER_enuDisable(u8 Copy_u8TimerId){
	
	ES_t Local_enuErrorState = ES_OK;
	
#if    Copy_u8TimerId == TIMER0

    TCCR0 &= TIMER_DISABLE;

#elif  Copy_u8TimerId == TIMER1
	
	TCCR1 &= TIMER_DISABLE;
	
#elif  Copy_u8TimerId == TIMER2

    TCCR2 &= TIMER_DISABLE;

#else
#error "UN_Supported Timer"
#endif	
	
	return Local_enuErrorState;
}



ES_t TIMER_enuSetCallBack(u8 Copy_TimerIntId, void (*Copy_pvCallBackFunction)(void))
{
	ES_t Local_enuErrorState = ES_OK;
	
	if(Copy_pvCallBackFunction != NULL)
	{
		if(Copy_TimerIntId >= 0 && Copy_TimerIntId <= 7)
		{
			TIMERS_pvCallBackFunc[Copy_TimerIntId] = Copy_pvCallBackFunction;
		}
		else
		{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}	
	}
	else 
	{
		Local_enuErrorState = ES_NULL_POINTER;	
	}
	
	return Local_enuErrorState;
}



/*=================================================Overflow timer interrupts ISRs=================================================*/

ISR(VECT_TIMER0_OVF)
{
	
	if(TIMERS_pvCallBackFunc[TIMER0_OVF_INT_ID] != NULL) 
	{
		Global_u32Timer0Counter++;
		if(Global_u32Timer0Counter == Global_u32Timer0ReqTimeCounts) 
		{
			Global_u32Timer0Counter = 0;
			TCNT0 = Global_u32Timer0PreloadValue;
		    TIMERS_pvCallBackFunc[TIMER0_OVF_INT_ID]();
		}
	}	
}


ISR(VECT_TIMER1_OVF)
{
	
	if(TIMERS_pvCallBackFunc[TIMER1_OVF_INT_ID] != NULL) 
	{
		Global_u32Timer1Counter++;
		if(Global_u32Timer1Counter == Global_u32Timer1ReqTimeCounts) 
		{
			Global_u32Timer1Counter = 0;
			TCNT1 = Global_u32Timer1PreloadValue;
		    TIMERS_pvCallBackFunc[TIMER1_OVF_INT_ID]();
		}
	}	
}



ISR(VECT_TIMER2_OVF)
{
	
	if(TIMERS_pvCallBackFunc[TIMER2_OVF_INT_ID] != NULL) 
	{
		Global_u32Timer2Counter++;
		if(Global_u32Timer2Counter == Global_u32Timer2ReqTimeCounts) 
		{
			Global_u32Timer2Counter = 0;
			TCNT2 = Global_u32Timer2PreloadValue;
		    TIMERS_pvCallBackFunc[TIMER2_OVF_INT_ID]();
		}
	}	
}



/*=============================================Compare match timer interrupts ISRs=============================================*/

ISR(VECT_TIMER0_CTC)
{
	if(TIMERS_pvCallBackFunc[TIMER0_CTC_INT_ID] != NULL) 
	{
		if(Global_u8Timer0CTCFlag){
			OCR0 = 0xff;
		}
		
		Global_u32Timer0Counter++;
		if(Global_u32Timer0Counter >= Global_u32Timer0ReqTimeCounts)
		{
			OCR0 = Global_u8Timer0CTCValue;
			Global_u32Timer0Counter = 0;
			TIMERS_pvCallBackFunc[TIMER0_CTC_INT_ID]();

		}
	}	
}


ISR(VECT_TIMER1_CTC_A)
{
	
	if(TIMERS_pvCallBackFunc[TIMER1_CTCA_INT_ID] != NULL) 
	{

		TIMERS_pvCallBackFunc[TIMER1_CTCA_INT_ID]();
	}	
}


ISR(VECT_TIMER1_CTC_B)
{
	
	if(TIMERS_pvCallBackFunc[TIMER1_CTCB_INT_ID] != NULL) 
	{
		    TIMERS_pvCallBackFunc[TIMER1_CTCB_INT_ID]();
	}	
}



ISR(VECT_TIMER2_CTC)
{
	
	if(TIMERS_pvCallBackFunc[TIMER2_CTC_INT_ID] != NULL) 
	{
		
		if(Global_u8Timer2CTCFlag){
			OCR2 = 0xff;
		}
		
		Global_u32Timer2Counter++;
		if(Global_u32Timer2Counter >= Global_u32Timer2ReqTimeCounts)
		{
			OCR2 = Global_u8Timer2CTCValue;
			Global_u32Timer2Counter = 0;
			TIMERS_pvCallBackFunc[TIMER2_CTC_INT_ID]();

		}
	}	
}


/*=============================================Capture Event timer1 interrupt ISR=============================================*/


ISR(VECT_TIMER1_ICU)
{
	
	if(TIMERS_pvCallBackFunc[TIMER1_ICU_INT_ID] != NULL) 
	{
		    TIMERS_pvCallBackFunc[TIMER1_ICU_INT_ID]();
	}	
}



