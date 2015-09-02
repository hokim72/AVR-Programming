#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include "macros.h"
#include "fullSaw15.h"

#define	SPEAKER_DDR		DDRD
#define	SPEAKER			PD6
#define LED_DDR			DDRB
#define LED0			PB0

#define	BASEPITCH		220		/* in tuningWord steps, which are ~1/2 Hz */
#define PHASE_RATE		7		/* controls speed of phasing effect */

#define	NUMBER_OSCILLATORS		4
/*	2 and 4 work just fine.
 	8 and 16 take too long to maintain our 31.25kHz sample rate
	so the pitch shifts downwards and there's all sorts of aliasing.
	If you're just after scary sounds, 8 and 16 are awesome, but you may want
	to increase the BASEPITCH to compensate. */

#define OSCILLATOR_SHIFT		2
/*	This is the number of bits to shift when volume mixing.
 	2**OSCILLATOR_SHIFT = NUMBER_OSCILLATORS
	If you don't change this to match the number of oscillators, you'll
	get clipping and digital distortion. */

static inline void initTimer0(void) {
	set_bit(TCCR0A, WGM00);			/* Fast PWM mode */
	set_bit(TCCR0A, WGM01);			/* Fast PWM mode */

	set_bit(TCCR0A, COM0A1);		/* PWM output on OCR0A */
	set_bit(SPEAKER_DDR, SPEAKER);	/* enable output on pin */

	set_bit(TCCR0B, CS00);			/* Clock with /1 prescaler */
}
