/* 
 * Co-Pilot - analog.h
 */
#ifndef ANALOG_H
#define	ANALOG_H

// x64 prescale, Vcc ref
#define ADC_MUX (1<<REFS0) // ADMUX
#define ADC_SRA (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1) // ADCSRA
#define ARCIR4  0x00
#define ARCIR5  0x01
#define ARCIR6  0x02
#define ARCIR7  0x03
#define AVG_COUNT 4 // Number of values to save for the ADC reads. FIX UTIL.H IF MODIFIED!

uint8_t arrayIndex;
uint16_t arcIR4[AVG_COUNT];
uint16_t arcIR5[AVG_COUNT];
uint16_t arcIR6[AVG_COUNT];
uint16_t arcIR7[AVG_COUNT];

extern uint16_t servoPos1;

void adcInit(void);
void analogGather(void);

#endif	/* ANALOG_H */

