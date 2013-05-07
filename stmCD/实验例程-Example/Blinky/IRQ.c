/*----------------------------------------------------------------------------
 * Name:    IRQ.c
 * Purpose: MCB1700 IRQ Handler
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "LPC17xx.H"                    /* LPC17xx definitions                */


unsigned short AD_last;                 /* Last converted value               */
unsigned char  clock_1s;                /* Flag activated each second         */

/* Import function for turning LEDs on or off                                 */
extern void LED_Out (unsigned int num);


/*----------------------------------------------------------------------------
  SysTick IRQ: Executed periodically
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void) {           /* SysTick Interrupt Handler (10ms)   */
  static unsigned long ticks;
  static unsigned long timetick;
  static unsigned char leds = 0x01;

  if (ticks++ >= 99) {                  /* Set Clock1s to 1 every 1 second    */
    ticks    = 0;
    clock_1s = 1;
  }

  /* Blink the LEDs depending on ADC_ConvertedValue                           */
  if (timetick++ >= (AD_last >> 8)) {
    timetick   = 0;
    leds     <<= 1;
    if (leds == 0) leds = 0x01;
    LED_Out (leds);
  }

  LPC_ADC->ADCR |=  (1<<24);            /* Start A/D Conversion               */
}

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is done
 *----------------------------------------------------------------------------*/
void ADC_IRQHandler(void) {

  AD_last = (LPC_ADC->ADGDR>>4) & 0xFFF;/* Read Conversion Result             */

}
