 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 2, 2022
 *
 *******************************************************************************/

/************************Libraries and inclusions*******************************/

#include"common_macros.h"
#include<avr/io.h>
#include"gpio.h"

/*******************************************************************************/

/*
 * Description :
 * A function to set pin direction if it was input pin or output pin
 */
void GPIO_setupPinDirection(uint8 port_num,uint8 pin_num,GPIO_PinDirectionType direction)
{
	if(pin_num>PIN7_ID||pin_num<PIN0_ID)
	{
		/*do noting*/
	}
	else{

		if(direction==PIN_OUTPUT)
		{
			switch(port_num)
			{
			case PORTA_ID:
				DDRA|=(1<<pin_num);
				break;
			case PORTB_ID:
				DDRB|=(1<<pin_num);
				break;
			case PORTC_ID:
				DDRC|=(1<<pin_num);
				break;
			default:
				DDRD|=(1<<pin_num);
				break;
			}
		}
		else if(direction==PIN_INPUT)
		{
			switch(port_num)
			{
			case PORTA_ID:
				DDRA&=~(1<<pin_num);
				break;
			case PORTB_ID:
				DDRB&=~(1<<pin_num);
				break;
			case PORTC_ID:
				DDRC&=~(1<<pin_num);
				break;
			default:
				DDRD&=~(1<<pin_num);
				break;
			}
		}
	}
}

/*
 * Description :
 * A function to set whole port direction if it was input port or output port
 */
void GPIO_setupPortDirection(uint8 port_num,GPIO_PinDirectionType direction)
{
	if(port_num>PORTD_ID||port_num<PORTA_ID)
	{
		/*do noting*/
	}

	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			DDRA=direction;
			break;
		case PORTB_ID:
			DDRB=direction;
			break;
		case PORTC_ID:
			DDRC=direction;
			break;
		default:
			DDRD=direction;
			break;
		}
	}
}


/*
 * Description :
 * A function to set pin with 1 or 0
 */
void GPIO_writePin(uint8 port_num,uint8 pin_num,GPIO_PinDirectionType direction)
{
	if(pin_num>PIN7_ID||pin_num<PIN0_ID||(direction!=1 && direction!=0))
	{
		/*do noting*/
	}
	else{

		if(direction==PIN_OUTPUT)
		{
			switch(port_num)
			{
			case PORTA_ID:
				PORTA|=(1<<pin_num);
				break;
			case PORTB_ID:
				PORTB|=(1<<pin_num);
				break;
			case PORTC_ID:
				PORTC|=(1<<pin_num);
				break;
			default:
				PORTD|=(1<<pin_num);
				break;
			}
		}
		else if(direction==PIN_INPUT)
		{
			switch(port_num)
			{
			case PORTA_ID:
				PORTA&=~(1<<pin_num);
				break;
			case PORTB_ID:
				PORTB&=~(1<<pin_num);
				break;
			case PORTC_ID:
				PORTC&=~(1<<pin_num);
				break;
			default:
				PORTD&=~(1<<pin_num);
				break;
			}
		}
	}
}

/*
 * Description :
 * A function to write whole port direction if it is 0 or 0xFF
 */
void GPIO_writePort(uint8 port_num,GPIO_PinDirectionType direction)
{
	if(port_num>PORTD_ID||port_num<PORTA_ID)
	{
		/*do noting*/
	}

	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA=direction;
			break;
		case PORTB_ID:
			PORTB=direction;
			break;
		case PORTC_ID:
			PORTC=direction;
			break;
		default:
			PORTD=direction;
			break;
		}
	}
}


/*
 * Description :
 * A function to read pin if it is 1 or 0
 */
uint8 GPIO_readPin(uint8 port_num,uint8 pin_num)
{
	if(pin_num>PIN7_ID||pin_num<PIN0_ID)
	{
		return 0;
	}
	else{
		switch(port_num)
		{
		case PORTA_ID:
			return GET_BIT(PINA,pin_num);
		case PORTB_ID:
			return GET_BIT(PINB,pin_num);
		case PORTC_ID:
			return GET_BIT(PINC,pin_num);
		default:
			return GET_BIT(PIND,pin_num);
		}
	}
}


/*
 * Description :
 * A function to read whole port direction if it is 0 or 0xFF
 */
uint8 GPIO_readPort(uint8 port_num)
{
	if(port_num>PORTD_ID||port_num<PORTA_ID)
	{
		return 0;
	}

	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			return PINA;
		case PORTB_ID:
			return PINB;
		case PORTC_ID:
			return PINC;
		default:
			return PINC;
		}
	}
}
