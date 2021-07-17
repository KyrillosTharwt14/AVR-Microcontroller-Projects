/*
 * main.c
 *
 *  Created on: 15 Jun 2021
 *      Author: Kyrillos Tharwat
 */



#include "hmi_programs.h"
#include "lcd.h"
#include "uart.h"
/**********************************************************
 *                   Function Definitions                 *
 **********************************************************/
int main ()
{
	DDRB = 0xFF;

	/*Enable global interrupts in MC. */
	SREG  |= (1<<7);

	/*initiate the programs and modules*/
	startupProgram();
	PORTB= 0xff;

	while (1)
	{
		if ( flagProgram == 1)
		{
			firstProgram();
		}
		else if ( flagProgram == 2)
		{
			defaultProgram();
		}
		//flagProgram = UART_receiveByte();
	}
}



