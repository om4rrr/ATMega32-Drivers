
/*
#include <util/delay.h>

#include "../../MCAL/EXTI/EXTI_int.h"
#include "../../MCAL/GIE/GIE_int.h"
#include "../../MCAL/ADC/ADC_int.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "../../HAL/LCD/LCD_int.h"
#include "../../HAL/LCD/LCD_config.h"
#include "../../HAL/LM35/LM35_int.h"

//extern EXTI_t EXTI_AstrEXTIConfig[3];

u8 flag = 0, Temp; u16 ADC16 = 0;

void ISR_ADC(void) {

	LCD_enuWriteNumber(ADC16);
	flag = 1;
}

void ADC_Test(void) {

	LCD_enuInit();

	ADC_enuInit();

	//GIE_VoidEnable();

	LM35_CONFIG lm_35_1 = {ADC_CHANNEL_0, 5, ADC_RESOLUTION_10_BIT};



	//LCD_enuWriteNumber(ADC_enuStartConversionAsynch(0, &ADC16, ISR_ADC));

	while(1) {

//		LM35_u8GetTemp(&lm_35_1, &Temp);
//		LCD_enuWriteNumber(Temp);
//		LCD_enuClearDisplay();
		//ADC_enuGetReadSync(0, &ADC16);

		ADC_enuStartConversionAsynch(0, &ADC16, ISR_ADC);

//		if(flag) {
//			LCD_enuClearDisplay();
//			flag = 0;
//		}
	}
}
*/