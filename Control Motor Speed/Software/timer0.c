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


#include "timer0.h"

uint8 g_tick = 0 ;

ISR(TIMER0_OVF_vect)
{
	g_tick++ ;
}

void TIMER0_OVF_Start(uint8 a_tick)
{
	/*Configure Timer0 Control register
	 * 1. Non OWM mode FOC0=1
	 * 2. Normal MODE WGM01 =0 & WGM00 = 0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. Clock is input by user
	 */
	TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
	//TCCR0 = (TCCR0 & 0xE0) | (clock & 0x07); /*select clock prescaler*/
	TCCR0 = (1<<FOC0) ;

	g_tick = a_tick ;
}
void Timer0_PWM_Init(uint8 set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value

	OCR0  = set_duty_cycle; // Set Compare Value

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
