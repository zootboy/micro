/* 
 * Navigator - analog.h
 */
#ifndef ANALOG_H
#define	ANALOG_H

// x64 prescale, Vcc ref
#define ADC_MUX (1<<REFS0) // ADMUX
#define ADC_SRA (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1) // ADCSRA
#define IRLEFT  0x00
#define IRRIGHT 0x01
#define SONAR   0x02
#define AVG_COUNT 4 // Number of values to save for the ADC reads. FIX UTIL.H IF MODIFIED!

uint8_t arrayIndex;
uint16_t irLeft[AVG_COUNT];
uint16_t irRight[AVG_COUNT];
uint16_t sonar[AVG_COUNT];

void adcInit(void);
void analogGather(void);

#endif	/* ANALOG_H */

