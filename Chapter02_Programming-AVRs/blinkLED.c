#include <avr/io.h> 		/* Defines pins, ports, etc */
#include <util/delay.h>		/* Functions to wast time */
#include <avr/power.h>

int main(void) {
	clock_prescale_set(clock_div_16);

	// Inits
	DDRD |= 0b00000001;		/* Data Direction Register D:
							   writing a one to the bit
							   enables output. */

	// Event loop
	while (1) {
		PORTD = 0b00000001;		/* Turn on first LED bit/pin in PORTD */
		_delay_ms(1000);									/* wait */

		PORTD = 0b00000000;		/* Turn off all D pins, including LED */
		_delay_ms(1000);									/* wait */

	}

	return (0);  /* This line is never reached */
}
