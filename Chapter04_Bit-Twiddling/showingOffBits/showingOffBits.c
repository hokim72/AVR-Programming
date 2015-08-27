#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define DELAYTIME 85
#define LED_PORT	PORTD
#define LED_DDR		DDRD

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t i;
	uint8_t repetitions;
	uint8_t whichLED;
	uint16_t randomNumber = 0x1234;

	LED_DDR = 0xff;			/* all LEDs configured for output */

	while (1) {
										/* Go Left */
		for (i=0; i<8; i++) {
			LED_PORT |= (1 << i);		/* turn on the i'th pin */
			_delay_ms(DELAYTIME);		/* wait */
		}
		for (i=0; i<8; i++) {
			LED_PORT &= ~(1 << i);		/* turn off the i'th pin */
			_delay_ms(DELAYTIME);		/* wait */
		}
		_delay_ms(5 * DELAYTIME);		/* pause */


		for (i=7; i<255; i--) {
			LED_PORT |= (1 << i);		/* turn on the i'th pin */
			_delay_ms(DELAYTIME);		/* wait */
		}
		for (i=7; i<255; i--) {
			LED_PORT &= ~(1 << i);		/* turn off the i'th pin */
			_delay_ms(DELAYTIME);		/* wait */
		}
		_delay_ms(5 * DELAYTIME);		/* pause */

										/* Toggle "random" bits for a while */
		for (repetitions = 0; repetitions < 75; repetitions++) {
										/* "random" number generator */
			randomNumber = 2053 * randomNumber + 13849;
										/* low three bits from high byte */
			whichLED = (randomNumber >> 8) & 0b00000111;
			LED_PORT ^= (1 << whichLED);/* toggle our LED */
			_delay_ms(DELAYTIME);
		}
		LED_PORT = 0;					/* all LEDs off */
		_delay_ms(5 * DELAYTIME);		/* pause */

	}

	return (0);
}
