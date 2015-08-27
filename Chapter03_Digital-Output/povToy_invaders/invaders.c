#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define DELAYTIME 200

#define LED_PORT	PORTD
#define LED_DDR		DDRD

uint8_t invaderData1[] = {
  0b01110000,
  0b00011000,
  0b11111101,
  0b10110110,
  0b00111100,
  0b00111100,
  0b00111100,
  0b10110110,
  0b11111101,
  0b00011000,
  0b01110000
};

uint8_t invaderData2[] = {
  0b00001110,
  0b00011000,
  0b10111101,
  0b01110110,
  0b00111100,
  0b00111100,
  0b00111100,
  0b01110110,
  0b10111101,
  0b00011000,
  0b00001110
};

void pause(void) {
	uint8_t i;
	for (i=0; i<5; i++) {
		_delay_ms(DELAYTIME);
	}
}

void POVDisplay(uint8_t povData[], uint8_t numberRows) {
	uint8_t i;
	for (i=0; i<numberRows; ++i) {
		LED_PORT = povData[i];
		_delay_ms(DELAYTIME);
	}
	pause();
}

int main(void) {
	clock_prescale_set(clock_div_16);

	LED_DDR = 0xff;			/* set all LEDs to output */

	while (1) {
		POVDisplay(invaderData1, sizeof(invaderData1));
		POVDisplay(invaderData2, sizeof(invaderData2));
	}
	return (0);
}
