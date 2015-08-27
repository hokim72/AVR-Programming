#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define DELAYTIME	75

int main(void) {
	clock_prescale_set(clock_div_16);

	DDRD = 0b11111111;		/* Data Direction Register D:
							   all set up for output */

	while(1) {
		PORTD = 0b00000001;
		_delay_ms(DELAYTIME);
		PORTD = 0b00000010;
		_delay_ms(DELAYTIME);
		PORTD = 0b00000100;
		_delay_ms(DELAYTIME);
		PORTD = 0b00001000;
		_delay_ms(DELAYTIME);
		PORTD = 0b00010000;
		_delay_ms(DELAYTIME);
		PORTD = 0b00100000;
		_delay_ms(DELAYTIME);
		PORTD = 0b01000000;
		_delay_ms(DELAYTIME);
		PORTD = 0b10000000;
		_delay_ms(DELAYTIME);
		PORTD = 0b01000000;
		_delay_ms(DELAYTIME);
		PORTD = 0b00100000;
		_delay_ms(DELAYTIME);
		PORTD = 0b00010000;
		_delay_ms(DELAYTIME);
		PORTD = 0b00001000;
		_delay_ms(DELAYTIME);
		PORTD = 0b00000100;
		_delay_ms(DELAYTIME);
		PORTD = 0b00000010;
		_delay_ms(DELAYTIME);
	}
	return (0);
}
