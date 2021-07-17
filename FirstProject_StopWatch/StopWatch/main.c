/*
 * main.c
 *
 *  Created on: 2 May 2021
 *  Author: kyrillos Tharwat
 *  Decreption: A program of stop watch simulation, using ATmega 16, six 7-segments and 3 buttons for (RESET, STOP, RESUME)
 *              IN ATmega16:
 *              PORTA and PORTC are used as outputs ports for 7 segemnts
 *              INT0, INT1 and INT2 pins in PORTD and PORTB are used as inputs bin for the 3 buttons
 *              TIMER1 is used for stop watch as a clock
 */


#include "StopWatch.h"

unsigned char Digit = ZERO_SECOND;
unsigned char stopwatch [Segments_num] = {0,0,0,0,0,0};  //{s1,s2,m1,m2,h1,h2};


int main()
{
	Init_IOs();
	Init_Interrupts ();
	Init_Timers();
	while(1)
	{
		Display_StopWatch ();
	}
}

