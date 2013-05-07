/******************************************************************
 *****                                                        *****
 *****  Name: cs8900.c                                        *****
 *****  Ver.: 1.0                                             *****
 *****  Date: 07/05/2001                                      *****
 *****  Auth: Andreas Dannenberg                              *****
 *****        HTWK Leipzig                                    *****
 *****        university of applied sciences                  *****
 *****        Germany                                         *****
 *****  Func: ethernet packet-driver for use with LAN-        *****
 *****        controller CS8900 from Crystal/Cirrus Logic     *****
 *****                                                        *****
 *****  Keil: Module modified for use with Philips            *****
 *****        LPC2378 EMAC Ethernet controller                *****
 *****                                                        *****
 ******************************************************************/

#include "EMAC.h"
#include "tcpip.h"
#include "LPC17xx.h"

static unsigned short *rptr;
static unsigned short *tptr;

// Keil: function added to write PHY
void write_PHY (int PhyReg, int Value)
{
  unsigned int tout;

  LPC_EMAC->MADR = DP83848C_DEF_ADR | PhyReg;
  LPC_EMAC->MWTD = Value;

  /* Wait utill operation completed */
  tout = 0;
  for (tout = 0; tout < MII_WR_TOUT; tout++) {
    if ((LPC_EMAC->MIND & MIND_BUSY) == 0) {
      break;
    }
  }
}


// Keil: function added to read PHY
unsigned short read_PHY (unsigned char PhyReg) 
{
  unsigned int tout;

  LPC_EMAC->MADR = DP83848C_DEF_ADR | PhyReg;
  LPC_EMAC->MCMD = MCMD_READ;

  /* Wait until operation completed */
  tout = 0;
  for (tout = 0; tout < MII_RD_TOUT; tout++) {
    if ((LPC_EMAC->MIND & MIND_BUSY) == 0) {
      break;
    }
  }
  LPC_EMAC->MCMD = 0;
  return (LPC_EMAC->MRDD);
}


// Keil: function added to initialize Rx Descriptors
void rx_descr_init (void)
{
  unsigned int i;

  for (i = 0; i < NUM_RX_FRAG; i++) {
    RX_DESC_PACKET(i)  = RX_BUF(i);
    RX_DESC_CTRL(i)    = RCTRL_INT | (ETH_FRAG_SIZE-1);
    RX_STAT_INFO(i)    = 0;
    RX_STAT_HASHCRC(i) = 0;
  }

  /* Set EMAC Receive Descriptor Registers. */
  LPC_EMAC->RxDescriptor    = RX_DESC_BASE;
  LPC_EMAC->RxStatus        = RX_STAT_BASE;
  LPC_EMAC->RxDescriptorNumber = NUM_RX_FRAG-1;

  /* Rx Descriptors Point to 0 */
  LPC_EMAC->RxConsumeIndex  = 0;
}


// Keil: function added to initialize Tx Descriptors
void tx_descr_init (void) {
  unsigned int i;

  for (i = 0; i < NUM_TX_FRAG; i++) {
    TX_DESC_PACKET(i) = TX_BUF(i);
    TX_DESC_CTRL(i)   = 0;
    TX_STAT_INFO(i)   = 0;
  }

  /* Set EMAC Transmit Descriptor Registers. */
  LPC_EMAC->TxDescriptor    = TX_DESC_BASE;
  LPC_EMAC->TxStatus        = TX_STAT_BASE;
  LPC_EMAC->TxDescriptorNumber = NUM_TX_FRAG-1;

  /* Tx Descriptors Point to 0 */
  LPC_EMAC->TxProduceIndex  = 0;
}


// configure port-pins for use with LAN-controller,
// reset it and send the configuration-sequence

void Init_EMAC(void)
{
// Keil: function modified to access the EMAC
// Initializes the EMAC ethernet controller
  unsigned int regv,tout,id1,id2;

   /* Power Up the EMAC controller. */
   LPC_SC->PCONP |= 0x40000000;
  /* Enable P1 Ethernet Pins. */
//  if (MAC_MODULEID == OLD_EMAC_MODULE_ID) { 
    /* For the first silicon rev.'-' ID P1.6 should be set. */
//   LPC_PINCON->PINSEL2 = 0x50151105;
 // }
 // else {
    /* on rev. 'A' and later, P1.6 should NOT be set. */
    LPC_PINCON->PINSEL2 = 0x50150105;
 // }
  LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~0x0000000F) | 0x00000005;

  /* Reset all EMAC internal modules. */
  LPC_EMAC->MAC1 = MAC1_RES_TX | MAC1_RES_MCS_TX | MAC1_RES_RX | MAC1_RES_MCS_RX | MAC1_SIM_RES | MAC1_SOFT_RES;
 // MAC_COMMAND = CR_REG_RES | CR_TX_RES | CR_RX_RES;
 LPC_EMAC->Command = CR_REG_RES | CR_TX_RES | CR_RX_RES | CR_PASS_RUNT_FRM;
  
  /* A short delay after reset. */
  for (tout = 100; tout; tout--);

  /* Initialize MAC control registers. */
  LPC_EMAC->MAC1 = MAC1_PASS_ALL;
  LPC_EMAC->MAC2 = MAC2_CRC_EN | MAC2_PAD_EN;
 //  MAC2 = MAC2_CRC_EN | MAC2_PAD_EN | MAC2_VLAN_PAD_EN;

  LPC_EMAC->MAXF = ETH_MAX_FLEN;
  LPC_EMAC->CLRT = CLRT_DEF;
  LPC_EMAC->IPGR = IPGR_DEF;

  /* Enable Reduced MII interface. */
  LPC_EMAC->Command = CR_RMII | CR_PASS_RUNT_FRM;


  /* Put the DP83848C in reset mode */
  write_PHY (PHY_REG_BMCR, 0x8000);

  /* Wait for hardware reset to end. */
  for (tout = 0; tout < 0x100000; tout++) {
    regv = read_PHY (PHY_REG_BMCR);
    if (!(regv & 0x8000)) {
      /* Reset complete */
      break;
    }
  }

  /* Check if this is a DP83848C PHY. */
  id1 = read_PHY (PHY_REG_IDR1);
  id2 = read_PHY (PHY_REG_IDR2);
  if (((id1 << 16) | (id2 & 0xFFF0)) == DP83848C_ID) {
    /* Configure the PHY device */

    /* Use autonegotiation about the link speed. */
    write_PHY (PHY_REG_BMCR, PHY_AUTO_NEG);
    /* Wait to complete Auto_Negotiation. */
    for (tout = 0; tout < 0x100000; tout++) {
      regv = read_PHY (PHY_REG_BMSR);
      if (regv & 0x0020) {
        /* Autonegotiation Complete. */
        break;
      }
    }
  }

  /* Check the link status. */
  for (tout = 0; tout < 0x10000; tout++) {
    regv = read_PHY (PHY_REG_STS);
    if (regv & 0x0001) {
      /* Link is on. */
      break;
    }
  }

  /* Configure Full/Half Duplex mode. */
  if (regv & 0x0004) {
    /* Full duplex is enabled. */
    LPC_EMAC->MAC2    |= MAC2_FULL_DUP;
    LPC_EMAC->Command |= CR_FULL_DUP;
    LPC_EMAC->IPGT     = IPGT_FULL_DUP;
  }
  else {
    /* Half duplex mode. */
    LPC_EMAC->IPGT = IPGT_HALF_DUP;
  }

  /* Configure 100MBit/10MBit mode. */
  if (regv & 0x0002) {
    /* 10MBit mode. */
    LPC_EMAC->SUPP = 0;
  }
  else {
    /* 100MBit mode. */
    LPC_EMAC->SUPP = SUPP_SPEED;
  }

  /* Set the Ethernet MAC Address registers */
  LPC_EMAC->SA0 = (MYMAC_1 << 8) | MYMAC_2;
  LPC_EMAC->SA1 = (MYMAC_3 << 8) | MYMAC_4;
  LPC_EMAC->SA2 = (MYMAC_5 << 8) | MYMAC_6;

  /* Initialize Tx and Rx DMA Descriptors */
  rx_descr_init ();
  tx_descr_init ();

  /* Receive Broadcast and Perfect Match Packets */
  LPC_EMAC->RxFilterCtrl = RFC_BCAST_EN | RFC_PERFECT_EN;					 

  /* Enable EMAC interrupts. */
  LPC_EMAC->IntEnable = INT_RX_DONE | INT_TX_DONE;

  /* Reset all interrupts */
  LPC_EMAC->IntClear  = 0xFFFF;

  /* Enable receive and transmit mode of MAC Ethernet core */
  LPC_EMAC->Command  |= (CR_RX_EN | CR_TX_EN);
  LPC_EMAC->MAC1     |= MAC1_REC_EN;
}


// reads a word in little-endian byte order from RX_BUFFER

unsigned short ReadFrame_EMAC(void)
{
  return (*rptr++);
}

// reads a word in big-endian byte order from RX_FRAME_PORT
// (useful to avoid permanent byte-swapping while reading
// TCP/IP-data)

unsigned short ReadFrameBE_EMAC(void)
{
  unsigned short ReturnValue;

  ReturnValue = SwapBytes (*rptr++);
  return (ReturnValue);
}


// copies bytes from frame port to MCU-memory
// NOTES: * an odd number of byte may only be transfered
//          if the frame is read to the end!
//        * MCU-memory MUST start at word-boundary

void CopyFromFrame_EMAC(void *Dest, unsigned short Size)
{
  unsigned short * piDest;                       // Keil: Pointer added to correct expression

  piDest = Dest;                                 // Keil: Line added
  while (Size > 1) {
    *piDest++ = ReadFrame_EMAC();
    Size -= 2;
  }
  
  if (Size) {                                         // check for leftover byte...
    *(unsigned char *)piDest = (char)ReadFrame_EMAC();// the LAN-Controller will return 0
  }                                                   // for the highbyte
}

// does a dummy read on frame-I/O-port
// NOTE: only an even number of bytes is read!

void DummyReadFrame_EMAC(unsigned short Size)    // discards an EVEN number of bytes
{                                                // from RX-fifo
  while (Size > 1) {
    ReadFrame_EMAC();
    Size -= 2;
  }
}

// Reads the length of the received ethernet frame and checks if the 
// destination address is a broadcast message or not
// returns the frame length
unsigned short StartReadFrame(void) {
  unsigned short RxLen;
  unsigned int idx;

  idx = LPC_EMAC->RxConsumeIndex;
  RxLen = (RX_STAT_INFO(idx) & RINFO_SIZE) - 3;
  rptr = (unsigned short *)RX_DESC_PACKET(idx);
  return(RxLen);
}

void EndReadFrame(void) {
  unsigned int idx;

  /* DMA free packet. */
  idx = LPC_EMAC->RxConsumeIndex;
  if (++idx == NUM_RX_FRAG) idx = 0;
  LPC_EMAC->RxConsumeIndex = idx;
}

unsigned int CheckFrameReceived(void) {             // Packet received ?

  if (LPC_EMAC->RxProduceIndex != LPC_EMAC->RxConsumeIndex) // more packets received ?		
    return(1);
  else 
    return(0);
}

// requests space in EMAC memory for storing an outgoing frame

void RequestSend(unsigned short FrameSize)
{
  unsigned int idx;

  idx  = LPC_EMAC->TxProduceIndex;
  tptr = (unsigned short *)TX_DESC_PACKET(idx);
  TX_DESC_CTRL(idx) = FrameSize | TCTRL_LAST;
}

// check if ethernet controller is ready to accept the
// frame we want to send

unsigned int Rdy4Tx(void)
{
  return (1);   // the ethernet controller transmits much faster
}               // than the CPU can load its buffers


// writes a word in little-endian byte order to TX_BUFFER
void WriteFrame_EMAC(unsigned short Data)
{
  *tptr++ = Data;
}

// copies bytes from MCU-memory to frame port
// NOTES: * an odd number of byte may only be transfered
//          if the frame is written to the end!
//        * MCU-memory MUST start at word-boundary

void CopyToFrame_EMAC(void *Source, unsigned int Size)
{
  unsigned short * piSource;
  unsigned int idx;

  piSource = Source;
  Size = (Size + 1) & 0xFFFE;    // round Size up to next even number
  while (Size > 0) {
    WriteFrame_EMAC(*piSource++);
    Size -= 2;
  }

  idx = LPC_EMAC->TxProduceIndex;
  if (++idx == NUM_TX_FRAG) idx = 0;
  LPC_EMAC->TxProduceIndex = idx;
}

