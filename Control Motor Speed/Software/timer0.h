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
#ifndef TIMER0_H_
#define TIMER0_H_


#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"


void TIMER0_init(void);
void Timer0_PWM_Init(uint8 set_duty_cycle);

#endif /* TIMER0_H_ */
