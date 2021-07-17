 /******************************************************************************
 *
 * Module: INT1
 *
 * File Name: INT1.c
 *
 * Description: Source file for the INT1 driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#include "INT1.h"

void INT1_init(void)
{
	GICR  |= (1<<INT1);                 // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC11) | (1<<ISC10);   // Set rising edge of INT1 to generate interrupt request
}

