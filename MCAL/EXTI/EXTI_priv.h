/*
 * EXIT_priv.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef EXTI_PRIV_H_
#define EXTI_PRIV_H_


#define    MCUCR_REG               *((volatile u8 *)0x55)
#define    MCUCSR_REG              *((volatile u8 *)0x54)
#define    GICR_REG                *((volatile u8 *)0x5B)
#define    GIFR_REG                *((volatile u8 *)0x5A)


#define    ENABLED			       88
#define    DISABLED		           99

#define    EXTI_INT0               0
#define    EXTI_INT1               1
#define    EXTI_INT2               2

#define    GICR_INT0   	           6
#define    GICR_INT1	           7
#define    GICR_INT2               5

#define    EXTI_FALLING_EDGE       0
#define    EXTI_RISING_EDGE        1
#define    EXTI_LOW_LEVEL          2
#define    EXTI_ON_CHANGE          3

#define    MCUCR_ISC00		       0
#define    MCUCR_ISC01		       1
#define    MCUCR_ISC10		       2
#define    MCUCR_ISC11		       3
#define    MCUCSR_ISC2		       6

#endif /* EXTI_PRIV_H_ */
