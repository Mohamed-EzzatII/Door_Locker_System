 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: i2c.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
 * Author: Mohamed Ezzat
 *
 *******************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define I2C_START         0x08 /* start has been sent */
#define I2C_REP_START     0x10 /* repeated start */
#define I2C_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define I2C_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define I2C_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define I2C_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define I2C_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


/*******************************************************************************
 *                      Type definition                                        *
 *******************************************************************************/



typedef struct{
 uint8 address;
 uint8 bit_rate;
}I2C_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description :
 * A function to initialize the I2C with address and frequency
 */
void I2C_init(const I2C_ConfigType * config_ptr);

/* Description :
 * A function to send the start bit
 */
void I2C_start(void);

/* Description :
 * A function to send stop bit
 */
void I2C_stop(void);

/* Description :
 * A function to send data
 */
void I2C_writeByte(uint8 data);

/* Description :
 * A function to read data and reply with ACK,so you can receive more data
 */
uint8 I2C_readByteWithACK(void);

/* Description :
 * A function to read data and reply with NACK,so you can't receive more data
 */
uint8 I2C_readByteWithNACK(void);

/* Description :
 * A function to get the status of I2C
 */
uint8 I2C_getStatus(void);


#endif /* I2C_H_ */
