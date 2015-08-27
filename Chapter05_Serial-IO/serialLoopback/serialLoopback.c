#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "USART.h"


int main(void) {
	clock_prescale_set(clock_div_16);

	char serialCharacter;

	/* LED0-1 : PORTD6-7, LED2-7 : PORTB0-5 */
	DDRD |= 0xc0;
	DDRB = 0x3f;						/* set up LEDs for output */

	initUSART();
	printString("Hello World!\r\n");	/* to test */

	while (1) {
		serialCharacter = receiveByte();
		transmitByte(serialCharacter);
		PORTD &= ~0xc0;
		PORTD |= (serialCharacter & 0x03) << 6;
		PORTB = (serialCharacter & 0xfc) >> 2;
					/* display ascii/numeric value of character */
	}
	return (0);
}
