/************************************************************************//**
 * @file    Exti.c
 * @brief   Demonstrate the use of an external interrupt
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-M3 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#include <stdint.h>
#include "LPC17xx.h"
                  
#define LED_NUM     8                      /* Number of user LEDs             */
const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3,
                                   1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };
int idxCur = -1;                           /* current led position from 0..7  */
int idxOld =  0;                           /* old     led position from 0..7  */
int dir    =  1;                           /* direction for switching the LED */

/**
 * @brief  Function that initializes Button INT0
 */
void BUTTON_init(void) {
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input       */
  LPC_GPIOINT->IO2IntEnF |=  (1 << 10);    /* enable falling edge irq         */

  NVIC_EnableIRQ(EINT3_IRQn);              /* enable irq in nvic              */
}

/**
 * @brief  Function that initializes LEDs
 */
void LED_init(void) {
  LPC_GPIO2->FIODIR = 0x000000FF;          /* LEDs on PORT2 defined as Output */
  
  LPC_GPIO0->FIODIR   |= 0x03f80000;
  LPC_GPIO0->FIOSET    = 0x03f80000;
}

/**
 * @brief  Function that turns on requested LED
 */
void LED_On (unsigned int num) {

  LPC_GPIO2->FIOPIN |= led_mask[num];
}

/**
 * @brief  Function that turns off requested LED
 */
void LED_Off (unsigned int num) {

  LPC_GPIO2->FIOPIN &= ~led_mask[num];
}

/**
 * @brief  Function that initializes Button INT0
 */
void EINT3_IRQHandler()
{
  LPC_GPIOINT->IO2IntClr |= (1 << 10);     /* clear pending interrupt         */

  /* Calculate 'idx': 0,1,...,LED_NUM-1,LED_NUM-1,...,1,0,0,...   */
  idxCur += dir;
  if (idxCur == LED_NUM) { dir = -1; idxCur -=  2; } 
  else if   (idxCur < 0) { dir =  1; idxCur +=  2; }

  LED_Off(idxOld);                         /* switch off    old LED position  */
  LED_On (idxCur);                         /* switch on  current LED position */
  idxOld = idxCur;
}


/**
 * @brief  Main Function
 */
int main (void) {

  SystemInit();                            /* initialize system               */

  LED_init();

  idxCur = 0;                              /* current led position from 0..7  */
  idxOld = 0;                              /* old     led position from 0..7  */
  dir    = 1;                              /* direction for switching the LED */
  LED_On (idxCur);                         /* switch on  first LED            */

  BUTTON_init();

  while (1);
}
