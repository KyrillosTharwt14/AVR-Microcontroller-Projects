 /******************************************************************************
 *
 * Module: Button
 *
 * File Name: button.c
 *
 * Description: Source file for the button driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#include "button.h"
#include "INT1.h"



uint8 mode = 1;

void BUTTON_init()
{
	INT1_init();
	CLEAR_BIT(BUTTON_PORT_DIR,BUTTON_PIN);  /*make pin of button as input*/
}


ISR (INT1_vect)  //Toggle mode of motors
{
	TOGGLE_BIT(mode,0);
}
