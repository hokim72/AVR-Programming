#include <avr/io.h>
#include <util/delay.h>

#define DELAYTIME	100


int main(void) {
	DDRD = 0b11111111;
	PORTD = 0;

	while (1) {
		PORTD = PORTD + 1;
		_delay_ms(DELAYTIME);
	}

	return (0);
}
