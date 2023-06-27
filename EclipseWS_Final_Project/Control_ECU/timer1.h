/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Description: header file for the AVR TIMER1 driver
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 27, 2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/
#include"std_types.h"

#ifndef TIMER1_H_
#define TIMER1_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	NO_CLK_SOURCE,N_1,N_8,N_64,N_256,N_1024

}Timer1_prescaler;

typedef enum
{
	NORMAL,COMPARE
}Timer1_mode;

typedef struct
{
	uint16 initial_value;
	uint16 compare_value;
	Timer1_prescaler prescaler;
	Timer1_mode mode;
}Timer1_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * A function to initialize the timer
 */
void TIMER1_init(const Timer1_ConfigType* config_ptr);

/*
 * Description :
 * A function to disable the timer
 */
void TIMER1_deInit(void);

/*
 * Description : -
 * A function to set callback function
 */
void TIMER1_setCallBack(void ( *a_ptr ) ( void ));


#endif /* TIMER1_H_ */
