/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    SMTP_DEMO.C
 *      Purpose: SMTP Client demo example
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <RTL.h>
#include <LPC17xx.h>
#include "GLCD.h"
#include <string.h>

/* Enter your valid SMTP Server IP address here. */
U8 srv_ip[4] = { 192,168,0,253 };

BOOL tick;
BOOL tick2;
BOOL sent;
U32  delay;

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


/*--------------------------- init_display ----------------------------------*/

static void init_display () {
  /* LCD Module init */

  GLCD_Init ();
  GLCD_Clear (White);
  GLCD_SetTextColor (Blue);
  GLCD_DisplayString (2, 4, "   RL-ARM");
  GLCD_DisplayString (3, 4, "SMTP example");
}


/*--------------------------- timer_poll ------------------------------------*/

static void timer_poll () {
  /* System tick timer running in poll mode */

  if (SysTick->CTRL & 0x10000) {
    /* Timer tick every 100 ms */
    timer_tick ();
    tick  = __TRUE;
    tick2 = __TRUE;
  }
}


/*--------------------------- fputc -----------------------------------------*/

int fputc(int ch, FILE *f)  {
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
    LED_out (led_val[cnt]);
    if (++cnt >= sizeof(led_val)) {
      cnt = 0;
    }
  }
}


/*--------------------------- AD_in ----------------------------------------*/

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


/*---------------------------------------------------------------------------*/

static void smtp_cback (U8 code) {
  /* This function is called by TcpNet to inform about SMTP status. */
  switch (code) {
    case SMTP_EVT_SUCCESS:
      printf ("Email successfully sent\n");
      sent = __TRUE;
      break;
    case SMTP_EVT_TIMEOUT:
      /* Timeout, try again. */
      printf ("Mail Server timeout.\n");
      delay = 0;
      break;
    case SMTP_EVT_ERROR:
      /* Error, try again. */
      printf ("Error sending email.\n");
      delay = 0;
      break;
  }
}

/*---------------------------------------------------------------------------*/

int main (void) {
  /* Main Thread of the TcpNet */

  init ();
  init_display ();
  init_TcpNet ();

  delay = 0;
  sent  = __FALSE;
  while (1) {
    timer_poll ();
    main_TcpNet ();
    blink_led ();
    if (tick2 == __FALSE) {
      continue;
    }
    tick2 = __FALSE;
    if (sent == __TRUE) {
      continue;
    }
    if (++delay == 100) {
      /* After 10 seconds send an email. */
      printf ("Sending email...\n");
      smtp_connect ((U8 *)&srv_ip,25,smtp_cback);
    }
  }
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
