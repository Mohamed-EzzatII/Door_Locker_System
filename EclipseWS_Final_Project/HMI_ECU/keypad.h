 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the keypad driver
 *
 * Author: Mohamed Ezzat
 *
 * created date : 8/10/2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*******************************************************************************
 *                                Inclusions                                  *
 *******************************************************************************/

#include"std_types.h"

/*******************************************************************************
 *                         	    Definitions                                    *
 *******************************************************************************/
//#define STANDARD_KEYPAD
/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID           PIN1_ID

#define KEYPAD_COL_PORT_ID                PORTC_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN4_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH


/*******************************************************************************
 *                         FUNCTIONS Prototypes                                *
 *******************************************************************************/
/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);
#endif /* KEYPAD_H_ */
