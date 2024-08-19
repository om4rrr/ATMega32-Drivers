

//#include "stdTypes.h"

/*
void UASRT_Init(void);
void USART_TX(u8 Local_u8Data);
u8 USART_RX(void);




int main(void) {
	
	UASRT_Init();
	
	
	while(1){
		
		
	USART_TX(USART_RX());
	
	}
	
	return 0;
}
*/


/*
void UASRT_Init(void) {
	
	u8 Local_u8UCSRC = 0;


	
	
	Local_u8UCSRC |= (1 << UCSRC_UCSZ0); 
	Local_u8UCSRC |= (1 << UCSRC_UCSZ1);
	UCSRB &= ~(1 << UCSRB_UCSZ2); 
	
	
	
	Local_u8UCSRC &= ~(1 << UCSRC_UMSEL);
	
	u16 local_u16UBBR = (u16)(8000000UL / (long long)(16 * 9600) - 1);
	
	//su16 local_u16UBBR = 51;
	
	UBRRH = (u8)(local_u16UBBR >> 8 );
	UBRRL = (u8)local_u16UBBR;
	
	
	
	Local_u8UCSRC &= ~(1 << UCSRC_UPM0);
	Local_u8UCSRC &= ~(1 << UCSRC_UPM0);
	
	
	
	Local_u8UCSRC &= ~(1 << UCSRC_USBS);
	
	
	UCSRA &= ~(1 << UCSRA_U2X);
	
	
	
	UCSRA &= ~(1 << UCSRA_MPCM);
	
	
	UCSRC |= (1 << UCSRC_URSEL); 
	
	UCSRC = Local_u8UCSRC; // one operation
	
	
	
	UCSRB |= (1 << UCSRB_TXEN); 
	UCSRB |= (1 << UCSRB_RXEN);
	
	
}


void USART_TX(u8 Local_u8Data) {
	
	while(!((UCSRA >> UCSRA_UDRE) & 1) );
	
	UDR = Local_u8Data;
	
}


u8 USART_RX(void) {
	
	while(!((UCSRA >> UCSRA_RXC) & 1) );
	
	return UDR ;
	
}

 */