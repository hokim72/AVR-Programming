#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "USART.h"

#define PIEZO		PC2
#define	LED_DDR		DDRB
#define	LED_PORT	PORTB
#define	LED0		PB0
#define	LED1		PB1
#define	ON_TIME		2000
#define	CYCLE_DELAY	10
#define	INITIAL_PADDING	16		/* higher is less sensitive */
#define	SWITCH		PB7			/* Attach LED or switch relay here */
#define	USE_POT		0			/* define to 1 if using potentiometer */
#if	USE_POT
#define	POT			PC5			/* optional padding pot */
#endif

void initADC(void) {
	ADMUX |= (1 << REFS0);		/* reference voltage to AVCC */
	ADCSRA |= (1 << ADPS1) | (1 << ADPS2); 	/* ADC clock prescaler /64 */
	ADCSRA |= (1 << ADEN);		/* enable ADC */
}

uint16_t readADC(uint8_t channel) {
	ADMUX = (0b11110000 & ADMUX) | channel;
	ADCSRA |= (1 << ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return (ADC);
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint16_t lightsOutTimer = 0;		/* timer for the switch */
	uint16_t adcValue;
	uint16_t middleValue = 511<<4;
	uint16_t highValue = 520<<4;
	uint16_t lowValue = 500<<4;
	uint16_t noiseVolume = 0;
	uint8_t padding = INITIAL_PADDING;

	LED_DDR = ((1 << LED0) | (1 << LED1) | (1 << SWITCH));
	initADC();
	initUSART();

	while (1) {
		adcValue = readADC(PIEZO);
		/* moving average -- tracks sensor's bias voltage */
		middleValue = adcValue + middleValue - ((middleValue - 8) >> 4);
		if (adcValue > (middleValue >> 4)) {
			highValue = adcValue + highValue - ((highValue - 8) >> 4);
		}
		if (adcValue < (middleValue >> 4)) {
			lowValue = adcValue + lowValue - ((lowValue - 8) >> 4);
		}
		/* "padding" provides a minimum value for the noise volume */
		noiseVolume = highValue - lowValue + padding;

		/* Now check to see if ADC value above or below thresholds */
		/* Comparison with >> 4 b/c EWMA is on different scale */
		if (adcValue < ((middleValue - noiseVolume) >> 4)) {
			LED_PORT = (1 << LED0) | (1 << SWITCH);		/* one LED, switch */
			lightsOutTimer = ON_TIME / CYCLE_DELAY;		/* reset timer */
		}
		else if (adcValue > ((middleValue + noiseVolume) >> 4)) {
			LED_PORT = (1 << LED1) | (1 << SWITCH);		/* other LED, switch */
			lightsOutTimer = ON_TIME / CYCLE_DELAY;		/* reset timer */
		}
		else {			/* Nothing seen, turn off lights */
			LED_PORT &= ~(1 << LED0);
			LED_PORT &= ~(1 << LED1);		/* Both off */
			if (lightsOutTimer > 0) {		/* time left on timer */
				lightsOutTimer--;
			}
			else {
				LED_PORT &= ~(1 << SWITCH);		/* turn switch off */
			}
		}
#if USE_POT				/* optional padding potentiometer */
		padding = readADC(POT) << 4; /* scale up to useful range */
#endif
						/* Serial output and delay */
						/* ADC is 10-bits, recenter around 127 for display purposes */
		transmitByte(adcValue - 512 + 127);
		transmitByte((lowValue >> 4) - 512 + 127);
		transmitByte((highValue >> 4) - 512 + 127);
		_delay_ms(CYCLE_DELAY);
	}
	return (0);
}
