 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Kyrillos Tharwat
 *
 *******************************************************************************/
#include "i2c.h"
#include "external_eeprom.h"

void EEPROM_init(void)
{
	/* just initialize the I2C(TWI) module inside the MC */
	TWI_init(0x01,400000);
}

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
    TWI_Start();
    if (TWI_getStatus() != TW_START)
        return ERROR1;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_Write((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR2;
		 
    /* Send the required memory location address */
    TWI_Write((uint8)(u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR3;
		
    /* write byte to eeprom */
    TWI_Write(u8data);
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR4;

    /* Send the Stop Bit */
    TWI_Stop();
	
    return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
    TWI_Start();
    if (TWI_getStatus() != TW_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_Write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR;
		
    /* Send the required memory location address */
    TWI_Write((uint8)(u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;
		
    /* Send the Repeated Start Bit */
    TWI_Start();
    if (TWI_getStatus() != TW_REP_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_Write((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TW_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readWithNACK();
    if (TWI_getStatus() != TW_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_Stop();
    return SUCCESS;
}


void EEPROM_writeString(uint16 u16addr,const uint8* Str)
{
	uint8 i = 0;
	while(Str[i]!='\0')
	{
		EEPROM_writeByte(u16addr+i,Str[i]);
		_delay_ms(80);
		i++;
	}
	EEPROM_writeByte(u16addr+i,Str[i]);
	_delay_ms(80);
}


void EEPROM_readString(uint16 u16addr,uint8 * Str)
{
	uint8 i = 0;
	EEPROM_readByte(u16addr+(uint16)i,&Str[i]);
	_delay_ms(10);
	while(Str[i]!='\0')
	{
		i++;
		EEPROM_readByte(u16addr+i,&Str[i]);
		_delay_ms(10);
	}
	Str[i] = '\0' ;
}
