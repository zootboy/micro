/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: MCB1700 LED Flasher
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
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "Serial.h"

/* Import external variables from IRQ.c file                                  */
extern unsigned short AD_last;
extern unsigned char  clock_1s;

#define LED_NUM     8                   /* Number of user LEDs                */
const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3,
                                   1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };


/*----------------------------------------------------------------------------
  Function that initializes ADC
 *----------------------------------------------------------------------------*/
void ADC_init (void) {

  LPC_PINCON->PINSEL3 &= ~(3UL<<30);      /* P1.31 is GPIO                      */
  LPC_PINCON->PINSEL3 |=  (3UL<<30);      /* P1.31 is AD0.5                     */

  LPC_SC->PCONP       |=  (1<<12);      /* Enable power to ADC block          */

  LPC_ADC->ADCR        =  (1<< 5) |     /* select AD0.5 pin                   */
                          (4<< 8) |     /* ADC clock is 25MHz/5               */
                          (1<<21);      /* enable ADC                         */ 

  LPC_ADC->ADINTEN     =  (1<< 8);      /* global enable interrupt            */

  NVIC_EnableIRQ(ADC_IRQn);             /* enable ADC Interrupt               */
}


/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
void LED_init(void) {

  LPC_GPIO2->FIODIR |= 0x000000ff;  //P2.0...P2.7 Output LEDs on PORT2 defined as Output

  /* Configure the LCD Control pins                                           */
  LPC_GPIO0->FIODIR   |= 0x03f80000;
  LPC_GPIO0->FIOSET    = 0x03f80000;
}

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On (unsigned int num) {
 
  LPC_GPIO2->FIOPIN |= led_mask[num];
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off (unsigned int num) {

  LPC_GPIO2->FIOPIN &= ~led_mask[num];
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
}


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  short AD_value, AD_print;

  SystemInit();
  SysTick_Config(SystemFrequency/100);  /* Generate interrupt each 10 ms      */

  LED_init();                           /* LED Initialization                 */
  SER_init(0);                          /* UART#0 Initialization              */
  ADC_init();                           /* ADC Initialization                 */

  while (1) {                           /* Loop forever                       */
    AD_value = AD_last;                 /* Read AD_last value                 */
    if (AD_value != AD_last)            /* Make sure that AD interrupt did    */
      AD_value = AD_last;               /* not interfere with value reading   */
    AD_print  = AD_value;               /* Get unscaled value for printout    */

    if (clock_1s) {
      clock_1s = 0;
      printf ("AD value = 0x%03x\n\r", AD_print);
	  LED_Out(AD_print);
    }
  }
}
