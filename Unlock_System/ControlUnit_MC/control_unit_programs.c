 /******************************************************************************
 *
 * Module: control unit programs
 *
 * File Name: control_unit_programs.c
 *
 * Description: Source file for performing programs and receive the password
 * from hmi MC ans store it in the eeprom then compare it to inlock the door
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/



/**********************************************************
 *                        INCLUDES                        *
 **********************************************************/

#include "control_unit_programs.h"
#include "led.h"
#include "uart.h"
#include "door.h"
#include "motor.h"
#include "timer.h"
#include "buzzer.h"



uint8 flagProgram = 0;

static TIMER_Config delay= {TIMER1,Compare_Mode,F_CPU_1024,0,39062};

static uint8 g_tick = 0;
static uint8 g_alarmIsONFlag = FALSE ;


/*
 * Description: delay function for 60 seconds
 */
void _delayForAlarm(void)
{
	g_tick ++ ;
	if (g_tick == NUMBER_OF_COMPARE_MATCH_PER_1_MINUTE)
	{
		g_tick = 0 ;
		g_alarmIsONFlag = TRUE ;
	}
}

/*
 * Description: A program to initiate All the modules
 */

void startupProgram(void)
{
	/*Configure UART*/
	UART paramUart = {9600,1,dataMode_8,disableParity};

	/*Door initialization*/
	DOOR_init();

	/*EPPROM initialization*/
	EEPROM_init();

	/*UART initialization*/
	UART_init(&paramUart);


	EEPROM_readByte(PROGRAM_ADDRESS,&flagProgram);
	if (flagProgram == 255 )
	{
		EEPROM_writeByte(PROGRAM_ADDRESS,FIRST_PROGRAM);
		_delay_ms(10);
	}
	EEPROM_readByte(PROGRAM_ADDRESS,&flagProgram);

	/* Wait until HMI_MC is ready*/
	while(UART_receiveByte() != HMI_MC_READY){}
	UART_sendByte(flagProgram);
}

/*
 * Description:
 * This program run once, when the user start to implement his system
 * It receive the password from the HMI MC and save it to in EEPROM
 * It may run again if the user want to change his password
 */
void firstProgram(void)
{
	uint8 password[PASSWORD_LENGHT];
	uint8 confirmedPassword[PASSWORD_LENGHT];

	UART_receiveString(password);
	_delay_ms(10);
	UART_receiveString(confirmedPassword);

	if (comparePassword(password,confirmedPassword) == 0)
	{
		EEPROM_writeString(PASSWORD_ADDRESS,confirmedPassword);

		EEPROM_writeByte(PROGRAM_ADDRESS,SECOND_PROGRAM);
		_delay_ms(10);

		UART_sendByte(SECOND_PROGRAM);
	}
	else
	{
		EEPROM_writeByte(PROGRAM_ADDRESS,FIRST_PROGRAM);
		_delay_ms(10);

		UART_sendByte(FIRST_PROGRAM);
	}
}

/*
 * Description:
 * This is the default program
 * Receive the password from HMI_MC
 * if the password is correct, the door is opened and closed in 30 s
 * if the password is not correct, Alarm is started  in 60 s
 * for both option the have only 3 trial
 */
void defaultProgram(void)
{
	uint8 key, matchPassword ;
	key = UART_receiveByte();

	if (key == '+')
	{
		checkPassword(&matchPassword);
		if (matchPassword == ZERO_NUMBER_OF_TRIALS)
		{
			DOOR_isOpened();
			DOOR_isClosed();
		}
		else if (matchPassword == MAX_NUMBERS_OF_TRIALS)
		{
			alarmProgram();
		}

	}
	else if (key == '-')
	{
		checkPassword(&matchPassword);
		if (matchPassword == ZERO_NUMBER_OF_TRIALS)
		{
			firstProgram();
		}
		else if (matchPassword == MAX_NUMBERS_OF_TRIALS)
		{
			alarmProgram();
		}

	}
}

/*
 * Description: Get the password from the HMI_MC and check it
 * if is right or not
 */
void checkPassword(uint8 * matchPassword)
{
	uint8 password[PASSWORD_LENGHT];
	uint8 savedPassword[PASSWORD_LENGHT];
	static uint8 trials = 0;

	UART_receiveString(password);
	EEPROM_readString(PASSWORD_ADDRESS,savedPassword);

	if (comparePassword(password,savedPassword) == 0)
	{
		trials = 0;
		*matchPassword = trials ;
		UART_sendByte(trials);
	}
	else
	{
		trials++;
		*matchPassword = trials ;
		UART_sendByte(trials);
		if (trials == MAX_NUMBERS_OF_TRIALS)
		{
			trials = 0 ;
		}
	}
}

/*
 * Description: Function show error message for 1 minute
 */
void alarmProgram(void)
{
	LED_init(LED_RED);
	BUZZER_init(BUZZER);
	TIMER_setCallBack(delay.number,_delayForAlarm);

	BUZZER_turnON(BUZZER);
	LED_turnON(LED_RED);

	/*Start Timer to count until reach 60 sec*/
	TIMER_init(&delay);

	 /*Wait until alarm is finished*/
	while(!g_alarmIsONFlag);

	/*Stop timer*/
	TIMER_deInit (delay.number);

	/*Alarm is finished*/
	g_alarmIsONFlag = FALSE ;

	BUZZER_turnOFF(BUZZER);
	LED_turnOFF(LED_RED);

}

/*
 * Description: Function to compare the passwords
 */

uint8 comparePassword(const uint8 * password1,const uint8 * password2)
{
    uint8 matchFlag=0,i=0;  // integer variables declaration
    while((password1[i]!='\0') && (password2[i]!='\0'))  // loop on 2 passwords
    {
       if(password1[i]!=password2[i])
       {
    	   matchFlag=1;
           break;
       }
       i++;
    }
    if(matchFlag==0)
    {
    	return 0;
    }

    else
    {
    	return 1;
    }

}
