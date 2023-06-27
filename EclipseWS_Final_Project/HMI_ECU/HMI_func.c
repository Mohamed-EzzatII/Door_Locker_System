
/*******************************************************************************
 *                         	    Inclusions                                     *
 *******************************************************************************/
#include"uart.h"
#include"timer1.h"
#include"gpio.h"
#include"lcd.h"
#include"keypad.h"
#include"HMI_func.h"
#include"common_macros.h"

#include<util/delay.h>
#include<avr/io.h>
#include<avr/interrupt.h>

/*******************************************************************************
 *                         	    Global Variables                               *
 *******************************************************************************/
uint8 static g_checkPassword=0;
uint8 g_sec=0;


/*******************************************************************************
 *                         	      Functions                                    *
 *******************************************************************************/

/*
 * Description : -
 * A function that recieve a Operation
 */
volatile uint8 HMI_recieveOperation(void)
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
void HMI_sendOperation(uint8 op)
{
	/*request communication*/
	UART_sendByte(START_COMM);

	/*ready to recieve*/
	while(UART_recieveByte()!=READY_RECIEVE);

	/*Send operation*/
	UART_sendByte(op);
}

/* Description
 * A function to get the password from user while entering it
 * and send it to control ECU .
 */
volatile void HMI_sendPassword(uint8 row,uint8 col,uint8 op)
{
	uint8 counter=0;

	/* Sending our operation to MC2 and ask him to start*/
	HMI_sendOperation(op);
	_delay_ms(300);

	/*Move LCD cursor to the place which we will get password from*/
	LCD_moveCursor(row,col);
	_delay_ms(300);
	/*get password and display * instead of entered character*/
	for(counter=0;counter<5;counter++)
	{
		UART_sendByte( KEYPAD_getPressedKey());
		_delay_ms(100);
		LCD_displayCharacter('*');
		_delay_ms(100);
	}

	/* Polling till the user entered = as enter button */
	while( KEYPAD_getPressedKey() != '=' );
	_delay_ms(300);
}

/* Description
 * A function to create system password , and get to change password
 * or open door screen
 */
void HMI_createSystemPassword(void)
{
	LCD_clearScreen();
	/*Ask the user to enter password first time*/
	LCD_displayString("please enter password:");
	_delay_ms(20);
	HMI_sendPassword(1,0,PASSWORD_SEND2CONFIRM);
	_delay_ms(200);

	/*Ask the user to enter password second time*/
	LCD_moveCursor(1,0);
	LCD_displayString("same password : ");
	_delay_ms(20);
	HMI_sendPassword(1,17,PASSWORD_CHECK);
	_delay_ms(200);

	/*repeat the previous step again*/
	while(UART_recieveByte()==PASS_MISMATCH)
	{
		HMI_createSystemPassword();
	}

	LCD_clearScreen();
	LCD_displayString("Password updated successfully!");
	_delay_ms(1000);
	HMI_changeOrOpen();

}

/* Description : -
 * A helping function to open door , which rotate the motor clockwise
 */
void HMI_openDoor(void)
{
	/*Rotate motor clockwise*/
	HMI_sendOperation(OPEN_DOOR);
	_delay_ms(20);

	LCD_clearScreen();
	LCD_displayString("Door is Unlocking!!");
	delaySeconds(15);

	LCD_clearScreen();
	LCD_displayString("Door is Unlocked!!");
	delaySeconds(3);

	LCD_clearScreen();
	LCD_displayString("Door is locking!!");
	delaySeconds(15);

	LCD_clearScreen();
	LCD_displayString("Door is locked!!");

	_delay_ms(1000);
	HMI_changeOrOpen();

}

void HMI_threeWrong()
{
	/*We exceeded 3 wrong entries*/
	if(g_checkPassword==MAX_WRONG)
	{
		_delay_ms(20);
		/*Tell control MCU*/
		HMI_sendOperation(TIME_1_WRONG);

		/*Display wrong pass on screen*/
		LCD_clearScreen();
		_delay_ms(20);
		LCD_displayString("Error !! wrong password");

		delaySeconds(20);
		g_checkPassword=0;
		HMI_changeOrOpen();
	}
}


/* Description : -
 * A function to open door and start rotation clockwise
 */
void HMI_openDoorCheck(void)
{
	LCD_clearScreen();
	/*Ask the user to enter password*/
	LCD_displayString("please enter password:");

	HMI_sendPassword(1,0,PASSWORD_CHECK);

	uint8 pass_stat=UART_recieveByte();

	/*Password matches*/
	if(pass_stat == PASS_MATCH)
	{
		LCD_clearScreen();
		HMI_openDoor();
		_delay_ms(20);
		g_checkPassword=0;
		HMI_sendOperation(OPEN_DOOR);
		return;
	}
	/*Password doesn't match*/
	while(pass_stat == PASS_MISMATCH)
	{
		g_checkPassword++;
		LCD_clearScreen();
		LCD_displayString("Wrong Password ! ");
		LCD_moveCursor(1,0);
		LCD_displayString("Wrong password");
		LCD_moveCursor(1,0);
		LCD_displayString("Remaining trials : ");
		LCD_integerToString(3-g_checkPassword);
		_delay_ms(1000);
		HMI_threeWrong();

		LCD_clearScreen();
		/*Call the function again*/
		HMI_openDoorCheck();

		LCD_clearScreen();
		/*Ask the user to enter password*/
		LCD_displayString("please enter password:");

		HMI_sendPassword(1,0,PASSWORD_CHECK);

		pass_stat=UART_recieveByte();
		if(g_checkPassword==0)
			break;
	}
}



/* Description : -
 * A function to change the password
 */
void HMI_changePass(void)
{
	LCD_clearScreen();
	TIMER1_deInit();
	/*Ask the user to enter password*/
	LCD_displayString("please enter password:");
	HMI_sendPassword(1,0,PASSWORD_CHECK);


	uint8 pass_stat=UART_recieveByte();
	/*Password matches*/
	if(pass_stat == PASS_MATCH)
	{
		LCD_clearScreen();
		HMI_createSystemPassword();
		g_checkPassword=0;
		_delay_ms(1000);
		HMI_changeOrOpen();
		return;
	}

	/*Password doesn't match*/
	/*Password doesn't match*/
	while(pass_stat == PASS_MISMATCH)
	{
		g_checkPassword++;
		HMI_threeWrong();

		LCD_clearScreen();
		LCD_displayString("Wrong Password ! ");
		LCD_moveCursor(1,0);
		LCD_displayString("Remaining trials : ");
		LCD_integerToString(3-g_checkPassword);
		_delay_ms(1000);

		LCD_clearScreen();

		/*Call the function again*/

		LCD_clearScreen();
		/*Ask the user to enter password*/
		LCD_displayString("please enter password:");

		HMI_sendPassword(1,0,PASSWORD_CHECK);

		pass_stat=UART_recieveByte();
		if(g_checkPassword==0)
			break;
	}
}


/* Description : -
 * A function to get what the user wants to do
 */
void HMI_changeOrOpen(void)
{
	uint8 key;
	LCD_clearScreen();
	/*Ask the user to enter what he wants to do*/
	LCD_displayString("+ : Open the door");
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Password");
	_delay_ms(500);

	key=KEYPAD_getPressedKey();
	_delay_ms(500);
	/*The user chose to open door , so we call it's function*/
	if(key=='+')
	{
		HMI_openDoorCheck();
	}

	/*The user chose to change password , so we call it's function*/
	else if(key=='-')
	{
		HMI_changePass();
	}
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
