#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"


int main(void) {
	char serialCharacter;

	/* LED0-1 : PORTD6-7, LED2-7 : PORTB0-5 */
	DDRD |= 0xc0;
	DDRB = 0x3f;						/* set up LEDs for output */

	initUSART();
	printString("Hello World!\r\n");	/* to test */

	while (1) {
		serialCharacter = receiveByte();
		transmitByte(serialCharacter);
		DDRD &= ~0xc0;
		DDRD |= (serialCharacter & 0x03) << 6;
		DDRB = (serialCharacter & 0xfc) >> 2;
					/* display ascii/numeric value of character */
	}
	return (0);
}
