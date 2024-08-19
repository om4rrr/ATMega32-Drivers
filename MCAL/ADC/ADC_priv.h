/*
 * ADC_priv.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef MCAL_ADC_ADC_PRIV_H_
#define MCAL_ADC_ADC_PRIV_H_

#define   ADCL                   *((volatile u8*)0x24)
#define   ADCH                   *((volatile u8*)0x25)
#define   ADCSRA                 *((u8*)0x26)
#define   ADMUX                  *((u8*)0x27)
#define   SFIOR                  *((u8*)0x50)


#define ADC_PRESCALER_MASK		 0b11111000
#define ADC_CHANNEL_MASK	     0b11100000


#define   ADCSRA_ADPS0           0
#define   ADCSRA_ADPS1           1
#define   ADCSRA_ADPS2           2

#define   ADMUX_REFS0            6
#define   ADMUX_REFS1            7

#define   ADMUX_ADLAR            5

#define   SFIOR_ADTS0            5
#define   SFIOR_ADTS1            6
#define   SFIOR_ADTS2            7

#define   ADCSRA_ADEN            7
#define   ADCSRA_ADSC            6
#define   ADCSRA_ADATE           5
#define   ADCSRA_ADIF            4
#define   ADCSRA_ADIE            3


// Values of the global variable (Global_u8ADCISRSource)
#define SINGLE_CHANNEL_ASYNCH    0
#define CHAIN_CHANNEL_ASYNCH     1



#endif /* MCAL_ADC_ADC_PRIV_H_ */
