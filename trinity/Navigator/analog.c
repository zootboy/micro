/* Navigator - analog.c */

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
	DDRC = 0x00;
	sei(); // Enable interrupts globally.
}

void analogGather(void)
{
	for(uint8_t i=0;i<6;i++)
	{
		ADCSRA |= (1<<ADSC); // Start next conversion.
		while(!(ADCSRA & (1<<ADIF))) delay_us(1);
		switch(i)
		{
			case 0: // irLeft toss.
			case 2: // irRight toss.
			case 4: // sonar toss.
				break;
			case 1: // irLeft keep.
				irLeft[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | IRRIGHT); // Switch to irRight.
				break;
			case 3: // irRight keep.
				irRight[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | SONAR); // Switch to sonar.
				break;
			case 5: // ArcIR6 keep.
				sonar[arrayIndex] = ADC;
				ADMUX = ((ADMUX & 0xE0) | IRLEFT); // Switch to irLeft.
				break;
		}
		
	}
	arrayIndex++;
		if(arrayIndex >= AVG_COUNT) arrayIndex = 0;
	
}