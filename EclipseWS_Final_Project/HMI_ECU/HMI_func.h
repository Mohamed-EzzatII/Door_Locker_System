#ifndef HMI_FUNC_H_
#define HMI_FUNC_H_


/*******************************************************************************
 *                         	    Inclusions                                     *
 *******************************************************************************/
#include"std_types.h"

/*******************************************************************************
 *                         	    Definitions                                    *
 *******************************************************************************/
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
 * A function that send a Operation
 */
void HMI_sendOperation(uint8 op);

/*
 * Description : -
 * A function that recieve a Operation
 */
volatile uint8 HMI_recieveOperation(void);
/*
 * Description
 * A function to get the password from user while entering it
 * and send it to control ECU .
 */
void HMI_sendPassword(uint8 row,uint8 col,uint8 op);

/*
 * Description
 * A function to receive status from Control if password is accepted or not
 * if password is accepted , then return 1 , else return 0
 */
uint8 HMI_recieveStatus(void);

/*
 * Description
 * A function to create system password
 */
void HMI_createSystemPassword(void);

/* Description : -
 * A function to open door
 */
void HMI_openDoor(void);


/* Description : -
 * A function to open door
 */
void HMI_openDoorCheck(void);

/*
 * Description : -
 * A function to change the password
 */
void HMI_changePass(void);

/*
 * Description : -
 * A function to get what the user wants to do
 */
void HMI_changeOrOpen(void);


/*
 * Description :
 * A function that counts the sec by causing an interrupt every second and increase our global variable
 */
void delaySeconds(uint8 sec);

/*
 * Description : 
 * A function that increase our global variable each second
 */
void countSec(void);


#endif /* HMI_FUNC_H_ */
