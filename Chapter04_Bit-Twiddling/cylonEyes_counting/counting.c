#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define DELAYTIME	100


int main(void) {
	clock_prescale_set(clock_div_16);

	DDRD = 0b11111111;
	PORTD = 0;

	while (1) {
		PORTD = PORTD + 1;
		_delay_ms(DELAYTIME);
	}

	return (0);
}
