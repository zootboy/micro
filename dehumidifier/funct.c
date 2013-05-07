/* Functions */
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include "sevseg.h"

#define RELAYPORT PORTC
#define RELAY1 PC5
#define RELAY2 PC4

void delay_ms(uint16_t ms)
{
    while(ms){
        _delay_ms(1);
        ms--;
    }
}

void testRelays(void) // Turn on both relays in turn for 5 seconds.
{
	segl = 0b10000000;
	segr = 0b00000000;
	delay_ms(5);
	RELAYPORT |= (1<<RELAY1);
	delay_ms(5000);
	RELAYPORT &= ~(1<<RELAY1);
	RELAYPORT |= (1<<RELAY2);
	segl = 0b00000000;
	segr = 0b10000000;
	delay_ms(5000);
	RELAYPORT &= ~(1<<RELAY2);
}

void adcReadout(void) // Give the current ADC reading as a two-stage hex readout.
{
	ADCSRA |= (1<<ADSC); // Start a new conversion.
	
	for(uint8_t i=0;i<=6;i++)
	{
		sevsegLoading(i);
		delay_ms(100);
	}
	
	while(bit_is_set(ADCSRA,ADSC)) 
	{
		for(uint8_t i=0;i<=6;i++)
		{
			sevsegLoading(i);
			delay_ms(100);
		}
	}
	
	// This order is VERY important.
	uint8_t lo = ADCL;
	uint8_t hi = ADCH;
	
	sevsegHex(hi);
	delay_ms(1000);
	sevsegHex(lo);
	delay_ms(1000);
	
}
