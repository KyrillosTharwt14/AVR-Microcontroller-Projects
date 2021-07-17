/*
 *StopWatch.c
 *
 *Created on: 3 May 2021
 *Author: Kyrillos Tharwat
 *
 *Decreption:
 */

#include "StopWatch.h"


void Display_StopWatch () //Loop for display each digit in six 7segment consecutively
{
	for (Digit = Digit_1 ; Digit < Segments_num ; Digit ++ ) //loop to display the all digit
	{
		PORTA |=(1<<Digit); //turn on the digit to show it's value
		PORTC = stopwatch[Digit]; //show the value of the digit
		_delay_ms(Delay_5ms); //delay 5 ms
		PORTA &=~(1<<Digit); //turn off the digit
	}
}

void Reset_StopWatch ()
{

	for (Digit = Digit_1 ; Digit < Segments_num ; Digit++ ) //Loop to reset every digit
	{
		stopwatch[Digit] = ZERO_SECOND; //set all digits to zero
	}
}


void Increment_StopWatch()
{
	if (stopwatch[Digit_1] == MAX_OF_FIRIST_SEC_DIGIT) /*When digit reach to its maximum reset the digit and increase following digit*/
	{
		stopwatch[Digit_1] = ZERO_SECOND;
		stopwatch[Digit_2]++;
		if (stopwatch[Digit_2] == MAX_OF_SECOND_SEC_DIGIT) /*When digit reach to its maximum reset the digit and increase following digit*/
		{
			stopwatch[Digit_2] = ZERO_SECOND;
			stopwatch[Digit_3]++;
		}
	}

	if (stopwatch[Digit_3] == MAX_OF_FIRIST_MIN_DIGIT) /*When digit reach to its maximum reset the digit and increase following digit*/
	{
		stopwatch[Digit_3] = ZERO_SECOND;
		stopwatch[Digit_4]++;
		if (stopwatch[Digit_4] == MAX_OF_SECOND_MIN_DIGIT) /*When digit reach to its maximum reset the digit and increase following digit*/
		{
			stopwatch[Digit_4] = ZERO_SECOND;
			stopwatch[Digit_5]++;
		}
	}

	if (stopwatch[Digit_5] == MAX_OF_FIRIST_HOUR_DIGIT) /*When digit reach to its maximum reset the digit and increase following digit*/
	{
		stopwatch[Digit_5]=0;
		stopwatch[Digit_6]++;
		if (stopwatch[Digit_6] == MAX_OF_SECOND_HOUR_DIGIT) /*When digit reach to its maximum reset the digit and increase following digit*/
		{
			stopwatch[Digit_6] = ZERO_SECOND;
		}
	}
}
