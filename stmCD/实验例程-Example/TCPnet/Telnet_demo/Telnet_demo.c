/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    TELNET_DEMO.C
 *      Purpose: Telnet Server demo example
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <RTL.h>
#include <LPC17xx.H>                    /* LPC17xx definitions               */
#include "GLCD.h"

BOOL tick;
BOOL LEDrun;
BOOL LCDupdate;
U8   lcd_text[2][16+1] = {"Line 1",           /* Buffer for LCD text         */
                          "Line 2"};


/*--------------------------- init ------------------------------------------*/

static void init () {
  /* Add System initialisation code here */

  /* Set the clocks. */
  SystemInit();

  /* Configure the GPIO for LEDs. */
  LPC_GPIO1->FIODIR   |= 0xB0000000;
  LPC_GPIO2->FIODIR   |= 0x0000007C;

  /* Configure UART1 for 115200 baud. */
  LPC_PINCON->PINSEL4 &= 0xFFFFFFF0;
  LPC_PINCON->PINSEL4 |= 0x0000000A;
  LPC_UART1->LCR = 0x83;
  LPC_UART1->DLL = 9;                             /* 115200 Baud Rate @ 25.0 MHZ PCLK */
  LPC_UART1->FDR = 0x21;                          /* FR 1,507, DIVADDVAL = 1, MULVAL = 2 */
  LPC_UART1->DLM = 0;
  LPC_UART1->LCR = 0x03;

  /* Configure AD0.2 input. */
  LPC_PINCON->PINSEL1 &= 0xFFF3FFFF;
  LPC_PINCON->PINSEL1 |= 0x00040000;
  LPC_SC->PCONP       |= 0x00001000;
  LPC_ADC->ADCR        = 0x00200404;              /* ADC enable, ADC clock 25MHz/5, select AD0.2 pin */


  /* Setup and enable the SysTick timer for 100ms. */
  SysTick->LOAD = (SystemFrequency / 10) - 1;
  SysTick->CTRL = 0x05;

  LEDrun = __TRUE;
}


/*--------------------------- LED_out ---------------------------------------*/

void LED_out (U32 val) {
  const U8 led_pos[8] = { 28, 29, 31, 2, 3, 4, 5, 6 };
  U32 i,mask;

  for (i = 0; i < 8; i++) {
    mask = 1 << led_pos[i];
    if (val & (1<<i)) {
      if (i < 3) LPC_GPIO1->FIOSET = mask;
      else       LPC_GPIO2->FIOSET = mask;
    }
    else {
      if (i < 3) LPC_GPIO1->FIOCLR = mask;
      else       LPC_GPIO2->FIOCLR = mask;
    }
  }
}


/*--------------------------- upd_display -----------------------------------*/

static void upd_display () {
  /* Update LCD Module display text. */

  GLCD_ClearLn (5);
  GLCD_DisplayString (5, 0, lcd_text[0]);
  GLCD_ClearLn (6);
  GLCD_DisplayString (6, 0, lcd_text[1]);

  LCDupdate =__FALSE;
}


/*--------------------------- init_display ----------------------------------*/

static void init_display () {
  /* LCD Module.2x16 init*/

  GLCD_Init ();
  GLCD_Clear (White);
  GLCD_SetTextColor (Blue);
  GLCD_DisplayString (2, 3, "    RL-ARM");
  GLCD_DisplayString (3, 3, "Telnet example");

  upd_display ();
}


/*--------------------------- AD_in -----------------------------------------*/

U16 AD_in (U32 ch) {
  /* Read ARM Analog Input */
  U32 val = 0;
  U32 adcr;

  if (ch < 8) {
    adcr = 0x01000000 | (1 << ch);
    LPC_ADC->ADCR = adcr | 0x00200100;        /* Setup A/D: 10-bit @ 9MHz  */

    do {
      val = LPC_ADC->ADGDR;                   /* Read A/D Data Register    */
    } while ((val & 0x80000000) == 0);        /* Wait for end of A/D Conv. */
    LPC_ADC->ADCR &= ~adcr;                   /* Stop A/D Conversion       */
    val = (val >> 6) & 0x03FF;                /* Extract AINx Value        */
  }
  return (val);
}


/*--------------------------- timer_poll ------------------------------------*/

static void timer_poll () {
  /* System tick timer running in poll mode */

  if (SysTick->CTRL & 0x10000) {
    /* Timer tick every 100 ms */
    timer_tick ();
    tick = __TRUE;
  }
}


/*--------------------------- fputc -----------------------------------------*/

int fputc (int ch, FILE *f)  {
  /* Debug output to serial port. */

  if (ch == '\n')  {
    while (!(LPC_UART1->LSR & 0x20));
    LPC_UART1->THR = 0x0D;
  }
  while (!(LPC_UART1->LSR & 0x20));
  LPC_UART1->THR = (ch & 0xFF);
  return (ch);
}


/*--------------------------- blink_led -------------------------------------*/

static void blink_led () {
  /* Blink the LEDs on an eval board */
  const U8 led_val[16] = { 0x48,0x88,0x84,0x44,0x42,0x22,0x21,0x11,
                           0x12,0x0A,0x0C,0x14,0x18,0x28,0x30,0x50 };
  static U32 cnt;

  if (tick == __TRUE) {
    /* Every 100 ms */
    tick = __FALSE;
    if (LEDrun == __TRUE) {
      LED_out (led_val[cnt]);
      if (++cnt >= sizeof(led_val)) {
        cnt = 0;
      }
    }
    if (LCDupdate == __TRUE) {
      upd_display ();
    }
  }
}


/*---------------------------------------------------------------------------*/

int main (void) {
  /* Main Thread of the TcpNet */

  init ();
  init_display ();
  init_TcpNet ();

  while (1) {
    timer_poll ();
    main_TcpNet ();
    blink_led ();
  }
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
