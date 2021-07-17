 /******************************************************************************
 *
 * Application : Control Motor Speed and Direction
 *
 * File Name: main.c
 *
 * Description: Control motor speed by using ADC to convert the Analog input from
 * 				and the result value is the speed of motor.
 * 				Also, the direction of motor can be changed by using a button init
 * 				external inturrpts
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#include "lcd.h"
#include "motor.h"
#include "button.h"

int main()
{
	SREG  |= (1<<7);    /*Enable Global Interrupts*/
	LCD_init();         /*Configure the LCD*/
	BUTTON_init();      /*Configure the button*/
	MOTOR_init();       /*Start the movement of motor*/
	while(1)
	{
		MOTOR_Rotate(mode);
		LCD_goToRowColumn(0,0);
		LCD_displayString ("ADC Value: ");
		LCD_intgerToString(adc_value);
		if (adc_value < 1023)
		{
			LCD_displayCharacter(' ');
			if (adc_value < 100)
			{
				LCD_displayCharacter(' ');
			}
		}
	}
}
