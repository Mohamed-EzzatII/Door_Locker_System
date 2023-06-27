 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: 24c16.h
 *
 * Description: Header file for the External EEPROM Memory
 *
 * Author: Mohamed Ezzat
 *
 *******************************************************************************/


#ifndef EEPROM24C16_H_
#define EEPROM24C16_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* EEPROM24C16_H_ */
