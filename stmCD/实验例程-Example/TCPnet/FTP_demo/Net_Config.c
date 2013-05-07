/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    NET_CONFIG.C
 *      Purpose: Configuration of RL TCPnet by user.
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
//
// <h>System Definitions
// =====================
// <i> Global TCPnet System definitions
//   <s.15>Local Host Name
//   <i> This is the name under which embedded host can be
//   <i> accessed on a local area network.
//   <i> Default: "mcb2100"
#define LHOST_NAME     "mcb1700"

//   <o>Memory Pool size <1500-32000:4><#/4>
//   <i> This is the size of a memory pool in bytes. Buffers for
//   <i> TCPnet packets are allocated from this memory pool.
//   <i> Default: 8000 bytes
#define MEM_SIZE       2048

//   <o>Tick Timer interval <10=> 10 ms <20=> 20 ms <25=> 25 ms
//                          <40=> 40 ms <50=> 50 ms <100=> 100 ms 
//                          <200=> 200 ms
//   <i> System Tick Timer interval for software timers
//   <i> Default: 100 ms
#define TICK_INTERVAL  100

// </h>
// <e>Ethernet Network Interface
// =============================
// <i> Enable or disable Ethernet Network Interface
#define ETH_ENABLE     1

//   <h>MAC Address
//   ==============
//   <i> Local Ethernet MAC Address
//   <i> Value FF:FF:FF:FF:FF:FF is not allowed.
//   <i> It is an ethernet Broadcast MAC address.
//     <o>Address byte 1 <0x00-0xff:2>
//     <i> LSB is an ethernet Multicast bit.
//     <i> Must be 0 for local MAC address.
//     <i> Default: 0x00
#define _MAC1          0x1E

//     <o>Address byte 2 <0x00-0xff>
//     <i> Default: 0x30
#define _MAC2          0x30

//     <o>Address byte 3 <0x00-0xff>
//     <i> Default: 0x6C
#define _MAC3          0x6C

//     <o>Address byte 4 <0x00-0xff>
//     <i> Default: 0x00
#define _MAC4          0xA2

//     <o>Address byte 5 <0x00-0xff>
//     <i> Default: 0x00
#define _MAC5          0x45

//     <o>Address byte 6 <0x00-0xff>
//     <i> Default: 0x01
#define _MAC6          0x5E

//   </h>
//   <h>IP Address
//   =============
//   <i> Local Static IP Address
//   <i> Value 255.255.255.255 is not allowed.
//   <i> It is a Broadcast IP address.
//     <o>Address byte 1 <0-255>
//     <i> Default: 192
#define _IP1           192

//     <o>Address byte 2 <0-255>
//     <i> Default: 168
#define _IP2           168

//     <o>Address byte 3 <0-255>
//     <i> Default: 0
#define _IP3           0

//     <o>Address byte 4 <0-255>
//     <i> Default: 100
#define _IP4           100

//   </h>
//   <h>Subnet mask
//   ==============
//   <i> Local Subnet mask
//     <o>Mask byte 1 <0-255>
//     <i> Default: 255
#define _MSK1          255

//     <o>Mask byte 2 <0-255>
//     <i> Default: 255
#define _MSK2          255

//     <o>Mask byte 3 <0-255>
//     <i> Default: 255
#define _MSK3          255

//     <o>Mask byte 4 <0-255>
//     <i> Default: 0
#define _MSK4          0

//   </h>
//   <h>Default Gateway
//   ==================
//   <i> Default Gateway IP Address
//     <o>Address byte 1 <0-255>
//     <i> Default: 192
#define _GW1           192

//     <o>Address byte 2 <0-255>
//     <i> Default: 168
#define _GW2           168

//     <o>Address byte 3 <0-255>
//     <i> Default: 0
#define _GW3           0

//     <o>Address byte 4 <0-255>
//     <i> Default: 254
#define _GW4           254

//   </h>
//   <h>Primary DNS Server
//   =====================
//   <i> Primary DNS Server IP Address
//     <o>Address byte 1 <0-255>
//     <i> Default: 194
#define _pDNS1         194

//     <o>Address byte 2 <0-255>
//     <i> Default: 25
#define _pDNS2         25

//     <o>Address byte 3 <0-255>
//     <i> Default: 2
#define _pDNS3         2

//     <o>Address byte 4 <0-255>
//     <i> Default: 129
#define _pDNS4         129

//   </h>
//   <h>Secondary DNS Server
//   =======================
//   <i> Secondary DNS Server IP Address
//     <o>Address byte 1 <0-255>
//     <i> Default: 194
#define _sDNS1         194

//     <o>Address byte 2 <0-255>
//     <i> Default: 25
#define _sDNS2         25

//     <o>Address byte 3 <0-255>
//     <i> Default: 2
#define _sDNS3         2

//     <o>Address byte 4 <0-255>
//     <i> Default: 130
#define _sDNS4         130

//   </h>
//   <h>ARP Definitions
//   ==================
//   <i> Address Resolution Protocol Definitions
//     <o>Cache Table size <5-100>
//     <i> Number of cached hardware/IP addresses
//     <i> Default: 10
#define ARP_TABSIZE    10

//     <o>Cache Timeout in seconds <5-255>
//     <i> A timeout for a cached hardware/IP addresses
//     <i> Default: 150
#define ARP_TIMEOUT    150

//     <o>Number of Retries <0-20>
//     <i> Number of Retries to resolve an IP address
//     <i> before ARP module gives up
//     <i> Default: 4
#define ARP_MAXRETRY   4

//     <o>Resend Timeout in seconds <1-10>
//     <i> A timeout to resend the ARP Request
//     <i> Default: 2
#define ARP_RESEND     2

//   </h>
//   <e>IGMP Group Management
//   ========================
//   <i> Enable or disable Internet Group Management Protocol
#define IGMP_ENABLE    0

//     <o>Membership Table size <2-50>
//     <i> Number of Groups this host can join
//     <i> Default: 5
#define IGMP_TABSIZE   5

//   </e>
//   <q>NetBIOS Name Service
//   =======================
//   <i> When this option is enabled, the embedded host can be
//   <i> accessed by his name on the local LAN using NBNS protocol.
//   <i> You need to modify also the number of UDP Sockets,
//   <i> because NBNS protocol uses one UDP socket to run.
#define NBNS_ENABLE    1

//   <q>Dynamic Host Configuration
//   =============================
//   <i> When this option is enabled, local IP address, Net Mask
//   <i> and Default Gateway are obtained automatically from
//   <i> the DHCP Server on local LAN.
//   <i> You need to modify also the number of UDP Sockets,
//   <i> because DHCP protocol uses one UDP socket to run.
#define DHCP_ENABLE    1

// </e>

// <e>PPP Network Interface
// ========================
// <i> Enable or disable PPP Network Interface
#define PPP_ENABLE     0

//   <h>IP Address
//   =============
//   <i> Local Static IP Address
//     <o>Address byte 1 <0-255>
//     <i> Default: 192
#define _IP1P          192

//     <o>Address byte 2 <0-255>
//     <i> Default: 168
#define _IP2P          168

//     <o>Address byte 3 <0-255>
//     <i> Default: 125
#define _IP3P          125

//     <o>Address byte 4 <0-255>
//     <i> Default: 1
#define _IP4P          1

//   </h>
//   <h>Subnet mask
//   ==============
//   <i> Local Subnet mask
//     <o>Mask byte 1 <0-255>
//     <i> Default: 255
#define _MSK1P         255

//     <o>Mask byte 2 <0-255>
//     <i> Default: 255
#define _MSK2P         255

//     <o>Mask byte 3 <0-255>
//     <i> Default: 255
#define _MSK3P         255

//     <o>Mask byte 4 <0-255>
//     <i> Default: 0
#define _MSK4P         0

//   </h>
//   <h>Primary DNS Server
//   =====================
//   <i> Primary DNS Server IP Address
//     <o>Address byte 1 <0-255>
//     <i> Default: 194
#define _pDNS1P        194

//     <o>Address byte 2 <0-255>
//     <i> Default: 25
#define _pDNS2P        25

//     <o>Address byte 3 <0-255>
//     <i> Default: 2
#define _pDNS3P        2

//     <o>Address byte 4 <0-255>
//     <i> Default: 129
#define _pDNS4P        129

//   </h>
//   <h>Secondary DNS Server
//   =======================
//   <i> Secondary DNS Server IP Address
//     <o>Address byte 1 <0-255>
//     <i> Default: 194
#define _sDNS1P        194

//     <o>Address byte 2 <0-255>
//     <i> Default: 25
#define _sDNS2P        25

//     <o>Address byte 3 <0-255>
//     <i> Default: 2
#define _sDNS3P        2

//     <o>Address byte 4 <0-255>
//     <i> Default: 130
#define _sDNS4P        130

//   </h>
//   <q>Obtain Client IP address automatically
//   =========================================
//   <i> This option only applies when PPP Dial-up is used to dial
//   <i> to remote PPP Server. If checked, network connection
//   <i> dynamically obtains an IP address from remote PPP Server.
#define PPP_GETIP      1

//   <q>Use Default Gateway on remote Network
//   ========================================
//   <i> This option only applies when both Ethernet and PPP Dial-up
//   <i> are used. If checked, data that cannot be sent to local LAN
//   <i> is forwarded to Dial-up network instead.
#define PPP_DEFGW      1

//   <h>Async Control Character Map
//   ==============================
//   <i> A map of control characters 0..31 which are transmitted 
//   <i> escaped as a 2 byte sequence.
//     <o>Map char 31..24 mask <0x00-0xff>
//     <i> Maps control characters from 31...24
//     <i> Default: 0x00
#define _ACCM1         0x00

//     <o>Map char 23..16 mask <0x00-0xff>
//     <i> Maps control characters from 23...16
//     <i> For XON/XOFF set this value to: 0x0A
//     <i> Default: 0x00
#define _ACCM2         0x0A

//     <o>Map char 15..8 mask <0x00-0xff>
//     <i> Maps control characters from 15...8
//     <i> Default: 0x00
#define _ACCM3         0x00

//     <o>Map char 7..0 mask <0x00-0xff>
//     <i> Maps control characters from 7...0
//     <i> Default: 0x00
#define _ACCM4         0x00

//   </h>
//   <h>Retransmissions and Timeouts
//   ===============================
//   <i> Several protocol settings.
//     <o>LCP Number of Retries <0-20>
//     <i> How many times Link Control Protocol will try to retransmit
//     <i> data before giving up. Increase this value for links with
//     <i> low baud rates or high latency.
//     <i> Default: 2
#define LCP_MAXRETRY   2

//     <o>LCP Retry Timeout in seconds <1-10>
//     <i> If no response received within this time frame,
//     <i> LCP module will try to resend data again.
//     <i> Default: 2
#define LCP_RETRYTOUT  2

//     <o>PAP Number of Retries <0-20>
//     <i> How many times Password Authentication Protocol will try to 
//     <i> retransmit data before giving up. Increase this value for links
//     <i> with low baud rates or high latency.
//     <i> Default: 3
#define PAP_MAXRETRY   3

//     <o>PAP Retry Timeout in seconds <1-10>
//     <i> If no response received within this time frame,
//     <i> PAP module will try to resend data again
//     <i> Default: 3
#define PAP_RETRYTOUT  3

//     <o>IPCP Number of Retries <0-20>
//     <i> How many times Internet Protocol Control Protocol will try
//     <i> to retransmit data before giving up. Increase this value for
//     <i> links with low baud rates or high latency.
//     <i> Default: 3
#define IPCP_MAXRETRY  3

//     <o>IPCP Retry Timeout in seconds <1-10>
//     <i> If no response received within this time frame,
//     <i> IPCP module will try to resend data again
//     <i> Default: 2
#define IPCP_RETRYTOUT 2

//   </h>
// </e>
// <e>SLIP Network Interface
// ========================
// <i> Enable or disable SLIP Network Interface
#define SLIP_ENABLE    0

//   <h>IP Address
//   =============
//   <i> Local Static IP Address
//     <o>Address byte 1 <0-255>
//     <i> Default: 192
#define _IP1S          192

//     <o>Address byte 2 <0-255>
//     <i> Default: 168
#define _IP2S          168

//     <o>Address byte 3 <0-255>
//     <i> Default: 225
#define _IP3S          225

//     <o>Address byte 4 <0-255>
//     <i> Default: 1
#define _IP4S          1

//   </h>
//   <h>Subnet mask
//   ==============
//   <i> Local Subnet mask
//     <o>Mask byte 1 <0-255>
//     <i> Default: 255
#define _MSK1S         255

//     <o>Mask byte 2 <0-255>
//     <i> Default: 255
#define _MSK2S         255

//     <o>Mask byte 3 <0-255>
//     <i> Default: 255
#define _MSK3S         255

//     <o>Mask byte 4 <0-255>
//     <i> Default: 0
#define _MSK4S         0

//   </h>
//   <h>Primary DNS Server
//   =====================
//   <i> Primary DNS Server IP Address
//     <o>Address byte 1 <0-255>
//     <i> Default: 194
#define _pDNS1S        194

//     <o>Address byte 2 <0-255>
//     <i> Default: 25
#define _pDNS2S        25

//     <o>Address byte 3 <0-255>
//     <i> Default: 2
#define _pDNS3S        2

//     <o>Address byte 4 <0-255>
//     <i> Default: 129
#define _pDNS4S        129

//   </h>
//   <h>Secondary DNS Server
//   =======================
//   <i> Secondary DNS Server IP Address
//     <o>Address byte 1 <0-255>
//     <i> Default: 194
#define _sDNS1S        194

//     <o>Address byte 2 <0-255>
//     <i> Default: 25
#define _sDNS2S        25

//     <o>Address byte 3 <0-255>
//     <i> Default: 2
#define _sDNS3S        2

//     <o>Address byte 4 <0-255>
//     <i> Default: 130
#define _sDNS4S        130

//   </h>
//   <q>Use Default Gateway on remote Network
//   ========================================
//   <i> This option only applies when both Ethernet and SLIP Dial-up
//   <i> are used. If checked, data that cannot be sent to local LAN
//   <i> is forwarded to Dial-up network instead.
#define SLIP_DEFGW     1

// </e>
// <e>UDP Sockets
// ==============
// <i> Enable or disable UDP Sockets
#define UDP_ENABLE     1

//   <o>Number of UDP Sockets <1-20>
//   <i> Number of available UDP sockets
//   <i> Default: 5
#define UDP_NUMSOCKS   2

// </e>
// <e>TCP Sockets
// ==============
// <i> Enable or disable TCP Sockets
#define TCP_ENABLE     1

//   <o>Number of TCP Sockets <1-20>
//   <i> Number of available TCP sockets
//   <i> Default: 5
#define TCP_NUMSOCKS   6

//   <o>Number of Retries <0-20>
//   <i> How many times TCP module will try to retransmit data
//   <i> before giving up. Increase this value for high-latency
//   <i> and low_throughput networks.
//   <i> Default: 5
#define TCP_MAXRETRY   5

//   <o>Retry Timeout in seconds <1-10>
//   <i> If data frame not acknowledged within this time frame,
//   <i> TCP module will try to resend data again
//   <i> Default: 4
#define TCP_RETRYTOUT  4

//   <o>Default Connect Timeout in seconds <1-600>
//   <i> Default TCP Socket Keep Alive timeout. When it expires
//   <i> with no TCP data frame send, TCP Connection is closed.
//   <i> Default: 120
#define TCP_DEFTOUT    120

/* TCP fixed timeouts */
#define TCP_INIT_RETRY_TOUT 1     /* TCP initial Retransmit period in sec.   */
#define TCP_SYN_RETRY_TOUT  2     /* TCP SYN frame retransmit period in sec. */
#define TCP_CONRETRY        7     /* Number of retries to establish a conn.  */

// </e>
// <e>HTTP Server
// ==============
// <i> Enable or disable HTTP Server
#define HTTP_ENABLE    0

//   <o>Number of HTTP Sessions <1-10>
//   <i> Number of simultaneously active HTTP Sessions.
//   <i> Modify also the number of TCP Sockets because
//   <i> each HTTP session uses it's own TCP socket
//   <i> Default: 3
#define HTTP_NUMSESS   3

//   <o>Port Number <1-65535>
//   <i> Listening port number.
//   <i> Default: 80
#define HTTP_PORTNUM   80

//   <e>Enable User Authentication
//     <i> When enabled, the user will have to authenticate
//     <i> himself by username and password before accessing
//     <i> any page on this Embedded WEB server.
#define HTTP_ENAUTH    1

//     <s.20>Authentication Realm string
//     <i> Default: "Embedded WEB Server"
#define HTTP_AUTHREALM "Embedded WEB Server"

//     <s.15>Authentication Username
//     <i> Default: "admin"
#define HTTP_AUTHUSER  "admin"

//     <s.15>Authentication Password
//     <i> Default: ""
#define HTTP_AUTHPASSW ""

//   </e>
// </e>
// <e>Telnet Server
// ================
// <i> Enable or disable Telnet Server
#define TNET_ENABLE    0

//   <o>Number of Telnet Connections <1-10>
//   <i> Number of simultaneously active Telnet Connections.
//   <i> Modify also the number of TCP Sockets because
//   <i> each Telnet connection uses it's own TCP socket
//   <i> Default: 1
#define TNET_NUMSESS   2

//   <o>Port Number <1-65535>
//   <i> Listening port number.
//   <i> Default: 23
#define TNET_PORTNUM   23

//   <e>Enable User Authentication
//   <i> When enabled, the user will have to authenticate
//   <i> himself by username and password before access
//   <i> to the system is allowed.
#define TNET_ENAUTH    1

//     <s.15>Authentication Username
//     <i> Default: "admin"
#define TNET_AUTHUSER  "admin"

//     <s.15>Authentication Password
//     <i> Default: ""
#define TNET_AUTHPASSW ""

//   </e>
// </e>
// <e>TFTP Server
// ==============
// <i> Enable or disable TFTP Server
#define TFTP_ENABLE    0

//   <o>Number of TFTP Sessions <1-10>
//   <i> Number of simultaneously active TFTP Sessions
//   <i> All TFTP Sessions use the same UDP socket listening
//   <i> on defalut TFTP Server port 69.
//   <i> Default: 1
#define TFTP_NUMSESS   1

//   <o>Port Number <1-65535>
//   <i> Listening port number.
//   <i> Default: 69
#define TFTP_PORTNUM   69

//   <o>Inactive Session Timeout in seconds <5-120>
//   <i> When timeout expires TFTP Session is closed. This timeout
//   <i> is used when the UDP connection is broken because of error.
//   <i> Default: 15
#define TFTP_DEFTOUT   15

//   <o>Number of Retries <1-10>
//   <i> How many times TFTP Server will try to retransmit data
//   <i> before giving up.
//   <i> Default: 4
#define TFTP_MAXRETRY  4

// </e>
// <e>FTP Server
// ==============
// <i> Enable or disable FTP Server
#define FTP_ENABLE     1

//   <o>Number of FTP Sessions <1-10>
//   <i> Number of simultaneously active FTP Sessions
//   <i> Modify also the number of TCP Sockets because
//   <i> each FTP connection uses 2 TCP sockets
//   <i> Default: 1
#define FTP_NUMSESS    3

//   <o>Port Number <1-65535>
//   <i> Listening port number.
//   <i> Default: 21
#define FTP_PORTNUM    21

//   <e>Enable User Authentication
//   <i> When enabled, the user will have to authenticate
//   <i> himself by username and password before access
//   <i> to the system is allowed.
#define FTP_ENAUTH     1

//     <s.15>Authentication Username
//     <i> Default: "admin"
#define FTP_AUTHUSER   "admin"

//     <s.15>Authentication Password
//     <i> Default: ""
#define FTP_AUTHPASSW  ""

//   </e>
// </e>
// <e>DNS Client
// =============
// <i> Enable or disable DNS Client
#define DNS_ENABLE     0

//     <o>Cache Table size <5-100>
//     <i> Number of cached DNS host names/IP addresses
//     <i> Default: 20
#define DNS_TABSIZE    20

// </e>
// <e>SMTP Client
// ==============
// <i> Enable or disable SMTP Client
#define SMTP_ENABLE     0

//     <o>Response Timeout in seconds <5-120>
//     <i> This is a time for SMTP Client to wait for a response from
//     <i> SMTP Server. If timeout expires, Client aborts operation.
//     <i> Default: 20
#define SMTP_DEFTOUT   20

// </e>
//------------- <<< end of configuration section >>> -----------------------

/*----------------------------------------------------------------------------
 *      Fatal Error Handler
 *---------------------------------------------------------------------------*/

void sys_error (ERROR_CODE code) {
  /* This function is called when a fatal error is encountered. The normal */
  /* program execution is not possible anymore. Add your crytical error   .*/
  /* handler code here.                                                    */

  switch (code) {
    case ERR_MEM_ALLOC:
      /* Out of memory. */
      break;

    case ERR_MEM_FREE:
      /* Trying to release non existing memory block. */
      break;

    case ERR_MEM_CORRUPT:
      /* Memory Link pointer is Corrupted. */
      /* More data written than the size of allocated mem block. */
      break;

    case ERR_UDP_ALLOC:
      /* Out of UDP Sockets. */
      break;

    case ERR_TCP_ALLOC:
      /* Out of TCP Sockets. */
      break;

    case ERR_TCP_STATE:
      /* TCP State machine in undefined state. */
      break;
  }

  /* End-less loop */
  while (1);
}

/*----------------------------------------------------------------------------
 *      TCPnet Config Functions
 *---------------------------------------------------------------------------*/

#define  __NET_CONFIG__

#include <Net_lib.c>

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
