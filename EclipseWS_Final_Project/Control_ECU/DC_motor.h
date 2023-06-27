
/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_motor.h
 *
 * Description: header file for the DC Motor driver dynamic configuration
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

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/*******************************************************************************
 *                              Type Definition                                *
 *******************************************************************************/

typedef enum{
	STOP_THE_MOTOR,ROTATE_CLOCKWISE,ROTATE_ANTI_CLOCKWISE
}DcMotor_State;

/*******************************************************************************
 *                               Definition                                    *
 *******************************************************************************/

#define DC_MOTOR_OUTPUT_PORT_ID PORTA_ID
#define DC_MOTOR_OUTPUT_PIN0_ID PIN2_ID
#define DC_MOTOR_OUTPUT_PIN1_ID PIN1_ID
#define DC_MOTOR_ENABLE_PORT_ID PORTA_ID
#define DC_MOTOR_ENABLE_PIN_ID  PIN0_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description:
 * The Function responsible for setup the direction for the two motor
 * pins through the GPIO driver.
 */
void DcMotor_Init(void);

/* Description:
 * The function responsible for rotate the DC Motor CW/ or
 * A-CW or stop the motor based on the state input state value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
