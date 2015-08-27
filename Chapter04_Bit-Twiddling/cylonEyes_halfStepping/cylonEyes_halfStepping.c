#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define DELAYTIME	85

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t i;
	DDRD = 0xff;		/* Data Direction Register B:
						   all set up for output */
	
	while(1) {

		for (i=0; i<7; i++) {			/* count i from 0 to 6 */
			PORTD |= (1 << i);			/* turn on led i */
			_delay_ms(DELAYTIME);					/* wait */

			PORTD |= (1 << (i+1));		/* turn the next led on */
			_delay_ms(DELAYTIME / 2);

			PORTD &= ~(1 << i);			/* turn off led i */
		}

		for (i=7; i>0; i--) {			/* count i from 7 to 1 */
			PORTD |= (1 << i);
			_delay_ms(DELAYTIME);

			PORTD |= (1 << (i-1));		/* turn the next led on */
			_delay_ms(DELAYTIME / 2);

			PORTD &= ~(1 << i);			/* turn off led i */
		}

	}
	return (0);
}
