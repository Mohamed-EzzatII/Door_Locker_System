 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: i2c.c
 *
 * Description: Source file for the TWI(I2C) AVR driver
 *
 * Author: Mohamed Ezzat
 *
 *******************************************************************************/

#include "i2c.h"
#include "common_macros.h"
#include <avr/io.h>

/* Description :
 * A function to initialize the I2C with address and frequency
 */
void I2C_init(const I2C_ConfigType * config_ptr)
{
	/* setup the prescaler and baud rate*/
	TWBR=config_ptr->bit_rate;
	TWSR=0;

	/* For TWCR register : -
	 *  6 - enable ACK(is for receiving only!!)
	 *  2 - enable I2C
	 */
	TWCR=(1<<TWEN);

	/* Set the device address */
	TWAR=config_ptr->address;
}

/* Description :
 * A function to send the start bit
 */
void I2C_start(void)
{

	/*send the start bit and clear the flag*/
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);

	/*Polling till the start is send(flag is set)*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

}

/* Description :
 * A function to send stop bit
 */
void I2C_stop(void)
{
	/*send the stop bit and clear the flag*/
	TWCR=(1<<TWSTO)|(1<<TWEN)|(1<<TWINT);
}

/* Description :
 * A function to send data
 */
void I2C_writeByte(uint8 data)
{
	/* we write data to data register and clear the flag and enable the i2c
	 */
	TWDR=data;
	TWCR=(1<<TWEN)|(1<<TWINT);

	/*Polling till the data is send(flag is set)*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/* Description :
 * A function to read data and reply with ACK,so you can receive more data
 */
uint8 I2C_readByteWithACK(void)
{
	/*Enable I2C and ACK and clear the flag*/
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);

	/*polling till the data is received(flag is set)*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/*Get the data from TWDR register(data register)*/
	return TWDR;

}

/* Description :
 * A function to read data and reply with NACK,so you can't receive more data
 */
uint8 I2C_readByteWithNACK(void)
{
	/*Enable I2C and clear the flag*/
	TWCR=(1<<TWEN)|(1<<TWINT);

	/*polling till the data is received(flag is set)*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/*Get the data from TWDR register(data register)*/
	return TWDR;

}

/* Description :
 * A function to get the status of I2C
 */
uint8 I2C_getStatus(void)
{
	/*we get the bits from 3 to 7*/
	return TWSR & 0b11111000;
}
