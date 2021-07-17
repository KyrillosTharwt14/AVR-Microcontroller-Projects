 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"


#define BUZZER   PD5

#define BUZZER_PORT_DIR DDRD
#define BUZZER_PORT_IN  PIND
#define BUZZER_PORT_OUT PORTD


void BUZZER_init(uint8 buzzer);
void BUZZER_turnON(uint8 buzzer);
void BUZZER_turnOFF(uint8 buzzer);
