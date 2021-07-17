 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the ADC driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/
#ifndef ADC_H_
#define ADC_H_

#include <stdlib.h>
#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"

uint16 ADC_readChannel(uint8 channel);
void ADC_Init(void);
#endif /* ADC_H_ */
