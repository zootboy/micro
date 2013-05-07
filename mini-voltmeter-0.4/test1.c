/*
* vim: set sw=8 ts=8 si :
* Author: Guido Socher, Copyright: GPL 2
* Chip type           : ATMEGA8
* Clock frequency     : Internal clock 8 Mhz 
*/
#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 8000000UL  // 8 MHz
#include <util/delay.h>

//Connections of the seven segment elements: 
//     10 9 7 6 4 2 1 = pin
//   0| -  f a b c d e | 0111111 | 3f
//   1| -  - - b c - - | 0001100 | 0c
//   2| g  - a b - d e | 1011011 | 5b
//   3| g  - a b c d - | 1011110 | 5e
//   4| g  f - b c - - | 1101100 | 6c
//   5| g  f a - c d - | 1110110 | 76
//   6| g  f a - c d e | 1110111 | 77
//   7| -  - a b c - - | 0011100 | 1c
//   8| g  f a b c d e | 1111111 | 7f
//   9| g  f a b c d - | 1111110 | 7e
// digit to seven segment LED mapping:
static unsigned char d2led[]={0x3f,0x0c,0x5b,0x5e,0x6c,0x76,0x77,0x1c,0x7f,0x7e};

void delay_ms(unsigned int ms)
{
        // if we would use the library function _delay_ms
        // everywhere then the code would become very fat
        // We just need integers therefore we wrap it.
	while(ms){
		_delay_ms(0.96);
		ms--;
	}
}

void init7segment(void)
{
	// least significant digit, cathode transistor:
        DDRD|= (1<<DDD7);
	// middle digit:
        DDRB|= (1<<DDB6);
	// left digit:
        DDRB|= (1<<DDB7);
	// digit pins:
        DDRD|= 0x7F;
	// off
	PORTD=0;
}
// Update the sevent segement display.
// You must loop over this function all the time.
inline void upd7segment(unsigned int number)
{
	// LS digit:
	PORTD=d2led[(number%10)];
	//
	PORTD|=(1<<PD7);// digit on for a short time:
	delay_ms(4);
	number/=10; // divide by 10 (shift off right most digit)
	PORTD&=~(1<<PD7);
	// middle digit:
	PORTD=d2led[(number%10)];
	//
	PORTB|= (1<<PB6);// digit on for a short time:
	delay_ms(4);
	number/=10; // divide by 10 (shift off right most digit)
	PORTB &= ~(1<<PB6);
	if (number>0){ // chop off left most digit if it is zero
		//
		// left digit, we assume there that the number is
		// smaller than 999, no modulo here:
		PORTD=d2led[number];
		//
		PORTB|= (1<<PB7);// digit on for a short time:
		delay_ms(4);
		PORTB &= ~(1<<PB7);
	}
}

int main(void)
{
	unsigned char lc=0;
	unsigned char i=0; // i will wrap at 8 bit (255)
	init7segment();

        while (1) {
		lc++;
		lc=lc%15;
                delay_ms(1);
		// 
		if (lc==0){
			i++;
		}
		upd7segment(i);
		//upd7segment(142);
        }
	return(0);
}


