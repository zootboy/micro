/**************************************************************************//**
 * @file     main.c
 * @brief    CMSIS Cortex-M3 GPIO example
 *           a LED using CM3 SysTick
 * @version  V1.30
 * @date     24. Jan 2010
 *
 * @note
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#include "LPC17xx.h"


volatile uint32_t msTicks;                            /* counts 1ms timeTicks */
/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;                        /* increment counter necessary in Delay() */
}

/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
__INLINE static void Delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}

/*------------------------------------------------------------------------------
  configer LED pins
 *------------------------------------------------------------------------------*/
__INLINE static void LED_Config(void) {

  LPC_GPIO2->FIODIR = 0x000000ff;               /* LEDs PORT2 are Output */
  LPC_GPIO0->FIODIR = 0x00200000; 
  LPC_GPIO0->FIOPIN |=  0x00200000; 
}

/*------------------------------------------------------------------------------
  Switch on LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_On (uint32_t led) {

  LPC_GPIO2->FIOPIN |=  (led);                  /* Turn On  LED */
}

/*------------------------------------------------------------------------------
  Switch off LEDs
 *------------------------------------------------------------------------------*/
__INLINE static void LED_Off (uint32_t led) {

  LPC_GPIO2->FIOPIN &= ~(led);                  /* Turn Off LED */
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
  uint8_t  location;
 	
  if (SysTick_Config(SystemCoreClock / 1000)) { /* Setup SysTick Timer for 1 msec interrupts  */
    while (1);                                  /* Capture error */
  }
  
  LED_Config();                             
 
  while(1) 
  {
  	LED_On (0xff);
	Delay (500);
	LED_Off(0xff);
  	for(location=0;location<8;location++)
	{
    	LED_On ((1<<location));                     /* Turn on the LED. */
    	Delay (100);                                /* delay  100 Msec */
    	LED_Off ((1<<location));                    /* Turn off the LED. */
    	Delay (100);                                /* delay  100 Msec */
	}
  }
  
}

