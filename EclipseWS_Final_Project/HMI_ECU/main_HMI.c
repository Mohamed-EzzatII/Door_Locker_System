#include"HMI_func.h"
#include"uart.h"
#include"lcd.h"
#include"keypad.h"

#include"common_macros.h"
#include"std_types.h"

#include<util/delay.h>
#include<avr/io.h>
#include<avr/interrupt.h>


int main(void)
{
	SREG|=(1<<7);
	UART_ConfigType conf_UART;
	conf_UART.baud_rate=RATE_9600;
	conf_UART.bit_data=BitData_8;
	conf_UART.parity=NONE;
	conf_UART.stop_bit=BIT_1;
	UART_init(&conf_UART);
	LCD_init();
	LCD_displayString("        DOOR LOCKER SYSTEM ");
	LCD_moveCursor(1,0);
	_delay_ms(200);
	LCD_displayString("MADE BY : Mohamed Ezzat");
	_delay_ms(2000);
	LCD_clearScreen();
	LCD_displayString("            WELCOME");
	_delay_ms(2000);

	HMI_createSystemPassword();


	while(1)
	{

	}
}
