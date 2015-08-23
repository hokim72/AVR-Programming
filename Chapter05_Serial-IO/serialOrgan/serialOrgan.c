#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale16.h"
#include "USART.h"

#define NOTE_DURATION	0xF000		/* determines long note length */

int main(void) {
	DDRD |= (1 << PD6);		/* speaker for output */
	initUSART();
	printString("----- Serial Organ -----\r\n");

	char fromCompy;			/* used to store serial input */
	uint16_t currentNoteLength = NOTE_DURATION / 2;
	const uint8_t keys[] = { 'a', 'w', 's', 'e', 'd', 'f', 't',
		'g', 'y', 'h', 'j', 'i', 'k', 'o',
		'l', 'p', ';', '\''
	};
	uint8_t isNote;
	uint8_t i;

	while (1) {
								/* Get Key */
		fromCompy = receiveByte(); /* waits here until there is input */
		transmitByte('N');	/* alert computer we're ready for next note */

								/* Play Notes */
		isNote = 0;
		for (i=0; i<sizeof(keys); i++) {
			if (fromCompy == '[') {			/* code for short note */
				currentNoteLength = NOTE_DURATION / 2;
			}
			else if (fromCompy == ']') {	/* code for long note */
				currentNoteLength = NOTE_DURATION;
			}
			else {						/* unrecognized, just rest */
				rest(currentNoteLength);
			}
		}
	}

	return (0);
}
