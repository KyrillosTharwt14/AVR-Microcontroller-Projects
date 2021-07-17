 /******************************************************************************
 *
 * Module: control_unit_programs.h
 *
 * File Name: control_unit_programs.h
 *
 * Description: Header file for performing programs and receive the password
 * from hmi MC ans store it in the eeprom then compare it to inlock the door
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#ifndef CONTROL_UNIT_PROGRAMS_H_
#define CONTROL_UNIT_PROGRAMS_H_



/**********************************************************
 *                        INCLUDES                        *
 **********************************************************/
#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"
#include "external_eeprom.h"

/**********************************************************
 *             Definitions And Configurations             *
 **********************************************************/

#define HMI_MC_READY   0x14

#define PROGRAM_ADDRESS  0x50
#define PASSWORD_ADDRESS 0x100

#define FIRST_PROGRAM  1
#define SECOND_PROGRAM 2

#define PASSWORD_LENGHT 7

#define ZERO_NUMBER_OF_TRIALS 0
#define MAX_NUMBERS_OF_TRIALS 3

#define NUMBER_OF_COMPARE_MATCH_PER_1_MINUTE 12

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
 * Description: A program to initiate All the modules
 */
void startupProgram(void);

/*
 * Description:
 * This program run once, when the user start to implement his system
 * It receive the password from the HMI MC and save it to in EEPROM
 * It may run again if the user want to change his password
 */
void firstProgram(void);

/*
 * Description:
 * This is the default program
 * Receive the password from HMI_MC
 * if the password is correct, the door is opened and closed in 30 s
 * if the password is not correct, Alarm is started  in 60 s
 * for both option the have only 3 trial
 */
void defaultProgram(void);

/*
 * Description: Get the password from the HMI_MC and check it
 * if is right or not
 */
void checkPassword(uint8 * matchPassword);

/*
 * Description: Function show error message for 1 minute
 */
void alarmProgram(void);

/*
 * Description: Function to compare the passwords
 */
uint8 comparePassword(const uint8 * password1,const uint8 * password2);

#endif /* CONTROL_UNIT_PROGRAMS_H_ */
