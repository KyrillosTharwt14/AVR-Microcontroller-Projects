 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_



#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"




#define N_ROW 4
#define N_COL 4

#define KEYPAD_PORT_DIR    DDRA
#define KEYPAD_PORT_OUT    PORTA
#define KEYPAD_PORT_IN     PINA


uint8 Keypad_getPressedKey (void);


#endif /* KEYPAD_H_ */
