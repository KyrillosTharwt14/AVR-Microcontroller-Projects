 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/

#include "uart.h"
/**********************************************************
 *                     Global Variables                   *
 **********************************************************/

uint8 data ;

#define BAUD_PRESCALER(USART_BAUDRATE) (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)


/**********************************************************
 *                   Function Definitions                 *
 **********************************************************/
void UART_init(UART * uartParam)
{
	/**********UCSRA Configuration:
	 * U2X = 1, Set U2X to reduce the divisor of the baud rate divider from 16 to 8*/
	UCSRA = (1<<U2X);
	/****************************************************************************/
	/*********UCSRB Configuration:
	 * RXCIE = 0, Writing this bit to zero disables interrupt on the RXC Flag
	 * TXCIE = 0, Writing this bit to zero disables interrupt on the TXC Flag
	 * UDRIE = 0, Writing this bit to zero disables interrupt on the UDRE Flag
	 * RXEN  = 1, Writing this bit to one enables the USART Receiver
	 * TXEN  = 1, Writing this bit to one enables the USART Transmitter
	 * UCSZ2 = 0, Writing this bit to zero to use 8-data bit mode
	 * RXB8  = 0, Writing this bit to zero to use 8-data bit mode
	 * TXB8  = 0, Writing this bit to zero to use 8-data bit mode
	 ****************************************************************************/
	UCSRB |= (1<<RXEN) | (1<<TXEN) ;
	/****************************************************************************/
	/*************UCSRC Configuration:
	 * URSEL = 1, Writing this bit to one to write in the UCSRC
	 * UMSEL = 0, Writing this bit to zero to use Asynchronous mode
	 * UCPOL  = 0, Writing this bit to zero cause we use Asynchronous mode
	 ***************************************************************************/
	UCSRC |= (1<<URSEL);

	/*Set bit stop settings if we use 2 stop bit mode*/
	if (uartParam->stopBit == 2)
	{
		UCSRC |= (1<<USBS);
	}
	/*Set parity mode*/
	UCSRC = (UCSRC & 0xCF) | (uartParam->paritySelect & 0x30);
	/*Set the character size Mode*/
	UCSRC = (UCSRC & 0xF9) | (uartParam->dataMode & 0x06);

	/****************************************************************************/
	/* First 8 bits from the BAUD_PRESCALER inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = BAUD_PRESCALER(uartParam->BAUDRATE)>>8;
	UBRRL = BAUD_PRESCALER(uartParam->BAUDRATE);

}

void UART_sendByte(uint8 a_data)
{
	/*UDRE flag is set to one, the buffer is empty, and therefore ready to be written,
	 * so wait until is set and write the data into UDR register
	 */
	while (BIT_IS_CLEAR(UCSRA,UDRE));
	UDR=a_data;
	/************************* Another Method *************************
	UDR = a_data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

uint8 UART_receiveByte(void)
{
	/*RXC flag is set when when he receive a byte,and therefore ready to be read,
	 * so wait until is set and read the data from UDR register
	 */
	while (BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;
}

void UART_sendString(const uint8 * Str)
{
	uint8 i = 0 ;
	while (Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

void UART_receiveString(uint8 * Str)
{
	*Str = UART_receiveByte();
	while (*Str != '#')
	{
		Str++;
		*Str=UART_receiveByte();
	}
	*Str = '\0';
}

