/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC17xx with MCB1700
 * Note(s): see also http://www.port.de/engl/canprod/sv_req_form.html
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
#include "CAN.h"                                 /* LPC17xx CAN adaption layer */

CAN_msg       CAN_TxMsg[2];                      /* CAN message for sending */
CAN_msg       CAN_RxMsg[2];                      /* CAN message for receiving */                                

unsigned int  CAN_TxRdy[2] = {0,0};              /* CAN HW ready to transmit a message */
unsigned int  CAN_RxRdy[2] = {0,0};              /* CAN HW received a message */


#define  PCLK            (100000000UL/4)         /* Peripheral clock, depends on VPBDIV */

/* Values of bit time register for different baudrates
   NT = Nominal bit time = TSEG1 + TSEG2 + 3
   SP = Sample point     = ((TSEG2 +1) / (TSEG1 + TSEG2 + 3)) * 100%
                                            SAM,  SJW, TSEG1, TSEG2, NT,  SP */
const uint32_t CAN_BIT_TIME[] = {          0, /*             not used             */
                                           0, /*             not used             */
                                           0, /*             not used             */
                                           0, /*             not used             */
                                  0x0001C000, /* 0+1,  3+1,   1+1,   0+1,  4, 75% */
                                           0, /*             not used             */
                                  0x0012C000, /* 0+1,  3+1,   2+1,   1+1,  6, 67% */
                                           0, /*             not used             */
                                  0x0023C000, /* 0+1,  3+1,   3+1,   2+1,  8, 63% */
                                           0, /*             not used             */
                                  0x0025C000, /* 0+1,  3+1,   5+1,   2+1, 10, 70% */
                                           0, /*             not used             */
                                  0x0036C000, /* 0+1,  3+1,   6+1,   3+1, 12, 67% */
                                           0, /*             not used             */
                                           0, /*             not used             */
                                  0x0048C000, /* 0+1,  3+1,   8+1,   4+1, 15, 67% */
                                  0x0049C000, /* 0+1,  3+1,   9+1,   4+1, 16, 69% */
                                };

/*----------------------------------------------------------------------------
  configure the requested baudrate.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
static void CAN_cfgBaudrate (uint32_t ctrl, uint32_t baudrate)  {
  LPC_CAN_TypeDef *pCAN = (ctrl == 1) ? LPC_CAN1 : LPC_CAN2;
  uint32_t result = 0;
  uint32_t nominal_time;

  /* Determine which nominal time to use for PCLK */
  if (((PCLK / 1000000) % 6) == 0) {
    nominal_time = 12;                   /* PCLK based on  72MHz CCLK */
  } else {
    nominal_time = 10;                   /* PCLK based on 100MHz CCLK */
  }

  /* Prepare value appropriate for bit time register */
  result  = (PCLK / nominal_time) / baudrate - 1;
  result &= 0x000003FF;
  result |= CAN_BIT_TIME[nominal_time];

  pCAN->BTR  = result;                           /* Set bit timing */
}


/*----------------------------------------------------------------------------
  setup CAN interface.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_setup (uint32_t ctrl)  {
  LPC_CAN_TypeDef *pCAN = (ctrl == 1) ? LPC_CAN1 : LPC_CAN2;

  if (ctrl == 1) {
    LPC_SC->PCONP       |=  (1 << 13);           /* Enable power to CAN1 block */
    LPC_PINCON->PINSEL0 |=  (1 <<  0);           /* Pin P0.0 used as RD1 (CAN1) */
    LPC_PINCON->PINSEL0 |=  (1 <<  2);           /* Pin P0.1 used as TD1 (CAN1) */
    
    NVIC_EnableIRQ(CAN_IRQn);                    /* Enable CAN interrupt */
  } else {
    LPC_SC->PCONP       |=  (1 << 14);           /* Enable power to CAN2 block */
    LPC_PINCON->PINSEL0 |=  (1 <<  9);           /* Pin P0.4 used as RD2 (CAN2) */
    LPC_PINCON->PINSEL0 |=  (1 << 11);           /* Pin P0.5 used as TD2 (CAN2) */
    
    NVIC_EnableIRQ(CAN_IRQn);                    /* Enable CAN interrupt */
  }

  LPC_CANAF->AFMR = 2;                           /* By default filter is not used */
  pCAN->MOD   = 1;                               /* Enter reset mode */
  pCAN->IER   = 0;                               /* Disable all interrupts */
  pCAN->GSR   = 0;                               /* Clear status register */
  CAN_cfgBaudrate(ctrl, 500000);                 /* Set bit timing */
  pCAN->IER   = 0x0003;                          /* Enable Tx and Rx interrupt */
}


/*----------------------------------------------------------------------------
  leave initialisation mode.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_start (uint32_t ctrl)  {
  LPC_CAN_TypeDef *pCAN = (ctrl == 1) ? LPC_CAN1 : LPC_CAN2;

  pCAN->MOD = 0;                                 /* Enter normal operating mode */
}

/*----------------------------------------------------------------------------
  check if transmit mailbox is empty
 *----------------------------------------------------------------------------*/
void CAN_waitReady (uint32_t ctrl)  {
  LPC_CAN_TypeDef *pCAN = (ctrl == 1) ? LPC_CAN1 : LPC_CAN2;

  while ((pCAN->SR & (1<<2)) == 0);              /* Transmitter ready for transmission */
  CAN_TxRdy[ctrl-1] = 1;
}

/*----------------------------------------------------------------------------
  wite a message to CAN peripheral and transmit it.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_wrMsg (uint32_t ctrl, CAN_msg *msg)  {
  LPC_CAN_TypeDef *pCAN = (ctrl == 1) ? LPC_CAN1 : LPC_CAN2;
  uint32_t CANData;

  CANData = (((uint32_t) msg->len) << 16)     & 0x000F0000 | 
            (msg->format == EXTENDED_FORMAT ) * 0x80000000 |
            (msg->type   == REMOTE_FRAME)     * 0x40000000;

  if (pCAN->SR & (1<<2))  {                      /* Transmit buffer 1 free */
    pCAN->TFI1  = CANData;                       /* Write frame informations */
    pCAN->TID1 = msg->id;                        /* Write CAN message identifier */
    pCAN->TDA1 = *(uint32_t *) &msg->data[0];    /* Write first 4 data bytes */
    pCAN->TDB1 = *(uint32_t *) &msg->data[4];    /* Write second 4 data bytes */
    //pCAN->CMR  = 0x31;                           /* Select Tx1 for Self Tx/Rx */
    pCAN->CMR  = 0x21;                           /* Start transmission without loop-back */
  }
}

/*----------------------------------------------------------------------------
  read a message from CAN peripheral and release it.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_rdMsg (uint32_t ctrl, CAN_msg *msg)  {
  LPC_CAN_TypeDef *pCAN = (ctrl == 1) ? LPC_CAN1 : LPC_CAN2;
  uint32_t CANData;

                                                 /* Read frame informations */
  CANData = pCAN->RFS;
  msg->format   = (CANData & 0x80000000) == 0x80000000;
  msg->type     = (CANData & 0x40000000) == 0x40000000;
  msg->len      = ((uint8_t)(CANData >> 16)) & 0x0F;

  msg->id = pCAN->RID;                           /* Read CAN message identifier */

  if (msg->type == DATA_FRAME)  {                /* Read the data if received message was DATA FRAME  */ 
    *(uint32_t *) &msg->data[0] = pCAN->RDA;
    *(uint32_t *) &msg->data[4] = pCAN->RDB;
  }
}


/*----------------------------------------------------------------------------
  setup acceptance filter.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_wrFilter (uint32_t ctrl, uint32_t id, uint8_t format)  {
  static int CAN_std_cnt = 0;
  static int CAN_ext_cnt = 0;
         uint32_t buf0, buf1;
         int cnt1, cnt2, bound1;

  /* Acceptance Filter Memory full */
  if ((((CAN_std_cnt + 1) >> 1) + CAN_ext_cnt) >= 512)
    return;                                       /* error: objects full */

  /* Setup Acceptance Filter Configuration 
    Acceptance Filter Mode Register = Off  */                                 
  LPC_CANAF->AFMR = 0x00000001;

  if (format == STANDARD_FORMAT)  {              /* Add mask for standard identifiers */
    id |= (ctrl-1) << 13;                        /* Add controller number */
    id &= 0x0000F7FF;                            /* Mask out 16-bits of ID */

    /* Move all remaining extended mask entries one place up                 
       if new entry will increase standard ID filters list   */
    if ((CAN_std_cnt & 0x0001) == 0 && CAN_ext_cnt != 0) {
      cnt1   = (CAN_std_cnt >> 1);
      bound1 = CAN_ext_cnt;
      buf0   = LPC_CANAF_RAM->mask[cnt1];
      while (bound1--)  {
        cnt1++;
        buf1 = LPC_CANAF_RAM->mask[cnt1];
        LPC_CANAF_RAM->mask[cnt1] = buf0;
        buf0 = buf1;
      }        
    }

    if (CAN_std_cnt == 0)  {                     /* For entering first  ID */
      LPC_CANAF_RAM->mask[0] = 0x0000FFFF | (id << 16);
    }  else if (CAN_std_cnt == 1)  {             /* For entering second ID */
      if ((LPC_CANAF_RAM->mask[0] >> 16) > id)
        LPC_CANAF_RAM->mask[0] = (LPC_CANAF_RAM->mask[0] >> 16) | (id << 16);
      else
        LPC_CANAF_RAM->mask[0] = (LPC_CANAF_RAM->mask[0] & 0xFFFF0000) | id;
    }  else  {
      /* Find where to insert new ID */
      cnt1 = 0;
      cnt2 = CAN_std_cnt;
      bound1 = (CAN_std_cnt - 1) >> 1;
      while (cnt1 <= bound1)  {                  /* Loop through standard existing IDs */
        if ((LPC_CANAF_RAM->mask[cnt1] >> 16) > id)  {
          cnt2 = cnt1 * 2;
          break;
        }
        if ((LPC_CANAF_RAM->mask[cnt1] & 0x0000FFFF) > id)  {
          cnt2 = cnt1 * 2 + 1;
          break;
        }
        cnt1++;                                  /* cnt1 = U32 where to insert new ID */
      }                                          /* cnt2 = U16 where to insert new ID */

      if (cnt1 > bound1)  {                      /* Adding ID as last entry */
        if ((CAN_std_cnt & 0x0001) == 0)         /* Even number of IDs exists */
          LPC_CANAF_RAM->mask[cnt1]  = 0x0000FFFF | (id << 16);
        else                                     /* Odd  number of IDs exists */
          LPC_CANAF_RAM->mask[cnt1]  = (LPC_CANAF_RAM->mask[cnt1] & 0xFFFF0000) | id;
      }  else  {
        buf0 = LPC_CANAF_RAM->mask[cnt1];        /* Remember current entry */
        if ((cnt2 & 0x0001) == 0)                /* Insert new mask to even address */
          buf1 = (id << 16) | (buf0 >> 16);
        else                                     /* Insert new mask to odd  address */
          buf1 = (buf0 & 0xFFFF0000) | id;
     
        LPC_CANAF_RAM->mask[cnt1] = buf1;        /* Insert mask */

        bound1 = CAN_std_cnt >> 1;
        /* Move all remaining standard mask entries one place up */
        while (cnt1 < bound1)  {
          cnt1++;
          buf1  = LPC_CANAF_RAM->mask[cnt1];
          LPC_CANAF_RAM->mask[cnt1] = (buf1 >> 16) | (buf0 << 16);
          buf0  = buf1;
        }

        if ((CAN_std_cnt & 0x0001) == 0)         /* Even number of IDs exists */
          LPC_CANAF_RAM->mask[cnt1] = (LPC_CANAF_RAM->mask[cnt1] & 0xFFFF0000) | (0x0000FFFF);
      }
    }
    CAN_std_cnt++;
  }  else  {                                     /* Add mask for extended identifiers */
    id |= (ctrl-1) << 29;                        /* Add controller number */

    cnt1 = ((CAN_std_cnt + 1) >> 1);
    cnt2 = 0;
    while (cnt2 < CAN_ext_cnt)  {                /* Loop through extended existing masks */
      if (LPC_CANAF_RAM->mask[cnt1] > id)
        break;
      cnt1++;                                    /* cnt1 = U32 where to insert new mask */
      cnt2++;
    }

    buf0 = LPC_CANAF_RAM->mask[cnt1];            /* Remember current entry */
    LPC_CANAF_RAM->mask[cnt1] = id;              /* Insert mask */

    CAN_ext_cnt++;

    bound1 = CAN_ext_cnt - 1;
    /* Move all remaining extended mask entries one place up */
    while (cnt2 < bound1)  {
      cnt1++;
      cnt2++;
      buf1 = LPC_CANAF_RAM->mask[cnt1];
      LPC_CANAF_RAM->mask[cnt1] = buf0;
      buf0 = buf1;
    }        
  }
  
  /* Calculate std ID start address (buf0) and ext ID start address (buf1) */
  buf0 = ((CAN_std_cnt + 1) >> 1) << 2;
  buf1 = buf0 + (CAN_ext_cnt << 2);

  /* Setup acceptance filter pointers */
  LPC_CANAF->SFF_sa     = 0;
  LPC_CANAF->SFF_GRP_sa = buf0;
  LPC_CANAF->EFF_sa     = buf0;
  LPC_CANAF->EFF_GRP_sa = buf1;
  LPC_CANAF->ENDofTable = buf1;

  LPC_CANAF->AFMR = 0x00000000;                  /* Use acceptance filter */
}


/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/
void CAN_IRQHandler (void)  {
  volatile uint32_t icr;

  /* check CAN controller 1 */
  icr = LPC_CAN1->ICR;                           /* clear interrupts */

  if (icr & (1 << 0)) {                          /* CAN Controller #1 meassage is received */
	CAN_rdMsg (1, &CAN_RxMsg[0]);                /*  read the message */
    LPC_CAN1->CMR = (1 << 2);                    /* Release receive buffer */

    CAN_RxRdy[0] = 1;                            /*  set receive flag */
  }

  if (icr & (1 << 1)) {                          /* CAN Controller #1 meassage is transmitted */
	CAN_TxRdy[0] = 1; 
  }

  /* check CAN controller 2 */
  icr = LPC_CAN2->ICR;                           /* clear interrupts */

  if (icr & (1 << 0)) {                          /* CAN Controller #2 meassage is received */
	CAN_rdMsg (2, &CAN_RxMsg[1]);                /*  read the message */
    LPC_CAN2->CMR = (1 << 2);                    /* Release receive buffer */

    CAN_RxRdy[1] = 1;                            /*  set receive flag */
  }

  if (icr & (1 << 1)) {                          /* CAN Controller #2 meassage is transmitted */
	CAN_TxRdy[1] = 1; 
  }

}
