/* Single 7 segment display controller */
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DELAY 100

#define SEGA 5 // B
#define SEGB 4 // B
#define SEGC 7 // D
#define SEGD 6 // D
#define SEGE 5 // D
#define SEGF 3 // B
#define SEGG 2 // B
#define DP 4   // D
#define DIGL 2 // D
#define DIGR 3 // D


// Function to enable the interrupt-driven digit separation.
void sevsegDuality(uint8_t on) 
{
	if(on)
	{
		// Enable timer2 to handle the display driving.
		TCCR2 = (0<<CS22)|(1<<CS21)|(1<<CS20); // Div 32.
		TIMSK |= (1<<TOIE2); // Enable overflow interrupt.
		sei(); // Enable global interrupts.
	}
	else
	{
		TCCR2 = 0; // Clock off.
		TIMSK &= ~(1<<TOIE2); // Disable overflow interrupt.
		// No cli just in case we need other interrupts.
	}
}

// Vars for each digit of the display.
//            Format: DP|G|F|E|D|C|B|A
volatile uint8_t segl = 0b00000000; // Left segment
volatile uint8_t segr = 0b10000000; // Right Segment
volatile uint8_t currentSide = 0; // 0 = left, 1 = right.

// Interrupt to drive the display.
ISR(TIMER2_OVF_vect)
{
	uint8_t digit;
	if(currentSide)
	{ // Right -> left
		PORTD &= ~(1<<DIGR); // Right side off.
		digit = segl; // Pull in the left segment.
	}
	else
	{ // Left -> right
		PORTD &= ~(1<<DIGL); // Left side off.
		digit = segr; // Pull in the right segment.
	}
	
	// Turn off all segments.
	PORTB |= 0b00111100;
	PORTD |= 0b11110000;
	if(bit_is_set(digit,0)) PORTB &= ~(1<<SEGA); // a
	if(bit_is_set(digit,1)) PORTB &= ~(1<<SEGB); // b
	if(bit_is_set(digit,2)) PORTD &= ~(1<<SEGC); // c
	if(bit_is_set(digit,3)) PORTD &= ~(1<<SEGD); // d
	if(bit_is_set(digit,4)) PORTD &= ~(1<<SEGE); // e
	if(bit_is_set(digit,5)) PORTB &= ~(1<<SEGF); // f
	if(bit_is_set(digit,6)) PORTB &= ~(1<<SEGG); // g
	if(bit_is_set(digit,7)) PORTD &= ~(1<<DP); // dp
	
	if(currentSide)
	{ // Right -> left
		PORTD |= (1<<DIGL); // Left side on.
		currentSide = 0; // We're left.
	}
	else
	{ // Left -> right
		PORTD |= (1<<DIGR); // Right side on.
		currentSide = 1; // We're right.
	}
}
 
// Convert number to segments. 
void sevsegNumber(uint8_t input)
{
	uint8_t lefty=0;
	uint8_t n = input;
	
	while (n >= 100) {
		n-=100;
	}
	while (n >= 10) {
		n-=10;
		lefty++;
	}
	
	uint8_t righty = input % 10;
	
	if(lefty == 0) segl = 0b00111111;
	if(lefty == 1) segl = 0b00000110;
	if(lefty == 2) segl = 0b01011011;
	if(lefty == 3) segl = 0b01001111;
	if(lefty == 4) segl = 0b01100110;
	if(lefty == 5) segl = 0b01101101;
	if(lefty == 6) segl = 0b01111101;
	if(lefty == 7) segl = 0b00100111;
	if(lefty == 8) segl = 0b01111111;
	if(lefty == 9) segl = 0b01101111;
	
	if(righty == 0) segr = 0b00111111;
	if(righty == 1) segr = 0b00000110;
	if(righty == 2) segr = 0b01011011;
	if(righty == 3) segr = 0b01001111;
	if(righty == 4) segr = 0b01100110;
	if(righty == 5) segr = 0b01101101;
	if(righty == 6) segr = 0b01111101;
	if(righty == 7) segr = 0b00100111;
	if(righty == 8) segr = 0b01111111;
	if(righty == 9) segr = 0b01101111;
	
	if(input > 99) // Display "OL" for out-of-limit
	{
		segl = 0b00111111;
		segr = 0b00111000;
	}
}

void sevsegHex(uint8_t input)
{
	uint8_t lefty=0;
	uint8_t n = input;
	
	while (n >= 16) {
		n-=16;
		lefty++;
	}
	
	uint8_t righty = input % 16;
	
	if(lefty == 0) segl = 0b00111111;
	if(lefty == 1) segl = 0b00000110;
	if(lefty == 2) segl = 0b01011011;
	if(lefty == 3) segl = 0b01001111;
	if(lefty == 4) segl = 0b01100110;
	if(lefty == 5) segl = 0b01101101;
	if(lefty == 6) segl = 0b01111101;
	if(lefty == 7) segl = 0b00100111;
	if(lefty == 8) segl = 0b01111111;
	if(lefty == 9) segl = 0b01101111;
	if(lefty == 10) segl = 0b01110111; // A
	if(lefty == 11) segl = 0b01111100; // b
	if(lefty == 12) segl = 0b00111001; // C
	if(lefty == 13) segl = 0b01011110; // d
	if(lefty == 14) segl = 0b01111001; // E
	if(lefty == 15) segl = 0b01110001; // F
	
	if(righty == 0) segr = 0b00111111;
	if(righty == 1) segr = 0b00000110;
	if(righty == 2) segr = 0b01011011;
	if(righty == 3) segr = 0b01001111;
	if(righty == 4) segr = 0b01100110;
	if(righty == 5) segr = 0b01101101;
	if(righty == 6) segr = 0b01111101;
	if(righty == 7) segr = 0b00100111;
	if(righty == 8) segr = 0b01111111;
	if(righty == 9) segr = 0b01101111;
	if(righty == 10) segr = 0b01110111; // A
	if(righty == 11) segr = 0b01111100; // b
	if(righty == 12) segr = 0b00111001; // C
	if(righty == 13) segr = 0b01011110; // d
	if(righty == 14) segr = 0b01111001; // E
	if(righty == 15) segr = 0b01110001; // F
}

// Run test routines for the 7seg. Good boot-up show.
void sevsegTest(void)
{
	DDRB = 0b00111100; // Enable LED pins
	DDRD = 0b11111100; // as outputs.
	
	
	PORTD = 0b00001100;
	PORTB = 0b00000011;
	_delay_ms(DELAY*6);
	
	// Kill all LEDs (setting the cathodes high).
	PORTB |= 0b11111100;
	PORTD |= 0b11100000;
	
	// First digit.
	PORTD |= (1<<DIGL);
	PORTD &= ~(1<<DIGR);
	
	PORTD &= ~(1<<DP);
	PORTB &= ~(1<<SEGF);
	_delay_ms(DELAY);
	
	PORTB |= (1<<SEGF);
	PORTB &= ~(1<<SEGA);
	_delay_ms(DELAY);
	
	PORTB |= (1<<SEGA);
	PORTB &= ~(1<<SEGB);
	_delay_ms(DELAY);
	
	PORTB |= (1<<SEGB);
	PORTD &= ~(1<<SEGC);
	_delay_ms(DELAY);
	
	PORTD |= (1<<SEGC);
	PORTD &= ~(1<<SEGD);
	_delay_ms(DELAY);
	
	PORTD |= (1<<SEGD);
	PORTD &= ~(1<<SEGE);
	_delay_ms(DELAY);
	
	PORTD |= (1<<SEGE);
	PORTB &= ~(1<<SEGG);
	_delay_ms(DELAY);
	
	// Second digit.
	PORTD &= ~(1<<DIGL);
	PORTD |= (1<<DIGR);
	PORTD &= ~(1<<DP);
	
	_delay_ms(DELAY);
	
	PORTB |= (1<<SEGG);
	PORTB &= ~(1<<SEGF);
	_delay_ms(DELAY);
	
	PORTB |= (1<<SEGF);
	PORTB &= ~(1<<SEGA);
	_delay_ms(DELAY);
	
	PORTB |= (1<<SEGA);
	PORTB &= ~(1<<SEGB);
	_delay_ms(DELAY);
	
	PORTB |= (1<<SEGB);
	PORTD &= ~(1<<SEGC);
	_delay_ms(DELAY);
	
	PORTD |= (1<<SEGC);
	PORTD &= ~(1<<SEGD);
	_delay_ms(DELAY);
	
	PORTD |= (1<<SEGD);
	PORTD &= ~(1<<SEGE);
	_delay_ms(DELAY);
	
	
	PORTD &= ~((1<<DIGR)|(1<<DIGL));	
}

// Show a loading bar of sorts (fill in the circles).
// TODO: Incomplete!
void sevsegLoading(uint8_t level)
{
	sevsegDuality(1); // Enable both displays.
	
	
	if(level >= 1)
	{
		segl = 0b00000001;
		segr = 0b00000000;
	}
	if(level >= 2)  segl = 0b00000011;
	if(level >= 3)  segl = 0b00000111;
	if(level >= 4)  segl = 0b00001111;
	if(level >= 5)  segl = 0b00011111;
	if(level >= 6)  segl = 0b00111111;
	if(level >= 7)  segr = 0b00000001;
	if(level >= 8)  segr = 0b00000011;
	if(level >= 9)  segr = 0b00000111;
	if(level >= 10) segr = 0b00001111;
	if(level >= 11) segr = 0b00011111;
	if(level >= 12) segr = 0b00111111;
	
	
}