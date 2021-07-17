/*
 * StopWatch.h
 *
 *  Created on: 2 May 2021
 *      Author: kyrillos tharwat
 */

#ifndef STOPWATCH_H_
#define STOPWATCH_H_


/***************************************/
/********Libraries**********************/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/***************************************/
/***************************************/

/***************************************/
/**********variables********************/
#define GIE 7   //I bit
#define Segments_num 6
#define ONE_SECOND 1
#define ZERO_SECOND 0
#define Digit_1  0
#define Digit_2  1
#define Digit_3  2
#define Digit_4  3
#define Digit_5  4
#define Digit_6  5
#define Delay_5ms 5 //delay 5 ms
/***************************************/
#define MAX_OF_FIRIST_SEC_DIGIT 10
#define MAX_OF_SECOND_SEC_DIGIT 6
#define MAX_OF_FIRIST_MIN_DIGIT 10
#define MAX_OF_SECOND_MIN_DIGIT 6
#define MAX_OF_FIRIST_HOUR_DIGIT 10
#define MAX_OF_SECOND_HOUR_DIGIT 10
/***************************************/
#define start_btn PB2
#define reset_btn PD2
#define stop_btn  PD3
/***************************************/
extern unsigned char Digit ;
extern unsigned char stopwatch [Segments_num] ;
/************************************************/
/************************************************/

/***********************************************************/
/**********Decleration of IO_peripheral fucntions***********/
void Init_IOs();
void PORTA_Config();
void PORTB_Config();
void PORTC_Config();
void PORTD_Config();
/*****Decleration of Interrupts_peripheral fucntions*******/
void Init_Interrupts ();
void INT0_Config ();
void INT1_Config ();
void INT2_Config ();
/*********Decleration of Timers_peripheral fucntions*******/
void Init_Timers();
void Timer1_Config();
void Set_Clock_ON();
void Set_Clock_OFF();
/**************Decleration of stopwatch fucntions***********/
void Reset_StopWatch ();
void Display_StopWatch ();
void Increment_StopWatch ();
/***********************************************************/
/***********************************************************/

#endif /* STOPWATCH_H_ */
