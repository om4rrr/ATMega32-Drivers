/*

 * Seven_Segment_priv.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef SEVEN_SEGMENT_PRIV_H_
#define SEVEN_SEGMENT_PRIV_H_

#define  BITS_NUM            3
#define  SEG_PINS_NUM        7

#define  COMMON_ANODE        55
#define  COMMON_CTHODE       99

#define  NOT_CONNECTED       11

#define  SEG_A_PIN           0
#define  SEG_B_PIN           1
#define  SEG_C_PIN           2
#define  SEG_D_PIN           3
#define  SEG_E_PIN           4
#define  SEG_F_PIN           5
#define  SEG_G_PIN           6


u8 Seven_Segment_Au8DisplayedNumbers[] = { 0x3F, 0x06, 0x5B,
			                               0x4F, 0x66, 0x6D,
					                       0x7D, 0x07, 0x7F,
				                           0x6F};

#endif /* SEVEN_SEGMENT_PRIV_H_ */
