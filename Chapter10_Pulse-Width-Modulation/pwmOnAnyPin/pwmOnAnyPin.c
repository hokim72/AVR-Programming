#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#define LED_DDR		DDRB
#define	LED_PORT	PORTB
#define DELAY	3

volatile uint8_t brightnessA;
volatile uint8_t brightnessB;

static inline void initTimer0(void) {
			/* must be /64 or more for ISR timing */
	TCCR0B |= (1 << CS01) | (1 << CS00);
			/*  both output compare interrupts */
	TIMSK0 |= ((1 << OCIE0A) | (1 << OCIE1B));
	TIMSK0 |= (1 << TOIE0);		/* overflow interrupt enable */
	sei();
}

ISR(TIMER0_OVF_vect) {
	LED_PORT = 0x03;
	OCR0A = brightnessA;
	OCR0B = brightnessB;
}
ISR(TIMER0_COMPA_vect) {
	LED_PORT &= 0x01;		/* turn off LED0 */
}
ISR(TIMER0_COMPB_vect) {
	LED_PORT &= 0x02;		/* turn off LED1 */
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t i;
	LED_DDR = 0xff;
	initTimer0();

	while (1) {
		for (i=0; i< 255; i++) {
			_delay_ms(DELAY);
			brightnessA = i;
			brightnessB = 255 - i;
		}

		for (i=254; i>0; i--) {
			_delay_ms(DELAY);
			brightnessA = i;
			brightnessB = 255 -i;
		}
	}

	return (0);
}
