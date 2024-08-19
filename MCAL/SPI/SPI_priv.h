/*******************************************************************************************/
/*******************************************************************************************/
/*************************            Author : Omar Ali            *************************/
/*************************            Component : SPI              *************************/
/*************************            Layer : MCAL                 *************************/
/*************************            Version : 1.00               *************************/
/*******************************************************************************************/
/*******************************************************************************************/

#ifndef SPI_PRIV_H_
#define SPI_PRIV_H_


#define    SPDR            *((volatile u8*)0x2F)     /* SPI Data Register        */


#define    SPSR            *((volatile u8*)0x2E)     /* SPI Status Register      */

#define    SPSR_SPI2X 	   0                         /* Double SPI Speed Bit     */
#define    SPSR_WCOL	   6                         /* Write Collision Flag Bit */
#define    SPSR_SPIF       7                         /* SPi Interrupt Flag       */ 
	
		
#define    SPCR            *((volatile u8*)0x2D)     /* SPI Control Register     */
	
#define    SPCR_SPR0       0                         /* Prescaler Select Bit0    */
#define    SPCR_SPR1       1                         /* Prescaler Select Bit1    */	 
#define    SPCR_CPHA       2                         /* Clock Phase Bit          */ 	
#define    SPCR_CPOL       3	                     /* Clock Polarity Bit       */
#define    SPCR_MSTR       4                         /* Master/Slave Select Bit  */ 	
#define    SPCR_DORD       5                         /* Data Order Bit           */	
#define    SPCR_SPE	       6                         /* SPI Enable Bit           */
#define    SPCR_SPIE	   7                         /* SPI Interrupt Enable Bit */ 
	
	
	
#define    DISABLE                    11
#define    ENABLE   	              22
	
#define    MASTER   	              11
#define    SLAVE   	                  22
	
#define    LOW   	                  11
#define    HIGH   	                  22 
	
#define    LSB_FIRST   	              11
#define    MSB_FIRST   	              22  
	
#define    SAMPLE_FIRST   	          11
#define    SETUP_FIRST	              22
	
#define    SPI_DIVISION_BY_2          2 
#define    SPI_DIVISION_BY_4          4
#define    SPI_DIVISION_BY_8          8
#define    SPI_DIVISION_BY_16         16
#define    SPI_DIVISION_BY_32         32 
#define    SPI_DIVISION_BY_64         64
#define    SPI_DIVISION_BY_128        128
	
	
	
#endif
