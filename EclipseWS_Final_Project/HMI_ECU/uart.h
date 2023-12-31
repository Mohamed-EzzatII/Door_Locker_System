 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"


/*******************************************************************************
 *                      	 Type Definition                                   *
 *******************************************************************************/

/*Even parity or odd parity or none*/
typedef enum{
	NONE,
	EVEN_PARITY=2,
	ODD_PARITY=3
}UART_Parity;

/*How many bits we will send*/
typedef enum{
	BitData_5,
	BitData_6,
	BitData_7,
	BitData_8
}UART_BitData;

/*How many stop bits we will send*/
typedef enum{
	BIT_1=0,
	BIT_2=1
}UART_StopBit;

/*Value of UBRR according to our baud rate , while we works in double speed mode*/
typedef enum{
	RATE_2400=416,
	RATE_4800=207,
	RATE_9600=103,
	RATE_14_4K=68,
	RATE_19_2K=51,
	RATE_28_8K=34,
	RATE_38_4K=25,
	RATE_57_6K=16,
	RATE_115_2K=8,
	RATE_230_4K=3,
	RATE_250K=3,
	RATE_500K=1,
	RATE_1M=0,
}UART_BaudRate;


/*Our configurations*/
typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * A function to setup the UART with the given baud rate and number of send bits and parity
 * checker and number of stop bits .
 */
void UART_init(const UART_ConfigType* config);

/*
 * Description :
 * A function to send a given byte using UART
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * A function to return the received byte
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * A function to send a given string , u don't need to add anything after the end of string
 * but don't send a string that contain #
 */
void UART_sendString(const uint8 *str);

/*
 * Description :
 * A function that receive a string ended by #
 */
void UART_receiveString(uint8 *str); // Receive until #

#endif /* UART_H_ */
