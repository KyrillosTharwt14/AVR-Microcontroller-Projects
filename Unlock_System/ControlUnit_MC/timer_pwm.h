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
#ifndef TIMER_PWM_H_
#define TIMER_PWM_H_


#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"


void Timer0_PWM_Init(uint8 set_duty_cycle);

#endif /* TIMER_PWM_H_ */
