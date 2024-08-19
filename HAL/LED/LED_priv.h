/*
 * LED_priv.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */

#ifndef LED_PRIV_H_
#define LED_PRIV_H_

typedef struct
{
	u8 LED_u8PortID;
	u8 LED_u8PinID;
	u8 LED_u8Connection;
	u8 LED_Status;
}LED_t;


#define LED_ON        1
#define LED_OFF       0
#define LED_SOURCE    1
#define LED_SINK      0

#endif /* LED_PRIV_H_ */
