#include <avr/io.h>
#include <util/delay.h>

#define DELAYTIME 85
#define LED_PORT PORTD
#define LED_DDR  DDRD

int main(void) {

	uint8_t i=0;
	LED_DDR=0xff;	/* Data Direction Register D:
	all setup for output */

	while(1) {
		while (i < 7) {
			LED_PORT = (1 << i);		/* illuminate only i'th pin */
			_delay_ms(DELAYTIME);						/* wait */
			i = i + 1;					/* move to the next LED */
		}

		while (i > 0) {
			LED_PORT = (1 << i);		/* illuminate only i'th pin */
			_delay_ms(DELAYTIME);						/* wait */
			i = i - 1;					/* move to the previous LED */
		}
	}
	return (0);
}
