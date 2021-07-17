 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/




#include "lcd.h"

void LCD_init()
{
	LCD_CTRL_PORT_DIR |= (1<<RS) | (1<<RW) | (1<<EN);
	LCD_DATA_PORT_DIR = 0xFF ;
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RS) ;
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RW) ;
	_delay_ms(1);
	SET_BIT(PORTD,EN) ;
	_delay_ms(1);
	LCD_DATA_PORT_OUT = command;
	_delay_ms(1);
	CLEAR_BIT(PORTD,EN) ;
	_delay_ms(1);
}

void LCD_displayCharacter(char data)
{
	SET_BIT(LCD_CTRL_PORT_OUT,RS) ;
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RW) ;
	_delay_ms(1);
	SET_BIT(PORTD,EN) ;
	_delay_ms(1);
	LCD_DATA_PORT_OUT = data;
	_delay_ms(1);
	CLEAR_BIT(PORTD,EN) ;
	_delay_ms(1);
}

void LCD_displayString(char * str)
{
	uint8 character = 0 ;
	while (str[character] != '\0')
	{
		LCD_displayCharacter(str[character]);
		character++;
	}
}

void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* 10 for decimal */
   LCD_displayString(buff);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}
