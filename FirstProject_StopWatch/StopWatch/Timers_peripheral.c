/*
 *Timers_peripheral.c
 *
 *Created on: 3 May 2021
 *Author: Kyrillos Tharwat
 *
 *Configure and set Timer1 (16-bit) to generate an interrupt every 1 sec
 */

#include "StopWatch.h"


void Init_Timers()
{
	Timer1_Config();
}

void Timer1_Config()
{
	TCCR1A |= (1<<FOC1A)| (1<<FOC1B);  //set Force Output Compar to avoid working with PWM mode

	/*Choose output compare mode for timer 1 */
	TCCR1A &= ~(1<<WGM10) & ~(1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	/*****************************************/
	TCNT1 = ZERO_SECOND;  //Set the initial value of timer is 0
	OCR1A = (ONE_SECOND * 15625 );   // Every clk takes 64 Ms, so 1 second takes = (1 s / 64 Ms) = 15625 clk
	TIMSK |= (1<<OCIE1A);  //Enable ISR for TIMER1
}

void Set_Clock_ON()
{
	/*select clk/64 as a pre-scaler*/
	TCCR1B |= (1<<CS10) | (1<<CS11);
	TCCR1B &= ~(1<<CS12);
}

void Set_Clock_OFF()
{
	TCCR1B &= ~(1<<CS10) & ~(1<<CS11) & ~(1<<CS12); // NO clock source
}
