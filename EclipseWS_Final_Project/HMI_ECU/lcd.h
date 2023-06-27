 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Mohamed Ezzat
 *
 * created date : 3/10/2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include"std_types.h"
#include"gpio.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LCD_BIT_MODE				   8

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTB_ID
#define LCD_RS_PIN_ID                  PIN6_ID

#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN5_ID

#if(LCD_BIT_MODE==4)
#define LCD_DATA_PORT_ID               PORTA_ID
#define LCD_DATA_PIN0_ID			   PIN3_ID
#define LCD_DATA_PIN1_ID			   PIN4_ID
#define LCD_DATA_PIN2_ID			   PIN5_ID
#define LCD_DATA_PIN3_ID			   PIN6_ID

#elif(LCD_BIT_MODE==8)
#define LCD_DATA_PORT_ID               PORTA_ID
#endif
/* LCD Commands */
#define LCD_CLEAR_SCREEN               		 0x01
#define LCD_GO_TO_HOME                 		 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  		 0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   		 0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                 		 0x0C
#define LCD_CURSOR_ON                  		 0x0E
#define LCD_SET_CURSOR_LOCATION        		 0x80

/*******************************************************************************
 *                                FUNCTIONS                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 8-bits.
 */
void LCD_init(void);

/*
 * Description :
 * Send the required data to the screen
 */
void LCD_displayCharacter(uint8 data);

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command);


/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *str);

/*
 * Description :
 * A function which change the cursor position according to given row and column
 */
void LCD_moveCursor(uint8 row,uint8 column);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 column,const char *str);
/*
 * Description :
 * remove the text displayed on the screen
 */
void LCD_clearScreen(void);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_integerToString(int data);

#endif /* LCD_H_ */
