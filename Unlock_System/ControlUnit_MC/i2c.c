 /******************************************************************************
 *
 * Module: I2C(TWI)
 *
 * File Name: i2c.c
 *
 * Description: Source file for the I2C(TWI) AVR driver
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/


#include "i2c.h"
#define BUAD_PRESCALER(I2C_BUADRATE) ((((F_CPU/I2C_BUADRATE)-16)/2UL))


void TWI_init(uint8 address,uint32 Buadrate)
{
    /* Configure bit Rate: 400.000 kbps, using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
    TWBR = BUAD_PRESCALER(Buadrate);
	TWSR = 0x00;

	/*Two wire bus address, configure my address when another master call
	 * me as a slave
	 *Turn off  general call recognetion*/
	TWAR = (address<<1); /*Shift address by one to put in 7 MSB bit in TWAR*/
	/****TWCR Description:
	 * TWEN = 1, Enable TWI operations and activate TWI interface
	 */
	TWCR = (1<<TWEN);
}

#ifdef TWI_init_void
void TWI_init(void)
{
    /* Configure bit Rate: 400.000 kbps, using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
    TWBR = 0x02;
	TWSR = 0x00;

	/*Two wire bus address, configure my address when another master call
	 * me as a slave
	 *Turn off  general call recognetion*/
	TWAR = 0b00000010;
	/****TWCR Description:
	 * TWEN = 1, Enable TWI operations and activate TWI interface
	 */
	TWCR = (1<<TWEN);
}
#endif

void TWI_Start(void)
{
	/*
	 * Clear the TWINT bi  before sending start bit
	 * Send start bit by set TWSTA
	 * Enable TWI operations by set TWEN
	 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	/*Wait until start bit is sent (TWINT flag is set)*/
	while (BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_Stop(void)
{
	/*
	 * Clear the TWINT before sending stop bit
	 * Send stop bit by set TWSTO
	 * Enable TWI operations by set TWEN
	 */
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

void TWI_Write(uint8 data)
{
	/*Put data in TWDR register*/
	TWDR = data ;
	/*
	 * Clear the TWINT before sending data
	 * Enable TWI operations by set TWEN
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
	/*Wait until data is sent (TWINT flag is set)*/
	while (BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readWithACK(void)
{
	/*
	 * Clear the TWINT before receiving data
	 * Send sending ACK after sending or receving data by set TWEA
	 * Enable TWI operations by set TWEN
	 */
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	/*Wait until data is received (TWINT flag is set)*/
	while (BIT_IS_CLEAR(TWCR,TWINT));
	/*read the data in TWDR*/
	return TWDR;
}

uint8 TWI_readWithNACK(void)
{
	/*
	 * Clear the TWINT before receiving data
	 * Enable TWI operations by set TWEN
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
	/*Wait until data is received (TWINT flag is set)*/
	while (BIT_IS_CLEAR(TWCR,TWINT));
	/*read the data in TWDR*/
	return TWDR;
}
uint8 TWI_getStatus(void)
{
	uint8 status;
	/*Mask first 3 LSB with zero to read the 5 MSB clearly (status bits)*/
	status = (TWSR & 0xF8);
	return status;

}
