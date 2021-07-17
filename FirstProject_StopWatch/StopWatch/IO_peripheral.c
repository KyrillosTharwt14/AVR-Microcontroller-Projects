/*
 * main.c
 *
 *  Created on: 2 May 2021
 *      Author: kyrillos Tharwat
 *      A program of stop watch simulation
 *      using ATmega 16, six 7-segment
 *      3 interrupts are used and timer 1
 */

#include "StopWatch.h"


void PORTA_Config()
{
	DDRA = 0x3F; //Configure First 6 pins in PORTA as output PINS
	PORTA = 0x3F ; //Turn ALL six 7segment
}
void PORTB_Config()
{
	DDRB &= ~ (1<<start_btn); //Configure pin 2 in PORTB as input pin
	PORTB|= (1<<start_btn);   //Enable internal pull up resistor for pin 2 on PORTB

}
void PORTC_Config()
{
	DDRC  |= 0x0F; //Configure First 4 pins in PORTC as output PINS
	PORTC &= (0xF0) ; //Put zero in all 7segments
}
void PORTD_Config()
{
	DDRD &= ~ (1<<reset_btn) & ~(1<<stop_btn); //Configure pin 2,3 in PORTD as input pins
	PORTD|= (1<<reset_btn);   //Enable internal pull up resistor for pin 2 on PORTD
}

void Init_IOs()
{
	PORTA_Config();
	PORTB_Config();
	PORTC_Config();
	PORTD_Config();

}
