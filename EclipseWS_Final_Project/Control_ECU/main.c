#include"main_Functions.h"
#include<avr/io.h>
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

int main(void)
{
	DcMotor_Init();
	Buzzer_init();
	SREG |= (1<<7);

	UART_ConfigType conf_UART;
	conf_UART.baud_rate=RATE_9600;
	conf_UART.bit_data=BitData_8;
	conf_UART.parity=NONE;
	conf_UART.stop_bit=BIT_1;
	UART_init(&conf_UART);

	/* I2C configurations structure */
	I2C_ConfigType i2cConfig = {0x20,0b0000010};

	/* initialize I2C */
	I2C_init(&i2cConfig);

	while(1)
	{
		CONTROL_getOperation();
	}
}
