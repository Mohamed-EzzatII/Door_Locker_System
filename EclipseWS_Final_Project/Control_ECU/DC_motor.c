/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_motor.c
 *
 * Description: Source file for the DC Motor driver dynamic configuration
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 7, 2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/*******************************************************************************
 *                                 Inclusion                                   *
 *******************************************************************************/

#include"std_types.h"
#include"gpio.h"
#include<avr/io.h>
#include"DC_motor.h"
#include"common_macros.h"


/*******************************************************************************
 *                                 Functions                                   *
 *******************************************************************************/

/* Description:
 * The Function responsible for setup the direction for the two motor
 * pins through the GPIO driver.
 */
void DcMotor_Init(void)
{
	/* setup the pin direction*/
	GPIO_setupPinDirection(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN0_ID,1);
	GPIO_setupPinDirection(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN1_ID,1);
	GPIO_setupPinDirection(DC_MOTOR_ENABLE_PORT_ID, DC_MOTOR_ENABLE_PIN_ID,1);

	/*stop the motor at the beginning*/
	GPIO_writePin(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN0_ID,0);
	GPIO_writePin(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN0_ID,0);

	/* Set the Enable bit*/
	GPIO_writePin(DC_MOTOR_ENABLE_PORT_ID, DC_MOTOR_ENABLE_PIN_ID,1);

}

/* Description:
 * The function responsible for rotate the DC Motor CW/ or
 * A-CW or stop the motor based on the state input state value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/* Choose the state if off or clockwise or anti-clockwise */
	switch(state)
	{
	case STOP_THE_MOTOR:
		GPIO_writePin(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN0_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN1_ID, LOGIC_LOW);
		break;
	case ROTATE_CLOCKWISE:
		GPIO_writePin(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN0_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN1_ID, LOGIC_LOW);
		break;
	case ROTATE_ANTI_CLOCKWISE:
		GPIO_writePin(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN0_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_OUTPUT_PORT_ID, DC_MOTOR_OUTPUT_PIN1_ID, LOGIC_HIGH);
		break;
	}
}
