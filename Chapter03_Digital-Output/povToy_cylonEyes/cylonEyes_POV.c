#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define DELAYTIME 200

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t i=0;
	DDRD = 0b11111111;	/* Data Direction Register D: all on */


	while (1) {

		while (i < 7) {
			PORTD = (1 << i);	/* illuminate only i'th pin */
			_delay_ms(DELAYTIME);				/* wait */
			i = i + 1;			/* move to the next LED */
		}

		while (i > 0) {
			PORTD = (1 << i);	/* illuminate only i'th pin */
			_delay_ms(DELAYTIME);				/* wait */
			i = i - 1;			/* move to the previous LED */
		}
	}

	return (0);
}
