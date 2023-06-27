

 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.c
 *
 * Description: Source file for the AVR Timer driver
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 27, 2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/************************Libraries and inclusions*******************************/

#include"common_macros.h"
#include<avr/io.h>
#include <avr/interrupt.h>
#include"timer1.h"

/*******************************************************************************/

/****************************Global Variables***********************************/

/*The global variable used in callback operation*/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************/

/****************************Functions and ISRs*********************************/

/* Normal mode ISR */
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* Compare mode ISR */
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}


/*
 * Description :
 * A function to initialize the timer
 */
void TIMER1_init(const Timer1_ConfigType* config_ptr)
{
	/*
	 * For TCCR1A register : -
	 * non-pwm mode so FOC1A and FOC2A = 1
	 * in case of compare and normal mode , WGM11 & WGM10 & WGM13 = 0
	 * but only WGM12 = 1 in case of compare and equal to 0 in case of normal mode
	 */
	TCCR1A = ( 1 << FOC1A ) | ( 1 << FOC1B );

	/*
	 * For TCCR1B register : -
	 * WGM12 = 1 -> Compare mode or 0 -> Normal mode
	 * CS12 : CS10 = prescaler value
	 */
	TCCR1B = ( config_ptr -> prescaler ) | ( ( config_ptr -> mode ) << WGM12 );

	/*
	 * OCR1A and TCNT1 and TIMASK registers configurations : -
	 */

	/*Timer works in compare mode*/
	if(config_ptr->mode==COMPARE)
	{
		/*
		 * For OCR1A register : -
		 * we put the max compare mode value here in case of compare mode only
		 */
		OCR1A = config_ptr -> compare_value;

		/*
		 * For TIMSK register : -
		 * we enable compare mode (A) interrupt
		 */
		TIMSK=(1<<OCIE1A);
	}

	/*Timer works in Normal mode*/
	else if(config_ptr->mode==NORMAL)
	{
		/*
		 * For TCNT1 register : -
		 * we put the initial counter value here
		 */
		TCNT1 = config_ptr -> initial_value;

		/*
		 * For TIMSK register : -
		 * we enable Normal mode interrupt
		 */
		TIMSK = ( 1 << TOIE1 );
	}
}

/*
 * Description :
 * A function to disable the timer
 */
void TIMER1_deInit(void)
{
	/* clear all registers */
	TCCR1A = TCCR1B = TIMSK = TCNT1 = OCR1A = 0;
}

/*
 * Description : -
 * A function to set callback function
 */
void TIMER1_setCallBack(void ( *a_ptr ) ( void ))
{
	g_callBackPtr = (volatile void (*)(void))a_ptr;

}
