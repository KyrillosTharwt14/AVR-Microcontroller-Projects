 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.c
 *
 * Description: Source file for the LED driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#include "led.h"

void LED_init(uint8 LED)
{
	SET_BIT(LED_PORT_DIR, LED);
}

void LED_turnON(uint8 LED)
{
	SET_BIT(LED_PORT_OUT, LED);
}

void LED_turnOFF(uint8 LED)
{
	CLEAR_BIT(LED_PORT_OUT, LED);

}
