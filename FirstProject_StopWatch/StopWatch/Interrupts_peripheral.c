/*
 *Interrupts_peripheral.c
 *
 *Created on: 3 May 2021
 *Author: Kyrillos Tharwat
 *
 *Configuration of interrupts INT0 INT1, INT2
 */

#include "StopWatch.h"



void Init_Interrupts () //Enable INT0, INT1 and INT 2
{
	INT0_Config();  // Configure INT0
	INT1_Config();  // Configure INT1
	INT2_Config();  // Configure INT2

	SREG |= (1<<GIE); //Enable global interrupt bit (I-bit)
	GICR |= 0xE0;     //Enable external interrupts INT0, INT1 and INT2
}
void INT0_Config()
{
	MCUCR |= 0x03;  //Set falling edge of INT0 to generate interrupt request
}

void INT1_Config()
{
	MCUCR |= 0x06;  //Set rising edge of INT1 to generate interrupt request
}

void INT2_Config()
{
	MCUCSR &= ~(1<<ISC2);  //Set falling edge of INT2 to generate interrupt request
}



ISR (INT0_vect) //Reset/Start stop watch
{
	SREG |= (1<<GIE); //Enable global interrupt bit (I-bit)
	Set_Clock_ON();
	Reset_StopWatch ();
}

ISR (INT1_vect) //Pause stop watch
{
	SREG |= (1<<GIE); //Enable global interrupt bit (I-bit)
	Set_Clock_OFF();
}

ISR (INT2_vect) //Resume stop watch
{
	SREG |= (1<<GIE); //Enable global interrupt bit (I-bit)
	Set_Clock_ON();
}

ISR (TIMER1_COMPA_vect) // Increment stop watch by 1 second
{
	SREG |= (1<<GIE); //Enable global interrupt bit (I-bit)
	stopwatch[Digit_1]++; //Increment time by 1 second
	Increment_StopWatch(); //Increment the time in stop watch
}
