/*
 * main.c
 *
 *  Created on: 15 Jun 2021
 *      Author: Kyrillos
 */
#include "control_unit_programs.h"



int main ()
{
	/*Enable global interrupts in MC. */
	SREG  |= (1<<7);

	startupProgram();

	while (1)
	{
		EEPROM_readByte(PROGRAM_ADDRESS,&flagProgram);
		if (flagProgram == FIRST_PROGRAM)
		{
			firstProgram();
		}
		else if (flagProgram == SECOND_PROGRAM)
		{
			defaultProgram();
		}
	}
}

