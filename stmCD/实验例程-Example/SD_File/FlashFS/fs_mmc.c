/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_MMC.C 
 *      Purpose: MultiMedia and SD Flash Card Interface
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"

/* SD/MMC Commands */
#define GO_IDLE_STATE    (0x40 + 0)
#define SEND_OP_COND     (0x40 + 1)
#define SEND_CSD         (0x40 + 9)
#define SEND_CID         (0x40 + 10)
#define STOP_TRAN        (0x40 + 12)
#define SET_BLOCKLEN     (0x40 + 16)
#define READ_BLOCK       (0x40 + 17)
#define READ_MULT_BLOCK  (0x40 + 18)
#define WRITE_BLOCK      (0x40 + 24)
#define WRITE_MULT_BLOCK (0x40 + 25)
#define APP_CMD          (0x40 + 55)
#define CRC_ON_OFF       (0x40 + 59)
#define SD_SEND_OP_COND  (0x40 + 41)

/* Wait timeouts, in multiples of 1 byte send over SPI */
#define WR_TOUT           500000        /* ~ 200 ms with SPI clk 20MHz */
#define STOP_TOUT         125000        /* ~  50 ms with SPI clk 20MHz */
#define CMD_TOUT          2500          /* ~   1 ms with SPI clk 20MHz */

/* Local variables */
static U8 CardType;

/*----------------------------------------------------------------------------
 *      MMC Driver Functions
 *----------------------------------------------------------------------------
 *  Required functions for MMC driver module:
 *   - BOOL mmc_init        ()
 *   - BOOL mmc_read_sect   (U32 sect, U8 *buf, U32 cnt)
 *   - BOOL mmc_write_sect  (U32 sect, U8 *buf, U32 cnt)
 *   - BOOL mmc_read_config (MMCFG *cfg)
 *---------------------------------------------------------------------------*/


/* Local Function Prototypes */
static U8   mmc_command     (U8 cmd, U32 arg);
static BOOL mmc_read_bytes  (U8 cmd, U32 arg, U8 *buf, U32 len);
static BOOL mmc_read_block  (U8 cmd, U32 arg, U8 *buf, U32 cnt);
static BOOL mmc_write_block (U8 cmd, U32 arg, U8 *buf, U32 cnt);

/*--------------------------- mmc_init --------------------------------------*/

BOOL mmc_init (void) {
  /* Initialize and enable the Flash Card. */
  U32 i,r1;

  /* Initialize SPI interface and enable Flash Card SPI mode. */
  spi_init ();

  spi_ss (1);
  spi_hi_speed (__FALSE);

  /* Send SPI Command with card not selected at 400 KBit. */
  for (i = 0; i < 16; i++) {
    spi_send (0xFF);
  }

  /* Reset the card, send CMD0. */
  spi_ss (0);
  r1 = mmc_command (GO_IDLE_STATE, 0);
  for (i = 0; i < 100; i++) {
    if (r1 == 0x01) {
      break;
    }
    r1 = spi_send (0xFF);
  }
  spi_ss (1);
  if (r1 != 0x01) {
    /* Failed to Reset Flash Card. */
    return (__FALSE);
  }
  spi_hi_speed (__TRUE);

  CardType = CARD_NONE;
  /* Check if SD card, send ACMD41 */
  for (i = 0; i < 50000; i++) {
    spi_ss (0);
    r1 = mmc_command (APP_CMD, 0);
    spi_ss (1);
    if (r1 & 0x04) {
      /* Illegal Command. */
      break;
    }
    if (r1 == 0x01) {
      spi_ss (0);
      r1 = mmc_command (SD_SEND_OP_COND, 0);
      spi_ss (1);
      if (r1 == 0x00) {
        /* OK, SD card initialized. */
        CardType = CARD_SD;
        break;
      }
    }
  }
  if (CardType == CARD_NONE) {
    /* Initialize MMC Card, send CMD1. */
    for (i = 0; i < 50000; i++) {
      spi_ss (0);
      r1 = mmc_command (SEND_OP_COND, 0);
      spi_ss (1);
      if (r1 != 0x01) {
        break;
      }
    }
    if (r1 != 0x00) {
      /* Failed to Initialize the card. */
      return (__FALSE);
    }
    CardType = CARD_MMC;
  }

  /* Set block length in the Flash Card to 512 bytes. */
  spi_ss (0);
  r1 = mmc_command (SET_BLOCKLEN, 512);
  spi_ss (1);
  if (r1 != 0x00) {
    return (__FALSE);
  }
  /* Turn Off CRC option. */
  spi_ss (0);
  r1 = mmc_command (CRC_ON_OFF, 0);
  spi_ss (1);
  if (r1 != 0x00) {
    return (__FALSE);
  }
  /* Success, card initialized. */
  return (__TRUE);
}


/*--------------------------- mmc_command -----------------------------------*/

static U8 mmc_command (U8 cmd, U32 arg) {
  /* Send a Command to Flash card and get a Response. */
  U32 r1,i;

  spi_send (0xFF);
  spi_send (cmd);
  spi_send (arg >> 24);
  spi_send (arg >> 16);
  spi_send (arg >> 8);
  spi_send (arg);
  /* Checksum, should only be valid for the first command.CMD0 */
  spi_send (0x95);

  /* Response will come after 1 - 8 retries. */
  for (i = 0; i < 8; i++) {
    r1 = spi_send (0xFF);
    if (r1 != 0xFF) {
      break;
    }
  }
  return (r1);
}


/*--------------------------- mmc_read_block --------------------------------*/

static BOOL mmc_read_block (U8 cmd, U32 arg, U8 *buf, U32 cnt) {
  /* Read a 'cnt' of data blocks from Flash Card. */
  U32 i;

  if (mmc_command (cmd, arg) != 0x00) {
    /* R1 status error. */
    return (__FALSE);
  }

  for (  ; cnt; buf += 512, cnt--) {
    for (i = CMD_TOUT; i; i--) {
      if (spi_send (0xFF) == 0xFE) {
        /* Data Start token. */
        break;
      }
    }
    if (i == 0) {
      /* Sector Read Tiomeout. */
      return (__FALSE);
    }

    for (i = 0; i < 512; i++) {
      buf[i] = spi_send (0xFF);
    }
    /* Read also a 16-bit CRC. */
    spi_send (0xFF);
    spi_send (0xFF);
  }
  return (__TRUE);
}


/*--------------------------- mmc_read_bytes --------------------------------*/

static BOOL mmc_read_bytes (U8 cmd, U32 arg, U8 *buf, U32 len) {
  /* Read a 'len' bytes from Flash Card. */
  U32 i;

  if (mmc_command (cmd, arg) != 0x00) {
    /* R1 status error. */
    return (__FALSE);
  }

  for (i = CMD_TOUT; i; i--) {
    if (spi_send (0xFF) == 0xFE) {
      /* Data Start token. */
      break;
    }
  }
  if (i == 0) {
    /* Data Read Tiomeout. */
    return (__FALSE);
  }

  for (i = 0; i < len; i++) {
    buf[i] = spi_send (0xFF);
  }
  /* Read also a 16-bit CRC. */
  spi_send (0xFF);
  spi_send (0xFF);
  return (__TRUE);
}


/*--------------------------- mmc_write_block -------------------------------*/

static BOOL mmc_write_block (U8 cmd, U32 arg, U8 *buf, U32 cnt) {
  /* Write a 'cnt' of data blocks to Flash Card. */
  U32 i;
  U8  tkn;

  if (mmc_command (cmd, arg) != 0x00) {
    /* R1 status error. */
    return (__FALSE);
  }

  /* Select token, for single write or multiple write. */
  tkn = 0xFE;
  if (cnt > 1) {
    tkn = 0xFC;
  }

  for (  ; cnt; buf += 512, cnt--) {
    /* Send Data Start token. */
    spi_send (tkn);
    /* Send data. */
    for (i = 0; i < 512; i++) {
      spi_send (buf[i]);
    }
    /* Send also a 16-bit CRC. */
    spi_send (0xFF);
    spi_send (0xFF);
    /* Check data response. */
    if ((spi_send (0xFF) & 0x0F) != 0x05) {
      return (__FALSE);
    }
    /* Wait while Flash Card is busy. */
    for (i = WR_TOUT; i; i--) {
      if (spi_send (0xFF) == 0xFF) {
        /* Sector Write finished. */
        break;
      }
    }
    if (i == 0) {
      /* Sector Write Timeout. */
      return (__FALSE);
    }
  }
  return (__TRUE);
}


/*--------------------------- mmc_read_sect ---------------------------------*/

BOOL mmc_read_sect (U32 sect, U8 *buf, U32 cnt) {
  /* Read single/multiple sectors from Flash Memory Card. */
  U32  i;
  BOOL retv;

  spi_ss (0);
  if (cnt > 1) {
    /* Multiple Block Read. */
    retv = mmc_read_block (READ_MULT_BLOCK, sect * 512, buf, cnt);

    mmc_command (STOP_TRAN, 0);
    /* Wait while Flash Card is busy. */
    for (i = STOP_TOUT; i; i--) {
      if (spi_send (0xFF) == 0xFF) {
        goto x;
      }
    }
    retv = __FALSE;
  }
  else {
    /* Single Block Read. */
    retv = mmc_read_block (READ_BLOCK, sect * 512, buf, 1);
  }
x:spi_ss (1);
  return (retv);
}


/*--------------------------- mmc_write_sect --------------------------------*/

BOOL mmc_write_sect (U32 sect, U8 *buf, U32 cnt) {
  /* Write a 512 byte sector to Flash Card. */
  U32  i;
  BOOL retv;

  spi_ss (0);
  if (cnt > 1) {
    /* Multiple Block Write. */
    retv = mmc_write_block (WRITE_MULT_BLOCK, sect * 512, buf, cnt);

    mmc_command (STOP_TRAN, 0);
    /* Wait while Flash Card is busy. */
    for (i = STOP_TOUT; i; i--) {
      if (spi_send (0xFF) == 0xFF) {
        goto x;
      }
    }
    retv = __FALSE;
  }
  else {
    /* Single Block Write. */
    retv = mmc_write_block (WRITE_BLOCK, sect * 512, buf, 1);
  }
x:spi_ss (1);
  return (retv);
}


/*--------------------------- mmc_read_config -------------------------------*/

BOOL mmc_read_config (MMCFG *cfg) {
  /* Read MMC/SD Card device configuration. */
  U8 buf[16],*bp;
  BOOL retv;
  U32 v,m;

  /* Read the CID - Card Identification. */
  spi_ss (0);
  retv = mmc_read_bytes (SEND_CID, 0, buf, 16);
  spi_ss (1);
  if (retv == __FALSE) {
    /* Read CID failed. */
    return (__FALSE);
  }
  /* CID register structure for SD is different than for MMC Card. */
  if (CardType == CARD_SD) {
    bp = &buf[9];
  }
  else {
    bp = &buf[10];
  }
  cfg->sernum = bp[0]<<24 | bp[1]<<16 | bp[2]<<8 | bp[3];

  /* Read the CSD - Card Specific Data. */
  spi_ss (0);
  retv = mmc_read_bytes (SEND_CSD, 0, buf, 16);
  spi_ss (1);
  if (retv == __FALSE) {
    /* Read CSD failed. */
    return (__FALSE);
  }
  /* Read Block length */
  v = buf[5] & 0x0F;
  cfg->read_blen = 1 << v;

  /* Write Block length */
  v = ((buf[12] << 8 | buf[13]) >> 6) & 0x0F;
  cfg->write_blen = 1 << v;

  /* Total Number of blocks */
  v = ((buf[6] << 16 | buf[7] << 8 | buf[8]) >> 6) & 0x0FFF;
  m = ((buf[9] << 8  | buf[10]) >> 7) & 0x07;
  cfg->blocknr = (v + 1) << (m + 2);

  return (__TRUE);
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
