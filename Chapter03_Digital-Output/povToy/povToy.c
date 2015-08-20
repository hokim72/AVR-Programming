#include <avr/io.h>
#include <util/delay.h>


void POVDisplay(uint8_t oneByte) {
	PORTD = oneByte;
	_delay_ms(2);
}

int main(void) {

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
		_delay_ms(10);

	}
	return (0);
}