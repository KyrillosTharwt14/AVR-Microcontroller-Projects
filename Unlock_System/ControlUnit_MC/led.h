 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.h
 *
 * Description: Header file for the LED driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

#define LED_GREEN PA1
#define LED_RED   PA0

#define LED_PORT_DIR DDRA
#define LED_PORT_IN  PINA
#define LED_PORT_OUT PORTA

void LED_init(uint8 LED);
void LED_turnON(uint8 LED);
void LED_turnOFF(uint8 LED);


