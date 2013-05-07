/*----------------------------------------------------------------------------
 * Name:    memory.c
 * Purpose: USB Memory Storage Demo
 * Version: V1.20
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

#include <LPC17xx.H>                        /* LPC17xx definitions */

#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "mscuser.h"

#include "memory.h"


unsigned int LED_State = 0;                 /* reflect the LEDs */

extern U8 Memory[MSC_MemorySize];           /* MSC Memory in RAM */


/*------------------------------------------------------------------------------
  Set value to LEDs
 *------------------------------------------------------------------------------*/
void LED_Set (unsigned int value) {
  static unsigned long led_mask[] = { 1<<28, 1<<29, 1UL<<31, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6 };
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      if (i < 3) LPC_GPIO1->FIOPIN |= led_mask[i];
      else       LPC_GPIO2->FIOPIN |= led_mask[i];
    } else {
      if (i < 3) LPC_GPIO1->FIOPIN &= ~led_mask[i];
      else       LPC_GPIO2->FIOPIN &= ~led_mask[i];
    }
  }
}


/*------------------------------------------------------------------------------
  Switch on LEDs
 *------------------------------------------------------------------------------*/
void LED_On (unsigned int value) {

  LED_State |= value;
  LED_Set(LED_State);
}


/*------------------------------------------------------------------------------
  Switch off LEDs
 *------------------------------------------------------------------------------*/
void LED_Off (unsigned int value) {

  LED_State &= ~value;
  LED_Set(LED_State);
}


/*------------------------------------------------------------------------------
  Main Program
 *------------------------------------------------------------------------------*/
int main (void) {
  U32 n;

  for (n = 0; n < MSC_ImageSize; n++) {       /* Copy Initial Disk Image */
    Memory[n] = DiskImage[n];                 /*   from Flash to RAM     */
  }

  LPC_GPIO1->FIODIR   |= ((1UL<<28)|(1UL<<29)|
                          (1UL<<31)           );  /* P1.28, P1.29, P1.31 is output (LED) */
  LPC_GPIO2->FIODIR   |= ((1UL<< 2)|(1UL<< 3)|
                          (1UL<< 4)|(1UL<< 5)|
                          (1UL<< 6)           ) ; /* P2.2..6             is output (LED) */

  LPC_GPIO4->FIODIR   |=  (1UL<< 28);         /* Pin P2.28           is output (GLCD BAcklight)*/
  LPC_GPIO4->FIOPIN   &= ~(1UL<< 28);         /* Turn backlight off */

  SystemInit();                               /* initialize clocks */

  USB_Init();                                 /* USB Initialization */
  USB_Connect(__TRUE);                        /* USB Connect */

  while (1);                                  /* Loop forever */
}
