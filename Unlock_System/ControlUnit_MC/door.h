/*
 * door.h
 *
 *  Created on: 25 Jun 2021
 *      Author: koko
 */

#ifndef DOOR_H_
#define DOOR_H_


/**********************************************************
 *                        INCLUDES                        *
 **********************************************************/
#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"

/**********************************************************
 *             Definitions And Configurations             *
 **********************************************************/
#define NUMBER_OF_COMPARE_MATCH_PER_5_SECOND 3

/**********************************************************
 *                  Function Declarations                 *
 **********************************************************/
void DOOR_init(void);
/*
 * Description:
 * Function to ROTATE the motor clockwise to open the door
 * in 15 sec
 */
void DOOR_isOpened(void);
/*
 * Description:
 * Function to ROTATE the motor anti-clockwise to close the door
 * in 15 sec
 */
void DOOR_isClosed(void);
/*
 * Description:
 * Function to start a delay of 15 sec to make sure that the door
 * is fully opened
 */
void _delayForMoveingTheDoor(void);

#endif /* DOOR_H_ */
