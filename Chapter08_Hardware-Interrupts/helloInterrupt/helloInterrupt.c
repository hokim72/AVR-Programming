#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#define LED_PORT	PORTB
#define LED_DDR		DDRB
#define LED0		PB0
#define LED1		PB1

#define BUTTON_PORT	PORTD
#define BUTTON_PIN	PIND
#define	BUTTON		PD2

ISR(INT0_vect) {		/* Run every time there is a change on button */
	if (bit_is_clear(BUTTON_PIN, BUTTON)) {
		LED_PORT |= (1 << LED1);
	} else {
		LED_PORT &= ~(1 << LED1);
	}
}

void initInterrupt0(void) {
	EIMSK |= (1 << INT0);				/* enable INT0 */
	EICRA |= (1 << ISC00);				/* trigger when button changes */
	sei();								/* set (global) interrupt enable bit */
}

int main(void) {
	clock_prescale_set(clock_div_16);

	LED_DDR = 0xff;					/* all LEDs active */
	BUTTON_PORT |= (1 << BUTTON);	/* pullup */
	initInterrupt0();

	while (1) {
		_delay_ms(200);
		LED_PORT ^= (1 << LED0);
	}

	return (0);
}
