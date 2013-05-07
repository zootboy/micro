/* vim: set sw=8 ts=8 si et : */
/*
* Title	:   C include file for analog conversion
* Copyright: GPL V2
* Autor: Guido Socher
* http://tuxgraphics.org/electronics/
*/
#ifndef ANALOG_H
#define ANALOG_H

// return analog value of a given channel.
extern void startConvert(void);
extern uint8_t analog2v(uint16_t aval);
extern void adcOn(void);
extern void adcOff(void);

#endif /* ANALOG_H */
