#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include "USART.h"
#include "support.h"

#define LED_DDR		DDRB
#define	LED_PORT	PORTB
#define BUTTON_PORT	PORTD
#define BUTTON_PIN	PIND
#define BUTTON		PD2

static inline void initTimer(void) {
			/* Normal mode (devault), just counting */
	TCCR1B |= (1 << CS11) || (1 << CS10);
	/* Clock speed: 1MHz / 64,
	   each tick is 64 microseconds ~= 15.6 per ms */
	/* No special output modes */
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint16_t timerValue;

	initUSART();
	initTimer();
	LED_DDR = 0xff;					/* all LED for output */
	BUTTON_PORT |= (1 << BUTTON);	/* enable internal pull-up */

	printString("\r\nReaction Timer:\r\n");
	printString("-------------------\r\n");
	printString("Press any key to start.\r\n");

	while(1) {

		receiveByte();				/* press any key */
		printString("\r\nGet ready...");
		randomDelay();

		printString("\r\nGo!\r\n");
		LED_PORT = 0xff;			/* light LEDs */
		TCNT1 = 0;					/* reset couter */

		if (bit_is_clear(BUTTON_PIN, BUTTON)) {
			/* Button pressed _exactly_ as LEDs light up. Suspicious. */
			printString("You're only cheating yourself.\r\n");
		}
		else {
			// Wait until button pressed, save timer value.
			loop_until_bit_is_clear(BUTTON_PIN, BUTTON);
			timerValue = TCNT1 >> 4;
			/* each tick is approx 1/16 milliseconds, so we bit-shift divide */

			printMilliseconds(timerValue);
			printComments(timerValue);
		}

		// Clear LEDs and start again.
		LED_PORT = 0x00;
		printString("Press any key to try again.\r\n");

	}

	return (0);
}
