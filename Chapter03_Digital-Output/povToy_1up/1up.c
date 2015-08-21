#include <avr/io.h>
#include <util/delay.h>
#define DELAYTIME 2


uint8_t Star1UP[] = {
  0b10000100,
  0b01101100,
  0b01111110,
  0b00011111,
  0b01111110,
  0b01101100,
  0b10000100,
  0b00000000,
  0b00000000,
  0b00000000,
  0b10000010,
  0b11111111,
  0b11111111,
  0b10000000,
  0b00000000,
  0b00000000,
  0b01111111,
  0b11111111,
  0b10000000,
  0b11111111,
  0b01111111,
  0b00000000,
  0b00000000,
  0b11111111,
  0b11111111,
  0b00110011,
  0b00110011,
  0b00011110,
  0b00011110,
};

int main(void) {
	uint8_t i;

	DDRD = 0xff;			/* all output */

	while (1) {
		for (i=0; i<sizeof(Star1UP); i++) {
			/* sizeof(Star1UP) returns the number of bytes in our array, */
			PORTD = Star1UP[i];
			_delay_ms(DELAYTIME);
		}

		PORTB = 0;			/* blank for gap between repetitions */
		_delay_ms(5 * DELAYTIME);
	}

	return (0);
}
