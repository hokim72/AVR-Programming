#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

int main(void) {
	clock_prescale_set(clock_div_16);

	PORTD |= (1 << PD2);	/* initialize pullup resistor on our input pin */
	DDRB = 0x3f;			/* set up all LEDs for output */

	while (1) {
		if (bit_is_clear(PIND, PD2)) {	/* look for button press */
				/* equivalent if ((PIND & (1 << PD2)) == 0) { */
			PORTB = 0b00111000;				/* pressed */
		}
		else {								/* not pressed */
			PORTB = 0b00000111;
		}
	}

	return (0);
}
