/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    LEDSWITCH.C
 *      Purpose: LED Control Server demo example
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>
#include <stdio.h>
#include <LPC17xx.h>
#include "GLCD.h"
#include <string.h>

U8 socket_tcp;
U8 socket_udp;

#define PORT_NUM 1001
#define BLINKLED 0x01  // Command for blink the leds on board

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

  /* Setup and enable the SysTick timer for 100ms. */
  SysTick->LOAD = (SystemFrequency / 10) - 1;
  SysTick->CTRL = 0x05;
}


/*--------------------------- init_display ----------------------------------*/

static void init_display () {
  /* LCD Module init */

  GLCD_Init ();
  GLCD_Clear (White);
  GLCD_SetTextColor (Blue);
  GLCD_DisplayString (2, 1, "     RL-ARM");
  GLCD_DisplayString (3, 1, "LEDswitch example");
}


/*--------------------------- timer_poll ------------------------------------*/

static void timer_poll () {
  /* System tick timer running in poll mode */

  if (SysTick->CTRL & 0x10000) {
    /* Timer tick every 100 ms */
    timer_tick ();
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


/*--------------------------- Process received data  ------------------------*/

void procrec (U8 *buf) {
  switch (buf[0]) {
    case BLINKLED:
      LED_out (buf[1]);
      break;
  }
}
/*--------------------------- UDP socket ------------------------------------*/

U16 udp_callback (U8 soc, U8 *rip, U16 rport, U8 *buf, U16 len) {
  rip  = rip;
  rport= rport;
  len  = len;

  if (soc != socket_udp) {
    /* Check if this is the socket we are connected to */
    return (0);
  }
  procrec(buf);
  return (0);
}

/*--------------------------- TCP socket ------------------------------------*/

U16 tcp_callback (U8 soc, U8 evt, U8 *ptr, U16 par) {
  /* This function is called by the TCP module on TCP event */
  /* Check the 'Net_Config.h' for possible events.          */
  par = par;

  if (soc != socket_tcp) {
    return (0);
  }

  switch (evt) {
    case TCP_EVT_DATA:
      /* TCP data frame has arrived, data is located at *par1, */
      /* data length is par2. Allocate buffer to send reply.   */
      procrec(ptr);
      break;

    case TCP_EVT_CONREQ:
      /* Remote peer requested connect, accept it */
      return (1);

    case TCP_EVT_CONNECT:
      /* The TCP socket is connected */
      return (1);
  }
  return (0);
}


/*--------------------------- main ------------------------------------------*/

int main (void) {
  /* Main Thread of the TcpNet */

  init ();
  init_display ();
  init_TcpNet ();

  /* Initialize UDP Socket and start listening */
  socket_udp = udp_get_socket (0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_callback);
  if (socket_udp != 0) {
    udp_open (socket_udp, PORT_NUM);
  }

  /* Initialize TCP Socket and start listening */
  socket_tcp = tcp_get_socket (TCP_TYPE_SERVER, 0, 10, tcp_callback);
  if (socket_tcp != 0) {
    tcp_listen (socket_tcp, PORT_NUM);
  }

  while (1) {
    timer_poll ();
    main_TcpNet ();
  }
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
