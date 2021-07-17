 /******************************************************************************
 *
 * Module: motor
 *
 * File Name: motor.h
 *
 * Description: Header file for the motor driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/


#ifndef MOTOR_H_
#define MOTOR_H_

#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"





#define CLOCKWISE       1
#define ANTICLOCKWISE  0

extern uint16 adc_value;   /*vairable to store adc value*/

typedef struct {
	uint8 m_IN1 ;
	uint8 m_IN2 ;
	uint8 m_EN ;
}MOTOR;



#define MOTOR_IN1 PB0
#define MOTOR_IN2 PB1
#define MOTOR_EN PB3


#define MOTOR_PORT_DIR DDRB
#define MOTOR_PORT_OUT PORTB


void MOTOR_init(void);
void MOTOR_Rotate(uint8 mode);




#endif /* MOTOR_H_ */
