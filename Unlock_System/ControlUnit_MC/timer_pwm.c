 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: timer0.c
 *
 * Description: Source file for the Timer0 driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/


#include "timer_pwm.h"


void Timer0_PWM_Init(uint8 set_duty_cycle)
{
	/*Set Timer Initial value*/
	TCNT0 = 0;

	/* Set Compare Value*/
	OCR0  = set_duty_cycle;

	/*set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.*/
	DDRB  = DDRB | (1<<PB3);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/64 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01)| (1<<CS00);
}
void TIMER0_PWM_deInit()
{
	TCCR0 = 0 ;
	TCNT0 = 0 ;
	OCR0 = 0 ;
}
