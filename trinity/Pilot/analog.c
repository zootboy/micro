/* Pilot - analog.c */
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
		while(!(ADCSRA & (1<<ADIF))) delay_ms(1);
		switch(i)
		{
			case 0: // ArcIR1 toss.
			case 2: // ArcIR2 toss.
			case 4: // ArcIR3 toss.
			case 6: // BattMon toss.
				break;
			case 1: // ArcIR1 keep.
				arcIR1[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | ARCIR2); // Switch to IR2.
				break;
			case 3: // ArcIR2 keep.
				arcIR2[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | ARCIR3); // Switch to IR3.
				break;
			case 5: // ArcIR3 keep.
				arcIR3[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | BATTMON); // Switch to BattMon.
				break;
			case 7:
				battMon[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | ARCIR1); // Switch to IR1
				break;
		}
		
	}
	arrayIndex++;
		if(arrayIndex >= AVG_COUNT) arrayIndex = 0;
	
}