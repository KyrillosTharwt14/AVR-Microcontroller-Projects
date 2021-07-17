 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include <stdlib.h>
#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"


#define LCD_DATA_PORT_DIR 	DDRC
#define LCD_DATA_PORT_OUT	PORTC

#define LCD_CTRL_PORT_DIR 	DDRD
#define LCD_CTRL_PORT_OUT	PORTD

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80
/***********Variables Declarations*************/
#define RS  PD4
#define RW  PD5
#define EN  PD6
/*********************************************/

/**********Functions Declarations*************/
void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(char data);
void LCD_displayString(char * str);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(int data);


/*********************************************/

#endif /* LCD_H_ */
