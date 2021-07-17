 /******************************************************************************
 *
 * Module: motor
 *
 * File Name: motor.c
 *
 * Description: Source file for the motor driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#include "adc.h"
#include "motor.h"
#include "timer0.h"

uint16 adc_value;   /*vairable to store adc value*/
static MOTOR motor = {MOTOR_IN1,MOTOR_IN2,MOTOR_EN};  /*Identify the pins of motors*/


static void MOTOR_setModeClockWise(uint8 a_IN1, uint8 a_IN2);
static void MOTOR_setModeAntiClockWise(uint8 a_IN1, uint8 a_IN2);


void MOTOR_init(void)
{
	ADC_Init();         /*Initiate ADC*/
	MOTOR_PORT_DIR = (1<<motor.m_IN1)| (1<<motor.m_IN2) | (1<<motor.m_EN) ;
}

void MOTOR_Rotate(uint8 mode)
{
	adc_value = ADC_readChannel(0);
	Timer0_PWM_Init(((float)adc_value / 1023)*255); //generate duty cycle (adc_value/1023)% to get half motor speed

	if (mode == CLOCKWISE)
	{
		MOTOR_setModeClockWise(motor.m_IN1,motor.m_IN2);
	}
	else //(mode == ANTICLOCKWISE)
	{
		MOTOR_setModeAntiClockWise(motor.m_IN1,motor.m_IN2);
	}
}

static void MOTOR_setModeClockWise(uint8 a_IN1, uint8 a_IN2)
{
	SET_BIT  (MOTOR_PORT_OUT,a_IN1);
	CLEAR_BIT(MOTOR_PORT_OUT,a_IN2);
}

static void MOTOR_setModeAntiClockWise(uint8 a_IN1, uint8 a_IN2)
{
	SET_BIT  (MOTOR_PORT_OUT,a_IN2);
	CLEAR_BIT(MOTOR_PORT_OUT,a_IN1);
}
