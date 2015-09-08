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

	const char *stringPointer; 
	const uint16_t *wordPointer;
	uint8_t i;
	char oneLetter;

	stringPointer = &myVeryLongString[0];		/* address of first char */
	// stringPointer = myVeryLongString;		/* same as above */
	wordPointer = &sixteenBits;					/* address of first byte */

	while (1) {
		for (i=0; i<sizeof(myVeryLongString); i++) {
			oneLetter = pgm_read_byte(stringPointer + i);
			transmitByte(oneLetter);
			_delay_ms(100);		/* slow it down to simulate typing effect :) */
		}
		_delay_ms(1000);

		printWord(pgm_read_word(wordPointer));
	}

	return (0);
}
