#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "USART.h"
#include "25LC256.h"

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t i;
	uint8_t address;

	initSPI();
	initUSART();


	while (1) {
		printString("\r\n==== EEPROM Memory Playground ====\r\n");
		printString("Address Value\r\n");

		for (i=0; i<10; i++) { /* print out first ten bytes of memory */
			printString("    ");
			printByte(i);
			printString("    ");
			printByte(EEPROM_readByte(i));
			printString("\r\n");
		}
		printString(" [e] to erase all memory\r\n");
		printString(" [w] to write byte to memory\r\n\r\n");

		switch (receiveByte()) {			/* take input */
		case 'e':
			printString("Clearing EEPROM, this could take a few seconds.\r\n");
			EEPROM_clearAll();
			break;
		case 'w':
			printString("Which memory slot would you like to write to?\r\n");
			address = getNumber();
			printString("\r\nWhat number would you like to store there?\r\n");
			i = getNumber();
			EEPROM_writeByte(address, i);
			printString("\r\n");
			break;
		default:
			printString("What?\r\n");
		}
	}

	return (0);
}
