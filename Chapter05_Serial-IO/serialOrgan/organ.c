#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"

void playNote(uint16_t wavelength, uint16_t duration) {
	uint16_t elapsed;
	uint16_t i;
	for (elapsed = 0; elapsed < duration; elapsed += wavelength) {
		/* for loop with variable wavelength selects the pitch */
		for (i=0; i<wavelength; i++) {
			_delay_us(1);
		}
		PORTD ^= (1 << PD6);
	}
}

void rest(uint16_t duration) {
	do {
		_delay_us(1);
	} while (--duration);
}
