// uart.h                //
// Sean Greenslade, 2012 //
#ifndef _UARTH_
#define _UARTH_

#include "stm32f10x.h"
#include <stdint.h>
#include "circular_buf.h"

// Globals
extern char uartTX[80]; // UART transmit buffer.
extern c_buffer_t uartBuf; // Circular buffer descriptor.

void uart_init(void);
void txStr(char str[]);

#endif
