/* 
 * Pilot - analog.h
 */
#ifndef ANALOG_H
#define	ANALOG_H

// x64 prescale, Vcc ref
#define ADC_MUX (1<<REFS0) // ADMUX
#define ADC_SRA (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1) // ADCSRA
#define ARCIR1  0x00
#define ARCIR2  0x01
#define ARCIR3  0x02
#define BATTMON 0x03
#define AVG_COUNT 4 // Number of values to save for the ADC reads. FIX UTIL.H IF MODIFIED!

uint8_t arrayIndex;
uint16_t arcIR1[AVG_COUNT];
uint16_t arcIR2[AVG_COUNT];
uint16_t arcIR3[AVG_COUNT];
uint16_t battMon[AVG_COUNT];

extern uint16_t servoPos1;

void adcInit(void);
void analogGather(void);

#endif	/* ANALOG_H */

