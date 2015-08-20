#include <avr/io.h>
#include <util/delay.h>


void POVDisplay(uint8_t oneByte) {
	PORTB = oneByte;
	_delay_ms(2);
}

int main(void) {

	DDRB = 0x3f;	/* Set up all of LED pins for output */

	while(1) {
		POVDisplay(0b001110);
		POVDisplay(0b011000);
		POVDisplay(0b111101);
		POVDisplay(0b110110);
		POVDisplay(0b111100);
		POVDisplay(0b111100);
		POVDisplay(0b111100);
		POVDisplay(0b110110);
		POVDisplay(0b111101);
		POVDisplay(0b011000);
		POVDisplay(0b001110);

		PORTB = 0;
		_delay_ms(10);

	}
	return (0);
}
