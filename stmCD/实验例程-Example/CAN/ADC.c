/*----------------------------------------------------------------------------
 * Name:    ADC.c
 * Purpose: MCB1700 low level ADC functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC17xx.H>                             /* LPC17xx definitions */
#include "ADC.h"

/*----------------------------------------------------------------------------
  initialize ADC Pins
 *----------------------------------------------------------------------------*/
void ADC_init (void) {

  LPC_PINCON->PINSEL3 &= ~(3UL<<30);               /* P1.31 is GPIO */
  LPC_PINCON->PINSEL3 |=  (3UL<<30);               /* P1.31 is AD0.5 */

  LPC_SC->PCONP       |=  (1<<12);               /* Enable power to ADC block */

  LPC_ADC->ADCR        =  (1<< 5) |              /* select AD0.5 pin */
                          (4<< 8) |              /* ADC clock is 25MHz/5 */
                          (1<<21);               /* enable ADC */ 
}


/*----------------------------------------------------------------------------
  start ADC Conversion
 *----------------------------------------------------------------------------*/
void ADC_startCnv (void) {
  LPC_ADC->ADCR &= ~(7<<24);                     /* stop conversion  */
  LPC_ADC->ADCR |=  (1<<24);                     /* start conversion */
}


/*----------------------------------------------------------------------------
  stop ADC Conversion
 *----------------------------------------------------------------------------*/
void ADC_stopCnv (void) {
  LPC_ADC->ADCR &= ~(7<<24);                     /* stop conversion */
}


/*----------------------------------------------------------------------------
  get converted ADC value
 *----------------------------------------------------------------------------*/
uint32_t ADC_getCnv (void) {
  uint32_t adGdr;
//  uint32_t adDr2;

  while (!(LPC_ADC->ADGDR & (1UL<<31)));         /* Wait for Conversion end */
  adGdr = LPC_ADC->ADGDR;
//  adDr2 = LPC_ADC->ADDR2;
  return((adGdr >> 4) & ADC_VALUE_MAX);          /* read converted value */
}
