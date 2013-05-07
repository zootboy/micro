/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    mscuser.c
 * Purpose: Mass Storage Class Custom User Module
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
 *----------------------------------------------------------------------------
 * History:
 *          V1.20 Added SCSI_READ12, SCSI_WRITE12
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#include "type.h"

#include "usb.h"
#include "msc.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "mscuser.h"

#include "memory.h"


U8   Memory[MSC_MemorySize];               /* MSC Memory in RAM */

BOOL MemOK;                                /* Memory OK */

U32  Offset;                               /* R/W Offset */
U32  Length;                               /* R/W Length */

U8   BulkStage;                            /* Bulk Stage */

U8   BulkBuf[MSC_MAX_PACKET];              /* Bulk In/Out Buffer */
U8   BulkLen;                              /* Bulk In/Out Length */

MSC_CBW CBW;                               /* Command Block Wrapper */
MSC_CSW CSW;                               /* Command Status Wrapper */



/*
 *  Set Stall for MSC Endpoint
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *    Return Value:    None
 */

void MSC_SetStallEP (U32 EPNum) {          /* set EP halt status according stall status */
  USB_SetStallEP(EPNum);
  USB_EndPointHalt  |=  (EPNum & 0x80) ? ((1 << 16) << (EPNum & 0x0F)) : (1 << EPNum);
}


/*
 *  MSC Mass Storage Reset Request Callback
 *   Called automatically on Mass Storage Reset Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL MSC_Reset (void) {

  LED_Off (LED_RD | LED_WR);               /* Turn Off R/W LED */

  USB_EndPointStall = 0x00000000;          /* EP must stay stalled */
  CSW.dSignature = 0;                      /* invalid signature */

  BulkStage = MSC_BS_CBW;

  return (__TRUE);
}


/*
 *  MSC Get Max LUN Request Callback
 *   Called automatically on Get Max LUN Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL MSC_GetMaxLUN (void) {

  EP0Buf[0] = 0;                           /* No LUN associated with this device */
  return (__TRUE);
}


/*
 *  MSC Memory Read Callback
 *   Called automatically on Memory Read Event
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_MemoryRead (void) {
  U32 n;

  if (Length > MSC_MAX_PACKET) {
    n = MSC_MAX_PACKET;
  } else {
    n = Length;
  }

  if ((Offset + n) > MSC_MemorySize) {
    n = MSC_MemorySize - Offset;
    BulkStage = MSC_BS_DATA_IN_LAST_STALL;
  }

  USB_WriteEP(MSC_EP_IN, &Memory[Offset], n);
  Offset += n;
  Length -= n;

  CSW.dDataResidue -= n;

  if (Length == 0) {
    BulkStage = MSC_BS_DATA_IN_LAST;
  }

  if (BulkStage != MSC_BS_DATA_IN) {
    LED_Off (LED_RD);            /* Turn Off Read LED */
    CSW.bStatus = CSW_CMD_PASSED;
  }
}


/*
 *  MSC Memory Write Callback
 *   Called automatically on Memory Write Event
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_MemoryWrite (void) {
  U32 n;

  if ((Offset + BulkLen) > MSC_MemorySize) {
    BulkLen = MSC_MemorySize - Offset;
    BulkStage = MSC_BS_CSW;
    MSC_SetStallEP(MSC_EP_OUT);
  }

  for (n = 0; n < BulkLen; n++) {
    Memory[Offset + n] = BulkBuf[n];
  }

  Offset += BulkLen;
  Length -= BulkLen;

  CSW.dDataResidue -= BulkLen;

  if ((Length == 0) || (BulkStage == MSC_BS_CSW)) {
    LED_Off (LED_WR);            /* Turn Off Write LED */
    CSW.bStatus = CSW_CMD_PASSED;
    MSC_SetCSW();
  }
}


/*
 *  MSC Memory Verify Callback
 *   Called automatically on Memory Verify Event
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_MemoryVerify (void) {
  U32 n;

  if ((Offset + BulkLen) > MSC_MemorySize) {
    BulkLen = MSC_MemorySize - Offset;
    BulkStage = MSC_BS_CSW;
    MSC_SetStallEP(MSC_EP_OUT);
  }

  for (n = 0; n < BulkLen; n++) {
    if (Memory[Offset + n] != BulkBuf[n]) {
      MemOK = __FALSE;
      break;
    }
  }

  Offset += BulkLen;
  Length -= BulkLen;

  CSW.dDataResidue -= BulkLen;

  if ((Length == 0) || (BulkStage == MSC_BS_CSW)) {
    CSW.bStatus = (MemOK) ? CSW_CMD_PASSED : CSW_CMD_FAILED;
    MSC_SetCSW();
  }
}


/*
 *  MSC SCSI Read/Write Setup Callback
 *    Parameters:      None (global variables)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL MSC_RWSetup (void) {
  U32 n;

  /* Logical Block Address of First Block */
  n = (CBW.CB[2] << 24) |
      (CBW.CB[3] << 16) |
      (CBW.CB[4] <<  8) |
      (CBW.CB[5] <<  0);

  Offset = n * MSC_BlockSize;

  /* Number of Blocks to transfer */
  switch (CBW.CB[0]) {
    case SCSI_READ10:
    case SCSI_WRITE10:
    case SCSI_VERIFY10:
      n = (CBW.CB[7] <<  8) |
          (CBW.CB[8] <<  0);
      break;

    case SCSI_READ12:
    case SCSI_WRITE12:
      n = (CBW.CB[6] << 24) |
          (CBW.CB[7] << 16) |
          (CBW.CB[8] <<  8) |
          (CBW.CB[9] <<  0);
      break;
  }

  Length = n * MSC_BlockSize;

  if (CBW.dDataLength == 0) {              /* host requests no data */
    CSW.bStatus = CSW_CMD_FAILED;
    MSC_SetCSW();
    return (__FALSE);
  }

  if (CBW.dDataLength != Length) {
    if ((CBW.bmFlags & 0x80) != 0) {       /* stall appropriate EP */ 
      MSC_SetStallEP(MSC_EP_IN);
    } else {
      MSC_SetStallEP(MSC_EP_OUT);
    }

    CSW.bStatus = CSW_CMD_FAILED;
    MSC_SetCSW();

    return (__FALSE);
  }

  return (__TRUE);
}


/*
 *  Check Data IN Format
 *    Parameters:      None (global variables)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL DataInFormat (void) {

  if (CBW.dDataLength == 0) {
    CSW.bStatus = CSW_PHASE_ERROR;
    MSC_SetCSW();
    return (__FALSE);
  }
  if ((CBW.bmFlags & 0x80) == 0) {
    MSC_SetStallEP(MSC_EP_OUT);
    CSW.bStatus = CSW_PHASE_ERROR;
    MSC_SetCSW();
    return (__FALSE);
  }
  return (__TRUE);
}


/*
 *  Perform Data IN Transfer
 *    Parameters:      None (global variables)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

void DataInTransfer (void) {

  if (BulkLen >= CBW.dDataLength) {
    BulkLen = CBW.dDataLength;
    BulkStage = MSC_BS_DATA_IN_LAST;
  }
  else {
    BulkStage = MSC_BS_DATA_IN_LAST_STALL; /* short or zero packet */
  }

  USB_WriteEP(MSC_EP_IN, BulkBuf, BulkLen);

  CSW.dDataResidue -= BulkLen;
  CSW.bStatus = CSW_CMD_PASSED;
}


/*
 *  MSC SCSI Test Unit Ready Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_TestUnitReady (void) {

  if (CBW.dDataLength != 0) {
    if ((CBW.bmFlags & 0x80) != 0) {
      MSC_SetStallEP(MSC_EP_IN);
    } else {
      MSC_SetStallEP(MSC_EP_OUT);
    }
  }

  CSW.bStatus = CSW_CMD_PASSED;
  MSC_SetCSW();
}


/*
 *  MSC SCSI Request Sense Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_RequestSense (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x70;                      /* Response Code */
  BulkBuf[ 1] = 0x00;
  BulkBuf[ 2] = 0x02;                      /* Sense Key */
  BulkBuf[ 3] = 0x00;
  BulkBuf[ 4] = 0x00;
  BulkBuf[ 5] = 0x00;
  BulkBuf[ 6] = 0x00;
  BulkBuf[ 7] = 0x0A;                      /* Additional Length */
  BulkBuf[ 8] = 0x00;
  BulkBuf[ 9] = 0x00;
  BulkBuf[10] = 0x00;
  BulkBuf[11] = 0x00;
  BulkBuf[12] = 0x30;                      /* ASC */
  BulkBuf[13] = 0x01;                      /* ASCQ */
  BulkBuf[14] = 0x00;
  BulkBuf[15] = 0x00;
  BulkBuf[16] = 0x00;
  BulkBuf[17] = 0x00;

  BulkLen = 18;
  DataInTransfer();
}


/*
 *  MSC SCSI Inquiry Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_Inquiry (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x00;                      /* Direct Access Device */
  BulkBuf[ 1] = 0x80;                      /* RMB = 1: Removable Medium */
  BulkBuf[ 2] = 0x00;                      /* Version: No conformance claim to standard */
  BulkBuf[ 3] = 0x01;

  BulkBuf[ 4] = 36-4;                      /* Additional Length */
  BulkBuf[ 5] = 0x80;                      /* SCCS = 1: Storage Controller Component */
  BulkBuf[ 6] = 0x00;
  BulkBuf[ 7] = 0x00;

  BulkBuf[ 8] = 'P';                       /* Vendor Identification */
  BulkBuf[ 9] = 'o';
  BulkBuf[10] = 'w';
  BulkBuf[11] = 'e';
  BulkBuf[12] = 'r';
  BulkBuf[13] = 'A';
  BulkBuf[14] = 'V';
  BulkBuf[15] = 'R';

  BulkBuf[16] = 'L';                       /* Product Identification */
  BulkBuf[17] = 'P';
  BulkBuf[18] = 'C';
  BulkBuf[19] = '1';
  BulkBuf[20] = '7';
  BulkBuf[21] = 'x';
  BulkBuf[22] = 'x';
  BulkBuf[23] = ' ';
  BulkBuf[24] = 'D';
  BulkBuf[25] = 'i';
  BulkBuf[26] = 's';
  BulkBuf[27] = 'k';
  BulkBuf[28] = ' ';
  BulkBuf[29] = ' ';
  BulkBuf[30] = ' ';
  BulkBuf[31] = ' ';

  BulkBuf[32] = '1';                       /* Product Revision Level */
  BulkBuf[33] = '.';
  BulkBuf[34] = '0';
  BulkBuf[35] = ' ';

  BulkLen = 36;
  DataInTransfer();
}


/*
 *  MSC SCSI Mode Sense (6-Byte) Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_ModeSense6 (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x03;
  BulkBuf[ 1] = 0x00;
  BulkBuf[ 2] = 0x00;
  BulkBuf[ 3] = 0x00;

  BulkLen = 4;
  DataInTransfer();
}


/*
 *  MSC SCSI Mode Sense (10-Byte) Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_ModeSense10 (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x00;
  BulkBuf[ 1] = 0x06;
  BulkBuf[ 2] = 0x00;
  BulkBuf[ 3] = 0x00;
  BulkBuf[ 4] = 0x00;
  BulkBuf[ 5] = 0x00;
  BulkBuf[ 6] = 0x00;
  BulkBuf[ 7] = 0x00;

  BulkLen = 8;
  DataInTransfer();
}


/*
 *  MSC SCSI Read Capacity Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_ReadCapacity (void) {

  if (!DataInFormat()) return;

  /* Last Logical Block */
  BulkBuf[ 0] = ((MSC_BlockCount - 1) >> 24) & 0xFF;
  BulkBuf[ 1] = ((MSC_BlockCount - 1) >> 16) & 0xFF;
  BulkBuf[ 2] = ((MSC_BlockCount - 1) >>  8) & 0xFF;
  BulkBuf[ 3] = ((MSC_BlockCount - 1) >>  0) & 0xFF;

  /* Block Length */
  BulkBuf[ 4] = (MSC_BlockSize >> 24) & 0xFF;
  BulkBuf[ 5] = (MSC_BlockSize >> 16) & 0xFF;
  BulkBuf[ 6] = (MSC_BlockSize >>  8) & 0xFF;
  BulkBuf[ 7] = (MSC_BlockSize >>  0) & 0xFF;

  BulkLen = 8;
  DataInTransfer();
}


/*
 *  MSC SCSI Read Format Capacity Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_ReadFormatCapacity (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x00;
  BulkBuf[ 1] = 0x00;
  BulkBuf[ 2] = 0x00;
  BulkBuf[ 3] = 0x08;                      /* Capacity List Length */

  /* Block Count */
  BulkBuf[ 4] = (MSC_BlockCount >> 24) & 0xFF;
  BulkBuf[ 5] = (MSC_BlockCount >> 16) & 0xFF;
  BulkBuf[ 6] = (MSC_BlockCount >>  8) & 0xFF;
  BulkBuf[ 7] = (MSC_BlockCount >>  0) & 0xFF;

  /* Block Length */
  BulkBuf[ 8] = 0x02;                      /* Descriptor Code: Formatted Media */
  BulkBuf[ 9] = (MSC_BlockSize >> 16) & 0xFF;
  BulkBuf[10] = (MSC_BlockSize >>  8) & 0xFF;
  BulkBuf[11] = (MSC_BlockSize >>  0) & 0xFF;

  BulkLen = 12;
  DataInTransfer();
}


/*
 *  MSC Get Command Block Wrapper Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_GetCBW (void) {
  U32 n;

  for (n = 0; n < BulkLen; n++) {
    *((U8 *)&CBW + n) = BulkBuf[n];
  }
  if ((BulkLen == sizeof(CBW)) && (CBW.dSignature == MSC_CBW_Signature)) {
    /* Valid CBW */
    CSW.dTag = CBW.dTag;
    CSW.dDataResidue = CBW.dDataLength;
    if ((CBW.bLUN      != 0) || 
        (CBW.bCBLength <  1) || 
        (CBW.bCBLength > 16)   ) {
fail: 
      CSW.bStatus = CSW_CMD_FAILED;
      MSC_SetCSW();
    } else {
      switch (CBW.CB[0]) {
        case SCSI_TEST_UNIT_READY:
          MSC_TestUnitReady();
          break;
        case SCSI_REQUEST_SENSE:
          MSC_RequestSense();
          break;
        case SCSI_FORMAT_UNIT:
          goto fail;
        case SCSI_INQUIRY:
          MSC_Inquiry();
          break;
        case SCSI_START_STOP_UNIT:
          goto fail;
        case SCSI_MEDIA_REMOVAL:
          goto fail;
        case SCSI_MODE_SELECT6:
          goto fail;
        case SCSI_MODE_SENSE6:
          MSC_ModeSense6();
          break;
        case SCSI_MODE_SELECT10:
          goto fail;
        case SCSI_MODE_SENSE10:
          MSC_ModeSense10();
          break;
        case SCSI_READ_FORMAT_CAPACITIES:
          MSC_ReadFormatCapacity();
          break;
        case SCSI_READ_CAPACITY:
          MSC_ReadCapacity();
          break;
        case SCSI_READ10:
		case SCSI_READ12:
          if (MSC_RWSetup()) {
            if ((CBW.bmFlags & 0x80) != 0) {
              LED_On (LED_RD);    /* Turn On Read LED */
              BulkStage = MSC_BS_DATA_IN;
              MSC_MemoryRead();
            } else {                       /* direction mismatch */
              MSC_SetStallEP(MSC_EP_OUT);
              CSW.bStatus = CSW_PHASE_ERROR;
              MSC_SetCSW();
            }
          }
          break;
        case SCSI_WRITE10:
		case SCSI_WRITE12:
          if (MSC_RWSetup()) {
            if ((CBW.bmFlags & 0x80) == 0) {
              LED_On (LED_WR);    /* Turn On Write LED */
              BulkStage = MSC_BS_DATA_OUT;
            } else {                       /* direction mismatch */
              MSC_SetStallEP(MSC_EP_IN);
              CSW.bStatus = CSW_PHASE_ERROR;
              MSC_SetCSW();
            }
          }
          break;
        case SCSI_VERIFY10:
          if ((CBW.CB[1] & 0x02) == 0) {
            // BYTCHK = 0 -> CRC Check (not implemented)
            CSW.bStatus = CSW_CMD_PASSED;
            MSC_SetCSW();
            break;
          }
          if (MSC_RWSetup()) {
            if ((CBW.bmFlags & 0x80) == 0) {
              BulkStage = MSC_BS_DATA_OUT;
              MemOK = __TRUE;
            } else {
              MSC_SetStallEP(MSC_EP_IN);
              CSW.bStatus = CSW_PHASE_ERROR;
              MSC_SetCSW();
            }
          }
          break;
        default:
          goto fail;
      }
    }
  } else {
    /* Invalid CBW */
    MSC_SetStallEP(MSC_EP_IN);
                                           /* set EP to stay stalled */
    USB_EndPointStall |=  (MSC_EP_IN  & 0x80) ? ((1 << 16) << (MSC_EP_IN  & 0x0F)) : (1 << MSC_EP_IN);
    MSC_SetStallEP(MSC_EP_OUT);
                                           /* set EP to stay stalled */
    USB_EndPointStall |=  (MSC_EP_OUT & 0x80) ? ((1 << 16) << (MSC_EP_OUT & 0x0F)) : (1 << MSC_EP_OUT);
    BulkStage = MSC_BS_ERROR;
  }
}


/*
 *  MSC Set Command Status Wrapper Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_SetCSW (void) {

  CSW.dSignature = MSC_CSW_Signature;
  USB_WriteEP(MSC_EP_IN, (U8 *)&CSW, sizeof(CSW));
  BulkStage = MSC_BS_CSW;
}


/*
 *  MSC Bulk In Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_BulkIn (void) {

  switch (BulkStage) {
    case MSC_BS_DATA_IN:
      switch (CBW.CB[0]) {
        case SCSI_READ10:
        case SCSI_READ12:
          MSC_MemoryRead();
          break;
      }
      break;
    case MSC_BS_DATA_IN_LAST:
      MSC_SetCSW();
      break;
    case MSC_BS_DATA_IN_LAST_STALL:
      MSC_SetStallEP(MSC_EP_IN);
      MSC_SetCSW();
      break;
    case MSC_BS_CSW:
      BulkStage = MSC_BS_CBW;
      break;
  }
}


/*
 *  MSC Bulk Out Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_BulkOut (void) {

  BulkLen = USB_ReadEP(MSC_EP_OUT, BulkBuf);
  switch (BulkStage) {
    case MSC_BS_CBW:
      MSC_GetCBW();
      break;
    case MSC_BS_DATA_OUT:
      switch (CBW.CB[0]) {
        case SCSI_WRITE10:
        case SCSI_WRITE12:
          MSC_MemoryWrite();
          break;
        case SCSI_VERIFY10:
          MSC_MemoryVerify();
          break;
      }
      break;
      case MSC_BS_CSW:
        break;
    default:
      MSC_SetStallEP(MSC_EP_OUT);
      CSW.bStatus = CSW_PHASE_ERROR;
      MSC_SetCSW();
      break;
  }
}
