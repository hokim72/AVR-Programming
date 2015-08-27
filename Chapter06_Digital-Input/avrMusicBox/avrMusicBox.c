#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "organ.h"
#include "scale16.h"

#define SPEAKER_DDR		DDRD
#define SPEAKER			PD6
#define BUTTON_PORT		PORTD
#define BUTTON_PIN		PIND
#define BUTTON			PD2

#define SONG_LENGTH (sizeof(song) / sizeof(uint16_t))

int main(void) {
	clock_prescale_set(clock_div_16);

	const uint16_t song[] = {
		E6, E6, E6, C6, E6, G6, G5,
		C6, G5, E5, A5, B5, Ax5, A5,
		G5, E6, G6, A6, F6, G6, E6, C6, D6, B5,
		C6, G5, E5, A5, B5, Ax5, A5,
		G5, E6, G6, A6, F6, G6, E6, C6, D6, B5,
	};

	/* starting at end b/c routine starts by incrementing and then playing
	   this makes the song start at the beginning after reboot */

	uint8_t whichNote = SONG_LENGTH - 1;
	uint8_t wasButtonPressed = 0;

	SPEAKER_DDR |= (1 << SPEAKER); 		/* speaker for output */
	BUTTON_PORT |= (1 << BUTTON);		/* pullup on button */

	while (1) {
		if (bit_is_clear(BUTTON_PIN, BUTTON)) {
			if (!wasButtonPressed) {		/* if it's a new press ... */
				whichNote++;				/* advance to next note */

				if (whichNote == SONG_LENGTH) {
					whichNote = 0;
				}
				wasButtonPressed = 1;
			}
			playNote(song[whichNote], 1600);
		}
		else {
			wasButtonPressed = 0;
		}
	}

	return (0);
}
