/*
 * door.c
 *
 *  Created on: 25 Jun 2021
 *      Author: kyrillos Tharwat
 */



/**********************************************************
 *                        INCLUDES                        *
 **********************************************************/
#include "door.h"
#include "motor.h"
#include "timer.h"
#include  "led.h"



/**********************************************************
 *                     Global Variables                   *
 **********************************************************/

/*configure timer 1 to count until 5 seconds*/
static TIMER_Config delay= {TIMER1,Compare_Mode,F_CPU_1024,0,39062};

static uint8 g_tick = 0;
static uint8 g_doorIsMovingFlag = FALSE ;

/**********************************************************
 *                   Function Definitions                 *
 **********************************************************/

/*
 * Description:
 * Function to start a delay of 15 sec to make sure that the door
 * is fully opened
 */
void _delayForMoveingTheDoor(void)
{
	g_tick ++ ;
	if (g_tick == NUMBER_OF_COMPARE_MATCH_PER_5_SECOND)
	{
		g_tick = 0 ;
		g_doorIsMovingFlag = TRUE ;
	}
}

void DOOR_init(void)
{
	/*Configure of motor*/
	MOTOR_init();
	LED_init(LED_GREEN);

	/*Set Timer call back function*/
	TIMER_setCallBack(delay.number,_delayForMoveingTheDoor);
}

/*
 * Description:
 * Function to ROTATE the motor clockwise to open the door
 * in 15 sec
 */
void DOOR_isOpened(void)
{
	/*Start to open the door*/
	MOTOR_Rotate(CLOCKWISE);

	/*Turn on green LED*/
	LED_turnON(LED_GREEN);

	/*Start Timer to count until reach 15 sec*/
	TIMER_init(&delay);

	 /*Wait until door is full open*/
	while(!g_doorIsMovingFlag);

	/*Stop timer*/
	TIMER_deInit (delay.number);

	/*Door is fully moved*/
	g_doorIsMovingFlag = FALSE ;

	/*Stop the movement of motor*/
	MOTOR_Stop();

	/*Delay for 2000 seconds */
	_delay_ms(2000);
}

/*
 * Description:
 * Function to ROTATE the motor anti-clockwise to close the door
 * in 15 sec
 */
void DOOR_isClosed(void)
{
	/*Start to close the door*/
	MOTOR_Rotate(ANTICLOCKWISE);

	/*Start Timer to count until reach 15 sec*/
	TIMER_init(&delay);

	 /*Wait until door is full open*/
	while(!g_doorIsMovingFlag);

	/*Stop timer*/
	TIMER_deInit (delay.number);

	/*Door is fully moved*/
	g_doorIsMovingFlag = FALSE ;

	/*Turn off green led*/
	LED_turnOFF(LED_GREEN);

	/*Stop the movement of motor*/
	MOTOR_Stop();
}


