
#ifndef MAIN_FUNCTIONS_H_
#define MAIN_FUNCTIONS_H_


/*******************************************************************************
 *                         	    Inclusions                                     *
 *******************************************************************************/

#include"std_types.h"

/*******************************************************************************
 *                         	    Definitions                                    *
 *******************************************************************************/

#define EEPROM_ADDRESS			  0x0311
#define PASSWORD_SEND2CHANGE  	  1
#define PASSWORD_SEND2CONFIRM  	  2
#define PASSWORD_CONF  	  		  3
#define PASSWORD_CHECK 	  		  4

#define OPEN_DOOR	   	  		  5
#define CLOSE_DOOR	   	  		  6

#define TIME_15_CW	   	  		  7
#define TIME_15_ACW	   	  	      8
#define TIME_3_delay   	  		  9

#define TIME_1_WRONG   	  		  10
#define MAX_WRONG      	  		  3

#define CONFIRM_SEND   	  		  11
#define CONFIRM_RECIEVE   		  12

#define READY_SEND   	  		  13
#define READY_RECIEVE     		  14

#define START_COMM		  		  15

#define PASS_MISMATCH  	  		  16
#define PASS_MATCH     	  		  17

#define TIME_15SEC				  14648
#define TIME_60SEC				  58593
#define TIME_3SEC				  4883

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : -
 * A function to get the operation from HMI micro
 */
void CONTROL_getOperation(void);

/*
 * Description : -
 * A function that recieve a Operation
 */
volatile uint8 CONTROL_recieveOperation(void);

/*
 * Description : -
 * A function that send a Operation
 */
void CONTROL_sendOperation(uint8 op);

/*
 * Description : -
 * A function to get the password from HMI micro and check it ,
 * and it returns PASS_MATCH if it the same password or return
 * PASS_MISMATCH if password doesn't match
 */
uint8 CONTROL_checkPassword(void);

/*
 * Description : -
 * A function to write new password in EEPROM
 */
void CONTROL_writePasswordInEEPROM(void);

/*
 * Description : -
 * A function to change our password
 */
void CONTROL_changePasswordEEPROM(void);

/*
 * Description : -
 * A function to Rotate Motor Clockwise for 15 sec
 */
void CONTROL_motorClockwise(void);

/*
 * Description : -
 * A function to Rotate Motor
 */
void CONTROL_motorRotate(void);
/*
 * Description : -
 * A function to active buzzer for 1 minute
 */
void CONTROL_activeBuzzer(void);

/*
 * Description :
 * A function that increase our global variable each second
 */
void countSec(void);

/*
 * Description :
 * A function that counts the sec by causing an interrupt every second and increase our global variable
 */
void delaySeconds(uint8 sec);
#endif /* MAIN_FUNCTIONS_H_ */
