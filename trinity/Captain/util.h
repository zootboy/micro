#ifndef UTIL_H
#define UTIL_H

/* util.h - Utilities */

#include <inttypes.h>
#include <stdlib.h>
#define F_CPU 8000000	      // Sets up the default speed for delay.h
#include <util/delay.h>

extern uint8_t stepperCountTempL;
extern uint8_t stepperCountTempR;

/// Prototypes ///
void delay_us(uint16_t delah);
void delay_ms(uint16_t delah);
void stepperSendTicks(int16_t left, int16_t right);

#endif