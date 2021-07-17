 /******************************************************************************
 *
 * Module: hmi programs
 *
 * File Name: hmi_programs.h
 *
 * Description: Header file for showing programs on LCD, and get the password
 * and send it to the control unit
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/


#ifndef HMI_PROGRAMS_H_
#define HMI_PROGRAMS_H_

/**********************************************************
 *                        INCLUDES                        *
 **********************************************************/
#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"

/**********************************************************
 *             Definitions And Configurations             *
 **********************************************************/
#define HMI_MC_READY   0x14

#define PASSWORD_LENGHT 7

#define NUMBER_OF_COMPARE_MATCH_PER_5_SECOND 3
#define NUMBER_OF_COMPARE_MATCH_PER_1_MINUTE 12

#define ZERO_NUMBER_OF_TRIALS 0
#define MAX_NUMBERS_OF_TRIALS 3


/**********************************************************
 *         Externs and shared global Variables            *
 **********************************************************/
extern uint8 flagProgram ;

/**********************************************************
 *                  Function Declarations                 *
 **********************************************************/


/*
 * Description: delay function for 60 seconds
 */
void _delayForAlarm(void);

/*
 * Description: delay function for 15 seconds
 */
void _delayForMoveingTheDoor(void);

/*
 * Description: Get the password from the user and send to it
 */
void enterPassword(void);

/*
 * Description: A program to initiate All the modules
 */
void startupProgram(void);

/*
 * Description:
 * This program run once, when the user start to implement his system
 * It takes the password from the user and send it to the control unit MC
 * It may run again if the user want to change his password
 */
void firstProgram(void);

/*
 * Description:
 * This is the default program
 * press + to enter the password, press - to change the password
 * for both option the have only 3 trials, then the system will give an alarm.
 */
void defaultProgram(void);

/*
 * Description: Function show error message for 1 minute
 */
void alarmOnProgram(void);

/*
 * Description: Function show opening door message for 15 second
 * and closing door message for 15 second also
 */
void doorMovementProgram(void);

/*
 * Description: Function of delay for 15 second
 */
void doorIsMoving(void);

#endif /* HMI_PROGRAMS_H_ */
