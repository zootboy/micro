/* Co-Pilot - analog.c */

#include <avr/io.h>
//#include <avr/iom328p.h>
#include <avr/interrupt.h>
#include "analog.h"
#include "util.h"

uint8_t arrayIndex = 0; // Which index in the arrays we're on.

void adcInit(void)
{
	ADMUX = ADC_MUX;
	ADCSRA = ADC_SRA; 
	DIDR0 = 0b00001111;
	sei(); // Enable interrupts globally.
}

void analogGather(void)
{
	for(uint8_t i=0;i<8;i++)
	{
		ADCSRA |= (1<<ADSC); // Start next conversion.
		while(!(ADCSRA & (1<<ADIF))) delay_us(1);
		switch(i)
		{
			case 0: // ArcIR4 toss.
			case 2: // ArcIR5 toss.
			case 4: // ArcIR6 toss.
			case 6: // ArcIR7 toss.
				break;
			case 1: // ArcIR4 keep.
				arcIR4[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | ARCIR5); // Switch to IR5.
				break;
			case 3: // ArcIR5 keep.
				arcIR5[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | ARCIR6); // Switch to IR6.
				break;
			case 5: // ArcIR6 keep.
				arcIR6[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | ARCIR7); // Switch to IR7.
				break;
			case 7: // ArcIR7 keep.
				arcIR7[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | ARCIR4); // Switch to IR4
				break;
		}
		
	}
	arrayIndex++;
		if(arrayIndex >= AVG_COUNT) arrayIndex = 0;
	
}