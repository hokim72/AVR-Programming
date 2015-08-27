#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "USART.h"

#define LED_PORT	PORTB
#define LED_DDR		DDRB
#define LED0		PB0
#define BUTTON_PORT	PORTD
#define BUTTON		PD6
#define BUTTON_PIN	PIND

static inline void blinkLED(void) {
	LED_PORT = (1 << LED0);
	_delay_ms(1000);
	LED_PORT &= ~(1 << LED0);
}

int main(void) {
	clock_prescale_set(clock_div_16);

	BUTTON_PORT |= (1 << BUTTON);		/* input mode, turn on pullup */

	LED_DDR = (1 << LED0);
	blinkLED();

	initUSART();
	transmitByte('O');

	while (1) {
		if (bit_is_clear(BUTTON_PIN, BUTTON)) {
			transmitByte('X');
			blinkLED();
		}
	}

	return (0);
}
