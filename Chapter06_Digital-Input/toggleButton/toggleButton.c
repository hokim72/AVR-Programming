#include <avr/io.h>
#include <avr/power.h>

#define BUTTON_PORT		PORTD
#define BUTTON			PD2
#define BUTTON_PIN		PIND
#define LED_DDR			DDRB
#define LED_PORT		PORTB
#define LED0			PB0

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t buttonWasPressed;			/* state */
	BUTTON_PORT |= (1 << BUTTON);		/* enable the pullup on the button */
	LED_DDR = (1 << LED0);				/* set up LED for output */

	while (1) {
		if (bit_is_clear(BUTTON_PIN, BUTTON)) {		/* button is pressed now */
			if (buttonWasPressed == 0) {			/* but wasn't last time through */
				LED_PORT ^= (1 << LED0);			/* do whatever */
				buttonWasPressed = 1;				/* update the state */
			}
		}
		else {										/* button is not pressed now */
		buttonWasPressed = 0;					/* update the state */
		}
	}

	return (0);
}
