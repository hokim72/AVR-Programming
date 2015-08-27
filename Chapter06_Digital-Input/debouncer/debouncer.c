#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define BUTTON_PORT			PORTD
#define BUTTON_PIN			PIND
#define BUTTON				PD2
#define LED_PORT			PORTB
#define LED_DDR				DDRB
#define	LED0				PB0

#define DEBOUNCE_TIME		1000

uint8_t debounce(void) {
	if (bit_is_clear(BUTTON_PIN, BUTTON)) {			/* button is pressed now */
		_delay_us(DEBOUNCE_TIME);
		if (bit_is_clear(BUTTON_PIN, BUTTON)) {		/* still pressed */
			return (1);
		}
	}
	return (0);
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t buttonWasPressed = 0;			/* state */
	BUTTON_PORT |= (1 << BUTTON);			/* enable the pullup on the button */
	LED_DDR = (1 << LED0);					/* set up LED for output */


	while (1) {
		if (debounce()) {					/* debounced button press */
			if (buttonWasPressed == 0) {	/* but wasn't last time through */
				LED_PORT ^= (1 << LED0);	/* do whatever */
				buttonWasPressed = 1;		/* update the state */
			}
		}
		else {								/* button is not pressed now */
			buttonWasPressed = 0;			/* update the state */
		}
	}
	return (0);
}
