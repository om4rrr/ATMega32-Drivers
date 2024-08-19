
#ifndef MCAL_TIMER_TIMER_PRIV_H_
#define MCAL_TIMER_TIMER_PRIV_H_


/*      8-bit Timer/Counter0 Register      */
#define    TCCR0                  *((volatile u8*)0x53)               // Timer/Counter0 Control Register
#define    TCNT0                  *((volatile u8*)0x52)               // Timer/Counter0 Register
#define    OCR0                   *((volatile u8*)0x5C)               // Output Compare0 Register

/*      Timer/Counter0 Control Register Bits      */
#define    TCCR0_CS00             0
#define    TCCR0_CS01             1
#define    TCCR0_CS02             2
#define    TCCR0_WGM01            3
#define    TCCR0_COM00            4
#define    TCCR0_COM01            5
#define    TCCR0_WGM00            6
#define    TCCR0_FOC0             7

/*     Timer/Counter Interrupt     */
#define    TIMSK                  *((volatile u8*)0x59)               // Timer/Counter Interrupt Mask Register
#define    TIFR                   *((volatile u8*)0x58)               // Timer/Counter Interrupt Flag Register

/*      Timer/Counter Interrupt Mask Register Bits      */
#define    TIMSK_TOIE0            0
#define    TIMSK_OCIE0            1
#define    TIMSK_TOIE1            2
#define    TIMSK_OCIE1B           3
#define    TIMSK_OCIE1A           4
#define    TIMSK_TICIE1           5
#define    TIMSK_TOIE2            6
#define    TIMSK_OCIE2            7

/*      Timer/Counter Interrupt Flag Register Bits      */
#define    TIFR_TOV0              0
#define    TIFR_OCF0              1
#define    TIFR_TOV1              2
#define    TIFR_OCF1B             3
#define    TIFR_OCF1A             4
#define    TIFR_ICF1              5
#define    TIFR_TOV2              6
#define    TIFR_OCF2              7


/*      Special Function IO Register      */
#define    SFIOR                  *((volatile u8*)0x50)
#define    SFIOR_PSR2             0
#define    SFIOR_PSR10            1


/*      16-bit Timer/Counter1 Register      */
#define    OCR1A		          *((volatile u16*)0x4A)
#define    OCR1B		          *((volatile u16*)0x48)
#define    TCCR1                  *((volatile u16*)0x4E) 	
#define    TCCR1A                 *((volatile u8*)0x4F)               // Timer/Counter1 Control Register A
#define    TCCR1B                 *((volatile u8*)0x4E)               // Timer/Counter1 Control Register B
#define    TCNT1			      *((volatile u16*)0x4c)              // Timer/Counter - TCNT1 register
#define    TCNT1H                 *((volatile u8*)0x4D)               // Timer/Counter1 – TCNT1H Register
#define    TCNT1L                 *((volatile u8*)0x4C)               // Timer/Counter1 – TCNT1L Register
#define    OCR1AH                 *((volatile u8*)0x4B)               // Output Compare Register1 A
#define    OCR1AL                 *((volatile u8*)0x4A)               // Output Compare Register1 A
#define    OCR1BH                 *((volatile u8*)0x49)               // Output Compare Register1 B
#define    OCR1BL                 *((volatile u8*)0x48)               // Output Compare Register1 B
#define    ICR1H                  *((volatile u8*)0x)                 // Input Capture Register1
#define    ICR1L                  *((volatile u8*)0x)                 // Input Capture Register1

/*      Timer/Counter1 Control Register A Bits      */
#define    TCCR1A_WGM10           0
#define    TCCR1A_WGM11           1
#define    TCCR1A_FOC1B           2
#define    TCCR1A_FOC1A           3
#define    TCCR1A_COM1B0          4
#define    TCCR1A_COM1B1          5
#define    TCCR1A_COM1A0          6
#define    TCCR1A_COM1A1          7

/*      Timer/Counter1 Control Register B Bits      */
#define    TCCR1B_CS10            0
#define    TCCR1B_CS11            1
#define    TCCR1B_CS12            2
#define    TCCR1B_WGM12           3
#define    TCCR1B_WGM13           4
#define    TCCR1B_ICES1           6
#define    TCCR1B_ICNC1           7


/*      8-bit Timer/Counter2 Register      */
#define    TCCR2                  *((volatile u8*)0x45)               // Timer/Counter2 Control Register
#define    TCNT2                  *((volatile u8*)0x44)               // Timer/Counter2 Register
#define    OCR2                   *((volatile u8*)0x43)               // Output Compare2 Register

/*      Timer/Counter2 Control Register Bits      */
#define    TCCR2_CS20             0
#define    TCCR2_CS21             1
#define    TCCR2_CS22             2
#define    TCCR2_WGM21            3
#define    TCCR2_COM20            4
#define    TCCR2_COM21            5
#define    TCCR2_WGM20            6
#define    TCCR2_FOC2             7


/*      Asynchronous Status Register      */
#define    ASSR                   *((volatile u8*)0x42)
#define    ASSR_TCR2UB            0
#define    ASSR_OCR2UB            1
#define    ASSR_TCN2UB            2
#define    ASSR_AS2               3


#define    TIMER_PRESCALER_MASk   0b11111000
#define    TIMER_COUNTER_MASk     0b11111000


#define    TIMER_DISABLE          0b11111000


#define    ENABLED                66
#define    DISABLED               88 


#define    TIMER_MODE             11
#define    COUNTER_MODE           22


/*------------Number of Bits of timres------------*/ 
#define    TIMER0_MAX		      255
#define    TIMER1_MAX		      65535ULL
#define    TIMER2_MAX		      255



#define    TIMER0_NUM_TICKS       256
#define    TIMER2_NUM_TICKS       256
#define    TIMER1_NUM_TICKS       65536 





/*=========================================================================*/

#define   OC_DISCONNECTED                  111
#define   TOGGLE_OC                        222
#define   SET_OC                           333
#define   CLEAR_OC                         444
#define   CLEAR_ON_COMP_SET_ON_TOP         555 
#define   SET_ON_COMP_CLEAR_ON_TOP         666
#define   CLEAR_ON_UP_SET_ON_DOWN          777  
#define   SET_ON_UP_CLEAR_ON_DOWN          888 
#define	  TOGGLE_OC1A_ON_COMP_MATCH        999 
	 
/*=========================================================================*/

#endif /* MCAL_TIMER_TIMER_PRIV_H_ */

