#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#define DELAY	100

static inline uint8_t LFSR8_step(uint8_t random);

int main(void) {
	clock_prescale_set(clock_div_16);

	DDRD = 0xff;			/* output on all LEDs */
	uint8_t random = 1;		/* can't init to 0, any other is ok */

	while (1) {
		random = LFSR8_step(random);
		PORTD = random;
		_delay_ms(DELAY);
	}

	return (0);
}

inline uint8_t LFSR8_step(uint8_t random) {
	/*
	 	Takes an 8-bit number, takes one step in a () LFSR.
		[3, 4, 5, 7] is the set of taps for 8-bits that goes through
		the whole cycle before repeating.

		If you're really serious about randomness, you'll want a different
		algorithm. In fact, this is a greate demo of how "predictable"
		the "pseudo-random" sequence is.

		Note that this is not a very efficient way to code this up,
		but it's meant mostly for teaching and is plenty fast
		because the compiler does an OK job with it.
	*/
   uint8_t tap1, tap2, tap3, tap4;
   uint8_t newBit;
   tap1 = 1 & (random >> 3);
   tap2 = 1 & (random >> 4);
   tap3 = 1 & (random >> 5);
   tap4 = 1 & (random >> 7);

   newBit = tap1 ^ tap2 ^ tap3 ^ tap4;
   random = ((random << 1) | newBit);

   return (random);
}
