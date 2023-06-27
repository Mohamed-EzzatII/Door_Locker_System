

 /******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer driver
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
#include"buzzer.h"
#include"gpio.h"

/*******************************************************************************/

/*******************************************************************************/

/**********************************Functions************************************/

/*
 * Description :
 * A function to initialize the buzzer
 */
void Buzzer_init(void)
{
	/*Make the buzzer pin output pin*/
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);

	/*Turn off the buzzer*/
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,PIN_INPUT);
}

/*
 * Description :
 * A function to turn on the buzzer
 */
void Buzzer_on(void)
{
	/*Turn on the buzzer*/
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
}

/*
 * Description :
 * A function to turn off the buzzer
 */
void Buzzer_off(void)
{
	/*Turn off the buzzer*/
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,PIN_INPUT);
}
