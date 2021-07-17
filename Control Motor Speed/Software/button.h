 /******************************************************************************
 *
 * Module: Button
 *
 * File Name: button.h
 *
 * Description: Header file for the button driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"

#define BUTTON_PIN  PD3

#define BUTTON_PORT_OUT PORTD
#define BUTTON_PORT_IN  PIND
#define BUTTON_PORT_DIR DDRD


extern uint8 mode;
void BUTTON_init();


#endif /* BUTTON_H_ */
