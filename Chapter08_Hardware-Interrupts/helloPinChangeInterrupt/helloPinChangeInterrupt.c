#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#define LED_DDR		DDRB
#define	LED_PORT	PORTB
#define	LED0		PB0
#define	LED1		PB1
#define BUTTON_PIN	PIND
#define BUTTON_PORT	PORTD
#define BUTTON		PD2

ISR(PCINT2_vect) {		/* Run every time button state changes */
	if (bit_is_clear(BUTTON_PIN, BUTTON)) {
		LED_PORT |= (1 << LED1);
	}
	else {
		LED_PORT &= ~(1 << LED1);
	}
}

void initPinChangeInterrupt18(void) {
	PCICR |= (1 << PCIE2);		/* set pin-change interrupt for D pins */
	PCMSK2 |= (1 << PCINT18);	/* set mask to look for PCINT18 / PD2 */
	sei();						/* set (global) interrupt enable bit */
}

int main(void) {
	clock_prescale_set(clock_div_16);

	LED_DDR = 0xff;					/* all LEDs active */
	BUTTON_PORT |= (1 << BUTTON);	/* pullup */
	initPinChangeInterrupt18();

	while (1) {
		_delay_ms(200);
		LED_PORT ^= (1 << LED0);
	}
	return (0);
}
