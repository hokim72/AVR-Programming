#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "USART.h"

#define SAMPLE_DELAY	30	

static inline void initFreerunningADC(void) {
	ADMUX |= (1 << REFS0);		/* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);	/* ADC clock prescaler /8 */

	//ADMUX |= (1 << ADLAR);	/* left-adjust result, return only 8bits */

	ADCSRA |= (1 << ADEN);		/* enable ADC */
	ADCSRA |= (1 << ADATE);		/* auto-trigger enable */
	ADCSRA |= (1 << ADSC);		/* start first conversion */
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t dummy;

	initUSART();
	initFreerunningADC();
	
	while (1) {
		//transmitByte(ADCH);	
		dummy = ADCH;
		dummy = ADCL;
		transmitByte(dummy);	
		_delay_ms(SAMPLE_DELAY);
	}

	return (0);
}
