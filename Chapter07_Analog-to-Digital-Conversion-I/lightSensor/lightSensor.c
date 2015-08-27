#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define LED_DDR		DDRB
#define LED_PORT	PORTB

static inline void initADC0(void) {
	ADMUX |= (1 << REFS0);				/* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS2);				/* ADC clock prescaler /16 */
	ADCSRA |= (1 << ADEN);				/* enable ADC */
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t ledValue;
	uint16_t adcValue;
	uint8_t i;

	initADC0();
	LED_DDR = 0xff;

	while (1) {

		ADCSRA |= (1 << ADSC);			/* start ADC conversion */
		loop_until_bit_is_clear(ADCSRA, ADSC);	/* wait until done */
		adcValue = ADC;					/* read ADC in */
							/* Have 10 bits, want 3 (eight LEDs after all) */
		ledValue = (adcValue >> 0) & 0x03;
							/* Light up all LEDs up to ledValue */

		LED_PORT = 0;
		for (i=0; i<=ledValue; i++) {
			if (i<6) {
				LED_PORT |= 1 << i;
			}
		}
		_delay_ms(50);
	}
	return (0);
}
