/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_LIB.C 
 *      Purpose: System Library Module
 *      Rev.:    V4.05
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2009 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "File_Config.h"
#include <string.h>

/*----------------------------------------------------------------------------
 *      Functions
 *---------------------------------------------------------------------------*/


/*--------------------------- fn_cmp ----------------------------------------*/

BOOL fn_cmp (const char *sp, const char *fp) {
  /* Compare flash filename string with provided filename. */

  for (  ; *sp; sp++, fp++) {
    if (*sp != *fp) {
      return (__FALSE);
    }
  }
  if (*fp != 0) {
    return (__FALSE);
  }
  return (__TRUE);
}


/*--------------------------- fs_strpos -------------------------------------*/

int fs_strpos (const char *sp, const char ch) {
  /* Find a position of 'ch' in a string */
  int i;

  for (i = 0; *sp; sp++, i++) {
    if (*sp == ch) {
      return (i);
    }
  }
  return (-1);
}


/*--------------------------- fs_ReadData -----------------------------------*/

int fs_ReadData (U32 adr, U32 cnt, U8 *buf)  {
  /* Read Data from RAM memory to buffer. */

  memcpy (buf, (void *)adr, cnt);
  return (0);
}


/*--------------------------- fs_WriteData -----------------------------------*/

int fs_WriteData (U32 adr, U32 cnt, U8 *buf)  {
  /* Write Data from buffer to RAM memory. */

  memcpy ((void *)adr, buf, cnt);
  return (0);
}


/*--------------------------- fs_get_drive ----------------------------------*/

int fs_get_drive (const char *fn) {
  /* Check if drive letter provided. */

  if (*(fn+1) != ':') {
    return (DRV_NONE);
  }
  switch (*fn) {
    /* 'F:' - Flash device */
    case 'F':
    case 'f':
      return (DRV_FLASH);
    /* 'S:' - SPI Flash device. */
    case 'S':
    case 's':
      return (DRV_SPI);
    /* 'R:' - RAM device */
    case 'R':
    case 'r':
      return (DRV_RAM);
    /* 'M:' - SD Card device. */
    case 'M':
    case 'm':
      return (DRV_MCARD);
  }
  return (DRV_NONE);
}


/*--------------------------- fs_find_iob -----------------------------------*/

int fs_find_iob (void) {
  /* Find unused _iob[] structure. */
  IOB *fcb;
  U32 i,nfile = _NFILE;

  for (i = 0, fcb = &_iob[0]; i < nfile; fcb++, i++) {
    if (!(fcb->flags & (_IOREAD|_IOWRT))) {
      /* Clear File Control Block, return '_iob' index. */
      memset (fcb, 0, sizeof (struct iob));
      return (i);
    }
  }
  return (EOF);
}


/*--------------------------- fs_set_params ---------------------------------*/

BOOL fs_set_params (IOB *fcb) {
  /* Set Flash/Ram drive Device parameters. */

  switch (fcb->drive) {
    case DRV_FLASH:
      fcb->DevCfg  = (DEVCONF *)&FlashDev[0];
      fcb->InitVal = _BlockFREE;
      fcb->NumSect = _FlashNumSect;
      break;
    case DRV_SPI:
      fcb->DevCfg  = (DEVCONF *)&SpiDev[0];
      fcb->InitVal = _SpiBlFREE;
      fcb->NumSect = _SpiNumSect;
      break;
    case DRV_RAM:
      fcb->DevCfg  = (DEVCONF *)&RamDev[0];
      fcb->InitVal = 0x00000000;
      fcb->NumSect = _RamNumSect;
      break;
    default:
      return (__FALSE);
  }
  if (fcb->NumSect == 0) {
    /* This device disabled from the configuration. */
    return (__FALSE);
  }
  return (__TRUE);
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
