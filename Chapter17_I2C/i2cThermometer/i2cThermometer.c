#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "USART.h"
#include "i2c.h"

#define	LM75_ADDRESS_W			0b10010000
#define	LM75_ADDRESS_R			0b10010001
#define	LM75_TEMP_REGISTER		0b00000000
#define	LM75_CONFIG_REGISTER	0b00000001
#define	LM75_THYST_REGISTER		0b00000010
#define LM75_TOS_REGISTER		0b00000011

int main(void) {
	
	uint8_t tempHighByte, tempLowByte;

	clock_prescale_set(clock_div_2);		/* 8MHz */
	initUSART();
	printString("\r\n====   i2c  Thermometer   ====\r\n");
	initI2C();

	while (1) {
		/* To set register, address LM75 in write mode */
		i2cStart();
		i2cSend(LM75_ADDRESS_W);
		i2cSend(LM75_TEMP_REGISTER);
		i2cStart();		/* restart, just send start again */
						/* Setup and send address, with read bit */
		i2cSend(LM75_ADDRESS_R);
						/* Now receive two bytes of temperature */
		tempHighByte = i2cReadAck();
		tempLowByte = i2cReadNoAck();
		i2cStop();

		// Print it out nicely over serial for now..
		printByte(tempHighByte);
		if (tempLowByte & _BV(7)) {
			printString(".5\r\n");
		}
		else {
			printString(".0\r\n");
		}

		_delay_ms(1000);
	}
	return (0);
}
