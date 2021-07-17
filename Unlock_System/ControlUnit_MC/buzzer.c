 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#include "buzzer.h"

void BUZZER_init(uint8 buzzer)
{
	SET_BIT(BUZZER_PORT_DIR, buzzer);
}

void BUZZER_turnON(uint8 buzzer)
{
	SET_BIT(BUZZER_PORT_OUT, buzzer);
}

void BUZZER_turnOFF(uint8 buzzer)
{
	CLEAR_BIT(BUZZER_PORT_OUT, buzzer);

}
