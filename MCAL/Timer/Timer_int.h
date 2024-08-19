#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/stdTypes.h"

/*----------------------------Timer ID--------------------------*/
#define    TIMER0				0
#define    TIMER1				1
#define    TIMER1A				2
#define    TIMER1B				3
#define    TIMER2				4

/*------------------------Timer Interrupt ID--------------------*/
#define TIMER0_OVF_INT_ID		      0
#define TIMER0_CTC_INT_ID		      1

#define TIMER1_OVF_INT_ID		      2
#define TIMER1_CTCB_INT_ID		      3
#define TIMER1_CTCA_INT_ID		      4
#define TIMER1_ICU_INT_ID		      5

#define TIMER2_OVF_INT_ID		      6
#define TIMER2_CTC_INT_ID		      7


/*------------------------Timer Prescaler-----------------------*/
#define    TIMER_PRE_1                1
#define    TIMER_PRE_8                2
#define    TIMER_PRE_64               3
#define    TIMER_PRE_256              4
#define    TIMER_PRE_1024             5


/*---------------------Timer Prescaler Values-------------------*/
#define    TIMER_PRE_VALUE_1          1
#define    TIMER_PRE_VALUE_8          8
#define    TIMER_PRE_VALUE_64         64
#define    TIMER_PRE_VALUE_256        256
#define    TIMER_PRE_VALUE_1024       1024


/*------------------------Counter Trigger-----------------------*/
#define    TIMER_FALLING_EDGE         6
#define    TIMER_RISING_EDGE          7


/*------------------Timer WaveForm Generation Mode--------------*/
#define    TIMER_OVF_MODE                    1
#define    TIMER_CTC_MODE                    2
#define    TIMER_PWM_MODE                    3
#define    TIMER_FASTPWM_MODE                4
#define    TIMER_CTC_ICR1_TOP_MODE           5
#define    TIMER_CTC_OCR1A_TOP_MODE          6
#define    TIMER_PWM_OCR1_TOP_MODE           7
#define    TIMER_PWM_OCR1A_TOP_MODE          8
#define    TIMER_PWM_FREQ_OCR1_TOP_MODE      9       
#define    TIMER_PWM_FREQ_OCR1A_TOP_MODE     10
#define    TIMER_PWM_8_BIT_MODE              11
#define    TIMER_PWM_9_BIT_MODE              12
#define    TIMER_PWM_10_BIT_MODE 	         13   
#define    TIMER_FAST_PWM_8_BIT_MODE         14
#define    TIMER_FAST_PWM_9_BIT_MODE         15
#define    TIMER_FAST_PWM_10_BIT_MODE        16  
#define    TIMER_FASTPWM_ICR1_MODE           17
#define    TIMER_FASTPWM_OCRA1_MODE          18
	
/*--------------------------------------------------------------*/
	                 
#define    CLEAR_ON_COMP_SET_ON_TOP         2
#define    SET_ON_COMP_CLEAR_ON_TOP         3 
#define    CLEAR_ON_UP_SET_ON_DOWN          4
#define    SET_ON_UP_CLEAR_ON_DOWN          5 


/*=========================================================TIMER 0=========================================================*/

/*
 * @brief function to initialize timer0 prepherals.
 *
 * @return the error statues.
 */
ES_t TIMER0_enuInit(void);


/*
 * @brief function to set the preload value of a timer0 prepheral for post build.
 *
 * @param[in]  timer setting Value.
 *
 * @return the error statues.
 */
ES_t Timer0_enuSetPreLoadValue(u8 Copy_u8PreLoadValue);


/*
 * @brief function to set the Compare Match value of a timer0 prepheral for post build.
 *
 * @param[in] Compare Match Value.
 *
 * @return the error statues.
 */
ES_t TIMER0_voidSetCTCValue(u8 Copy_u8CTCValue);


/*
 * @brief function to get the value of a timer0 prepheral for post build.
 *
 * @param[out] Timer reading.
 *
 * @return the error statues.
 */
ES_t TIMER0_enuGetTimerCounterValue(u8* Copy_Pu8TimerCounterValue);


/*
 * @brief function to set the desired time timer0 prepheral.
 *
 * @param[in] Copy_u32Time_us: required time in microseconed.
 *
 * @return the error statues.
 */
ES_t TIMER0_enuSetDesiredTime_ms(f32 Copy_u32Time_ms);



/*
 * @brief function to set the desired Duty cycle of the PWM signal for timer0 prepheral.
 *
 * @param[in] Copy_u8DutyCycle: Duty Cycle value between 0 to 100.
 *
 * @return the error statues.
 */
ES_t TIMER0_enuPWMSetDutyCycle(f32 Copy_f32DutyCycle);


/*=========================================================TIMER 1=========================================================*/

/*
 * @brief function to initialize timer1 prepherals.
 *
 * @return the error statues.
 */
ES_t TIMER1_enuInit(void);


/*
 * @brief function to set the preload value of a timer1 prepheral for post build.
 *
 * @param[in]  timer setting Value.
 *
 * @return the error statues.
 */
ES_t Timer1_enuSetPreLoadValue(u16 Copy_u16PreLoadValue);


/*
 * @brief function to set the Compare Match value of a timer1_A prepheral for post build.
 *
 * @param[in] Compare Match Value.
 *
 * @return the error statues.
 */
ES_t TIMER1_voidSetCTCAValue(u16 Copy_u16CTCAValue);


/*
 * @brief function to set the Compare Match value of a timer1_B prepheral for post build.
 *
 * @param[in] Compare Match Value.
 *
 * @return the error statues.
 */
ES_t TIMER1_voidSetCTCBValue(u16 Copy_u16CTCBValue);

/*
 * @brief function to get the value of a timer1 prepheral for post build.
 *
 * @param[out] Timer reading.
 *
 * @return the error statues.
 */
ES_t  TIMER1_enuGetTimerCounterValue(u16* Copy_Pu16TimerCounterValue);


ES_t TIMER1_enuSetDesiredTime_ms(f32 Copy_u32Time_ms);



/*=========================================================TIMER 2=========================================================*/

/*
 * @brief function to initialize timer2 prepherals.
 *
 * @return the error statues.
 */

ES_t TIMER2_enuInit(void);


/*
 * @brief function to set the preload value of a timer2 prepheral for post build.
 *
 * @param[in]  timer setting Value.
 *
 * @return the error statues.
 */
ES_t Timer2_enuSetPreLoadValue(u8 Copy_u8PreLoadValue);


/*
 * @brief function to set the Compare Match value of a timer2 prepheral for post build.
 *
 * @param[in] Compare Match Value.
 *
 * @return the error statues.
 */
ES_t TIMER2_voidSetCTCValue(u8 Copy_u8CTCValue) ;


/*
 * @brief function to get the value of a timer2 prepheral for post build.
 *
 * @param[out] Timer reading.
 *
 * @return the error statues.
 */
ES_t   TIMER2_enuGetTimerCounterValue (u8* Copy_Pu8TimerCounterValue) ;


/*
 * @brief function to set the desired time timer0 prepheral.
 *
 * @param[in] Copy_u32Time_us: required time in microseconed.
 *
 * @return the error statues.
 */
ES_t TIMER2_enuSetDesiredTime_ms(f32 Copy_u32Time_ms);


/*
 * @brief function to set the desired Duty cycle of the PWM signal for timer0 prepheral.
 *
 * @param[in] Copy_u8DutyCycle: Duty Cycle value between 0 to 100.
 *
 * @return the error statues.
 */
ES_t TIMER2_enuPWMSetDutyCycle(f32 Copy_f32DutyCycle);



/*=================================================TIMERS=================================================*/




/*
 * @brief function to disable a specific timer prepheral.
 *
 * @param[in] TIMER id:     1- TIMER0
 *                          2- TIMER1
 *                          3- TIMER2
 *
 * @return the error statues.
 */
ES_t TIMER_enuDisable(u8 Copy_u8TimerId);


/*
 * @brief function to receive the addresse of the ISR function of a specific timer prepheral.
 *
 * @param[in] TIMER id:  	1- TIMER0
 * 							2- TIMER1  (overflow)
 *                          2- TIMER1A (CTC A)
 *                          3- TIMER1B (CTC B)
 *                          4- TIMER2
 *
 * @param[in] the notification function.
 *
 * @return the error statues.
 */
ES_t TIMER_enuSetCallBack(u8 Copy_TimerId, void (*Copy_pvCallBackFunction)(void));



#endif /* MCAL_TIMER_TIMER_INT_H_ */
