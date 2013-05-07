/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    EMAC_LPC17xx.c
 *      Purpose: Driver for NXP LPC1768 EMAC Ethernet Controller
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include "EMAC_LPC17xx.h"
#include <LPC17xx.h>                    /* LPC17xx definitions               */


typedef void (*IAP)(U32 *cmd, U32 *res);
IAP iap_entry = (IAP)0x1FFF1FF1;

/* The following macro definitions may be used to select the speed
   of the physical link:

  _10MBIT_   - connect at 10 MBit only
  _100MBIT_  - connect at 100 MBit only

  By default an autonegotiation of the link speed is used. This may take 
  longer to connect, but it works for 10MBit and 100MBit physical links.     */

/* Net_Config.c */
extern U8 own_hw_adr[];

/* Local variables */
static BIT dev_175x;

/* EMAC local DMA Descriptors. */
static            RX_Desc Rx_Desc[NUM_RX_FRAG];
static __align(8) RX_Stat Rx_Stat[NUM_RX_FRAG]; /* Must be 8-Byte alligned   */
static            TX_Desc Tx_Desc[NUM_TX_FRAG];
static            TX_Stat Tx_Stat[NUM_TX_FRAG];

/* EMAC local DMA buffers. */
static U32 rx_buf[NUM_RX_FRAG][ETH_FRAG_SIZE>>2];
static U32 tx_buf[NUM_TX_FRAG][ETH_FRAG_SIZE>>2];

/*----------------------------------------------------------------------------
 *      EMAC Ethernet Driver Functions
 *----------------------------------------------------------------------------
 *  Required functions for Ethernet driver module:
 *  a. Polling mode: - void init_ethernet ()
 *                   - void send_frame (OS_FRAME *frame)
 *                   - void poll_ethernet (void)
 *  b. Interrupt mode: - void init_ethernet ()
 *                     - void send_frame (OS_FRAME *frame)
 *                     - void int_enable_eth ()
 *                     - void int_disable_eth ()
 *                     - interrupt function 
 *---------------------------------------------------------------------------*/

/* Local Function Prototypes */
static void rx_descr_init (void);
static void tx_descr_init (void);
static void write_PHY (U32 PhyReg, U16 Value);
static U16  read_PHY (U32 PhyReg);

/*--------------------------- init_ethernet ---------------------------------*/

void init_ethernet (void) {
  /* Initialize the EMAC ethernet controller. */
  U32 regv,tout,id1,id2;
  U32 pb[2];

  dev_175x = __FALSE;
  /* Read device ID with IAP*/
  pb[0] = 54;
  iap_entry (&pb[0], &pb[0]);
  if ((pb[1] >> 24) == 0x25) {
    /* Use software RMII management routines. */
    dev_175x = __TRUE;
  }

  /* Power Up the EMAC controller. */
  LPC_SC->PCONP |= 0x40000000;

  /* Enable P1 Ethernet Pins. */
  LPC_PINCON->PINSEL2 = 0x50150105;
  if (dev_175x == __FALSE) {
    /* LPC176x devices, no MDIO, MDC remap. */
    LPC_PINCON->PINSEL3 = (LPC_PINCON->PINSEL3 & ~0x0000000F) | 0x00000005;
  }
  else {
    /* LPC175x devices, use software MII management. */  
    LPC_PINCON->PINSEL4 &= ~0x000F0000;
    LPC_GPIO2->FIODIR |= MDC;
  }

  /* Reset all EMAC internal modules. */
  LPC_EMAC->MAC1    = MAC1_RES_TX | MAC1_RES_MCS_TX | MAC1_RES_RX | 
                      MAC1_RES_MCS_RX | MAC1_SIM_RES | MAC1_SOFT_RES;
  LPC_EMAC->Command = CR_REG_RES | CR_TX_RES | CR_RX_RES | CR_PASS_RUNT_FRM;

  /* A short delay after reset. */
  for (tout = 100; tout; tout--);

  /* Initialize MAC control registers. */
  LPC_EMAC->MAC1 = MAC1_PASS_ALL;
  LPC_EMAC->MAC2 = MAC2_CRC_EN | MAC2_PAD_EN;
  LPC_EMAC->MAXF = ETH_MAX_FLEN;
  LPC_EMAC->CLRT = CLRT_DEF;
  LPC_EMAC->IPGR = IPGR_DEF;

  /* Enable Reduced MII interface. */
  LPC_EMAC->Command = CR_RMII | CR_PASS_RUNT_FRM;

  /* Reset Reduced MII Logic. */
  LPC_EMAC->SUPP = SUPP_RES_RMII;
  for (tout = 100; tout; tout--);
  LPC_EMAC->SUPP = 0;

  /* Put the DP83848C in reset mode */
  write_PHY (PHY_REG_BMCR, 0x8000);

  /* Wait for hardware reset to end. */
  for (tout = 0; tout < 0x100000; tout++) {
    regv = read_PHY (PHY_REG_BMCR);
    if (!(regv & 0x8800)) {
      /* Reset complete, device not Power Down. */
      break;
    }
  }

  /* Check if this is a DP83848C PHY. */
  id1 = read_PHY (PHY_REG_IDR1);
  id2 = read_PHY (PHY_REG_IDR2);

  if (((id1 << 16) | (id2 & 0xFFF0)) == DP83848C_ID) {
    /* Configure the PHY device */
#if defined (_10MBIT_)
    /* Connect at 10MBit */
    write_PHY (PHY_REG_BMCR, PHY_FULLD_10M);
#elif defined (_100MBIT_)
    /* Connect at 100MBit */
    write_PHY (PHY_REG_BMCR, PHY_FULLD_100M);
#else
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
#endif
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
  LPC_EMAC->SA0 = ((U32)own_hw_adr[5] << 8) | (U32)own_hw_adr[4];
  LPC_EMAC->SA1 = ((U32)own_hw_adr[3] << 8) | (U32)own_hw_adr[2];
  LPC_EMAC->SA2 = ((U32)own_hw_adr[1] << 8) | (U32)own_hw_adr[0];

  /* Initialize Tx and Rx DMA Descriptors */
  rx_descr_init ();
  tx_descr_init ();

  /* Receive Broadcast, Multicast and Perfect Match Packets */
  LPC_EMAC->RxFilterCtrl = RFC_MCAST_EN | RFC_BCAST_EN | RFC_PERFECT_EN;

  /* Enable EMAC interrupts. */
  LPC_EMAC->IntEnable = INT_RX_DONE | INT_TX_DONE;

  /* Reset all interrupts */
  LPC_EMAC->IntClear  = 0xFFFF;

  /* Enable receive and transmit mode of MAC Ethernet core */
  LPC_EMAC->Command  |= (CR_RX_EN | CR_TX_EN);
  LPC_EMAC->MAC1     |= MAC1_REC_EN;

}


/*--------------------------- int_enable_eth --------------------------------*/

void int_enable_eth (void) {
  /* Ethernet Interrupt Enable function. */
  NVIC_EnableIRQ(ENET_IRQn);
}


/*--------------------------- int_disable_eth -------------------------------*/

void int_disable_eth (void) {
  /* Ethernet Interrupt Disable function. */
  NVIC_DisableIRQ(ENET_IRQn);
}


/*--------------------------- send_frame ------------------------------------*/

void send_frame (OS_FRAME *frame) {
  /* Send frame to EMAC ethernet controller */
  U32 idx,len;
  U32 *sp,*dp;

  idx = LPC_EMAC->TxProduceIndex;
  sp  = (U32 *)&frame->data[0];
  dp  = (U32 *)Tx_Desc[idx].Packet;

  /* Copy frame data to EMAC packet buffers. */
  for (len = (frame->length + 3) >> 2; len; len--) {
    *dp++ = *sp++;
  }
  Tx_Desc[idx].Ctrl = (frame->length-1) | (TCTRL_INT | TCTRL_LAST);

  /* Start frame transmission. */
  if (++idx == NUM_TX_FRAG) idx = 0;
  LPC_EMAC->TxProduceIndex = idx;
}


/*--------------------------- interrupt_ethernet ----------------------------*/

void ENET_IRQHandler (void) {
  /* EMAC Ethernet Controller Interrupt function. */
  OS_FRAME *frame;
  U32 idx,int_stat,RxLen,info;
  U32 *sp,*dp;

  while ((int_stat = (LPC_EMAC->IntStatus & LPC_EMAC->IntEnable)) != 0) {
    LPC_EMAC->IntClear = int_stat;
    if (int_stat & INT_RX_DONE) {
      /* Packet received, check if packet is valid. */
      idx = LPC_EMAC->RxConsumeIndex;
      while (idx != LPC_EMAC->RxProduceIndex) {
        info = Rx_Stat[idx].Info;
        if (!(info & RINFO_LAST_FLAG)) {
          goto rel;
        }

        RxLen = (info & RINFO_SIZE) - 3;
        if (RxLen > ETH_MTU || (info & RINFO_ERR_MASK)) {
          /* Invalid frame, ignore it and free buffer. */
          goto rel;
        }
        /* Flag 0x80000000 to skip sys_error() call when out of memory. */
        frame = alloc_mem (RxLen | 0x80000000);
        /* if 'alloc_mem()' has failed, ignore this packet. */
        if (frame != NULL) {
          dp = (U32 *)&frame->data[0];
          sp = (U32 *)Rx_Desc[idx].Packet;
          for (RxLen = (RxLen + 3) >> 2; RxLen; RxLen--) {
            *dp++ = *sp++;
          }
          put_in_queue (frame);
        }
rel:    if (++idx == NUM_RX_FRAG) idx = 0;
        /* Release frame from EMAC buffer. */
        LPC_EMAC->RxConsumeIndex = idx;
      }
    }
    if (int_stat & INT_TX_DONE) {
      /* Frame transmit completed. */
    }
  }

}


/*--------------------------- rx_descr_init ---------------------------------*/

static void rx_descr_init (void) {
  /* Initialize Receive Descriptor and Status array. */
  U32 i;

  for (i = 0; i < NUM_RX_FRAG; i++) {
    Rx_Desc[i].Packet  = (U32)&rx_buf[i];
    Rx_Desc[i].Ctrl    = RCTRL_INT | (ETH_FRAG_SIZE-1);
    Rx_Stat[i].Info    = 0;
    Rx_Stat[i].HashCRC = 0;
  }

  /* Set EMAC Receive Descriptor Registers. */
  LPC_EMAC->RxDescriptor       = (U32)&Rx_Desc[0];
  LPC_EMAC->RxStatus           = (U32)&Rx_Stat[0];
  LPC_EMAC->RxDescriptorNumber = NUM_RX_FRAG-1;

  /* Rx Descriptors Point to 0 */
  LPC_EMAC->RxConsumeIndex  = 0;
}


/*--------------------------- tx_descr_init ---- ----------------------------*/

static void tx_descr_init (void) {
  /* Initialize Transmit Descriptor and Status array. */
  U32 i;

  for (i = 0; i < NUM_TX_FRAG; i++) {
    Tx_Desc[i].Packet = (U32)&tx_buf[i];
    Tx_Desc[i].Ctrl   = 0;
    Tx_Stat[i].Info   = 0;
  }

  /* Set EMAC Transmit Descriptor Registers. */
  LPC_EMAC->TxDescriptor       = (U32)&Tx_Desc[0];
  LPC_EMAC->TxStatus           = (U32)&Tx_Stat[0];
  LPC_EMAC->TxDescriptorNumber = NUM_TX_FRAG-1;

  /* Tx Descriptors Point to 0 */
  LPC_EMAC->TxProduceIndex  = 0;
}


/*--------------------------- output_MDIO -----------------------------------*/

static void delay (void) {;};

static void output_MDIO (U32 val, U32 n) {
  /* Output a value to the MII PHY management interface. */

  for (val <<= (32 - n); n; val <<= 1, n--) {
    if (val & 0x80000000) {
      LPC_GPIO2->FIOSET = MDIO;
    }
    else {
      LPC_GPIO2->FIOCLR = MDIO;
    }
    delay ();
    LPC_GPIO2->FIOSET = MDC;
    delay ();
    LPC_GPIO2->FIOCLR = MDC;
  }
}

/*--------------------------- turnaround_MDIO -------------------------------*/

static void turnaround_MDIO (void) {
  /* Turnaround MDO is tristated. */

  LPC_GPIO2->FIODIR &= ~MDIO;
  LPC_GPIO2->FIOSET  = MDC;
  delay ();
  LPC_GPIO2->FIOCLR  = MDC;
  delay ();
}

/*--------------------------- input_MDIO ------------------------------------*/

static U32 input_MDIO (void) {
  /* Input a value from the MII PHY management interface. */
  U32 i,val = 0;

  for (i = 0; i < 16; i++) {
    val <<= 1;
    LPC_GPIO2->FIOSET = MDC;
    delay ();
    LPC_GPIO2->FIOCLR = MDC;
    if (LPC_GPIO2->FIOPIN & MDIO) {
      val |= 1;
    }
  }
  return (val);
}


/*--------------------------- write_PHY -------------------------------------*/

static void write_PHY (U32 PhyReg, U16 Value) {
  /* Write a data 'Value' to PHY register 'PhyReg'. */
  U32 tout;

  if (dev_175x == __TRUE) {
    /* Software MII Management for LPC175x. */
    /* Remapped MDC on P2.8 and MDIO on P2.9 do not work. */
    LPC_GPIO2->FIODIR |= MDIO;

    /* 32 consecutive ones on MDO to establish sync */
    output_MDIO (0xFFFFFFFF, 32);

    /* start code (01), write command (01) */
    output_MDIO (0x05, 4);

    /* write PHY address */
    output_MDIO (DP83848C_DEF_ADR >> 8, 5);

    /* write the PHY register to write */
    output_MDIO (PhyReg, 5);

    /* turnaround MDIO (1,0)*/
    output_MDIO (0x02, 2);

    /* write the data value */
    output_MDIO (Value, 16);

    /* turnaround MDO is tristated */
    turnaround_MDIO ();
  }
  else {
    /* Hardware MII Management for LPC176x devices. */
    LPC_EMAC->MADR = DP83848C_DEF_ADR | PhyReg;
    LPC_EMAC->MWTD = Value;

    /* Wait utill operation completed */
    for (tout = 0; tout < MII_WR_TOUT; tout++) {
      if ((LPC_EMAC->MIND & MIND_BUSY) == 0) {
        break;
      }
    }
  }
}


/*--------------------------- read_PHY --------------------------------------*/

static U16 read_PHY (U32 PhyReg) {
  /* Read a PHY register 'PhyReg'. */
  U32 tout, val;

  if (dev_175x == __TRUE) {
    /* Software MII Management for LPC175x. */
    /* Remapped MDC on P2.8 and MDIO on P2.9 does not work. */
    LPC_GPIO2->FIODIR |= MDIO;

    /* 32 consecutive ones on MDO to establish sync */
    output_MDIO (0xFFFFFFFF, 32);

    /* start code (01), read command (10) */
    output_MDIO (0x06, 4);

    /* write PHY address */
    output_MDIO (DP83848C_DEF_ADR >> 8, 5);

    /* write the PHY register to write */
    output_MDIO (PhyReg, 5);

    /* turnaround MDO is tristated */
    turnaround_MDIO ();

    /* read the data value */
    val = input_MDIO ();

    /* turnaround MDIO is tristated */
    turnaround_MDIO ();
  }
  else {
    LPC_EMAC->MADR = DP83848C_DEF_ADR | PhyReg;
    LPC_EMAC->MCMD = MCMD_READ;

    /* Wait until operation completed */
    for (tout = 0; tout < MII_RD_TOUT; tout++) {
      if ((LPC_EMAC->MIND & MIND_BUSY) == 0) {
        break;
      }
    }
    LPC_EMAC->MCMD = 0;
    val = LPC_EMAC->MRDD;
  }
  return (val);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
