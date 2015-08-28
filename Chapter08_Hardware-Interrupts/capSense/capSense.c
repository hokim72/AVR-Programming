#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include "USART.h"

#define CAP_SENSOR_DDR	DDRC
#define CAP_SENSOR_PORT	PORTC
#define CAP_SENSOR		PC1
#define LED_DDR			DDRB
#define LED_PORT		PORTB

#define SENSE_TIME	50
#define THRESHOLD	12000

volatile uint16_t chargeCycleCount;

void initPinChangeInterrupt(void) {
	PCICR |= (1 << PCIE1);	/* enable Pin-change interrupts 1 (bankC) */
	PCMSK1 |= (1 << PC1);	/* enable specific interrupt for out pin PC1 */
}

ISR(PCINT1_vect) {
	chargeCycleCount++;				/* count this change */

	CAP_SENSOR_DDR |= (1 << CAP_SENSOR);	/* output mode */
	_delay_us(1);						/* charging delay */

	CAP_SENSOR_DDR &= ~(1 << CAP_SENSOR);	/* set as input */
	PCIFR |= (1 << PCIF1);			/* clear the pin-change interrupt */
}

int main(void) {
	clock_prescale_set(clock_div_2);	/* full speed */
	initUSART();
	printString("==[ Cap Sensor ]==\r\n\r\n");

	LED_DDR = 0xff;
	MCUCR |= (1 << PUD);			/*  disable all pullups */
	CAP_SENSOR_PORT |= (1 << CAP_SENSOR);	/* we can leave output high */

	initPinChangeInterrupt();

	while (1) {
		chargeCycleCount = 0;		/* reset counter */
		CAP_SENSOR_DDR |= (1 << CAP_SENSOR);	/* start with cap charged */
		sei();				/* start up interrupts, counting */
		_delay_ms(SENSE_TIME);
		cli();
		if (chargeCycleCount < THRESHOLD) {
			LED_PORT = 0xff;
		}
		else {
			LED_PORT = 0;
		}
		printWord(chargeCycleCount);	/* for fine tuning */
		printString("\r\n");
	}

	return (0);
}
