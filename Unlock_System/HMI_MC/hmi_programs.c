 /******************************************************************************
 *
 * Module: hmi programs
 *
 * File Name: hmi_programs
 *
 * Description: Source file for showing programs on LCD, and get the password
 * and send it to the control unit
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

/**********************************************************
 *                        INCLUDES                        *
 **********************************************************/
#include "hmi_programs.h"
#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include "timer.h"

/**********************************************************
 *                     Global Variables                   *
 **********************************************************/
uint8 flagProgram = 0;

static TIMER_Config delay= {TIMER1,Compare_Mode,F_CPU_1024,0,39062};

static uint8 g_tick = 0;
static uint8 g_doorIsMovingFlag = FALSE ;
static uint8 g_alarmIsONFlag = FALSE ;
/**********************************************************
 *                   Function Definitions                 *
 **********************************************************/

/*
 * Description: delay function for 15 seconds
 */
void _delayForMoveingTheDoor(void)
{
	g_tick ++ ;
	if (g_tick == NUMBER_OF_COMPARE_MATCH_PER_5_SECOND)
	{
		g_tick = 0 ;
		g_doorIsMovingFlag = TRUE ;
	}
}

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
 * Description: Get the password from the user and send to it
 */
void enterPassword(void)
{
	uint8 key ;
	uint8 num ;
	uint8 pass[PASSWORD_LENGHT];
	for (num = 0; num<PASSWORD_LENGHT-1; num++)
	{

		if (num == PASSWORD_LENGHT-2)
		{
			/*
			 * Insure the to get only # to send password
			 * Ignore error inputs from the user
			 */
			do{
				key= Keypad_getPressedKey();
				_delay_ms(250);
			}while(!((key == '#')));
		}
		else
		{
			/*
			 * Insure the to get only numbers to wirte password
			 * Ignore error inputs from the user
			 */
			do{
				key= Keypad_getPressedKey();
				_delay_ms(250);
			}while(!((key >= 0) && (key <= 9)));
		}

		if (key != '#')
		{
			pass[num]= key+'0';  //Convert from intger to character
			LCD_displayCharacter('*');

		}
		else
		{
			pass[num] = key;
		}
	}
	UART_sendString(pass);
}

/*
 * Description:
 *A program to initiate All the modules
 */
void startupProgram(void)
{
	/*Configure UART*/
	UART paramUart = {9600,1,dataMode_8,disableParity};

	/*LCD initialization*/
	LCD_init();

	/*UART initialization*/
	UART_init(&paramUart);

	/* HMI_MC is ready*/
	UART_sendByte(HMI_MC_READY);

	/*Get the Program number from other MC to show in lCD*/
	flagProgram = UART_receiveByte();
}

/*
 * Description:
 * This program run once, when the user start to implement his system
 * It takes the password from the user and send it to the control unit MC
 * It may run again if the user want to change his password
 */
void firstProgram(void)
{
	/*
	 * Acknowladgment variable to get the response from
	 * control unit MC and start the program
	 */
	uint8 ack=0;

	/*Enter the password for first time*/
	LCD_clearScreen();
	LCD_displayString("Please Enter The New Password:");
	LCD_goToRowColumn(1,0);
	enterPassword();

	/*re-Enter the password for to confirm*/
	LCD_clearScreen();
	LCD_displayString("Please Enter again to confirm:");
	LCD_goToRowColumn(1,0);
	enterPassword();

	/*get the response from control unit MC
	 * if ack = 1, (non-match password)first program will run again
	 * if ack = 2, (match password)default program will start
	 */
	ack = UART_receiveByte();
	flagProgram = ack ;
	if (flagProgram == 1)
	{
		LCD_clearScreen();
		LCD_displayString("ERROR");
		_delay_ms(100);
	}

}

/*
 * Description:
 * This is the default program
 * press + to enter the password, press - to change the password
 * for both option the have only 3 trials, then the system will give an alarm.
 */
void defaultProgram(void)
{
	/*
	 * Get the user chosen then send it to control unit MC
	 */
	uint8 key_option;
	LCD_clearScreen();
	LCD_displayString("+: Open The Door");
	LCD_goToRowColumn(1,0);
	LCD_displayString("-: Change The Password");
	key_option= Keypad_getPressedKey();
	_delay_ms(300);
	/*Enter the password to unlock the door*/
	if (key_option == '+')
	{
		uint8 trails = ZERO_NUMBER_OF_TRIALS;

		/*Loop until the user enter the right password*/
		do{
			UART_sendByte(key_option);
			LCD_clearScreen();
			LCD_displayString("Please Enter your Password correctly:");
			LCD_goToRowColumn(1,0);
			enterPassword();
			/*Get the numbers of trials from control unit MC*/
			trails = UART_receiveByte();
			if (trails == 0)
			{
				/*Start the door movement program*/
				doorMovementProgram();
			}
		}while( (trails > ZERO_NUMBER_OF_TRIALS) && (trails < MAX_NUMBERS_OF_TRIALS));

		if (trails == MAX_NUMBERS_OF_TRIALS)
		{
			/*user enter passwords wrong for 3 times*/
			alarmOnProgram();
		}
	}
	/*Enter the password to change it*/
	else if (key_option == '-')
	{
		uint8 trails = ZERO_NUMBER_OF_TRIALS;

		/*Loop until the user enter the right password*/
		do{
			UART_sendByte(key_option);
			LCD_clearScreen();
			LCD_displayString("Please Enter The Old Password:");
			LCD_goToRowColumn(1,0);
			enterPassword();
			trails = UART_receiveByte();
			if (trails == ZERO_NUMBER_OF_TRIALS)
			{
				/*Start first program to reinsert the password */
				firstProgram();
			}
		}while( (trails > ZERO_NUMBER_OF_TRIALS) && (trails < MAX_NUMBERS_OF_TRIALS));

		if (trails == MAX_NUMBERS_OF_TRIALS)
		{
			/*user enter passwords wrong for 3 times*/
			alarmOnProgram();
		}
	}
	/*else
	{
		secondProgram();
	}*/
}

/*
 * Description:
 * Function show opening door message for 15 second
 * and closing door message for 15 second also
 */
void doorMovementProgram(void)
{
	/*Set Timer call back function*/
	TIMER_setCallBack(delay.number,_delayForMoveingTheDoor);

	LCD_clearScreen();
	LCD_displayString("Door is Opening Now");
	doorIsMoving();

	/*Delay for 2000 seconds */
	_delay_ms(2000);

	LCD_clearScreen();
	LCD_displayString("Door is Closing Now");
	doorIsMoving();
}

/*
 * Description:
 * Function of delay for 15 second
 */
void doorIsMoving(void)
{
	/*Start Timer to count until reach 15 sec*/
	TIMER_init(&delay);

	 /*Wait until door is full open*/
	while(!g_doorIsMovingFlag);

	/*Stop timer*/
	TIMER_deInit (delay.number);

	/*Door is fully moved*/
	g_doorIsMovingFlag = FALSE ;
}

/*
 * Description:
 * Function show error message for 1 minute
 */
void alarmOnProgram(void)
{
	/*Set Timer call back function*/
	TIMER_setCallBack(delay.number,_delayForAlarm);

	LCD_clearScreen();
	LCD_displayString("!!!!!!!!!!!!ERROR PASSWORD!!!!!!!!!!!!");

	/*Start Timer to count until reach 60 sec*/
	TIMER_init(&delay);

	 /*Wait until alarm is finished*/
	while(!g_alarmIsONFlag);

	/*Stop timer*/
	TIMER_deInit (delay.number);

	/*Alarm is finished*/
	g_alarmIsONFlag = FALSE ;

}
