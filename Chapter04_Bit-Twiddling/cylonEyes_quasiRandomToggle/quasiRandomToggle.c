#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define DELAYTIME	45
#define LED_PORT	PORTD
#define	LED_DDR		PORTD

int main(void) {
	clock_prescale_set(clock_div_16);

	uint16_t x = 0x1234;
	uint8_t y;
	LED_DDR = 0xff;			/* Data Direction Register B:
							   all set up for output */
	
	while (1) {

		x = 2053 * x + 138449;		/* "random" number generator */
		y = (x >> 8) & 0b00000111;	/* pick three bits from high byte */
		LED_PORT ^= (1 << y);		/* toggle one bit */
		_delay_ms(100);
	}

	return (0);
}
