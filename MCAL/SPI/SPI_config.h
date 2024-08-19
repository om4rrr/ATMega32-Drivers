/*******************************************************************************************/
/*******************************************************************************************/
/*************************            Author : Omar Ali            *************************/
/*************************            Component : SPI              *************************/
/*************************            Layer : MCAL                 *************************/
/*************************            Version : 1.00               *************************/
/*******************************************************************************************/
/*******************************************************************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_


/*
 * Choose the SPI initial state
 * Options:	
 *          1- ENABLE
 * 			2- DISABLE
 */
#define SPI_STATE		ENABLE


/*
 * Choose the SPI initial mode
 * Options:	
 *          1- MASTER
 * 			2- SLAVE
 */
#define SPI_MODE		SLAVE


/*
 * Choose the SPI data order
 * Options:	
 *          1- LSB_FIRST 
 * 			2- MSB_FIRST 
 */
#define SPI_DATA_ORDER		LSB_FIRST


/*
 * Choose the SPI clock polarity
 * Options:	
 *          1- LOW 
 * 			2- HIGH
 */
#define SPI_CLK_POLARITY	LOW


/*
 * Choose the SPI  clock phase
 * Options:	
 *          1- SAMPLE_FIRST	
 * 			2- SETUP_FIRST	
 */
#define SPI_CLK_PHASE		SAMPLE_FIRST

/*
 * Choose the relationship between SCK and the Oscillator Frequency
 * Options:
 *         1- SPI_DIVISION_BY_2
 *         2- SPI_DIVISION_BY_4
 *         3- SPI_DIVISION_BY_8
 *         4- SPI_DIVISION_BY_16
 *         5- SPI_DIVISION_BY_32
 *         6- SPI_DIVISION_BY_64 
 *         7- SPI_DIVISION_BY_128 
 */
#define SPI_CLK_RATE		SPI_DIVISION_BY_16
 
 
#define SPI_TIMEOUT 80000ULL
 
#endif