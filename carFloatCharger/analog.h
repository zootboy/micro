/*
* Title	:   C include file for analog conversion
* Copyright: GPL V2
* Autor: Guido Socher
* http://tuxgraphics.org/electronics/
*/
#ifndef ANALOG_H
#define ANALOG_H

// return analog value of a given channel.
extern void startConvert(uint8_t channel);
extern uint8_t analog2v1(uint16_t aval);
extern uint8_t analog2v2(uint16_t aval);
extern void adcOn(void);
extern void adcOff(void);

#endif /* ANALOG_H */
