 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ADC driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/
#include "adc.h"


void ADC_Init(void)
{
	ADMUX = 0 ;
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1);
	ADCSRA &= ~(1<<ADIE);
}


uint16 ADC_readChannel(uint8 channel)
{
	ADMUX = (ADMUX & 0xE0) | (channel & 0x073);
	ADCSRA |= (1<<ADSC);
	while (BIT_IS_CLEAR(ADCSRA,ADIF));
	ADCSRA |= (1<<ADIF);
	return ADC;

}
