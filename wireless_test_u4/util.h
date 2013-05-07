#ifndef UTIL_H
#define UTIL_H

/* util.h - Utilities */

#include <inttypes.h>
#include <stdlib.h>
#define F_CPU 16000000	      // Sets up the default speed for delay.h
#include <util/delay.h>

/// Prototypes ///
void delay_us(uint16_t delah);
void delay_ms(uint16_t delah);
#endif