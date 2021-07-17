 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: timer.c
 *
 * Description: Source file for the Timer0 driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/


/**********************************************************
 *                        INCLUDES                        *
 **********************************************************/
#include "timer.h"


/**********************************************************
 *                     Global Variables                   *
 **********************************************************/

/*Global variable to hold the address fucntion of the callback funstion in application*/
static volatile void (*g_callBackPtr[3])(void) = {NULL_PTR,NULL_PTR,NULL_PTR};

/**********************************************************
 *                          ISRs                          *
 **********************************************************/
ISR(TIMER0_OVF_vect)
{
	if (g_callBackPtr[TIMER0] != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[TIMER0])();
	}
}
ISR(TIMER0_COMP_vect)
{
	if (g_callBackPtr[TIMER0] != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[TIMER0])();
	}
}

ISR(TIMER1_OVF_vect)
{
	if (g_callBackPtr[TIMER1] != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[TIMER1])();
	}
}
ISR(TIMER1_COMPA_vect)
{
	if (g_callBackPtr[TIMER1] != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[TIMER1])();
	}
}

ISR(TIMER2_OVF_vect)
{
	if (g_callBackPtr[TIMER2] != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[TIMER2])();
	}
}
ISR(TIMER2_COMP_vect)
{
	if (g_callBackPtr[TIMER2] != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr[TIMER2])();
	}
}


/**********************************************************
 *                   Function Definitions                 *
 **********************************************************/

/*
 * Description: Function to initiate timers
 */
void TIMER_init(TIMER_Config * timerParam)
{
	if (timerParam->number == TIMER0)
	{
		/*Configure Timer0 Control register
		 * 1. Non PWM mode FOC0=1
		 * 2. Timer Mode and clock is an input
		 */
		TCCR0 = (1<<FOC0) ;
		/*Select clock prescaler for timer*/
		TCCR0 = (TCCR0 & 0xF8) | (timerParam->clock);

		/*Set inital value for the timer*/
		TCNT0 = timerParam->initVal ;

		if (timerParam->mode == Normal_Mode)
		{
			/*Enable Timer0 Overflow Interrupt*/
			TIMSK |= (1<<TOIE0);
		}
		else if (timerParam->mode == Compare_Mode)
		{
			/*select Compare mode for Timer0*/
			TCCR0 = (TCCR0 & 0xF7) | ((timerParam->mode)<<2);
			/*Set the compare value for Timer0*/
			OCR0 = timerParam->compVal ;
			/*Enable Timer0 Compare Interrupt*/
			TIMSK |= (1<<OCIE0);
		}
	}
	else if (timerParam->number == TIMER1)
	{
		/*Configure Timer1 Control register
		 * 1. Set Force Output Compare to avoid working with PWM mode
		 * FOC1A=1,FOC1B=1
		 * 2. Timer Mode and clock is an input
		 */
		TCCR1A |= (1<<FOC1A)| (1<<FOC1B);

		/*Select clock prescaler for Timer1*/
		TCCR1B |= (TCCR1B & 0xF8) | (timerParam->clock);

		/*Set initial value for the Timer1*/
		TCNT1 = timerParam->initVal ;

		if (timerParam->mode == Normal_Mode)
		{
			/*Enable Timer1 Overflow Interrupt*/
			TIMSK |= (1<<TOIE1);
		}
		else if (timerParam->mode == Compare_Mode)
		{
			/*select Compare mode for Timer1*/
			TCCR1B |= (TCCR1B & 0xF7) | ((timerParam->mode)<<2);
			/*Set the compare value for timer1*/
			OCR1A = timerParam->compVal ;
			/*Enable Timer1 Compare Interrupt*/
			TIMSK |= (1<<OCIE1A);
		}
	}
	else if (timerParam->number == TIMER2)
	{
		/*Configure Timer0 Control register
		 * 1. Non PWM mode FOC0=1
		 * 2. Timer Mode and clock is an input
		 */
		TCCR2 = (1<<FOC2) ;

		/*Select clock prescaler for Timer2*/
		TCCR2 = (TCCR2 & 0xF8) | (timerParam->clock);

		/*Set inital value for the Timer2*/
		TCNT2 = timerParam->initVal ;

		if (timerParam->mode == Normal_Mode)
		{
			/*Enable Timer2 Overflow Interrupt*/
			TIMSK |= (1<<TOIE2);
		}
		else if (timerParam->mode == Compare_Mode)
		{
			/*select Compare mode for Timer2*/
			TCCR2 = (TCCR2 & 0xF7) | ((timerParam->mode)<<2);
			/*Set the compare value for timer2*/
			OCR2 = timerParam->compVal ;
			/*Enable Timer2 Compare Interrupt*/
			TIMSK |= (1<<OCIE2);
		}
	}
}


/*
 * Description: Function to set call back address
 */
void TIMER_setCallBack(const Timer_Number a_number,void(*a_ptrFunc)(void))
{
	/*Put the call back fucntion address of the appliaction in the call back global pointer*/
	g_callBackPtr[a_number] = a_ptrFunc ;
}

/*
 * Description: Function to clear the value of the timer
 */
void TIMER_clearTimerValue(Timer_Number number)
{
	if (number == TIMER0)
	{
		TCNT0 = 0 ;
	}
	else if (number == TIMER1)
	{
		TCNT1 = 0 ;
	}
	else if (number == TIMER2)
	{
		TCNT2 = 0 ;
	}
}

/*
 * Description: Function to get the current value of the timer
 */
uint16 TIMER_getTimerValue(Timer_Number number)
{
	uint16 timerVal = 0 ;
	if (number == TIMER0)
	{
		timerVal = TCNT0;
	}
	else if (number == TIMER1)
	{
		timerVal = TCNT1 ;
	}
	else if (number == TIMER2)
	{
		timerVal = TCNT2;
	}
	return timerVal ;
}

/*
 * Description: Function to stop the timers*/

void TIMER_deInit (Timer_Number number)
{
	if (number == TIMER0)
	{
		TCCR0 = 0 ;
		TCNT0 = 0 ;
		OCR0  = 0 ;
		/*Disable interrupt for timer 0*/
		TIMSK &= ~(1<<TOIE0) & (~(1<<OCIE0));
	}
	else if (number == TIMER1)
	{
		TCCR1A = 0 ;
		TCCR1B = 0 ;
		TCNT1 = 0 ;
		OCR1A  = 0 ;
		/*Disable interrupt for timer 1*/
		TIMSK &= ~(1<<OCIE1A) & (~(1<<TOIE1));
	}
	else if (number == TIMER2)
	{
		TCCR2 = 0 ;
		TCNT2 = 0 ;
		OCR2  = 0 ;
		/*Disable interrupt for timer 2*/
		TIMSK &= ~(1<<TOIE2) & (~(1<<OCIE2));
	}
}


