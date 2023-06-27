
/*******************************************************************************
 *                         	    Inclusions                                     *
 *******************************************************************************/

#include"main_Functions.h"
#include"buzzer.h"
#include"DC_motor.h"
#include"E24c16.h"
#include"i2c.h"
#include"common_macros.h"
#include"uart.h"
#include"timer1.h"
#include"gpio.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

/*******************************************************************************
 *                         	    Global Variables                               *
 *******************************************************************************/
uint8 g_pass[5]={'A'};
uint8 g_operation=-1;
uint8 g_sec=0;
static volatile void (*g_functionPtr)(void)=NULL_PTR;
/*******************************************************************************
 *                         	      Functions                                    *
 *******************************************************************************/

/*
 * Description : -
 * A function to get the operation from HMI micro
 */
void CONTROL_getOperation(void)
{

	g_operation=CONTROL_recieveOperation();

	/*Discuss the function which will be done due to operation*/
	switch(g_operation)
	{
	case PASSWORD_SEND2CHANGE:
		g_functionPtr=CONTROL_changePasswordEEPROM;
		break;
	case PASSWORD_SEND2CONFIRM:
		CONTROL_writePasswordInEEPROM();
		break;
	case PASSWORD_CHECK:
		g_functionPtr=CONTROL_checkPassword;
		break;
	case OPEN_DOOR:
		g_functionPtr=CONTROL_motorRotate;
		break;
	case TIME_1_WRONG:
		g_functionPtr=CONTROL_activeBuzzer;
		break;
	}
	g_functionPtr();
	g_functionPtr=NULL_PTR;

}

/*
 * Description : -
 * A function that recieve a Operation
 */
volatile uint8 CONTROL_recieveOperation(void)
{
	/*Polling till we get a request for communication*/
	while(UART_recieveByte()!=START_COMM);

	/*tell the other micro that we are ready to recieve*/
	UART_sendByte(READY_RECIEVE);

	/*recieve the operation*/
	return UART_recieveByte();
}

/*
 * Description : -
 * A function that send a Operation
 */
void CONTROL_sendOperation(uint8 op)
{
	/*request communication*/
	UART_sendByte(START_COMM);

	/*ready to recieve*/
	while(UART_recieveByte()!=READY_RECIEVE);

	/*Send operation*/
	UART_sendByte(op);
}

/*
 * Description : -
 * A function to get the password from HMI micro and check it ,
 * and it returns PASS_MATCH if it the same password or return
 * PASS_MISMATCH if password doesn't match
 */
uint8 CONTROL_checkPassword(void)
{

	uint8 counter,temp;

	/*Get password from MC1*/
	for(counter=0;counter<5;counter++)
		g_pass[counter]=UART_recieveByte();

	/*Get password from EEPROM*/
	for(counter=0;counter<5;counter++)
	{
		EEPROM_readByte(EEPROM_ADDRESS+counter,&temp);

		/*Password doesn't match*/
		if(temp!=g_pass[counter])
		{
			UART_sendByte(PASS_MISMATCH);
			return PASS_MISMATCH;
		}
	}

	/*Password match*/
	UART_sendByte(PASS_MATCH);
	return PASS_MATCH;
}

/*
 * Description : -
 * A function to write new password in EEPROM
 */
void CONTROL_writePasswordInEEPROM(void)
{
	uint8 counter;
	for(counter=0;counter<5;counter++)
	{
		g_pass[counter]=UART_recieveByte();
		/*re-write the password*/
		EEPROM_writeByte(EEPROM_ADDRESS+counter,g_pass[counter]);
	}
}

/*
 * Description : -
 * A function to change our password
 */
void CONTROL_changePasswordEEPROM(void)
{
	if(CONTROL_checkPassword()==PASS_MATCH)
	{
		CONTROL_writePasswordInEEPROM();
	}
}

/*
 * Description : -
 * A function to Rotate Motor
 */
void CONTROL_motorRotate(void)
{
	/* Rotate motor clockwise*/
	DcMotor_Rotate(ROTATE_CLOCKWISE,5);
	delaySeconds(15);
	_delay_ms(300);

	/* Stop motor */
	DcMotor_Rotate(STOP_THE_MOTOR,5);
	delaySeconds(3);
	_delay_ms(300);

	/* Rotate motor clockwise*/
	DcMotor_Rotate(ROTATE_ANTI_CLOCKWISE,5);
	delaySeconds(15);
	_delay_ms(300);

	/* Stop motor */
	DcMotor_Rotate(STOP_THE_MOTOR,5);

}

/*
 * Description : -
 * A function to active buzzer for 1 minute
 */
void CONTROL_activeBuzzer(void)
{

	/*Turn on the buzzer*/
	Buzzer_on();

	delaySeconds(20);

	Buzzer_off();
}

/*
 * Description : 
 * A function that counts the sec by causing an interrupt every second and increase our global variable
 */
void delaySeconds(uint8 sec)
{
	/* setting the callBack function to count seconds */
	TIMER1_setCallBack(countSec);
	/* timer1 configurations to count sec per interrupt */
	Timer1_ConfigType timer1Config = {0,31250,N_256,COMPARE};

	TIMER1_init(&timer1Config);
	while(g_sec < sec);
	g_sec = 0;
	TIMER1_deInit();

}

/*
 * Description : 
 * A function that increase our global variable each second
 */
void countSec(void)
{
	g_sec++;
}
