#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "USART.h"

#define LED_DDR	DDRB
#define	LED1	PB1
#define LED2	PB2
#define LED3	PB3

static inline void initTimers(void) {
	// Timer 1 A,B
	TCCR1A |= (1 << WGM10);			/* Fast PWM mode, 8-bit */
	TCCR1B |= (1 << WGM12);			/* Fast PWM mode, pt.2 */
	TCCR1B |= (1 << CS11);			/* PWM Freq = F_CPU/8/256 */
	TCCR1A |= (1 << COM1A1);		/* PWM output on OCR1A */
	TCCR1A |= (1 << COM1B1);		/* PWM output on OCR1B */

	// Timer 2
	TCCR2A |= (1 << WGM20);			/* Fast PWM mode */
	TCCR2A |= (1 << WGM21);			/* Fast PWM mode, pt.2 */
	TCCR2B |= (1 << CS21);			/* PWM Freq = F_CPU/8/256 */
	TCCR2A |= (1 << COM2A1);		/* PWM output on OCR2A */
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t brightness;

	initTimers();
	initUSART();
	printString("-- LED PWM Demo --\r\n");

		/* enable output on LED pins, triggered by PWM hardware */
	LED_DDR |= (1 << LED1);
	LED_DDR |= (1 << LED2);
	LED_DDR |= (1 << LED3);

	while (1) {

		printString("\r\nEnter (0-255) for PWM duty cycle: ");
		brightness = getNumber();
		OCR2A = OCR1B;
		OCR1B = OCR1A;
		OCR1A = brightness;
	}

	return (0);
}
