#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include "USART.h"

#define ANTENNA_DDR	DDRD
#define	ANTENNA		PD5
#define	LED_PORT	PORTB
#define LED_DDR		DDRB
#define	LED0		PB0
#define	LED1		PB1
#define	SPEED_STEP_DELAY	2

static inline void initTimer0(void) {
	TCCR0A |= (1 << WGM00);			/* Fast PWM mode */
	TCCR0A |= (1 << WGM01);			/* Fast PWM mode, pt.2 */
	TCCR0A |= (1 << COM0B1);		/* output PWM to pin */
	TCCR0B |= (1 << CS02);			/* Clock with /256 prescaler */
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t updateSpeed;

	initTimer0();
	OCR0B = 0;

	ANTENNA_DDR |= (1 << ANTENNA);	/* now hooked up to MOSFET, output */
	LED_DDR |= (1 << LED0);
	LED_DDR |= (1 << LED1);

	initUSART();
	printString("DC Motor Workout\r\n");

	while (1) {

		updateSpeed = getNumber();

		/* Ramp up/down to desired speed */

		if (OCR0B < updateSpeed) {
			LED_PORT |= (1 << LED0);
			while (OCR0B < updateSpeed) {
				OCR0B++;
				_delay_ms(SPEED_STEP_DELAY);
			}
		}
		else {
			LED_PORT |= (1 << LED1);
			while (OCR0B > updateSpeed) {
				OCR0B--;
				_delay_ms(SPEED_STEP_DELAY);
			}
		}
		LED_PORT = 0;				/* all off */
	}

	return (0);
}
