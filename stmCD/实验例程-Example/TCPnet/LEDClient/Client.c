/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    CLIENT.C
 *      Purpose: LED Control Client demo example
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>
#include <stdio.h>
#include <LPC17xx.h>
#include "GLCD.h"
#include <string.h>

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

//   <h>Remote IP Address
//   ====================
//
//     <o>IP1: Address byte 1 <0-255>
//     <i> Default: 192
#define IP1            192

//     <o>IP2: Address byte 2 <0-255>
//     <i> Default: 168
#define IP2            168

//     <o>IP3: Address byte 3 <0-255>
//     <i> Default: 0
#define IP3            0

//     <o>IP4: Address byte 4 <0-255>
//     <i> Default: 100
#define IP4            100

//   </h>

//   <o>Remote Port <1-65535>
//   <i> Do not set number of port too small,
//   <i> maybe it is already used.
//   <i> Default: 1001
#define PORT_NUM       1001

//   <o>Communication Protocol <0=> TCP <1=> UDP
//   <i> Selecet a protocol for sending data.
#define PROTOCOL       1

//   <o>LED Blinking speed <1-100>
//   <i> Blinking speed = SPEED * 100ms
//   <i> Default: 2
#define SPEED          2


//------------- <<< end of configuration section >>> -----------------------


#define BLINKLED 0x01  /* Command for blink the leds on board */
#define SENDLEN  2     /* Number of bytes to send */
#define TCP      0
#define UDP      1

BOOL tick;
U8 socket_tcp;
U8 socket_udp;
U8 Rem_IP[4] = {IP1,IP2,IP3,IP4};


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
  GLCD_DisplayString (2, 3, "    RL-ARM");
  GLCD_DisplayString (3, 3, "Client example");
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


/*--------------------------- UDP socket ------------------------------------*/

U16 udp_callback (U8 soc, U8 *rip, U16 rport, U8 *buf, U16 len) {
  /* This function is called by the UDP module when UDP packet is received. */

  /* Make a reference to suppress compiler warnings. */
  buf  = buf;
  rip  = rip;
  rport= rport;
  len  = len;
  soc  = soc;
  return (0);
}


/*--------------------------- TCP socket ------------------------------------*/

U16 tcp_callback (U8 soc, U8 evt, U8 *ptr, U16 par) {
  /* This function is called by the TCP module on TCP event */
  /* Check the Net_Config.h for possible events.            */

  /* Make a reference to suppress compiler warnings. */
  soc = soc;
  par = par;
  evt = evt;
  ptr = ptr;
  return (0);
}


/*--------------------------- TCP send --------------------------------------*/

void send_data (U8 p2val) {
  U8 *sendbuf;
  U8 p2;

  /* UDP */
  if (socket_udp != 0) {
    /* Start Connection */
    sendbuf = udp_get_buf (SENDLEN);
    sendbuf[0] = BLINKLED;
    sendbuf[1] = p2val;
    udp_send (socket_udp, Rem_IP, 1001, sendbuf, SENDLEN);
  }

  /* TCP */
  if (socket_tcp != 0) {
    /* Start Connection */
    p2 = p2val;
    switch (tcp_get_state(socket_tcp)) {
      case TCP_STATE_FREE:
      case TCP_STATE_CLOSED:
        tcp_connect (socket_tcp, Rem_IP, PORT_NUM, 0);
        break;
      case TCP_STATE_CONNECT:
        if (tcp_check_send (socket_tcp) == __TRUE) {
          sendbuf = tcp_get_buf(SENDLEN);
          sendbuf[0] = BLINKLED;
          sendbuf[1] = p2;
          tcp_send (socket_tcp, sendbuf, SENDLEN);
        }
        break;
    }
  }
}


/*--------------------------- main ------------------------------------------*/

int main (void) {
  /* Main Thread of the TcpNet */
  U8 p2val, cnt, lshf;
  U8 protocol;

  init ();
  init_display ();
  init_TcpNet ();

  protocol = PROTOCOL;
  switch (protocol) {
    case TCP:
      socket_tcp = tcp_get_socket (TCP_TYPE_CLIENT, 0, 10, tcp_callback);
      break;
    case UDP:
      socket_udp = udp_get_socket (0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_callback);
      if (socket_udp != 0) {
        udp_open (socket_udp, PORT_NUM);
      }
      break;
  }

  p2val = 1;
  cnt   = 0;
  lshf  = 1;  /* left shift */
  while (1) {
    timer_poll ();
    main_TcpNet ();
    if (tick == __TRUE) {
      if (++cnt == SPEED) {
        LED_out (p2val);
        send_data(p2val);
        p2val = lshf ? (p2val << 1) : (p2val >> 1);
        if (p2val == 0x80) lshf = 0;
        if (p2val == 0x01) lshf = 1;
        cnt = 0;
      }
      tick = __FALSE;
    }
  }
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
