#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define	LED_PORT	PORTB
#define LED_DDR		DDRB
#define LED_DELAY	20

void pwmAllPins(uint8_t brightness) {
	uint8_t i;
	LED_PORT = 0xff;			/* turn on */
	for (i=0; i<255; i++) {
		if (i >= brightness) {	/* once it's been on long enough */
			LED_PORT = 0;		/* turn off */
		}
		_delay_us(LED_DELAY);
	}
}

int main(void) {
	clock_prescale_set(clock_div_16);

	uint8_t brightness = 0;
	int8_t direction = 1;

	LED_DDR = 0xff;

	while (1) {
		// Bright and dim
		if (brightness == 0) {
			direction = 1;
		}
		if (brightness == 255) {
			direction = -1;
		}
		brightness += direction;
		pwmAllPins(brightness);
	}

	return (0);
}
