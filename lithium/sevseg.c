/* Single 7 segment display controller */
#include <avr/io.h>
#include <avr/interrupt.h>

// Select which register the display is on. It must have at least 7 pins.
#define DISPREG DDRB
#define DISPORT PORTB

// Definitions of the numbers. This is for common anode displays.
static unsigned char segvals[] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x58,0x00,0x10}; 
////////////////////////////////// 0     1    2    3    4    5    6    7    8    9


void set7seg(unsigned int value)
{
	DISPREG = 0xff; // Set register to all outs.
	DISPORT = 0xff; // Bring all pins high (LED off in common anode mode)
	if (value >= 0 && value <= 9)
	{
		DISPORT = segvals[value];
	}
	else if(value > 400)
	{ //ERROR LIGHT
		DDRD |= _BV(PD5);
		PORTD |= _BV(PD5);
		delay_ms(20);
		PORTD &= ~_BV(PD5);
	}
}