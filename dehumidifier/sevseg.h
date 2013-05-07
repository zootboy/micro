/* Single 7 segment display controller */
#ifndef SEVSEG_H
#define SEVSEG_H

// functions to operate the display; all the code for it is separated.
extern void sevsegTest(void);
extern void sevsegLoading(uint8_t level);
extern void sevsegDuality(uint8_t on);
extern void sevsegNumber(uint8_t input);
extern void sevsegHex(uint8_t input);

// Direct control vars.
extern volatile uint8_t segl;
extern volatile uint8_t segr;

#endif /* SEVSEG_H */