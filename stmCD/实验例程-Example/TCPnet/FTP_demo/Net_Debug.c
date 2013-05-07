/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    NET_DEBUG.C
 *      Purpose: Debug Module
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include <stdarg.h>
#include <stdio.h>

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

// <h>TCPnet Debug Definitions
// ===========================

//   <o>Memory Management Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Dynamic Memory debug messages
#define DBG_MEM        1

//   <o>Ethernet Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Ethernet debug messages
#define DBG_ETH        1

//   <o>PPP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off PPP debug messages
#define DBG_PPP        0

//   <o>SLIP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off SLIP debug messages
#define DBG_SLIP       0

//   <o>ARP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off ARP debug messages
#define DBG_ARP        1

//   <o>IP Debug    <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off IP debug messages
#define DBG_IP         1

//   <o>ICMP Debug  <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off ICMP debug messages
#define DBG_ICMP       1

//   <o>IGMP Debug  <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off IGMP debug messages
#define DBG_IGMP       1

//   <o>UDP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off UDP debug messages
#define DBG_UDP        1

//   <o>TCP Debug   <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off TCP debug messages
#define DBG_TCP        1

//   <o>NBNS Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off NetBIOS Name Service debug messages
#define DBG_NBNS       1

//   <o>DHCP Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Dynamic Host Configuration debug messages
#define DBG_DHCP       1

//   <o>DNS Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Domain Name Service debug messages
#define DBG_DNS        1

//   <o>Application Debug <0=> Off <1=> Errors only <2=> Full debug
//   <i> Turn On/Off Application debug messages
//   <I> for: HTTP, TFTP, SMTP, Telnet
#define DBG_APP        1

// </h>

//------------- <<< end of configuration section >>> -----------------------


/*--------------------------- init_debug ------------------------------------*/

void init_debug (void) {
  /* Add your code to initialize the Debug output. This is usually the  */
  /* serial interface. The function is called at TCPnet system startup. */
  /* You may need to customize also the 'putchar()' function.           */

}


/*----------------------------------------------------------------------------
 *      TCPnet Debug Functions
 *---------------------------------------------------------------------------*/

#define  __NET_DEBUG__

#include <Net_lib.c>

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
