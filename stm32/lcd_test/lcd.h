// LCD headers and defs  //
// Sean Greenslade, 2012 //
#ifndef _LCDH_
#define _LCDH_

#include <stdint.h>
#include "stm32f10x.h"

// Pins and whatnot:
// LCD_CS - PD7
// LCD_WR - PD5
// LCD_RD - PD4
// LCD_RS - PD11

#define LCD_PORT  GPIOD
#define LCD_CS    (1<<7)
#define LCD_WR    (1<<5)
#define LCD_RD    (1<<4)
#define LCD_RS    (1<<11)

void lcdInit(void);
void lcdSetPixel(uint16_t x, uint16_t y, uint16_t pixel);
static void delay(int cnt);


#endif
