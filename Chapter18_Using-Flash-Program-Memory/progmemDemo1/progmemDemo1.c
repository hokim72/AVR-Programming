#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/power.h>
#include "USART.h"

const char myVeryLongString[] PROGMEM = "\r\nHi there, \
this is an example of a long string.\r\n\
The kind that you wouldn't want to store in RAM.\r\n";
const uint16_t sixteenBits PROGMEM = 12345;

int main(void) {
	clock_prescale_set(clock_div_16);

	initUSART();
	char oneLetter;
	uint8_t i;

	while (1) {
		for (i=0; i < sizeof(myVeryLongString); i++) {
			oneLetter = pgm_read_byte(&(myVeryLongString[i]));
			transmitByte(oneLetter);
			_delay_ms(100); /* slow it down to simulate typing effect :) */
		}
		_delay_ms(1000);

		printWord((uint16_t)&sixteenBits);	/* this throws a compiler warning... */
		transmitByte('\r');
		transmitByte('\n');
		printWord(pgm_read_word(&sixteenBits));
	}

	return (0);
}
