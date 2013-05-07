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
extern unsigned int convertanalog(unsigned char channel);
extern unsigned int analog2v(unsigned int aval);

#endif /* ANALOG_H */
