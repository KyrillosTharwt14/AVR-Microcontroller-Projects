 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: UART.h
 *
 * Description: Header file for the UART driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/
#ifndef UART_H_
#define UART_H_

/*------------------------INCLUDES------------------------*/
#include  "std_types.h"
#include  "micro_config.h"
#include  "common_macros.h"
/*--------------------------------------------------------*/


/*-------------Definitions And Configurations-------------*/
//#define USART_BAUDRATE 9600
#define disableParity 0x00
#define evenParity    0x20
#define oddParity     0x30

#define dataMode_5  0x00
#define dataMode_6  0x02
#define dataMode_7  0x04
#define dataMode_8  0x06
#define dataMode_9  0x0E
/*--------------------------------------------------------*/

/*----------Externs and shared global Variables-----------*/
extern uint8 data ;
/*--------------------------------------------------------*/
/*--------------------STRUCTURES--------------------------*/
typedef struct{
	uint32 BAUDRATE ;
	uint8 stopBit;
	uint8 dataMode;
	uint8 paritySelect;
}UART;
/*--------------------------------------------------------*/
/*----------------------ENUMS-----------------------------*/
/*--------------------------------------------------------*/
/*------------------Functions like Macros-----------------*/
/*--------------------------------------------------------*/
/*------------------Function Declarations-----------------*/
void UART_init(UART * uartParam);
uint8 UART_receiveByte(void);
void UART_sendByte(uint8 data);
void UART_sendString(const uint8 * Str);
void UART_receiveString(uint8 * Str);
/*--------------------------------------------------------*/





#endif /* UART_H_ */
