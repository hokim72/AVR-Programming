#include <avr/io.h> 		/* Defines pins, ports, etc */
#include <util/delay.h>		/* Functions to wast time */

int main(void) {

	// Inits
	DDRB |= 0b00000001;		/* Data Direction Register D:
							   writing a one to the bit
							   enables output. */

	// Event loop
	while (1) {
		PORTB = 0b00000001;		/* Turn on first LED bit/pin in PORTD */
		_delay_ms(1000);									/* wait */

		PORTB = 0b00000000;		/* Turn off all D pins, including LED */
		_delay_ms(1000);									/* wait */

	}

	return (0);  /* This line is never reached */
}
