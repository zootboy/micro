#ifndef UTIL_H
#define UTIL_H

/* util.h - Utilities */

#include <inttypes.h>
#include <stdlib.h>
#define F_CPU 8000000	      // Sets up the default speed for delay.h
#include <util/delay.h>

#define TICKS_PER_CM 50 // TODO: Is this right?

/// Globals ///
uint8_t globalError;
uint8_t i2cMode;
uint8_t gState;
uint32_t stepperCountLeft;
uint32_t stepperCountRight;

uint8_t i2cTxMode;
uint8_t bytesCount;
uint32_t holder;

extern uint16_t arcIR4[4]; 
extern uint16_t arcIR5[4];
extern uint16_t arcIR6[4];
extern uint16_t arcIR7[4];

/// Prototypes ///
void delay_us(uint16_t delah);
void delay_ms(uint16_t delah);
void rxDataHandler(uint8_t data);
void txDataHandler(void);

#endif