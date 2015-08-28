#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define LIGHT_SENSOR	PC0
#define POT				PC3
#define LED_DDR		DDRB
#define LED_PORT	PORTB

uint16_t readADC(uint8_t channel) {
	ADMUX = (0xf0 & ADMUX) | channel;
	ADCSRA |= (1 << ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return (ADC);
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint16_t lightThreshold;
	uint16_t sensorValue;

	// Set up ADC
	ADMUX |= (1 << REFS0);			/* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);	/* ADC clock prescaler /8 */
	ADCSRA |= (1 << ADEN);			/* enable ADC */

	LED_DDR = 0xff;

	while (1) {

		lightThreshold = readADC(POT);
		sensorValue = readADC(LIGHT_SENSOR);

		if (sensorValue < lightThreshold) {
			LED_PORT = 0xff;
		}
		else {
			LED_PORT = 0x00;
		}
	}

	return (0);
}
