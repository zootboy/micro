#ifndef UTIL_H
#define UTIL_H

/* util.h - Utilities */

#include <inttypes.h>
#include <stdlib.h>
#define F_CPU 8000000	      // Sets up the default speed for delay.h
#include <util/delay.h>


/// Globals ///
uint16_t servoPos1;
uint16_t servoPos2;
uint8_t globalError;
uint8_t i2cMode;
uint8_t gStatus;
uint8_t i2cTxMode;
uint8_t bytesCount;
uint32_t holder;

extern uint16_t arcIR1[4]; 
extern uint16_t arcIR2[4];
extern uint16_t arcIR3[4];
extern uint16_t battMon[4];

/// Prototypes ///
void delay_us(uint16_t delah);
void delay_ms(uint16_t delah);

void setServo(uint8_t servo, uint8_t position);
void co2Burst(void);

void rxDataHandler(uint8_t data);
void txDataHandler(void);

#endif