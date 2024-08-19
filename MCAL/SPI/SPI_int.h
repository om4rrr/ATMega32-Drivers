/*******************************************************************************************/
/*******************************************************************************************/
/*************************            Author : Omar Ali            *************************/
/*************************            Component : SPI              *************************/
/*************************            Layer : MCAL                 *************************/
/*************************            Version : 1.00               *************************/
/*******************************************************************************************/
/*******************************************************************************************/

#include "../../SERVICE/ErrorStates.h"

#ifndef SPI_INT_H
#define SPI_INT_H


/*
 * @brief function to initialize the SPI.
 *
 * @return the error statues.
 */
ES_t SPI_enuInit(void);



/*
 * @brief function to transmit and receive one byte.
 *
 * @param[out] Copy_pu8ReceivedData: data to be received
 *
 * @param[in] Copy_u8SentData: data to be transmitted
 *
 * @return the error statues.
 */
ES_t SPI_enuTransceiveByteSynch(u8* Copy_pu8ReceivedData, u8 Copy_u8SentData);



/*
 * @brief function to transmit and receive one byte.
 *
 * @param[out] Copy_pu8ReceivedData: data to be received
 *
 * @param[in] Copy_u8SentData: data to be transmitted
 *
 * @param[in] CallBack: the notification function
 * 
 * @return the error statues.
 */
ES_t SPI_enuTransceiveByteASynch(u8* Copy_pu8ReceivedData, u8 Copy_u8SentData, void(*Copy_PvoidNotificationFunction)(void) );


#endif