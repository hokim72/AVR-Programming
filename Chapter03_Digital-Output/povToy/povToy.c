#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>


void POVDisplay(uint8_t oneByte) {
	PORTD = oneByte;
	_delay_ms(200);
}

int main(void) {
	clock_prescale_set(clock_div_16);

	DDRD = 0xff;	/* Set up all of LED pins for output */

	while(1) {
		POVDisplay(0b00001110);
		POVDisplay(0b00011000);
		POVDisplay(0b10111101);
		POVDisplay(0b01110110);
		POVDisplay(0b00111100);
		POVDisplay(0b00111100);
		POVDisplay(0b00111100);
		POVDisplay(0b01110110);
		POVDisplay(0b10111101);
		POVDisplay(0b00011000);
		POVDisplay(0b00001110);

		PORTD = 0;
		_delay_ms(1000);

	}
	return (0);
}
