 /******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: timer0.h
 *
 * Description: Header file for the Timer0 driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

/**********************************************************
 *                        INCLUDES                        *
 **********************************************************/
#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"

/**********************************************************
 *                      ENUMS                             *
 **********************************************************/
typedef enum
{
	TIMER0,TIMER1,TIMER2
}Timer_Number;
typedef enum
{
	Normal_Mode,Compare_Mode=2
}Timer_Mode;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Clock;

/**********************************************************
 *                    STRUCTURES                          *
 **********************************************************/
typedef struct{
	Timer_Number number;
	Timer_Mode mode;
	Timer_Clock clock;
	uint16 initVal;
	uint16 compVal;
}TIMER_Config;


/**********************************************************
 *                  Function Declarations                 *
 **********************************************************/
void TIMER_init(TIMER_Config * timerParam);
void TIMER_setCallBack(const Timer_Number a_number,void(*a_ptrFunc)(void));
void TIMER_clearTimerValue(Timer_Number number);
void TIMER_deInit (Timer_Number number);
uint16 TIMER_getTimerValue(Timer_Number number);

#endif /* TIMER_H_ */
